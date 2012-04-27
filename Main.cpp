//Main.cpp : 定义控制台应用程序的入口点。
#include"stdafx.h"
#include"Main.h"
#include<omp.h>
using namespace std;

//全局变量
int THREADNUM=16;//线程数
int HASH_NUM_IMEI=4;//散列的hash key的前hash_num_imei位取得IMEI的从START_HASH_INDEX起共HASH_NUM位
int START_HASH_INDEX_IMEI=4;//散列的key取imei的第几位开始
int HASH_NUM_CELLID=2;//取CELLID的后几位作为HASH KEY的后几位

int SHORTCALL_THRESHOLD_1;//短呼门限1段，即xx<SHORTCALL_THRESHOLD_1
int SHORTCALL_THRESHOLD_2;//短呼门限2段，即SHORTCALL_THRESHOLD_1<xx<SHORTCALL_THRESHOLD_2
int SHORTCALL_THRESHOLD_3;//短呼门限3段，即SHORTCALL_THRESHOLD_2<xx<SHORTCALL_THRESHOLD_3

time_t STATISTIC_START_TIME;//CDR记录开始时间，以call_start_time为准
time_t STATISTIC_END_TIME;//CDR记录结束时间，以call_start_time为准
int TIME_SECTION_UNIT;//在统计时按时段的间隔，以秒为单位，如果为0，则无时段间隔。

vector<string> CDR_SCREEN_B_NUMBER_INITIAL_LIST;//如果被叫号码的前缀在这个LIST（逗号分隔)中，那么不计入CDR，主要是为了除掉彩玲

bool bIMEIOutput;//是否输出IMEI级的统计文件
string workmode;//工作模式
int FileBatchNum;//每次处理的文件数，s主要是内存不足造成速度慢，所以分批次倒入CDR

vector<string> itemlist;//字段位置列表
vector<string> filelist;//要处理的CDR文件列表
vector<string> tacstatfilelist;//tac输出的文件名
string CDRDirectory;//要处理的CDR文件所在的文件夹
string OutputDirectory;//最后输出的统计文件存放的目录
string CELLFILE;//cell类型的文件
string TACFILE;//tac类型的文件

vector<TAC_NAME> taclist;//TAC对应的品牌，型号和类型
vector<CELL_TYPE> celltypelist;//CELL对应的类型

vector<vector<CDR>> cdr;//文件读取CDR分文件存储
vector<recordp> rp;//rp指针，为了使线程的处理cdr数目相同
vector<vector<vector<IMEI_CDR_Statistic>>> imeicdrfile;//按线程平均分段统计imei的cdr
vector<vector<vector<IMEI_CDR_Statistic>>> taccdrfile;//将计算好的imeicdrfile中在各自的线程里进行tac合并
vector<vector<IMEI_CDR_Statistic>> imeistat;//将计算好的imeicdrfile中不同的线程fn合并生成imeistat
vector<vector<IMEI_CDR_Statistic>> tacstat;//将计算好的taccdrfile中不同的线程fn合并生成tacstat
vector<vector<IMEI_CDR_Statistic>> imeistat_cell;//将imei统计按照cellid合并
vector<vector<IMEI_CDR_Statistic>> tacstat_timesectioncell;//将tacstat_timesection中不同的cell合并生成tacstat_timesectioncell
vector<vector<IMEI_CDR_Statistic>> tacstat_timesection;//将计算好的tacstat中不同的TimeSection合并生成tacstat_timesection
//将字符串转化为time_t变量
time_t FormatTime(const char * szTime)
{
        struct tm tm1;
        time_t time1;
		UINT64 milisec;

		sscanf_s(szTime, "%4d-%2d-%2d %2d:%2d:%2d.%9d",    
                     &tm1.tm_year,
                     &tm1.tm_mon,
                     &tm1.tm_mday,
                     &tm1.tm_hour,
                     &tm1.tm_min,
                     &tm1.tm_sec,
					 &milisec);
              
        tm1.tm_year -= 1900;
        tm1.tm_mon --;

        tm1.tm_isdst=-1;
   
        time1 = mktime(&tm1);
        return time1;
}
//工作模式选择
bool WorkModeSelection(string mode){
	time_t start,end;
	start=clock();
	if(mode=="MatchCellType"){
		
		return true;
	}
	else if(mode=="MatchTACList"){
		return true;
	}
	else if(mode=="ComputeTACStatistic"){
		
		if(!WorkLoadDistribution(filelist,CDRDirectory)){
			cout<<"IMEI and TAC statistic computing is not complete due to error"<<endl;
		}
		CombineMultiTACStat(tacstatfilelist);

		CombineProcess();
		/*
		//开始按IMEI统计
		//在已有的IMEI列表查找是否有相同的
		//费时的过程，需要优化
		//因为涉及到写操作，如何做到并行操作？用#pragma omp critical
		//if(!ReadFileList(filelist,workingDirectory)){
		//	cout<<"Reading file is not complete due to error"<<endl;
		//	return 0;
		//}
		//else{
		//	end=clock();
		//	cout<<"Reading file complete in "<<difftime(end,start)/1000<<"s"<<endl;
		//}
		//if(!ComputeIMEIStatistic()){
		//	cout<<"IMEI statistic computing is not complete due to error"<<endl;
		//	return 0;
		//}
		//else{
		//	cout<<"IMEI statistic computing complete!!!"<<endl;
		//}
		////清空cdr
		//cdr.clear();
		//vector<vector<CDR>>().swap(cdr);
		//cout<<"CDR vector is cleared"<<endl;
		*/	
		
		//string result_file_name=OutputDirectory+"\\IMEIstat";
		//string result_file_name1=OutputDirectory+"\\IMEIstat.csv";
		//string result_combinefile_name=OutputDirectory+"\\CombineIMEIstat";
		//string result_combinefile_name1=OutputDirectory+"\\CombineIMEIstat.csv";
		//string result_combinecellfile_name=OutputDirectory+"\\CombineIMEICellstat";
		//string result_combinecellfile_name1=OutputDirectory+"\\CombineIMEICellstat.csv";
		//string result_tacfile_name=OutputDirectory+"\\TACstat";
		//string result_tacfile_name1=OutputDirectory+"\\TACstat.csv";
		
		

		//if(_access(OutputDirectory.c_str(),0)==0)//为真表示文件夹存在,则不做任何处理，如果不存在则新建一个文件夹
		//{
		//	//cout<<"directory exist\n";
		//}
		//else{
		//	string delresultpath=(string)"rmdir "+OutputDirectory+(string)" /q/s";
		//	_mkdir(OutputDirectory.c_str());
		//	if(_mkdir(OutputDirectory.c_str())==-1){
		//		system(delresultpath.c_str());
		//		_mkdir(OutputDirectory.c_str());
		//	}
		//}

		//int i=0;
		//char num[64];
		//while(_access(result_combinecelltacfile_name.c_str(),0)!=-1){//如果结果文档存在，则最后的标号加1，这是为了保存以前的计算结果
		//	sprintf_s(num,"%d",i);
		//	string result_file_name_new=result_file_name+(string)"_"+(string)num+".csv";
		//	string result_combinefile_name_new=result_combinefile_name+(string)"_"+(string)num+".csv";
		//	string result_combinecellfile_name_new=result_combinecellfile_name+(string)"_"+(string)num+".csv";
		//	string result_tacfile_name_new=result_tacfile_name+(string)"_"+(string)num+".csv";
		//	if(_access(result_combinecelltacfile_name_new.c_str(),0)==-1){
		//		result_file_name1=result_file_name_new;
		//		result_combinefile_name1=result_combinefile_name_new;
		//		result_combinecellfile_name1=result_combinefile_name_new;
		//		result_tacfile_name1=result_tacfile_name_new;
		//		result_combinecelltacfile_name1=result_combinecelltacfile_name_new;
		//		break;
		//	}
		//	i++;
		//}
		//
		/*if(bIMEIOutput==true){
			cout<<"Start writing file "<<result_file_name1<<endl;
			WriteIMEIFile(result_file_name1);
			cout<<"Start writing file "<<result_tacfile_name1<<endl;
			WriteTACFile(result_tacfile_name1);
		}*/
		
		//if(bCombine=true){
		//	if(bIMEIOutput==true){
		//		if(!CombineIMEI()){
		//			cout<<"IMEI combining is not complete due to error"<<endl;
		//		}
		//		else{
		//			cout<<"IMEI combining complete!!!"<<endl;
		//			imeicdrfile.clear();
		//			vector<vector<vector<IMEI_CDR_Statistic>>>().swap(imeicdrfile);
		//			cout<<"IMEI_CDR_FILE vector is cleared"<<endl;

		//			cout<<"Start writing file "<<result_combinefile_name1<<endl;
		//			WriteIMEIFile_Combine(result_combinefile_name1);
		//		}
		//		//清空imeistat
		//		imeistat.clear();
		//		vector<vector<IMEI_CDR_Statistic>>().swap(imeistat);
		//		cout<<"IMEI_STAT vector is cleared"<<endl;

		//		if(!CombineIMEI_Cell()){
		//			cout<<"IMEI combining with Cell is not complete due to error"<<endl;
		//		}
		//		else{
		//			cout<<"IMEI combining with Cell complete!!!"<<endl;
		//			imeistat.clear();
		//			vector<vector<IMEI_CDR_Statistic>>().swap(imeistat);
		//			cout<<"IMEI_STAT vector is cleared"<<endl;

		//			cout<<"Start writing file "<<result_combinecellfile_name1<<endl;
		//			WriteIMEIFile_Combine(result_combinecellfile_name1);
		//		}
		//		//清空imeistat_cell
		//		imeistat_cell.clear();
		//		vector<vector<IMEI_CDR_Statistic>>().swap(imeistat_cell);
		//		cout<<"IMEI_STAT_CELL vector is cleared"<<endl;
		//	}

		//	
		//}
		end=clock();
		cout<<"TAC Statistic compute complete in total "<<difftime(end,start)/1000<<"s "<<endl;
		return true;
	}
	else if(mode=="CombineTACStatistic"){
		tacstatfilelist.clear();
		tacstatfilelist.push_back("D:\\xudayong\\traffica20120326\\CombineTACCellstat.csv");
		tacstatfilelist.push_back("D:\\xudayong\\traffica20120326\\CombineTACCellstat_0.csv");
		tacstatfilelist.push_back("D:\\xudayong\\traffica20120326\\CombineTACCellstat_1.csv");
		tacstatfilelist.push_back("D:\\xudayong\\traffica20120326\\CombineTACCellstat_2.csv");
		tacstatfilelist.push_back("D:\\xudayong\\traffica20120326\\CombineTACCellstat_3.csv");

		CombineMultiTACStat(tacstatfilelist);

		CombineProcess();

		end=clock();
		cout<<"TAC Statistic File Combining complete in total "<<difftime(end,start)/1000<<"s "<<endl;
		return true;
	}
	return true;
}
//负载在各个线程中分配
bool WorkLoadDistribution(vector<string> fl,string workingdir){	
	taccdrfile.clear();
	taccdrfile.resize(THREADNUM);
	//每轮的tacstat存储的文件名
	tacstatfilelist.clear();
	//算每轮读FileBatchNum个文件进来，共需多少轮---ceil函数似乎变成了四舍五入的
	int batchnum=(int)(ceil((double)(fl.size()/(FileBatchNum))))+1;
	cout<<"Divide into "<<batchnum<<" Batch"<<endl;
	//开始
	for(int bn=0;bn<batchnum;bn++){
		cdr.clear();
		cdr.resize(fl.size());
		//如果只要tac，那么清空imeicdrfile,或者第一轮运行时，初始化imeicdrfile
		if(bIMEIOutput==false||bn==0){
			imeicdrfile.clear();
			imeicdrfile.resize(THREADNUM);
			for(int threadn=0;threadn<THREADNUM;threadn++){
				imeicdrfile[threadn].clear();
				imeicdrfile[threadn].resize((int)pow((double)10,HASH_NUM_IMEI+HASH_NUM_CELLID));
			}
		}
		//读取文件,并行
		omp_set_num_threads(THREADNUM);
		#pragma omp parallel for
			for(int fn=bn*FileBatchNum;fn<min((bn+1)*FileBatchNum,(int)fl.size());fn++){
				ReadCDRFile(fn,workingdir+"\\"+fl[fn]);
			}
		//创建基于record的列表，以平均分配任务给每个线程
		rp.clear();
		for(int fn=bn*FileBatchNum;fn<min((bn+1)*FileBatchNum,(int)fl.size());fn++){
			for(int j=0;j<cdr[fn].size();j++){
				recordp temp_rp;
				temp_rp.fn=fn;
				temp_rp.rn=j;
				rp.push_back(temp_rp);
			}
		}
		//计算每个线程的IMEI和TAC统计
		omp_set_num_threads(THREADNUM);
		#pragma omp parallel for
			for(int threadn=0;threadn<THREADNUM;threadn++){
				int threadi=omp_get_thread_num();
				int startnum=threadi*(int)(ceil((double)(rp.size()/(THREADNUM))));
				int endnum;
				if(threadi==THREADNUM-1){
					endnum=(int)rp.size()-1;
				}
				else{
					endnum=(threadi+1)*(int)(ceil((double)(rp.size()/(THREADNUM))))-1;
				}
				cout<<"Batch $"<<bn<<" Thread #"<<threadi<<" Compute IMEI statistic of Records No."<<startnum<<" to "<<endnum<<",Total "<<rp.size()<<".\n";
		
				ComputeIMEIStatistic(threadn,startnum,endnum);
				ComputeTACStatistic(threadn);
			}

		//每轮结束后，清空cdr和rp
		cout<<"Batch $"<<bn<<" Start clear CDR vector and record vector"<<endl;
		cdr.clear();
		vector<vector<CDR>>().swap(cdr);
		cout<<"Batch $"<<bn<<" CDR vector is cleared"<<endl;
		cout<<"Batch $"<<bn<<" Start clear Record vector"<<endl;
		rp.clear();
		vector<recordp>().swap(rp);
		cout<<"Batch $"<<bn<<" Record vector is cleared"<<endl;
		//如果只要tac，那么清空imeicdrfile
		if(bIMEIOutput==false){
			imeicdrfile.clear();
			vector<vector<vector<IMEI_CDR_Statistic>>>().swap(imeicdrfile);
			cout<<"IMEI_CDR_FILE vector is cleared"<<endl;
		}
		
		//初始化tacstat的输出文件夹
		if(_access(OutputDirectory.c_str(),0)==0)//为真表示文件夹存在,则不做任何处理，如果不存在则新建一个文件夹
		{
			//cout<<"directory exist\n";
		}
		else{
			string delresultpath=(string)"rmdir "+OutputDirectory+(string)" /q/s";
			_mkdir(OutputDirectory.c_str());
			if(_mkdir(OutputDirectory.c_str())==-1){
				system(delresultpath.c_str());
				_mkdir(OutputDirectory.c_str());
			}
		}

		//生成tacstat本轮的输出文件名
		string result_combinetacfile_name=OutputDirectory+"\\ToCombineTACstat";
		string result_combinetacfile_name1=OutputDirectory+"\\ToCombineTACstat.csv";
		int i=0;
		char num[64];
		while(_access(result_combinetacfile_name1.c_str(),0)==0){//如果结果文档存在，则最后的标号加1，这是为了保存以前的计算结果
			sprintf_s(num,"%d",i);
			string result_combinetacfile_name_new=result_combinetacfile_name+(string)"_"+(string)num+".csv";
			if(_access(result_combinetacfile_name_new.c_str(),0)!=0){
				result_combinetacfile_name1=result_combinetacfile_name_new;
				break;
			}
			i++;
		}
		//每轮后进行TAC的合并，以释放taccdrfile
		if(!CombineTAC_Thread()){
			cout<<"Batch $"<<bn<<" TAC combining is not complete due to error"<<endl;
		}
		else{
			cout<<"Batch $"<<bn<<" TAC combining complete!!!"<<endl;
			
			//清空taccdrfile
			taccdrfile.clear();
			vector<vector<vector<IMEI_CDR_Statistic>>>().swap(taccdrfile);
			cout<<"TAC_CDR_FILE vector is cleared"<<endl;

			//已经生成了tacstat，开始match tac with brand, name and type
			cout<<"Batch $"<<bn<<" Start Matching TAC with brand, name and type"<<endl;
			MatchTACList();
			//已经生成tacstat,开始match cell with celltype
			cout<<"Batch $"<<bn<<" Start Matching Cell with celltype"<<endl;
			MatchCellTypeList();
			//开始写文件
			cout<<"Batch $"<<bn<<" Start writing file "<<result_combinetacfile_name1<<endl;
			tacstatfilelist.push_back(result_combinetacfile_name1);
			WriteTACFile(result_combinetacfile_name1);
		}
		
	}

	return true;

}

bool CombineProcess(){
		//经过n轮后进行各轮tacstat的合并后的tacstat按照timesection和cell进行，合并后释放tacstat

		if(CombineTAC_TimeSection()!=true){
			cout<<"TAC with Same TimeSection combining is not complete due to error"<<endl;
		}
		else{
			cout<<"TAC with Same TimeSection combining complete!!!"<<endl;
			
			//清空tacstat
			tacstat.clear();
			vector<vector<IMEI_CDR_Statistic>>().swap(tacstat);
			cout<<"TAC_STAT vector is cleared"<<endl;

			string result_filename=OutputDirectory+"\\TACstat_Cell";
			string result_filename1=OutputDirectory+"\\TACstat_Cell.csv";
			int i=0;
			char num[64];
			while(_access(result_filename1.c_str(),0)==0){//如果结果文档存在，则最后的标号加1，这是为了保存以前的计算结果
				sprintf_s(num,"%d",i);
				string result_filename_new=result_filename+(string)"_"+(string)num+".csv";
				if(_access(result_filename_new.c_str(),0)!=0){
					result_filename1=result_filename_new;
					break;
				}
				i++;
			}

			cout<<"Start writing file "<<result_filename1<<endl;
			WriteTACFile_TimeSection(result_filename1);
		}
		

		if(CombineTAC_TimeSectionCell()!=true){
			cout<<"TAC with Cell combining is not complete due to error"<<endl;
		}
		else{
			cout<<"TAC with Cell combining complete!!!"<<endl;

			//清空tacstat_timesectioncell
			tacstat_timesection.clear();
			vector<vector<IMEI_CDR_Statistic>>().swap(tacstat_timesection);
			cout<<"TAC_STAT_TIMESECTION vector is cleared"<<endl;


			string result_filename=OutputDirectory+"\\TACstat";
			string result_filename1=OutputDirectory+"\\TACstat.csv";
			int i=0;
			char num[64];
			while(_access(result_filename1.c_str(),0)==0){//如果结果文档存在，则最后的标号加1，这是为了保存以前的计算结果
				sprintf_s(num,"%d",i);
				string result_filename_new=result_filename+(string)"_"+(string)num+".csv";
				if(_access(result_filename_new.c_str(),0)!=0){
					result_filename1=result_filename_new;
					break;
				}
				i++;
			}
			cout<<"Start writing file "<<result_filename1<<endl;
			WriteTACFile_TimeSectionCell(result_filename1);

			//清空tacstat_timesectioncell
			tacstat_timesectioncell.clear();
			vector<vector<IMEI_CDR_Statistic>>().swap(tacstat_timesectioncell);
			cout<<"TAC_STAT_TIMESECTION_CELL vector is cleared"<<endl;

		}
}
//入口函数
int _tmain(int argc, _TCHAR* argv[])
{
	
	//读取参数制定的文件名
	string readpathname;
	if(argc==1||argc==0){
		string defaultfilepath="D:\\xudayong\\Program\\TrafficaIMEI\\x64\\Release\\";
		readpathname=defaultfilepath+CONFIG_FILE_DEFAULT;;
	}
	else if(argc==2){
		char tempstring[1000];
		int i=0;
		while(argv[1][i]!='\0'){
			tempstring[i]=(char)argv[1][i];
			i++;
		}
		tempstring[i]='\0';
		readpathname=(std::string)tempstring;
	}

	if(!ReadConfigFile(readpathname)){
		cout<<"Reading config file is not complete due to error"<<endl;
		return 0;
	}
	else{
		if(filelist.size()>0){
			cdr.clear();
			cdr.resize(filelist.size());
			cout<<"Number of CDR file to be processed is "<<filelist.size()<<endl;
		}
		else{
			cout<<"File list is empty"<<endl;
			return 0;
		}
	}

	if(!ReadTACFile(TACFILE)){
		cout<<"Reading TAC list file is not complete due to error"<<endl;
		return 0;
	}

	if(!ReadCellTypeFile(CELLFILE)){
		cout<<"Reading Cell type file is not complete due to error"<<endl;
		return 0;
	}
	
	if(!WorkModeSelection(workmode)){
		cout<<"work mode "<<workmode<<" is wrong"<<endl;
		return 0;
	}
	
	return 0;
}

