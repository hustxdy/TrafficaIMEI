//#include"stdafx.h"
#include"Main.h"

#ifndef __TACStatistic

#define __TACStatistic

//��������

//��������
bool ReadTACSTATFile(string tacstatfile, vector<vector<IMEI_CDR_Statistic>>& tacstat_temp);//��ȡtacstat�洢���ļ�
//ȫ�ֱ���
extern vector<vector<vector<IMEI_CDR_Statistic>>> taccdrfile;//���ļ�ͳ��tac��cdr
extern vector<vector<IMEI_CDR_Statistic>> tacstat;//��tacͳ�Ƶĺϲ�
extern vector<vector<IMEI_CDR_Statistic>> tacstat_cell;//��tacͳ�ư���cellid�ϲ�

#endif