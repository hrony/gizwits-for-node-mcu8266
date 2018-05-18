/*
 * flash_management.C
 *
 *  Created on: 2018��5��14��
 *      Author: Administrator
 */
#include "driver/uart.h"
#include "osapi.h"
#include "os_type.h"
#include "mem.h"
#include "driver/spi_flash.h"

#pragma pack(4)
struct stu
{
	char ptr;
	uint8 x;
	uint32 y;
	void *z;
}test,sbuffer;
#pragma apop()


void flashwrite(int *p)//flashд�뺯�����˴��Դ���ṹ��Ϊ��
{
    test.ptr='a';
    test.x=0x8;
    test.y=0x0020;
    test.z=p;
    os_printf("size of test=%d,x=%x,y=%x,z=%x\r\n",sizeof(test),test.x,test.y,test.z);
    spi_flash_erase_sector(128);//����128����
    char prewrite[sizeof(test)];
    os_memcpy(prewrite,&test,sizeof(test));
    os_printf("prewrite=%s,size of prewrite=%d\r\n",prewrite,sizeof(prewrite));


    spi_flash_write((uint32)128*4*1024,(uint32 *)prewrite,(uint32)sizeof(prewrite));//128����д����


    os_delay_us(50000);//��ʱ50ms
    spi_flash_read((uint32)128*4*1024,(uint32 *)&sbuffer,(uint32)sizeof(sbuffer));//128����������
    os_printf("size of sbuffer=%d,ptr=%c,x=%x,y=%x,z=%x\r\n",sizeof(sbuffer),sbuffer.ptr,sbuffer.x,sbuffer.y,sbuffer.z);

}

