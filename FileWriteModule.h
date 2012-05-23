#include"Main.h"

#ifndef __FileWriteModule

#define __FileWriteModule

//常量定义

//函数声明

//全局变量
extern config cfg;//程序运行参数集
extern vector<vector<IMEI_CDR_Statistic>> tacstat;//将计算好的taccdrfile中不同的线程fn合并生成tacstat
extern vector<vector<IMEI_CDR_Statistic>> tacstat_timesection;//将计算好的tacstat中不同的TimeSection合并生成tacstat_timesection
extern vector<vector<IMEI_CDR_Statistic>> tacstat_timesectioncell;//将tacstat_timesection中不同的cell合并生成tacstat_timesectioncell

#endif