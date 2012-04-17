//#include"stdafx.h"
#include"Main.h"

#ifndef __FileReadModule

#define __FileReadModule

//常量定义
#define NOCDR_THRESHOLD 1//Signal_Complete_time与Call_Start_time差值小于1秒，则不记为呼叫一次

#define CELLIDMAX 65536 //celllisttype的大小

//函数声明

//全局变量
extern int FileBatchNum;//每次处理的文件数，s主要是内存不足造成速度慢，所以分批次倒入CDR
extern int HASH_NUM_IMEI;//散列的hash key的前hash_num_imei位取得IMEI的从START_HASH_INDEX起共HASH_NUM位
extern int START_HASH_INDEX_IMEI;//散列的key取imei的第几位开始
extern int HASH_NUM_CELLID;//取CELLID的后几位作为HASH KEY的后几位
extern time_t STATISTIC_START_TIME;//CDR记录开始时间，以call_start_time为准
extern time_t STATISTIC_END_TIME;//CDR记录结束时间，以call_start_time为准
extern int TIME_SECTION_UNIT;//在统计时按时段的间隔，以秒为单位，如果为0，则无时段间隔。
extern vector<string> CDR_SCREEN_B_NUMBER_INITIAL_LIST;//如果被叫号码的前缀在这个LIST（逗号分隔)中，那么不计入CDR，主要是为了除掉彩玲

extern vector<string> itemlist;//字段位置列表
extern vector<string> filelist;//要处理的CDR文件列表

extern string CDRDirectory;//要处理的CDR文件所在的文件夹
extern string OutputDirectory;//最后输出的统计文件存放的目录
extern string CELLFILE;//cell类型的文件
extern string TACFILE;//tac类型的文件

#endif