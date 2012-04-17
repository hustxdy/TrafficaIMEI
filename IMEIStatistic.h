//#include"stdafx.h"
#include"Main.h"

#ifndef __IMEIStatistic

#define __IMEIStatistic

//常量定义
#define MIN_IMEI_LENGTH 8//最小IMEI长度

//函数定义

//全局变量
extern vector<vector<IMEI_CDR_Statistic>> imeistat_cell;//将imei统计按照cellid合并
extern vector<vector<IMEI_CDR_Statistic>> imeistat;//按imei统计的合并

#endif