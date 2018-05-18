/*
 * timer.h
 *
 *  Created on: 2018年5月11日
 *      Author: Administrator
 */
#ifndef TIMER_H
#define TIMER_H
#include "osapi.h"
#include "os_type.h"

#define timernumber_MAX 10//拟使用定时器个数

void timerback(int* );
void timerback2(int *);
void timerfunction(int *,int ,void (* fun )());
void timerfunctiondisable(int);
void timerfunctionenable(int,int);
#endif


