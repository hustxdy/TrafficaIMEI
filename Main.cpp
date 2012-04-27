//Main.cpp : �������̨Ӧ�ó������ڵ㡣
#include"stdafx.h"
#include"Main.h"
#include<omp.h>
using namespace std;

//ȫ�ֱ���
int THREADNUM=16;//�߳���
int HASH_NUM_IMEI=4;//ɢ�е�hash key��ǰhash_num_imeiλȡ��IMEI�Ĵ�START_HASH_INDEX��HASH_NUMλ
int START_HASH_INDEX_IMEI=4;//ɢ�е�keyȡimei�ĵڼ�λ��ʼ
int HASH_NUM_CELLID=2;//ȡCELLID�ĺ�λ��ΪHASH KEY�ĺ�λ

int SHORTCALL_THRESHOLD_1;//�̺�����1�Σ���xx<SHORTCALL_THRESHOLD_1
int SHORTCALL_THRESHOLD_2;//�̺�����2�Σ���SHORTCALL_THRESHOLD_1<xx<SHORTCALL_THRESHOLD_2
int SHORTCALL_THRESHOLD_3;//�̺�����3�Σ���SHORTCALL_THRESHOLD_2<xx<SHORTCALL_THRESHOLD_3

time_t STATISTIC_START_TIME;//CDR��¼��ʼʱ�䣬��call_start_timeΪ׼
time_t STATISTIC_END_TIME;//CDR��¼����ʱ�䣬��call_start_timeΪ׼
int TIME_SECTION_UNIT;//��ͳ��ʱ��ʱ�εļ��������Ϊ��λ�����Ϊ0������ʱ�μ����

vector<string> CDR_SCREEN_B_NUMBER_INITIAL_LIST;//������к����ǰ׺�����LIST�����ŷָ�)�У���ô������CDR����Ҫ��Ϊ�˳�������

bool bIMEIOutput;//�Ƿ����IMEI����ͳ���ļ�
string workmode;//����ģʽ
int FileBatchNum;//ÿ�δ�����ļ�����s��Ҫ���ڴ治������ٶ��������Է����ε���CDR

vector<string> itemlist;//�ֶ�λ���б�
vector<string> filelist;//Ҫ�����CDR�ļ��б�
vector<string> tacstatfilelist;//tac������ļ���
string CDRDirectory;//Ҫ�����CDR�ļ����ڵ��ļ���
string OutputDirectory;//��������ͳ���ļ���ŵ�Ŀ¼
string CELLFILE;//cell���͵��ļ�
string TACFILE;//tac���͵��ļ�

vector<TAC_NAME> taclist;//TAC��Ӧ��Ʒ�ƣ��ͺź�����
vector<CELL_TYPE> celltypelist;//CELL��Ӧ������

vector<vector<CDR>> cdr;//�ļ���ȡCDR���ļ��洢
vector<recordp> rp;//rpָ�룬Ϊ��ʹ�̵߳Ĵ���cdr��Ŀ��ͬ
vector<vector<vector<IMEI_CDR_Statistic>>> imeicdrfile;//���߳�ƽ���ֶ�ͳ��imei��cdr
vector<vector<vector<IMEI_CDR_Statistic>>> taccdrfile;//������õ�imeicdrfile���ڸ��Ե��߳������tac�ϲ�
vector<vector<IMEI_CDR_Statistic>> imeistat;//������õ�imeicdrfile�в�ͬ���߳�fn�ϲ�����imeistat
vector<vector<IMEI_CDR_Statistic>> tacstat;//������õ�taccdrfile�в�ͬ���߳�fn�ϲ�����tacstat
vector<vector<IMEI_CDR_Statistic>> imeistat_cell;//��imeiͳ�ư���cellid�ϲ�
vector<vector<IMEI_CDR_Statistic>> tacstat_timesectioncell;//��tacstat_timesection�в�ͬ��cell�ϲ�����tacstat_timesectioncell
vector<vector<IMEI_CDR_Statistic>> tacstat_timesection;//������õ�tacstat�в�ͬ��TimeSection�ϲ�����tacstat_timesection
//���ַ���ת��Ϊtime_t����
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
//����ģʽѡ��
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
		//��ʼ��IMEIͳ��
		//�����е�IMEI�б�����Ƿ�����ͬ��
		//��ʱ�Ĺ��̣���Ҫ�Ż�
		//��Ϊ�漰��д����������������в�������#pragma omp critical
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
		////���cdr
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
		
		

		//if(_access(OutputDirectory.c_str(),0)==0)//Ϊ���ʾ�ļ��д���,�����κδ���������������½�һ���ļ���
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
		//while(_access(result_combinecelltacfile_name.c_str(),0)!=-1){//�������ĵ����ڣ������ı�ż�1������Ϊ�˱�����ǰ�ļ�����
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
		//		//���imeistat
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
		//		//���imeistat_cell
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
//�����ڸ����߳��з���
bool WorkLoadDistribution(vector<string> fl,string workingdir){	
	taccdrfile.clear();
	taccdrfile.resize(THREADNUM);
	//ÿ�ֵ�tacstat�洢���ļ���
	tacstatfilelist.clear();
	//��ÿ�ֶ�FileBatchNum���ļ����������������---ceil�����ƺ���������������
	int batchnum=(int)(ceil((double)(fl.size()/(FileBatchNum))))+1;
	cout<<"Divide into "<<batchnum<<" Batch"<<endl;
	//��ʼ
	for(int bn=0;bn<batchnum;bn++){
		cdr.clear();
		cdr.resize(fl.size());
		//���ֻҪtac����ô���imeicdrfile,���ߵ�һ������ʱ����ʼ��imeicdrfile
		if(bIMEIOutput==false||bn==0){
			imeicdrfile.clear();
			imeicdrfile.resize(THREADNUM);
			for(int threadn=0;threadn<THREADNUM;threadn++){
				imeicdrfile[threadn].clear();
				imeicdrfile[threadn].resize((int)pow((double)10,HASH_NUM_IMEI+HASH_NUM_CELLID));
			}
		}
		//��ȡ�ļ�,����
		omp_set_num_threads(THREADNUM);
		#pragma omp parallel for
			for(int fn=bn*FileBatchNum;fn<min((bn+1)*FileBatchNum,(int)fl.size());fn++){
				ReadCDRFile(fn,workingdir+"\\"+fl[fn]);
			}
		//��������record���б���ƽ�����������ÿ���߳�
		rp.clear();
		for(int fn=bn*FileBatchNum;fn<min((bn+1)*FileBatchNum,(int)fl.size());fn++){
			for(int j=0;j<cdr[fn].size();j++){
				recordp temp_rp;
				temp_rp.fn=fn;
				temp_rp.rn=j;
				rp.push_back(temp_rp);
			}
		}
		//����ÿ���̵߳�IMEI��TACͳ��
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

		//ÿ�ֽ��������cdr��rp
		cout<<"Batch $"<<bn<<" Start clear CDR vector and record vector"<<endl;
		cdr.clear();
		vector<vector<CDR>>().swap(cdr);
		cout<<"Batch $"<<bn<<" CDR vector is cleared"<<endl;
		cout<<"Batch $"<<bn<<" Start clear Record vector"<<endl;
		rp.clear();
		vector<recordp>().swap(rp);
		cout<<"Batch $"<<bn<<" Record vector is cleared"<<endl;
		//���ֻҪtac����ô���imeicdrfile
		if(bIMEIOutput==false){
			imeicdrfile.clear();
			vector<vector<vector<IMEI_CDR_Statistic>>>().swap(imeicdrfile);
			cout<<"IMEI_CDR_FILE vector is cleared"<<endl;
		}
		
		//��ʼ��tacstat������ļ���
		if(_access(OutputDirectory.c_str(),0)==0)//Ϊ���ʾ�ļ��д���,�����κδ���������������½�һ���ļ���
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

		//����tacstat���ֵ�����ļ���
		string result_combinetacfile_name=OutputDirectory+"\\ToCombineTACstat";
		string result_combinetacfile_name1=OutputDirectory+"\\ToCombineTACstat.csv";
		int i=0;
		char num[64];
		while(_access(result_combinetacfile_name1.c_str(),0)==0){//�������ĵ����ڣ������ı�ż�1������Ϊ�˱�����ǰ�ļ�����
			sprintf_s(num,"%d",i);
			string result_combinetacfile_name_new=result_combinetacfile_name+(string)"_"+(string)num+".csv";
			if(_access(result_combinetacfile_name_new.c_str(),0)!=0){
				result_combinetacfile_name1=result_combinetacfile_name_new;
				break;
			}
			i++;
		}
		//ÿ�ֺ����TAC�ĺϲ������ͷ�taccdrfile
		if(!CombineTAC_Thread()){
			cout<<"Batch $"<<bn<<" TAC combining is not complete due to error"<<endl;
		}
		else{
			cout<<"Batch $"<<bn<<" TAC combining complete!!!"<<endl;
			
			//���taccdrfile
			taccdrfile.clear();
			vector<vector<vector<IMEI_CDR_Statistic>>>().swap(taccdrfile);
			cout<<"TAC_CDR_FILE vector is cleared"<<endl;

			//�Ѿ�������tacstat����ʼmatch tac with brand, name and type
			cout<<"Batch $"<<bn<<" Start Matching TAC with brand, name and type"<<endl;
			MatchTACList();
			//�Ѿ�����tacstat,��ʼmatch cell with celltype
			cout<<"Batch $"<<bn<<" Start Matching Cell with celltype"<<endl;
			MatchCellTypeList();
			//��ʼд�ļ�
			cout<<"Batch $"<<bn<<" Start writing file "<<result_combinetacfile_name1<<endl;
			tacstatfilelist.push_back(result_combinetacfile_name1);
			WriteTACFile(result_combinetacfile_name1);
		}
		
	}

	return true;

}

bool CombineProcess(){
		//����n�ֺ���и���tacstat�ĺϲ����tacstat����timesection��cell���У��ϲ����ͷ�tacstat

		if(CombineTAC_TimeSection()!=true){
			cout<<"TAC with Same TimeSection combining is not complete due to error"<<endl;
		}
		else{
			cout<<"TAC with Same TimeSection combining complete!!!"<<endl;
			
			//���tacstat
			tacstat.clear();
			vector<vector<IMEI_CDR_Statistic>>().swap(tacstat);
			cout<<"TAC_STAT vector is cleared"<<endl;

			string result_filename=OutputDirectory+"\\TACstat_Cell";
			string result_filename1=OutputDirectory+"\\TACstat_Cell.csv";
			int i=0;
			char num[64];
			while(_access(result_filename1.c_str(),0)==0){//�������ĵ����ڣ������ı�ż�1������Ϊ�˱�����ǰ�ļ�����
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

			//���tacstat_timesectioncell
			tacstat_timesection.clear();
			vector<vector<IMEI_CDR_Statistic>>().swap(tacstat_timesection);
			cout<<"TAC_STAT_TIMESECTION vector is cleared"<<endl;


			string result_filename=OutputDirectory+"\\TACstat";
			string result_filename1=OutputDirectory+"\\TACstat.csv";
			int i=0;
			char num[64];
			while(_access(result_filename1.c_str(),0)==0){//�������ĵ����ڣ������ı�ż�1������Ϊ�˱�����ǰ�ļ�����
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

			//���tacstat_timesectioncell
			tacstat_timesectioncell.clear();
			vector<vector<IMEI_CDR_Statistic>>().swap(tacstat_timesectioncell);
			cout<<"TAC_STAT_TIMESECTION_CELL vector is cleared"<<endl;

		}
}
//��ں���
int _tmain(int argc, _TCHAR* argv[])
{
	
	//��ȡ�����ƶ����ļ���
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

