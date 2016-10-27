#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <linux/serial_core.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR( "ericxiao:xgr178@163.com" );

#define SERIAL8250_TYPE	99

inline static void serial8250_stop_send(struct uart_port *port);
spinlock_t my_lock = SPIN_LOCK_UNLOCKED;

enum check_type
{
	odd_check,
	even_check,
	no_check,
};

//#define SER_DBG 			 1
#define DEF_baudrate  9600
#define DEF_databit 		8
#define DEF_stopbit		1
#define DEF_check		no_check

#define ARRY_SIZE(arry)	sizeof((arry))/sizeof((arry)[0])

#if	SER_DBG
#define Ser_dbg(args...)	printk(args)
#else
#define Ser_dbg(args...)
#endif

static unsigned long baudrate_arry[]={110,300,600,1200,2400,4800,9600,14400,19200,38400,57600,115200,230400,380400,460800,921600};


static int baudrate = DEF_baudrate;
static int  check	= DEF_check;
static int stopbit	= DEF_stopbit;
static int databit	= DEF_databit;

enum reg_type
{
	RBR=0,
	THR=0,
	DIVR_L=0,
	DIVR_H=1,
	IER=1,
	IIR,
	LCR,
	MCR,
	LSR,
	MSR,
	FIFO,
	MAX_REG,
	
};

//LCR bit
#define  LCR_DIVENABLEBIT	7	
#define  LCR_DATABIT		0
#define  LCR_STOPBIT			2
#define  LCR_CHECKENABLE	3
#define  LCR_CHECKBIT		4

//IER bit
#define IER_RECEVEINTE			0
#define IER_SENTEMPTYINTE		1
#define IER_LINESTATAINTE		2
#define IER_MODESTATAINTE		3 

//MCR bit
#define MCR_SELFTEST		4
#define MCR_INTRENABLE		3

//IIR bit
#define IIR_ISINTR			0
#define IIR_INTERIDENT		1


static irqreturn_t serial8259_intr(int irqno, void *dev_id)
{
	u8 reg_data = 0;
	int count =0;
	unsigned long save;
	struct uart_port *port = (struct uart_port *)dev_id;
	u32 database = port->iobase;
	char c;
	int tail;
	int head;

	if(port->irq != irqno)
		return IRQ_NONE;
	
	while(1)	
	{
			reg_data = inb(database+IIR);
			if(reg_data&(1<<IIR_ISINTR) == 1)
			{
				Ser_dbg("Not have interrupt.\n");
				break;
			}else
			{

				switch((reg_data & (0x03<<IIR_INTERIDENT) )>>IIR_INTERIDENT)
				{
					case 0:
						Ser_dbg("Moden state change.\n");
						reg_data = 0;
						reg_data = inb(database + MSR);
						break;
					case 1:

						Ser_dbg("Sent buffer empty.\n");
				//		spin_lock_irqsave(&port->lock, save);
						tail = port->info->xmit.tail;

						//if the buffer is empty
						if(!uart_circ_empty(&port->info->xmit))
						{
							head = port->info->xmit.head;
							c = port->info->xmit.buf[tail];
							tail = (tail+1) & (UART_XMIT_SIZE - 1);
							port->info->xmit.tail = tail;
							outb(c,database+THR);
							Ser_dbg("input:%c\n",c);
						}else{
							serial8250_stop_send( port);
							Ser_dbg("buffer empty.\n");
						}	
						
			//			spin_unlock_irqrestore(&port->lock, save);
						break;
						
					case 2:
						Ser_dbg("Recve buffer full.\n");
						reg_data = 0;
						reg_data = inb(database + RBR);
						uart_insert_char(port,0,0,reg_data,0);
						tty_flip_buffer_push(port->info->tty);
//						printk("%c",reg_data);
						break;
					case 3:
						Ser_dbg("Recve data erron.\n");
						reg_data = 0;
						reg_data = inb(database + LSR);
						break;
				}	
			}

	}
	
	return IRQ_HANDLED;
}

inline static void serial8250_start_send(struct uart_port *port)
{
	u8 reg_data;
	u32 database = port->iobase;
	
	reg_data = inb(database+IER);
	reg_data |= 1<<IER_SENTEMPTYINTE;
	outb(reg_data,database+IER);
	return ;
	
}

inline static void serial8250_stop_send(struct uart_port *port)
{
	u8 reg_data;
	u32 database = port->iobase;
	
	reg_data = inb(database+IER);
	reg_data &= ~(1<<IER_SENTEMPTYINTE);
	outb(reg_data,database+IER);
	return ;
}

inline static void serial8250_set_enableinter(struct uart_port *port)
{
	u8	reg_data;
	u32 database = port->iobase;
	
	//enable intrrupte.allow all interrupt,except sent buffer empty interrupt
	reg_data = 0;
	reg_data |= 1<<IER_RECEVEINTE;
	reg_data |= 1<<IER_LINESTATAINTE;
	reg_data |= 1<<IER_MODESTATAINTE;
	outb(reg_data,database+IER);

	Ser_dbg("IER:%0x.\n",reg_data);

	//enable sent interrupte single to 8259
	reg_data = inb(database+MCR);
	reg_data &=~(1<<MCR_SELFTEST);
	reg_data |= 1<<MCR_INTRENABLE;
	reg_data |= 3; 
	outb(reg_data,database+MCR);


	return 0;
}

 
inline static int serial8250_set_dataformat(struct uart_port *port,int databit,int stopbit,int check)
{
	u8    reg_data = 0;
	u8 	data_bit = 0;
	u32  database;
	
	database = port->iobase;
	switch(databit)
	{
		case 5:
			data_bit= 0<<LCR_DATABIT;	//0X00
			break;
		case 6:
			data_bit = 1<<LCR_DATABIT;	//0X01
			break;
		case 7:
			data_bit = 2<<LCR_DATABIT;	//0X02
			break;
		case 8:
			data_bit = 3<<LCR_DATABIT;	//0X03
			break;
		default:
			Ser_dbg("set databit(%d) is not allowed.\n",databit);
			return -1;
	}

	reg_data |= data_bit;

	//set stopbit
	if(stopbit == 1)
		reg_data &=~(1<<LCR_STOPBIT);

	//set odd/even check
	if(check == no_check)
		reg_data &=~(1<<LCR_CHECKENABLE);
	else
	{
		if(check==odd_check)
			reg_data &=~(1<<LCR_CHECKBIT);
		else if(check == even_check)
			reg_data |= 1<<LCR_CHECKBIT;

		reg_data |= 1<< LCR_CHECKENABLE;
			
	}

	outb(reg_data,database+LCR);

	return 0;
}

inline static int serial8250_set_baudrate(struct uart_port *port,unsigned long  baudrate)
{
	int ret=-1;
	int i;
	u16 divnum;
	u8	div_l;
	u8	div_h;
	u8	reg_data = 0;
	u32	database ;

	database = port->iobase;
	for(i=1; i<ARRY_SIZE(baudrate_arry);i++)
	{
		if(baudrate_arry[i] == baudrate)
			ret=0;
	}

	if(ret == 0)
	{
				
		divnum = 1843200/(16*baudrate);
		div_l = *(u8*)(&divnum);
		div_h = *(u8*)((u8*)&divnum +sizeof(u8));

		Ser_dbg("divnum = %0x;div_l=%0x;div_h=%0x.\n",divnum,div_l,div_h);
		
		//set lcr bit 7 = 1
		reg_data = inb(database+LCR);
		reg_data |= (1<<LCR_DIVENABLEBIT);
		outb(reg_data,database+LCR);
		
		outb(div_l,database+DIVR_L);
		outb(div_h,database+DIVR_H);
		
		reg_data &=~(1<<LCR_DIVENABLEBIT);
		outb(reg_data,database+LCR);
		
		
	}
	return ret;
}


inline static int serial8250_init(struct uart_port *port)
{
	u16 divnum;
	u8	div_l;
	u8	div_h;
	u8	reg_data;
	u8 	data_bit=0;
	u32	database = port->iobase;
	
	if( !request_region(database,MAX_REG,"8250port"))
	{
		printk("8250 request region erron .\n");
		return -1;
	}

	//clear FIFO reg
	reg_data = 0;
	outb(reg_data,database+FIFO);

	if(serial8250_set_baudrate(port,baudrate) || serial8250_set_dataformat(port,databit,stopbit,check))
		goto erron;

	serial8250_set_enableinter(port);
	//reset MSR LSR RBR regiset
	inb(database+MSR);
	inb(database+LSR);
	inb(database+RBR);

	return 0;
erron:
	printk("serial 8250 configure erron.\n");
	return -1;
	
}

void	serial8250_config_port(struct uart_port *port, int line)
{
	
	Ser_dbg("serial8250 config port ...\n");
	port->type = SERIAL8250_TYPE;
	serial8250_init(port);
	
	return;
}

void	serial8250_release_port(struct uart_port *port)
{
	Ser_dbg("serial8250_release_port ...\n");
	return ;
}

void	serial8250_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	Ser_dbg("serial8250_set_mctrl ...\n");
	Ser_dbg("mctrl=%0x.\n",mctrl);
	return ;
}

int serial8250_startup(struct uart_port *port)
{
	int ret = 0;
	
	Ser_dbg("serial8250_startup ...\n");
	ret = request_irq(port->irq, serial8259_intr, IRQF_SHARED, "8250", port);
	if(ret)
	{
		Ser_dbg("request irq %d fail...\n",port->irq);
		ret = -1;
	}
	return ret;
}

void serial8250_enable_ms(struct uart_port *port)
{
	Ser_dbg("serial8250_enable_ms ...\n");
	return ;
}

void serial8250_set_termios(struct uart_port *port, struct ktermios *new,struct ktermios *old)
{
	Ser_dbg("serial8250_set_termios ...\n");
	return;	
}

unsigned int	serial8250_get_mctrl(struct uart_port *port)
{
	Ser_dbg("serial8250_get_mctrl ...\n");
	return TIOCM_CAR | TIOCM_DSR | TIOCM_CTS;
}

void	serial8250_start_tx(struct uart_port *port)
{
	Ser_dbg("serial8250_start_tx ...\n");
	serial8250_start_send(port);
	
	return ;
}

void	serial8250_stop_tx(struct uart_port *port)
{
	Ser_dbg("serial8250_stop_tx ...\n");
	serial8250_stop_send(port);
	
	return ;
}

void serial8250_stop_rx(struct uart_port *port)
{
	u8 reg_data;
	
	Ser_dbg("serial8250_stop_rx ...\n");
	reg_data = inb(port->iobase + IER);
	reg_data &=~(1<<IER_RECEVEINTE);
	outb(reg_data,port->iobase + IER);

	return;
	
}

void serial8250_shutdown(struct uart_port *port)
{
	Ser_dbg("serial8250_shutdown ...\n");
	release_region(port->iobase,MAX_REG);
	 free_irq(port->irq, port);
}

unsigned int serial8250_tx_empty(struct uart_port *port)
{
	Ser_dbg("serial8250_tx_empty ...\n");
	return 1;
}

struct uart_ops serial8250_deviceops = 
{
	.config_port	= serial8250_config_port,
	.set_termios	= serial8250_set_termios,	
	.set_mctrl	= serial8250_set_mctrl,
	.get_mctrl	= serial8250_get_mctrl,
	.enable_ms	= serial8250_enable_ms,
	.startup		= serial8250_startup,
	.start_tx		= serial8250_start_tx,
	.stop_tx		= serial8250_stop_tx,
	.stop_rx		= serial8250_stop_rx,
	.tx_empty	= serial8250_tx_empty,
	.shutdown	= serial8250_shutdown,
	.release_port	= serial8250_release_port,	
};


struct uart_port serial8250_com1 =
{
	.line 	= 0,
	.iobase	= 0x000003F8,
	.irq		= 4,
	.iotype	= UPIO_PORT,
	.ops 	= &serial8250_deviceops,
	.flags	= UART_CONFIG_IRQ|UPF_BOOT_AUTOCONF,
		
};

struct uart_port serial8250_com2 =
{
	.line 	= 1,
	.iobase	= 0x000002F8,
	.irq		= 3,
	.iotype	= UPIO_PORT,
	.ops 	= &serial8250_deviceops,
	.flags	= UART_CONFIG_IRQ|UPF_BOOT_AUTOCONF,
		
};


struct uart_driver serial8259_driver =
{
	.owner 		= THIS_MODULE,
	.driver_name 		= "uart_8250",
	.dev_name 	= "8250",
	.major		= 199,
	.nr			= 2,
};

static int serial_driver_init()
{
	int ret;
	
	Ser_dbg("serial_driver_init.\n");
	uart_register_driver(&serial8259_driver);
	uart_add_one_port(&serial8259_driver,&serial8250_com1);
	uart_add_one_port(&serial8259_driver,&serial8250_com2);

	return 0;
}

static int serial_driver_exit()
{
	Ser_dbg("serial_driver_exit.\n");
	uart_remove_one_port(&serial8259_driver,&serial8250_com1);
	uart_remove_one_port(&serial8259_driver,&serial8250_com2);
	uart_unregister_driver(&serial8259_driver);
	return 0;
}


module_init(serial_driver_init);
module_exit(serial_driver_exit);
