//#include"stdafx.h"
#include"Main.h"

#ifndef __FileReadModule

#define __FileReadModule

//常量定义
#define NOCDR_THRESHOLD 1//Signal_Complete_time与Call_Start_time差值小于1秒，则不记为呼叫一次

#define CELLIDMAX 65536 //celllisttype的大小

//函数声明

//全局变量
extern config cfg;//程序运行参数集

#endif