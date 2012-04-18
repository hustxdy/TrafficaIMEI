#include"stdafx.h"
#include"FileReadModule.h"
#include<omp.h>

bool isValidCDR(CDR cdr){
		
	for(int i=0;i<CDR_SCREEN_B_NUMBER_INITIAL_LIST.size();i++){
		if(cdr.B_number.size()>CDR_SCREEN_B_NUMBER_INITIAL_LIST[i].size()){//��substr�������ȼ�飬��ֹ����
			if(cdr.B_number.substr(0,CDR_SCREEN_B_NUMBER_INITIAL_LIST[i].size())==CDR_SCREEN_B_NUMBER_INITIAL_LIST[i]){
				return false;
			}
		}
	}
	/*if(difftime(cdr.signalling_complete_time,cdr.call_start_time)<NOCDR_THRESHOLD){
		return false;
	}*/
	if(cdr.INTER_MSC_HO==1){
		return false;
	}
	if((difftime(cdr.call_start_time,STATISTIC_START_TIME)<0||difftime(cdr.call_start_time,STATISTIC_END_TIME)>0)){
		return false;
	}
	return true;
}
bool ReadConfigFile(std::string configfile){
	//begin read config file 
	ifstream fi(configfile.c_str());
	if(!fi){
		cout<<"No Config Information!"<<endl;
		return false;
	}

	string str;
	filelist.clear();
	itemlist.clear();
	while(getline(fi,str)){
		if(str.find("WorkMode=")!=string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			workmode=trim(str.substr(j,str.length()-j));
		}
		if(str.find("CDRDirectory=")!=string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			CDRDirectory=trim(str.substr(j,str.length()-j));
		}
		if(str.find("OutputDirectory=")!=string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			OutputDirectory=trim(str.substr(j,str.length()-j));
		}
		if(str.find("TACFILE=")!=string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			TACFILE=trim(str.substr(j,str.length()-j));
		}
		if(str.find("CELLFILE=")!=string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			CELLFILE=trim(str.substr(j,str.length()-j));
		}
		if(str.find("CDR_SCREEN_B_NUMBER_INITIAL_LIST=")!=string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			
			CDR_SCREEN_B_NUMBER_INITIAL_LIST.clear();
			
			int it=0;//��¼��ǰ��ȡ�ֶεĿ�ͷ
			int jt=0;//��¼��ǰ��ȡ�ֶεĽ���
			string temp_b_number_initial_list=trim(str.substr(j,str.length()-j));
			while(jt<temp_b_number_initial_list.size()){
				it=jt;//���õ�ǰ��ȡ�ֶε��¿�ͷ
				while(jt<temp_b_number_initial_list.size()&&temp_b_number_initial_list[jt]!=','){
					jt++;//��Ѱ��һ��coma
				}
				if((jt-it)>0){
					CDR_SCREEN_B_NUMBER_INITIAL_LIST.push_back(temp_b_number_initial_list.substr(it,jt-it));
				}
				else if(jt==it){
					//
				}
				jt++;//Խ��coma
			}
		}
		if(str.find("IMEIFILEOUTPUT=")!=string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			if(trim(str.substr(j,str.length()-j))=="true"){
				bIMEIOutput=true;
			}
			else{
				bIMEIOutput=false;
			}
		}
		if(str.find("FileReadBatch=")!=string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			FileBatchNum=atoi(str.substr(j,str.length()-j).c_str());
		}
		if(str.find("THREADNUM=")!=string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			THREADNUM=atoi(str.substr(j,str.length()-j).c_str());
		}
		if(str.find("HASH_NUM_IMEI=")!=string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			HASH_NUM_IMEI=atoi(str.substr(j,str.length()-j).c_str());
		}
		if(str.find("HASH_NUM_CELLID=")!=string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			HASH_NUM_CELLID=atoi(str.substr(j,str.length()-j).c_str());
		}
		if(str.find("START_HASH_INDEX_IMEI=")!=string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			START_HASH_INDEX_IMEI=atoi(str.substr(j,str.length()-j).c_str());
		}
		if(str.find("CDRFile=") != string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			filelist.push_back(trim(str.substr(j,str.length()-j)));
			continue;
		}
		if(str.find("SHORTCALL_THRESHOLD_1=") != string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			SHORTCALL_THRESHOLD_1=atoi(trim(str.substr(j,str.length()-j)).c_str());
			continue;
		}
		if(str.find("SHORTCALL_THRESHOLD_2=") != string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			SHORTCALL_THRESHOLD_2=atoi(trim(str.substr(j,str.length()-j)).c_str());
			continue;
		}
		if(str.find("SHORTCALL_THRESHOLD_3=") != string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			SHORTCALL_THRESHOLD_3=atoi(trim(str.substr(j,str.length()-j)).c_str());
			continue;
		}
		if(str.find("STATISTIC_START_TIME=") != string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			STATISTIC_START_TIME=FormatTime(trim(str.substr(j,str.length()-j)).c_str());
			continue;
		}
		if(str.find("STATISTIC_END_TIME=") != string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			STATISTIC_END_TIME=FormatTime(trim(str.substr(j,str.length()-j)).c_str());
			continue;
		}
		if(str.find("TIME_SECTION_UNIT=") != string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			if(trim(str.substr(j,str.length()-j))=="all"){
				TIME_SECTION_UNIT=0;
			}
			else if(trim(str.substr(j,str.length()-j)).size()>3){
				if(trim(str.substr(j,str.length()-j)).substr(trim(str.substr(j,str.length()-j)).size()-3,3)=="min"){
					TIME_SECTION_UNIT=60*atoi(trim(str.substr(j,str.length()-j)).substr(0,trim(str.substr(j,str.length()-j)).size()-3).c_str());
				}
			}
			else{
				TIME_SECTION_UNIT=0;
			}
			continue;
		}
	}
	fi.close();
	return true;
}
bool ReadTACFile(string tacfile){
	ifstream fi(tacfile.c_str());
	if(!fi){
		cout<<"Reading File "<<tacfile<<" Error!!! "<<endl;
		return false;
	}
	
	taclist.clear();
	string sl;//ÿһ��
	while(getline(fi,sl)){
		TAC_NAME temptn;
		temptn.TAC="";
		temptn.brand="";
		temptn.name="";
		temptn.type="";

		int i=0;//��¼��ǰ��ȡ�ֶεĿ�ͷ
		int j=0;//��¼��ǰ��ȡ�ֶεĽ���
		while(j<sl.size()&&sl[j]!=','){
			j++;//��Ѱ��һ��coma
		}
		if((j-i)>0){
			temptn.TAC=sl.substr(i,j-i);
		}
		j++;//Խ��coma
		i=j;//���õ�ǰ��ȡ�ֶε��¿�ͷ
		while(j<sl.size()&&sl[j]!=','){
			j++;//��Ѱ��һ��coma
		}
		if((j-i)>0){
			temptn.brand=sl.substr(i,j-i);
		}
		j++;//Խ��coma
		i=j;//���õ�ǰ��ȡ�ֶε��¿�ͷ
		while(j<sl.size()&&sl[j]!=','){
			j++;//��Ѱ��һ��coma
		}
		if((j-i)>0){
			temptn.name=sl.substr(i,j-i);
		}
		j++;//Խ��coma
		i=j;//���õ�ǰ��ȡ�ֶε��¿�ͷ
		j=(int)sl.size();//���һ���ֶεĳ���
		if((j-i)>0){
			temptn.type=sl.substr(i,j-i);
		}

		taclist.push_back(temptn);
	}
	cout<<"TAC List has "<<taclist.size()<<" Records"<<endl;
	
	return true;
}
bool ReadCellTypeFile(string celltypefile){
	ifstream fi(celltypefile.c_str());
	if(!fi){
		cout<<"Reading File "<<celltypefile<<" Error!!! "<<endl;
		return false;
	}

	celltypelist.clear();
	celltypelist.resize(CELLIDMAX);

	for(int k=0;k<celltypelist.size();k++){//��ʼ������
		celltypelist[k].cellid=0;
		celltypelist[k].type="";
	}
	string sl;//ÿһ��
	int clist=0;
	while(getline(fi,sl)){

		CELL_TYPE tempct;
		tempct.cellid=0;
		tempct.type="";
		
		int i=0;//��¼��ǰ��ȡ�ֶεĿ�ͷ
		int j=0;//��¼��ǰ��ȡ�ֶεĽ���
		while(j<sl.size()&&sl[j]!=','){
			j++;//��Ѱ��һ��coma
		}
		if((j-i)>0){
			tempct.cellid=atoi(trim(sl.substr(i,j-i)).c_str());
		}
		j++;//Խ��coma
		i=j;//���õ�ǰ��ȡ�ֶε��¿�ͷ
		j=(int)sl.size();//���һ���ֶεĳ���
		if((j-i)>0){
			tempct.type=sl.substr(i,j-i);
		}

		celltypelist[tempct.cellid].cellid=tempct.cellid;
		celltypelist[tempct.cellid].type=tempct.type;
		clist++;
	}
	cout<<"Celltype List has "<<clist<<" Records"<<endl;
	return true;

}
bool ReadCDRFile(int fn,string cdrfile){
		//��ʼ��ȡָ�����ļ�
	time_t start,end;
	ifstream fi(cdrfile.c_str());
	if(!fi){
		cout<<"Reading File "<<filelist[fn]<<" Error!!! "<<endl;
		//return false;
	}
	else{
		start=clock();
		
		cdr[fn].clear();
		string sl;//ÿһ��
		while(getline(fi,sl)){
			CDR tempcdr;//��ʱ
			tempcdr.report_time=0;//CDR�ϱ�ʱ��
			tempcdr.A_BSSMAP_cause=DEFAULT_CAUSE_VALUE;//�����ͷ�ԭ��BSSMAP��
			tempcdr.A_BSSMAP_cause_ext=DEFAULT_CAUSE_VALUE;//TD�������ͷ�ԭ��(RANAP)
			tempcdr.A_cell=0;//���йһ�ʱ����С����
			tempcdr.A_sac=0;//���йһ�ʱ���ڵ�TDС����
			tempcdr.A_number="";//���к���
			tempcdr.A_first_cell=0;//�������ʱ����С����
			tempcdr.A_first_sac=0;//�������ʱ���ڵ�TDС����
			tempcdr.A_IMEI="";
			tempcdr.A_IMSI="";
			tempcdr.B_answered_time=0;
			tempcdr.B_BSSMAP_cause=DEFAULT_CAUSE_VALUE;
			tempcdr.B_BSSMAP_cause_ext=DEFAULT_CAUSE_VALUE;
			tempcdr.B_cell=0;
			tempcdr.B_sac=0;
			tempcdr.B_first_cell=0;
			tempcdr.B_first_sac=0;
			tempcdr.B_IMEI="";
			tempcdr.B_IMSI="";
			tempcdr.B_number="";
			tempcdr.call_start_time=0;
			tempcdr.charging_end_time=0;
			tempcdr.DX_cause=DEFAULT_CAUSE_VALUE;
			tempcdr.paging_time=0;
			tempcdr.signalling_complete_time=0;
			tempcdr.INTER_MSC_HO=-1;

			vector<string> readitem;
			readitem.clear();
			
			int i=0;//��¼��ǰ��ȡ�ֶεĿ�ͷ
			int j=0;//��¼��ǰ��ȡ�ֶεĽ���
			while(j<sl.size()){
				i=j;//���õ�ǰ��ȡ�ֶε��¿�ͷ
				while(j<sl.size()&&sl[j]!=','){
					j++;//��Ѱ��һ��coma
				}
				if((j-i)>0){
					readitem.push_back(sl.substr(i,j-i));
				}
				else if(j==i){
					readitem.push_back("empty");
				}
				j++;//Խ��coma
			}

			for(int k=0;k<itemlist.size();k++){
				int n=0;//��¼=λ��
				while(n<itemlist[k].size()&&itemlist[k][n]!='='){
					n++;//��Ѱ=
				}
				if(n!=itemlist[k].size()){
					string item=itemlist[k].substr(0,n);
					int pos=atoi(trim(itemlist[k].substr(n+1,itemlist[k].size()-n-1)).c_str());

					if(pos<readitem.size()){
						if(item=="REPORT_TIME"&&readitem[pos]!="empty"){
							tempcdr.report_time=FormatTime(trim(readitem[pos]).c_str());
						}
						else if(item=="A_BSSMAP_CAUSE"&&readitem[pos]!="empty"){
							tempcdr.A_BSSMAP_cause=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="A_BSSMAP_CAUSE_EXT"&&readitem[pos]!="empty"){
							tempcdr.A_BSSMAP_cause_ext=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="A_CELL"&&readitem[pos]!="empty"){
							tempcdr.A_cell=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="A_SAC"&&readitem[pos]!="empty"){
							tempcdr.A_sac=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="A_DIRECTION_NUMBER"&&readitem[pos]!="empty"){
							tempcdr.A_number=trim(readitem[pos]);
						}
						else if(item=="A_FIRST_CELL"&&readitem[pos]!="empty"){
							tempcdr.A_first_cell=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="A_FIRST_SAC"&&readitem[pos]!="empty"){
							tempcdr.A_first_sac=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="A_IMEI"&&readitem[pos]!="empty"){
							tempcdr.A_IMEI=trim(readitem[pos]);
						}
						else if(item=="A_IMSI"&&readitem[pos]!="empty"){
							tempcdr.A_IMSI=trim(readitem[pos]);
						}
						else if(item=="B_BSSMAP_CAUSE"&&readitem[pos]!="empty"){
							tempcdr.B_BSSMAP_cause=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="B_BSSMAP_CAUSE_EXT"&&readitem[pos]!="empty"){
							tempcdr.B_BSSMAP_cause_ext=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="B_ANSWERED_TIME"&&readitem[pos]!="empty"){
							tempcdr.B_answered_time=FormatTime(trim(readitem[pos]).c_str());
						}
						else if(item=="B_CELL"&&readitem[pos]!="empty"){
							tempcdr.B_cell=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="B_SAC"&&readitem[pos]!="empty"){
							tempcdr.B_sac=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="B_DIRECTION_NUMBER"&&readitem[pos]!="empty"){
							tempcdr.B_number=trim(readitem[pos]);
						}
						else if(item=="B_FIRST_CELL"&&readitem[pos]!="empty"){
							tempcdr.B_first_cell=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="B_FIRST_SAC"&&readitem[pos]!="empty"){
							tempcdr.B_first_sac=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="B_IMEI"&&readitem[pos]!="empty"){
							tempcdr.B_IMEI=trim(readitem[pos]);
						}
						else if(item=="B_IMSI"&&readitem[pos]!="empty"){
							tempcdr.B_IMSI=trim(readitem[pos]);
						}
						else if(item=="CHARGING_END_TIME"&&readitem[pos]!="empty"){
							tempcdr.charging_end_time=FormatTime(trim(readitem[pos]).c_str());
						}
						else if(item=="DX_CAUSE"&&readitem[pos]!="empty"){
							tempcdr.DX_cause=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="PAGING_TIME"&&readitem[pos]!="empty"){
							tempcdr.paging_time=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="CALL_START_TIME"&&readitem[pos]!="empty"){
							tempcdr.call_start_time=FormatTime(trim(readitem[pos]).c_str());
							if(TIME_SECTION_UNIT!=0){
								tempcdr.timeSection=(int)ceil(difftime(tempcdr.call_start_time,STATISTIC_START_TIME)/1000/TIME_SECTION_UNIT);
							}
							else{
								tempcdr.timeSection=0;
							}
						}
						else if(item=="SIGNALLING_COMPLETE_TIME"&&readitem[pos]!="empty"){
							tempcdr.signalling_complete_time=FormatTime(trim(readitem[pos]).c_str());
						}
						else if(item=="INTER_MSC_HO"&&readitem[pos]!="empty"){
							tempcdr.INTER_MSC_HO=atoi(trim(readitem[pos]).c_str());
						}
					}
				}			
			}
			if(isValidCDR(tempcdr)){
				cdr[fn].push_back(tempcdr);//ѹ��cdr[fn]�С�
			}
		}
	}
	end=clock();
	cout<<"Reading File "<<filelist[fn]<<" with "<<cdr[fn].size()<<" Records in "<<difftime(end,start)<<" ms\n";
	return true;
}

