//#include"stdafx.h"
#include"Main.h"

#ifndef __FileReadModule

#define __FileReadModule

//��������
#define NOCDR_THRESHOLD 1//Signal_Complete_time��Call_Start_time��ֵС��1�룬�򲻼�Ϊ����һ��

#define CELLIDMAX 65536 //celllisttype�Ĵ�С

//��������

//ȫ�ֱ���
extern int FileBatchNum;//ÿ�δ�����ļ�����s��Ҫ���ڴ治������ٶ��������Է����ε���CDR
extern int HASH_NUM_IMEI;//ɢ�е�hash key��ǰhash_num_imeiλȡ��IMEI�Ĵ�START_HASH_INDEX��HASH_NUMλ
extern int START_HASH_INDEX_IMEI;//ɢ�е�keyȡimei�ĵڼ�λ��ʼ
extern int HASH_NUM_CELLID;//ȡCELLID�ĺ�λ��ΪHASH KEY�ĺ�λ
extern time_t STATISTIC_START_TIME;//CDR��¼��ʼʱ�䣬��call_start_timeΪ׼
extern time_t STATISTIC_END_TIME;//CDR��¼����ʱ�䣬��call_start_timeΪ׼
extern int TIME_SECTION_UNIT;//��ͳ��ʱ��ʱ�εļ��������Ϊ��λ�����Ϊ0������ʱ�μ����
extern vector<string> CDR_SCREEN_B_NUMBER_INITIAL_LIST;//������к����ǰ׺�����LIST�����ŷָ�)�У���ô������CDR����Ҫ��Ϊ�˳�������

extern vector<string> itemlist;//�ֶ�λ���б�
extern vector<string> filelist;//Ҫ�����CDR�ļ��б�

extern string CDRDirectory;//Ҫ�����CDR�ļ����ڵ��ļ���
extern string OutputDirectory;//��������ͳ���ļ���ŵ�Ŀ¼
extern string CELLFILE;//cell���͵��ļ�
extern string TACFILE;//tac���͵��ļ�

#endif