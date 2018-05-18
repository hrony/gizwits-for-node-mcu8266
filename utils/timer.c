/*
 * timer.c
 *
 *  Created on: 2018��5��10��
 *      Author: Administrator
 */
#include "osapi.h"
#include "os_type.h"
#include "timer.h"
#include "mem.h"
#define ON 1



typedef void (* fun)(int *);
os_timer_t timer1;//����timer
os_timer_t *p;//timerָ��
int timercount=0;//timer������
void * timernumber[timernumber_MAX];//timerָ��list

void timerback(int* p)//timer1�ص�����
{

	os_printf("\r\nthe number is %d",*p);
	(*p)++;
	if(*p==5)
	{
		timerfunctiondisable(1);
	}
	if(*p==10)
	{
		timerfunctionenable(1,500);
		*p=0;
	}
}

void timerback2(int *q)//timer2�ص�����
{
	os_printf("\r\ni am timer2");

}


void timerinit()//timer��ʼ������
{
	p=&timer1;
	timernumber[0]=p;
}


void timerfunction(int *para,int time,fun tb)//timer����
{
	os_printf("timert in %x\r\n",p);
	os_printf("%d\r\n%d\r\n%s\r\n",p->timer_expire,p->timer_period,p->timer_arg);
    (p->timer_next) = (os_timer_t *)os_malloc(sizeof(os_timer_t));
	os_timer_t *b;
	b = p->timer_next;
	os_printf("the pointer of timer1 is %6x\r\n",timer1.timer_next);
    os_timer_disarm(p);
    os_timer_setfn(p,tb, para);
    os_timer_arm(p,time,1);
    os_printf("%d\r\n%d\r\n%s\r\n",p->timer_expire,p->timer_period,p->timer_arg);
    timercount++;
    timernumber[timercount]=b;
    p=b;
    os_printf("the pointer is %6x\r\n",p);
    os_printf("the pointer of timer1 is %6x\r\n",timer1.timer_next);

}

void timerfunctiondisable(int t)//timer����
{
	int i;
	os_timer_t *q,*b;
	if(t==0)
		os_timer_disarm(&timer1);
	else
	{
		q=timernumber[t];
        os_timer_disarm(q);
	}
	os_printf("\r\ntimerdisabled\r\n");
	timercount--;
}

void timerfunctionenable(int t,int time)//timer����
{
	os_timer_arm(timernumber[t],time,1);
	os_printf("\r\ntimerenabled\r\n");
}
