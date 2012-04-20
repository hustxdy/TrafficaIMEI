#include"stdafx.h"

#ifndef __MAIN

#define __MAIN

using namespace std;
//数据类型定义
typedef unsigned __int64    UINT64;
//常量定义
#define PROGRESS_THRES 200000//多少条记录刷新一次进度条
#define TAC_LENGTH 8//TAC的长度
#define CONFIG_FILE_DEFAULT "config.txt"
#define DEFAULT_CAUSE_VALUE -1
//#define DEFAULT_GSM_CAUSE_TO_COUNT "0,1,20,60"
//#define DEFAULT_TD_CAUSE_TO_COUNT ""

//结构定义
//CDR记录
struct CDR{
	time_t report_time;//CDR上报时间
	int A_BSSMAP_cause;//主叫释放原因（BSSMAP）
	int A_BSSMAP_cause_ext;//TD的主叫释放原因（RANAP）
	int A_cell;//主叫挂机时所在小区号
	int A_sac;//主叫挂机时所在的SAC
	string A_number;//主叫号码
	int A_first_cell;//主叫起呼时所在小区号
	int A_first_sac;//主叫起呼时所在的sac
	string A_IMEI;//主叫手机的IMEI
	string A_IMSI;//主叫号码对应的IMSI
	time_t B_answered_time;//被叫应答时间
	int B_cell;//被叫挂机时所在小区号
	int B_sac;//被叫挂机时所在的sac
	string B_number;//被叫号码
	int B_first_cell;//被叫接通时所在的小区号
	int B_first_sac;//被叫接通时所在的sac
	string B_IMEI;//被叫手机的IMEI
	string B_IMSI;//被叫号码的IMSI
	time_t charging_end_time;//Disconnect消息的时间
	int DX_cause;//核心网返回的
	int paging_time;//寻呼的次数
	time_t call_start_time;//主叫发setup消息的时间
	int timeSection;//时间段编号
	time_t signalling_complete_time;//主叫收到altering的时间
	int B_BSSMAP_cause;//被叫释放原因(BSSMAP)
	int B_BSSMAP_cause_ext;//TD被叫释放原因(RANAP)
	int INTER_MSC_HO;//是否为跨MSC呼叫
};
//用于工作量在线程间平均分配时用的指针，指向cdr
struct recordp{
		int fn;//哪个文件
		int rn;//哪个记录
};
//TAC对应的品牌，型号和类别
struct TAC_NAME{
	string TAC;
	string brand;//中文品牌
	string name;//型号
	string type;//类型
};
//Cell对应的类型
struct CELL_TYPE{
	int cellid;
	string type;//小区类型
};
struct CAUSE_TYPE{
	//string network;//何种网络
	int cause_id;//cause的id号
	int cause_num;//此类cause出现的次数
};
struct IMEI_IMSI{
	string IMEI;//IMEI号
	string IMSI;//IMSI号
};
//统计项列表
struct IMEI_CDR_Statistic{
	string TAC;//TAC号
	string brand;//中文品牌
	string name;//型号
	string type;//类型
	string IMEI;//IMEI号
	int cellid;//主叫小区
	string network;//是TD还是GSM
	string celltype;//小区类型
	int timeSection;//时段号
	string timeSectionStartTime;//某一时段的起始时间
	vector<CAUSE_TYPE> A_BSSMAP_Cause;//主叫在GSM结束原因的分类统计
	vector<CAUSE_TYPE> A_RANAP_Cause;//主叫在TD结束时原因的分类统计
	vector<CAUSE_TYPE> B_BSSMAP_Cause;//被叫在GSM结束时原因的分类统计
	vector<CAUSE_TYPE> B_RANAP_Cause;//被叫在TD结束时原因的分类统计
	vector<CAUSE_TYPE> A_DX_Cause_GSM;//GSM起呼时DX_Cause的分类统计
	vector<CAUSE_TYPE> A_DX_Cause_TD;//TD起呼时DX_Cause的分类统计
	vector<CAUSE_TYPE> B_DX_Cause_GSM;//GSM结束时DX_Cause的分类统计
	vector<CAUSE_TYPE> B_DX_Cause_TD;//TD结束时DX_Cause的分类统计
	//int A_causeGSM;//作为主叫时BSSMAP_cause值为0,1,20,60其中某一个的次数
	//int A_causeTD;//作为主叫时RANAP_cause值不为0的次数
	//int B_causeGSM;//作为被叫时BSSMAP_cause值为0,1,20,60其中某一个的次数
	//int B_causeTD;//作为被叫时RANAP_cause值不为0的次数
	vector<vector<IMEI_IMSI>> A_IMEI_IMSI_GSM;//IMEI，IMSI对
	vector<vector<IMEI_IMSI>> A_IMEI_IMSI_TD;//IMEI，IMSI对
	vector<vector<IMEI_IMSI>> B_IMEI_IMSI_GSM;//IMEI，IMSI对
	vector<vector<IMEI_IMSI>> B_IMEI_IMSI_TD;//IMEI，IMSI对
	int A_IMEI_TD;//distinct的IMEI数
	int A_IMEI_GSM;//distinct的IMEI数
	int B_IMEI_GSM;//distinct的IMEI数
	int B_IMEI_TD;//distinct的IMEI数
	//int A_cause0;//作为主叫时BSSMAP_cause值为0
	//int A_cause1;//作为主叫时BSSMAP_cause值为1
	//int A_cause20;//作为主叫时BSSMAP_cause值为20
	//int A_cause60;//作为主叫时BSSMAP_cause值为60
	//int A_causeTDRadioNetwork;//作为主叫时RANAP_cause值为1-64,257-512其中某一个的次数
	//int A_causeTDTransport;//作为主叫时RANAP_cause值为65-80其中某一个的次数
	//int A_causeTDNAS;//作为主叫时RANAP_cause值为81-96其中某一个的次数
	//int A_causeTDProtocol;//作为主叫时RANAP_cause值为97-112其中某一个的次数
	//int A_causeTDMisc;//作为主叫时RANAP_cause值为113-128其中某一个的次数
	//int A_causeTDNonStandard;//作为主叫时RANAP_cause值为129-256其中某一个的次数
	//int A_causeTD46;//作为主叫时RANAP_cause值为46的次数
	//int A_causeTD176;//作为主叫时RANAP_cause值为176的次数
	//int A_causeTD192;//作为主叫时RANAP_cause值为192的次数
	//int A_causeTD209;//作为主叫时RANAP_cause值为209的次数
	//int A_causeTD239;//作为主叫时RANAP_cause值为239的次数
	//int A_call_not_connected;//作为主叫未接通的次数
	//int B_cause0;//作为被叫时BSSMAP_cause值为0
	//int B_cause1;//作为被叫时BSSMAP_cause值为1
	//int B_cause20;//作为被叫时BSSMAP_cause值为20
	//int B_cause60;//作为被叫时BSSMAP_cause值为60
	//int B_causeTDRadioNetwork;//作为被叫时RANAP_cause值为1-64,257-512其中某一个的次数
	//int B_causeTDTransport;//作为被叫时RANAP_cause值为65-80其中某一个的次数
	//int B_causeTDNAS;//作为被叫时RANAP_cause值为81-96其中某一个的次数
	//int B_causeTDProtocol;//作为被叫时RANAP_cause值为97-112其中某一个的次数
	//int B_causeTDMisc;//作为被叫时RANAP_cause值为113-128其中某一个的次数
	//int B_causeTDNonStandard;//作为被叫时RANAP_cause值为129-256其中某一个的次数
	//int B_causeTD46;//作为被叫时RANAP_cause值为46的次数
	//int B_causeTD176;//作为被叫时RANAP_cause值为176的次数
	//int B_causeTD192;//作为被叫时RANAP_cause值为192的次数
	//int B_causeTD209;//作为被叫时RANAP_cause值为209的次数
	//int B_causeTD239;//作为被叫时RANAP_cause值为239的次数
	int A_shortcall_1;//作为主叫时通话时间<SHORTCALL_THRESHOLD_1
	int A_shortcall_2;//作为主叫时通话时间<SHORTCALL_THRESHOLD_2
	int A_shortcall_3;//作为主叫时通话时间<SHORTCALL_THRESHOLD_3
	int A_call_attempt;//call的次数
	int A_call_attempt_TD;//TD的call次数
	int A_call_attempt_GSM;//GSM的call次数
	int B_shortcall_1;//作为被叫时通话时间<SHORTCALL_THRESHOLD_1
	int B_shortcall_2;//作为被叫时通话时间<SHORTCALL_THRESHOLD_2
	int B_shortcall_3;//作为被叫时通话时间<SHORTCALL_THRESHOLD_3
	int B_call_attempt;//call的次数
	int B_call_attempt_TD;//TD的call次数
	int B_call_attempt_GSM;//GSM的call次数
};

//通用函数定义
time_t FormatTime(const char * szTime);//从字符串转换为时间

bool WorkModeSelection(string mode);//工作模式选择
bool WorkLoadDistribution(vector<string> fl,string workdir);//分配工作量
//==================文件读取=====
bool ReadConfigFile(std::string configfile);//读取配置文件
bool ReadCDRFile(int fn,string cdrfile);//读取文件列表中的CDR文件
bool ReadTACFile(string tacfile);//读取TAC对应的品牌，型号和类型文件
//读取cell类型的文件
bool ReadCellTypeFile(string celltypefile);
//在运行ReadCDRFile函数中，判决CDR是否有效，用于屏蔽和减少部分CDR数量
bool isValidCDR(CDR cdr);
//==================IMEI相关=========================
bool ComputeIMEIStatistic(int fn,int startnum,int endnum);//生成imeicdrfile
	//输出
bool WriteIMEIFile_Combine(std::string temp_result_path_name);
bool WriteIMEIFile_CombineCell(std::string temp_result_path_name);
	//合并
bool CombineIMEI_Cell();//用imeistat按照cellid合并
bool CombineIMEI();//用imeicdrfile生成imeistat
//==================TAC相关=======================
//从计算好的imeicdrfile中根据TAC合并生成taccdrfile
bool ComputeTACStatistic(int fn);
//将计算好的taccdrfile中不同的线程fn合并生成tacstat
bool CombineTAC_Thread();
//将tacstat和taclist进行join操作
bool MatchTACList();
////将tacstat和celltypelist进行join操作
bool MatchCellTypeList();
////将不同批次产生的tacstat文件合并成一个tacstat
bool CombineMultiTACStat(vector<string> tacstatfilelist);
//读取tacstat存储的文件
bool ReadTACSTATFile(string tacstatfile, vector<vector<IMEI_CDR_Statistic>>& tacstat_temp);
//输出tacstat
bool WriteTACFile(std::string temp_result_path_name);
//将计算好的tacstat中不同的TimeSection合并生成tacstat_timesection
bool ComputeTAC_TimeSection();
//将tacstat_timesection中不同的cell合并生成tacstat_cell
bool CombineTAC_TimeSectionCell();
//输出tacstat_timesection
bool WriteTACFile_TimeSection();
//输出tacstat_cell
bool WriteTACFile_TimeSectionCell(std::string temp_result_path_name);
//全局变量
extern int THREADNUM;//线程数
extern bool bIMEIOutput;//是否输出IMEI级的统计文件
extern string workmode;//工作模式
extern vector<recordp> rp;//rp指针
extern int SHORTCALL_THRESHOLD_1;//短呼门限1段，即xx<SHORTCALL_THRESHOLD_1
extern int SHORTCALL_THRESHOLD_2;//短呼门限2段，即SHORTCALL_THRESHOLD_1<xx<SHORTCALL_THRESHOLD_2
extern int SHORTCALL_THRESHOLD_3;//短呼门限3段，即SHORTCALL_THRESHOLD_2<xx<SHORTCALL_THRESHOLD_3
extern int HASH_NUM_IMEI;//散列的hash key的前hash_num_imei位取得IMEI的从START_HASH_INDEX起共HASH_NUM位
extern int START_HASH_INDEX_IMEI;//散列的key取imei的第几位开始
extern int HASH_NUM_CELLID;//取CELLID的后几位作为HASH KEY的后几位
//基础的全局变量
extern vector<vector<vector<IMEI_CDR_Statistic>>> imeicdrfile;//按文件统计imei的cdr
extern vector<vector<CDR>> cdr;//文件读取CDR分文件存储
extern vector<string> tacstatfilelist;//tac输出的文件名
extern vector<TAC_NAME> taclist;//TAC对应的品牌，型号和类型
extern vector<CELL_TYPE> celltypelist;//CELL对应的类型
//inline函数
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