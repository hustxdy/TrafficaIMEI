#include"stdafx.h"

#ifndef __MAIN

#define __MAIN

using namespace std;
//�������Ͷ���
typedef unsigned __int64    UINT64;
//��������
#define PROGRESS_THRES 50000//��������¼ˢ��һ�ν�����
#define TAC_LENGTH 8//TAC�ĳ���
#define CONFIG_FILE_DEFAULT "D:\\xudayong\\Program\\TrafficaIMEI\\x64\\Release\\config.txt"
#define DEFAULT_CAUSE_VALUE -1
#define DEFAULT_MAXIMUM_FIELD_NUM 100//����ֶ���
//#define DEFAULT_GSM_CAUSE_TO_COUNT "0,1,20,60"
//#define DEFAULT_TD_CAUSE_TO_COUNT ""

//�ṹ����
//CDR��¼
struct CDR{
	time_t report_time;//CDR�ϱ�ʱ��
	int A_BSSMAP_cause;//�����ͷ�ԭ��BSSMAP��
	int A_BSSMAP_cause_ext;//TD�������ͷ�ԭ��RANAP��
	int A_cell;//���йһ�ʱ����С����
	int A_sac;//���йһ�ʱ���ڵ�SAC
	string A_number;//���к���
	int A_first_cell;//�������ʱ����С����
	int A_first_sac;//�������ʱ���ڵ�sac
	string A_IMEI;//�����ֻ���IMEI
	string A_IMSI;//���к����Ӧ��IMSI
	time_t B_answered_time;//����Ӧ��ʱ��
	int B_cell;//���йһ�ʱ����С����
	int B_sac;//���йһ�ʱ���ڵ�sac
	string B_number;//���к���
	int B_first_cell;//���н�ͨʱ���ڵ�С����
	int B_first_sac;//���н�ͨʱ���ڵ�sac
	string B_IMEI;//�����ֻ���IMEI
	string B_IMSI;//���к����IMSI
	time_t charging_end_time;//Disconnect��Ϣ��ʱ��
	int DX_cause;//���������ص�
	int paging_time;//Ѱ���Ĵ���
	time_t call_start_time;//���з�setup��Ϣ��ʱ��
	int timeSection;//ʱ��α��
	time_t timeSectionStartTime;//��ʱ��ε���ʼʱ��
	time_t signalling_complete_time;//�����յ�altering��ʱ��
	int B_BSSMAP_cause;//�����ͷ�ԭ��(BSSMAP)
	int B_BSSMAP_cause_ext;//TD�����ͷ�ԭ��(RANAP)
	int INTER_MSC_HO;//�Ƿ�Ϊ��MSC����
};
//���ڹ��������̼߳�ƽ������ʱ�õ�ָ�룬ָ��cdr
struct recordp{
		int fn;//�ĸ��ļ�
		int rn;//�ĸ���¼
};
//TAC��Ӧ��Ʒ�ƣ��ͺź����
struct TAC_NAME{
	string TAC;
	string brand;//����Ʒ��
	string name;//�ͺ�
	string type;//����
};
//Cell��Ӧ������
struct CELL_TYPE{
	int cellid;
	string type;//С������
};
struct CAUSE_TYPE{
	//string network;//��������
	int cause_id;//cause��id��
	int cause_num;//����cause���ֵĴ���
};
struct IMEI_IMSI{
	string IMEI;//IMEI��
	string IMSI;//IMSI��
};
//ͳ�����б�
struct IMEI_CDR_Statistic{
	string TAC;//TAC��
	string brand;//����Ʒ��
	string name;//�ͺ�
	string type;//����
	string IMEI;//IMEI��
	int cellid;//����С��
	string network;//��TD����GSM
	string celltype;//С������
	int timeSection;//ʱ�κ�
	time_t timeSectionStartTime;//ĳһʱ�ε���ʼʱ��
	int A_BSSMAP_drop;//������Ľ���ԭ����
	int A_RANAP_drop;//������Ľ���ԭ����
	int B_BSSMAP_drop;//������Ľ���ԭ����
	int B_RANAP_drop;//������Ľ���ԭ����
	vector<CAUSE_TYPE> A_BSSMAP_Cause;//������GSM����ԭ��ķ���ͳ��
	vector<CAUSE_TYPE> A_RANAP_Cause;//������TD����ʱԭ��ķ���ͳ��
	vector<CAUSE_TYPE> B_BSSMAP_Cause;//������GSM����ʱԭ��ķ���ͳ��
	vector<CAUSE_TYPE> B_RANAP_Cause;//������TD����ʱԭ��ķ���ͳ��
	int A_DX_GSM_block;//������������
	int A_DX_TD_block;//������������
	int B_DX_GSM_block;//������������
	int B_DX_TD_block;//������������
	vector<CAUSE_TYPE> A_DX_Cause_GSM;//GSM���ʱDX_Cause�ķ���ͳ��
	vector<CAUSE_TYPE> A_DX_Cause_TD;//TD���ʱDX_Cause�ķ���ͳ��
	vector<CAUSE_TYPE> B_DX_Cause_GSM;//GSM����ʱDX_Cause�ķ���ͳ��
	vector<CAUSE_TYPE> B_DX_Cause_TD;//TD����ʱDX_Cause�ķ���ͳ��
	//int A_causeGSM;//��Ϊ����ʱBSSMAP_causeֵΪ0,1,20,60����ĳһ���Ĵ���
	//int A_causeTD;//��Ϊ����ʱRANAP_causeֵ��Ϊ0�Ĵ���
	//int B_causeGSM;//��Ϊ����ʱBSSMAP_causeֵΪ0,1,20,60����ĳһ���Ĵ���
	//int B_causeTD;//��Ϊ����ʱRANAP_causeֵ��Ϊ0�Ĵ���
	//vector<vector<IMEI_IMSI>> A_IMEI_IMSI_GSM;//IMEI��IMSI��
	//vector<vector<IMEI_IMSI>> A_IMEI_IMSI_TD;//IMEI��IMSI��
	//vector<vector<IMEI_IMSI>> B_IMEI_IMSI_GSM;//IMEI��IMSI��
	//vector<vector<IMEI_IMSI>> B_IMEI_IMSI_TD;//IMEI��IMSI��
	//int A_IMEI_TD;//distinct��IMEI��
	//int A_IMEI_GSM;//distinct��IMEI��
	//int B_IMEI_GSM;//distinct��IMEI��
	//int B_IMEI_TD;//distinct��IMEI��
	//int A_cause0;//��Ϊ����ʱBSSMAP_causeֵΪ0
	//int A_cause1;//��Ϊ����ʱBSSMAP_causeֵΪ1
	//int A_cause20;//��Ϊ����ʱBSSMAP_causeֵΪ20
	//int A_cause60;//��Ϊ����ʱBSSMAP_causeֵΪ60
	//int A_causeTDRadioNetwork;//��Ϊ����ʱRANAP_causeֵΪ1-64,257-512����ĳһ���Ĵ���
	//int A_causeTDTransport;//��Ϊ����ʱRANAP_causeֵΪ65-80����ĳһ���Ĵ���
	//int A_causeTDNAS;//��Ϊ����ʱRANAP_causeֵΪ81-96����ĳһ���Ĵ���
	//int A_causeTDProtocol;//��Ϊ����ʱRANAP_causeֵΪ97-112����ĳһ���Ĵ���
	//int A_causeTDMisc;//��Ϊ����ʱRANAP_causeֵΪ113-128����ĳһ���Ĵ���
	//int A_causeTDNonStandard;//��Ϊ����ʱRANAP_causeֵΪ129-256����ĳһ���Ĵ���
	//int A_causeTD46;//��Ϊ����ʱRANAP_causeֵΪ46�Ĵ���
	//int A_causeTD176;//��Ϊ����ʱRANAP_causeֵΪ176�Ĵ���
	//int A_causeTD192;//��Ϊ����ʱRANAP_causeֵΪ192�Ĵ���
	//int A_causeTD209;//��Ϊ����ʱRANAP_causeֵΪ209�Ĵ���
	//int A_causeTD239;//��Ϊ����ʱRANAP_causeֵΪ239�Ĵ���
	//int A_call_not_connected;//��Ϊ����δ��ͨ�Ĵ���
	//int B_cause0;//��Ϊ����ʱBSSMAP_causeֵΪ0
	//int B_cause1;//��Ϊ����ʱBSSMAP_causeֵΪ1
	//int B_cause20;//��Ϊ����ʱBSSMAP_causeֵΪ20
	//int B_cause60;//��Ϊ����ʱBSSMAP_causeֵΪ60
	//int B_causeTDRadioNetwork;//��Ϊ����ʱRANAP_causeֵΪ1-64,257-512����ĳһ���Ĵ���
	//int B_causeTDTransport;//��Ϊ����ʱRANAP_causeֵΪ65-80����ĳһ���Ĵ���
	//int B_causeTDNAS;//��Ϊ����ʱRANAP_causeֵΪ81-96����ĳһ���Ĵ���
	//int B_causeTDProtocol;//��Ϊ����ʱRANAP_causeֵΪ97-112����ĳһ���Ĵ���
	//int B_causeTDMisc;//��Ϊ����ʱRANAP_causeֵΪ113-128����ĳһ���Ĵ���
	//int B_causeTDNonStandard;//��Ϊ����ʱRANAP_causeֵΪ129-256����ĳһ���Ĵ���
	//int B_causeTD46;//��Ϊ����ʱRANAP_causeֵΪ46�Ĵ���
	//int B_causeTD176;//��Ϊ����ʱRANAP_causeֵΪ176�Ĵ���
	//int B_causeTD192;//��Ϊ����ʱRANAP_causeֵΪ192�Ĵ���
	//int B_causeTD209;//��Ϊ����ʱRANAP_causeֵΪ209�Ĵ���
	//int B_causeTD239;//��Ϊ����ʱRANAP_causeֵΪ239�Ĵ���
	int A_shortcall_1;//��Ϊ����ʱͨ��ʱ��<SHORTCALL_THRESHOLD_1
	int A_shortcall_2;//��Ϊ����ʱͨ��ʱ��<SHORTCALL_THRESHOLD_2
	int A_shortcall_3;//��Ϊ����ʱͨ��ʱ��<SHORTCALL_THRESHOLD_3
	int A_call_attempt;//call�Ĵ���
	int A_call_attempt_TD;//TD��call����
	int A_call_attempt_GSM;//GSM��call����
	int A_call_first_cell_connected;//���С��call��ͨ�Ĵ���
	int A_call_first_cell_connected_TD;//���С��TD��call��ͨ���� 
	int A_call_first_cell_connected_GSM;//���С��GSM��call��ͨ����
	int A_call_last_cell_connected;//����С��call��ͨ�Ĵ���
	int A_call_last_cell_connected_TD;//����С��TD��call��ͨ���� 
	int A_call_last_cell_connected_GSM;//����С��GSM��call��ͨ����
	int B_shortcall_1;//��Ϊ����ʱͨ��ʱ��<SHORTCALL_THRESHOLD_1
	int B_shortcall_2;//��Ϊ����ʱͨ��ʱ��<SHORTCALL_THRESHOLD_2
	int B_shortcall_3;//��Ϊ����ʱͨ��ʱ��<SHORTCALL_THRESHOLD_3
	int B_call_attempt;//call�Ĵ���
	int B_call_attempt_TD;//TD��call����
	int B_call_attempt_GSM;//GSM��call����
	int B_call_first_cell_connected;//���С��call��ͨ�Ĵ���
	int B_call_first_cell_connected_TD;//���С��TD��call��ͨ���� 
	int B_call_first_cell_connected_GSM;//���С��GSM��call��ͨ����
	int B_call_last_cell_connected;//����С��call��ͨ�Ĵ���
	int B_call_last_cell_connected_TD;//����С��TD��call��ͨ���� 
	int B_call_last_cell_connected_GSM;//����С��GSM��call��ͨ����
};
//ͳ�Ʋ��ظ���IMEI��
struct IMEI_Distinct_Count{
	string TAC;//TAC��
	string brand;//����Ʒ��
	string name;//�ͺ�
	string type;//����
	string IMEI;//IMEI��
	int cellid;//����С��
	string network;//��TD����GSM
	string celltype;//С������
	int timeSection;//ʱ�κ�
	time_t timeSectionStartTime;//ĳһʱ�ε���ʼʱ��
	vector<vector<IMEI_IMSI>> A_IMEI_IMSI_GSM;//IMEI��IMSI��
	vector<vector<IMEI_IMSI>> A_IMEI_IMSI_TD;//IMEI��IMSI��
	vector<vector<IMEI_IMSI>> B_IMEI_IMSI_GSM;//IMEI��IMSI��
	vector<vector<IMEI_IMSI>> B_IMEI_IMSI_TD;//IMEI��IMSI��
	int A_IMEI_TD;//distinct��IMEI��
	int A_IMEI_GSM;//distinct��IMEI��
	int B_IMEI_GSM;//distinct��IMEI��
	int B_IMEI_TD;//distinct��IMEI��
};
//�������
struct config{
	int THREADNUM;//�߳���
	bool bIMEIOutput;//�Ƿ����IMEI����ͳ���ļ�
	bool bComputeDistinctIMEI;//�Ƿ�ͳ�Ʋ��ظ���IMEI��
	string workmode;//����ģʽ
	string combinemode;//combine�Ĺ�����ʽ
	string toCombineConfigFile;//Combineģʽ�µ������ļ�λ��
	int FileBatchNum;//ÿ�δ�����ļ�����s��Ҫ���ڴ治������ٶ��������Է����ε���CDR
	int SHORTCALL_THRESHOLD_1;//�̺�����1�Σ���xx<SHORTCALL_THRESHOLD_1
	int SHORTCALL_THRESHOLD_2;//�̺�����2�Σ���SHORTCALL_THRESHOLD_1<xx<SHORTCALL_THRESHOLD_2
	int SHORTCALL_THRESHOLD_3;//�̺�����3�Σ���SHORTCALL_THRESHOLD_2<xx<SHORTCALL_THRESHOLD_3
	int HASH_NUM_IMEI;//ɢ�е�hash key��ǰhash_num_imeiλȡ��IMEI�Ĵ�START_HASH_INDEX��HASH_NUMλ
	int START_HASH_INDEX_IMEI;//ɢ�е�keyȡimei�ĵڼ�λ��ʼ
	int HASH_NUM_CELLID;//ȡCELLID�ĺ�λ��ΪHASH KEY�ĺ�λ
	time_t STATISTIC_START_TIME;//CDR��¼��ʼʱ�䣬��call_start_timeΪ׼
	time_t STATISTIC_END_TIME;//CDR��¼����ʱ�䣬��call_start_timeΪ׼
	int TIME_SECTION_UNIT;//��ͳ��ʱ��ʱ�εļ��������Ϊ��λ�����Ϊ0������ʱ�μ����
	vector<string> CDR_SCREEN_B_NUMBER_INITIAL_LIST;//������к����ǰ׺�����LIST�����ŷָ�)�У���ô������CDR����Ҫ��Ϊ�˳�������
	string CDRDirectory;//Ҫ�����CDR�ļ����ڵ��ļ���
	string OutputDirectory;//��������ͳ���ļ���ŵ�Ŀ¼
	string CELLFILE;//cell���͵��ļ�
	string TACFILE;//tac���͵��ļ�
	vector<string> itemlist;//�ֶ�λ���б�
	vector<string> filelist;//Ҫ�����CDR�ļ��б�
	//vector<int> filecurpos;//��ǰ��ȡ����λ��
	vector<string> tacstatfilelist;//tac������ļ���
	//vector<int> tacstatfilecurpos;//��ǰ��ȡ����λ��
};
//ͨ�ú�������
time_t FormatTime(const char * szTime);//���ַ���ת��Ϊʱ��

bool WorkModeSelection(string mode);//����ģʽѡ��
bool WorkLoadDistribution(vector<string> fl,string workdir);//���乤����
bool MatchProcess();//tacstat�������taclist��celltypelistƥ��
bool CombineProcess(std::string mode);//���Ķ�tacstat����timesection��cell���кϲ��Ľ���
//==================�ļ���ȡ=====
//������ReadCDRFile�����У��о�CDR�Ƿ���Ч���������κͼ��ٲ���CDR����
bool isValidCDR(CDR cdr);
bool ReadConfigFile(std::string configfile);//��ȡ�����ļ�
bool ReadToCombineFileList(std::string tocombinefile);//��ȡcombine�ļ��б�
bool ReadCDRFile(int fn,string cdrfile);//��ȡ�ļ��б��е�CDR�ļ�
bool ReadTACFile(string tacfile);//��ȡTAC��Ӧ��Ʒ�ƣ��ͺź������ļ�
//��ȡcell���͵��ļ�
bool ReadCellTypeFile(string celltypefile);
//��ȡtacstat�洢���ļ�
bool ReadTACSTATFile(string tacstatfile);
//==================�ļ�д��=====
//���tacstat
bool WriteTACFile(std::string temp_result_path_name);
//���tacstat_timesection
bool WriteTACFile_TimeSection(std::string temp_result_path_name);
//���tacstat_cell
bool WriteTACFile_TimeSectionCell(std::string temp_result_path_name);
//==================IMEI���=========================
bool ComputeIMEIStatistic(int fn,int startnum,int endnum);//����imeicdrfile
bool ComputeDistinctIMEI(int fn,int startnum,int endnum);//����imeidistinct
//==================TAC���=======================
//�Ӽ���õ�imeicdrfile�и���TAC�ϲ�����taccdrfile
bool ComputeTACStatistic(int fn);
//������õ�taccdrfile�в�ͬ���߳�fn�ϲ�����tacstat
bool CombineTAC_Thread();
//��tacstat��taclist����join����
bool MatchTACList();
////��tacstat��celltypelist����join����
bool MatchCellTypeList();
////����ͬ���β�����tacstat�ļ��ϲ���һ��tacstat
bool CombineMultiTACStat(vector<string> tacstatfilelist);

//������õ�tacstat�в�ͬ��TimeSection�ϲ�����tacstat_timesection
bool CombineTAC_TimeSection();
//��tacstat_timesection�в�ͬ��cell�ϲ�����tacstat_timesectioncell
bool CombineTAC_TimeSectionCell();
//==================���ܺ���=======================
bool IsDropCauseGSM(int causeid);
bool IsDropCauseTD(int causeid);
bool IsDXblockGSM(int causeid);
bool IsDXblockTD(int causeid);
//���ڶ�ȡ��һ����
bool ReadItemList(string sl,vector<string>& readitem);
//ȫ�ֱ���

extern vector<recordp> rp;//rpָ��
extern config cfg;//���������
//������ȫ�ֱ���
extern vector<vector<vector<IMEI_CDR_Statistic>>> imeicdrfile;//���ļ�ͳ��imei��cdr
extern vector<vector<vector<IMEI_Distinct_Count>>> imeidistinct;//���ļ�ͳ�Ʋ��ظ�imei
extern vector<vector<CDR>> cdr;//�ļ���ȡCDR���ļ��洢
extern vector<TAC_NAME> taclist;//TAC��Ӧ��Ʒ�ƣ��ͺź�����
extern vector<CELL_TYPE> celltypelist;//CELL��Ӧ������
//inline����
inline string&  lTrim(string   &ss)   
{  
    string::iterator p=find_if(ss.begin(),ss.end(),not1(ptr_fun(isspace)));   
    ss.erase(ss.begin(),p);   
    return  ss;   
}   
inline string&  rTrim(string   &ss)   
{   
    string::reverse_iterator  p=find_if(ss.rbegin(),ss.rend(),not1(ptr_fun(isspace)));   
    ss.erase(p.base(),ss.end());   
    return   ss;   
}   
inline string&   trim(string   &st)   
{   
    lTrim(rTrim(st));   
    return   st;   
}  

#endif