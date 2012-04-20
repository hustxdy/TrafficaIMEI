#include"stdafx.h"

#ifndef __MAIN

#define __MAIN

using namespace std;
//�������Ͷ���
typedef unsigned __int64    UINT64;
//��������
#define PROGRESS_THRES 200000//��������¼ˢ��һ�ν�����
#define TAC_LENGTH 8//TAC�ĳ���
#define CONFIG_FILE_DEFAULT "config.txt"
#define DEFAULT_CAUSE_VALUE -1
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
	string timeSectionStartTime;//ĳһʱ�ε���ʼʱ��
	vector<CAUSE_TYPE> A_BSSMAP_Cause;//������GSM����ԭ��ķ���ͳ��
	vector<CAUSE_TYPE> A_RANAP_Cause;//������TD����ʱԭ��ķ���ͳ��
	vector<CAUSE_TYPE> B_BSSMAP_Cause;//������GSM����ʱԭ��ķ���ͳ��
	vector<CAUSE_TYPE> B_RANAP_Cause;//������TD����ʱԭ��ķ���ͳ��
	vector<CAUSE_TYPE> A_DX_Cause_GSM;//GSM���ʱDX_Cause�ķ���ͳ��
	vector<CAUSE_TYPE> A_DX_Cause_TD;//TD���ʱDX_Cause�ķ���ͳ��
	vector<CAUSE_TYPE> B_DX_Cause_GSM;//GSM����ʱDX_Cause�ķ���ͳ��
	vector<CAUSE_TYPE> B_DX_Cause_TD;//TD����ʱDX_Cause�ķ���ͳ��
	//int A_causeGSM;//��Ϊ����ʱBSSMAP_causeֵΪ0,1,20,60����ĳһ���Ĵ���
	//int A_causeTD;//��Ϊ����ʱRANAP_causeֵ��Ϊ0�Ĵ���
	//int B_causeGSM;//��Ϊ����ʱBSSMAP_causeֵΪ0,1,20,60����ĳһ���Ĵ���
	//int B_causeTD;//��Ϊ����ʱRANAP_causeֵ��Ϊ0�Ĵ���
	vector<vector<IMEI_IMSI>> A_IMEI_IMSI_GSM;//IMEI��IMSI��
	vector<vector<IMEI_IMSI>> A_IMEI_IMSI_TD;//IMEI��IMSI��
	vector<vector<IMEI_IMSI>> B_IMEI_IMSI_GSM;//IMEI��IMSI��
	vector<vector<IMEI_IMSI>> B_IMEI_IMSI_TD;//IMEI��IMSI��
	int A_IMEI_TD;//distinct��IMEI��
	int A_IMEI_GSM;//distinct��IMEI��
	int B_IMEI_GSM;//distinct��IMEI��
	int B_IMEI_TD;//distinct��IMEI��
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
	int B_shortcall_1;//��Ϊ����ʱͨ��ʱ��<SHORTCALL_THRESHOLD_1
	int B_shortcall_2;//��Ϊ����ʱͨ��ʱ��<SHORTCALL_THRESHOLD_2
	int B_shortcall_3;//��Ϊ����ʱͨ��ʱ��<SHORTCALL_THRESHOLD_3
	int B_call_attempt;//call�Ĵ���
	int B_call_attempt_TD;//TD��call����
	int B_call_attempt_GSM;//GSM��call����
};

//ͨ�ú�������
time_t FormatTime(const char * szTime);//���ַ���ת��Ϊʱ��

bool WorkModeSelection(string mode);//����ģʽѡ��
bool WorkLoadDistribution(vector<string> fl,string workdir);//���乤����
//==================�ļ���ȡ=====
bool ReadConfigFile(std::string configfile);//��ȡ�����ļ�
bool ReadCDRFile(int fn,string cdrfile);//��ȡ�ļ��б��е�CDR�ļ�
bool ReadTACFile(string tacfile);//��ȡTAC��Ӧ��Ʒ�ƣ��ͺź������ļ�
//��ȡcell���͵��ļ�
bool ReadCellTypeFile(string celltypefile);
//������ReadCDRFile�����У��о�CDR�Ƿ���Ч���������κͼ��ٲ���CDR����
bool isValidCDR(CDR cdr);
//==================IMEI���=========================
bool ComputeIMEIStatistic(int fn,int startnum,int endnum);//����imeicdrfile
	//���
bool WriteIMEIFile_Combine(std::string temp_result_path_name);
bool WriteIMEIFile_CombineCell(std::string temp_result_path_name);
	//�ϲ�
bool CombineIMEI_Cell();//��imeistat����cellid�ϲ�
bool CombineIMEI();//��imeicdrfile����imeistat
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
//��ȡtacstat�洢���ļ�
bool ReadTACSTATFile(string tacstatfile, vector<vector<IMEI_CDR_Statistic>>& tacstat_temp);
//���tacstat
bool WriteTACFile(std::string temp_result_path_name);
//������õ�tacstat�в�ͬ��TimeSection�ϲ�����tacstat_timesection
bool ComputeTAC_TimeSection();
//��tacstat_timesection�в�ͬ��cell�ϲ�����tacstat_cell
bool CombineTAC_TimeSectionCell();
//���tacstat_timesection
bool WriteTACFile_TimeSection();
//���tacstat_cell
bool WriteTACFile_TimeSectionCell(std::string temp_result_path_name);
//ȫ�ֱ���
extern int THREADNUM;//�߳���
extern bool bIMEIOutput;//�Ƿ����IMEI����ͳ���ļ�
extern string workmode;//����ģʽ
extern vector<recordp> rp;//rpָ��
extern int SHORTCALL_THRESHOLD_1;//�̺�����1�Σ���xx<SHORTCALL_THRESHOLD_1
extern int SHORTCALL_THRESHOLD_2;//�̺�����2�Σ���SHORTCALL_THRESHOLD_1<xx<SHORTCALL_THRESHOLD_2
extern int SHORTCALL_THRESHOLD_3;//�̺�����3�Σ���SHORTCALL_THRESHOLD_2<xx<SHORTCALL_THRESHOLD_3
extern int HASH_NUM_IMEI;//ɢ�е�hash key��ǰhash_num_imeiλȡ��IMEI�Ĵ�START_HASH_INDEX��HASH_NUMλ
extern int START_HASH_INDEX_IMEI;//ɢ�е�keyȡimei�ĵڼ�λ��ʼ
extern int HASH_NUM_CELLID;//ȡCELLID�ĺ�λ��ΪHASH KEY�ĺ�λ
//������ȫ�ֱ���
extern vector<vector<vector<IMEI_CDR_Statistic>>> imeicdrfile;//���ļ�ͳ��imei��cdr
extern vector<vector<CDR>> cdr;//�ļ���ȡCDR���ļ��洢
extern vector<string> tacstatfilelist;//tac������ļ���
extern vector<TAC_NAME> taclist;//TAC��Ӧ��Ʒ�ƣ��ͺź�����
extern vector<CELL_TYPE> celltypelist;//CELL��Ӧ������
//inline����
inline string&  lTrim(string   &ss)   
{  
    string::iterator p=find_if(ss.begin(),ss.end(),not1(ptr_fun(isspace)));   
    ss.erase(ss.begin(),p);   
    return  ss;   
}   
inline  string&  rTrim(string   &ss)   
{   
    string::reverse_iterator  p=find_if(ss.rbegin(),ss.rend(),not1(ptr_fun(isspace)));   
    ss.erase(p.base(),ss.end());   
    return   ss;   
}   
inline   string&   trim(string   &st)   
{   
    lTrim(rTrim(st));   
    return   st;   
}  

#endif