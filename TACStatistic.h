//#include"stdafx.h"
#include"Main.h"

#ifndef __TACStatistic

#define __TACStatistic

//常量定义

//函数声明
bool ReadTACSTATFile(string tacstatfile, vector<vector<IMEI_CDR_Statistic>>& tacstat_temp);//读取tacstat存储的文件
//全局变量
extern vector<vector<vector<IMEI_CDR_Statistic>>> taccdrfile;//按文件统计tac的cdr
extern vector<vector<IMEI_CDR_Statistic>> tacstat;//按tac统计的合并
extern vector<vector<IMEI_CDR_Statistic>> tacstat_cell;//将tac统计按照cellid合并

#endif