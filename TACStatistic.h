//#include"stdafx.h"
#include"Main.h"

#ifndef __TACStatistic

#define __TACStatistic

//��������

//��������

//ȫ�ֱ���
extern vector<string> itemlist;//�ֶ�λ���б�
extern vector<vector<vector<IMEI_CDR_Statistic>>> taccdrfile;//���ļ�ͳ��tac��cdr
extern vector<vector<IMEI_CDR_Statistic>> tacstat;//������õ�taccdrfile�в�ͬ���߳�fn�ϲ�����tacstat
extern vector<vector<IMEI_CDR_Statistic>> tacstat_timesection;//������õ�tacstat�в�ͬ��TimeSection�ϲ�����tacstat_timesection
extern vector<vector<IMEI_CDR_Statistic>> tacstat_timesectioncell;//��tacstat_timesection�в�ͬ��cell�ϲ�����tacstat_timesectioncell

#endif