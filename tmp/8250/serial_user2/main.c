#include "SerDrive.h"
#include <fcntl.h>      /*文件控制定义*/
#include <stdio.h>
//======================================
int SerFd = -1;
void ProcessInit(void)
{

	/*
	 * 打开USB转串口（ttyUSB0）
	 * O_RDWR 可读写设备
	 * O_NOCTTY 如果欲打开的文件为终端机设备时，则不会将该终端机当成进程控制终端机
	 * O_NDELAY 以不可阻断的方式打开文件，也就是无论有无数据读取或等待，都会立即返回进程之中
	 */
	SerFd = open("/dev/ttyUSB0", O_RDWR|O_NOCTTY|O_NDELAY);
	if (0 < SerFd)
	{
		set_opt(SerFd, BAUD_2400, DATA_BIT_8, PARITY_NONE, STOP_BIT_1);//设置串口参数
	}
	else
	{
		printf("open_port ERROR !\n");
	}
}

int main(int argc, char *argv[])
{
	int nTmp = 0;
	char Buf[1024];
	ProcessInit();
	send_data_tty(SerFd, "hello series\n",sizeof("hello series\n"));
	return 0;
	while (1)
	{
		//从串口中读取数据
		nTmp = read_datas_tty(SerFd, Buf, 100, 1024);
		if(nTmp)printf("%s",Buf);
		if (0 < nTmp)
		{
			//printf("rcv len=%d,data:%s\n",nTmp,Buf);
			//向串口传数据
			send_data_tty(SerFd, Buf, nTmp);
		}
	}
}

