#include"stdafx.h"
#include"FileReadModule.h"
#include<omp.h>

bool isValidCDR(CDR cdr){
		
	for(int i=0;i<cfg.CDR_SCREEN_B_NUMBER_INITIAL_LIST.size();i++){
		if(cdr.B_number.size()>cfg.CDR_SCREEN_B_NUMBER_INITIAL_LIST[i].size()){//因substr不做长度检查，防止出错
			if(cdr.B_number.substr(0,cfg.CDR_SCREEN_B_NUMBER_INITIAL_LIST[i].size())==cfg.CDR_SCREEN_B_NUMBER_INITIAL_LIST[i]){
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
	if((difftime(cdr.call_start_time,cfg.STATISTIC_START_TIME)<0||difftime(cdr.call_start_time,cfg.STATISTIC_END_TIME)>0)){
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
	cfg.filelist.clear();
	cfg.itemlist.clear();
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
			cfg.workmode=trim(str.substr(j,str.length()-j));
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
			cfg.CDRDirectory=trim(str.substr(j,str.length()-j));
		}
		if(str.find("toCombineConfigFile=")!=string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			cfg.toCombineConfigFile=trim(str.substr(j,str.length()-j));
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
			cfg.OutputDirectory=trim(str.substr(j,str.length()-j));
		}
		if(str.find("OutputFilePostFix=")!=string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			cfg.OutputFilePostFix=trim(str.substr(j,str.length()-j));
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
			cfg.TACFILE=trim(str.substr(j,str.length()-j));
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
			cfg.CELLFILE=trim(str.substr(j,str.length()-j));
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
			
			cfg.CDR_SCREEN_B_NUMBER_INITIAL_LIST.clear();
			
			int it=0;//记录当前读取字段的开头
			int jt=0;//记录当前读取字段的结束
			string temp_b_number_initial_list=trim(str.substr(j,str.length()-j));
			while(jt<temp_b_number_initial_list.size()){
				it=jt;//设置当前读取字段的新开头
				while(jt<temp_b_number_initial_list.size()&&temp_b_number_initial_list[jt]!=','){
					jt++;//找寻下一个coma
				}
				if((jt-it)>0){
					cfg.CDR_SCREEN_B_NUMBER_INITIAL_LIST.push_back(temp_b_number_initial_list.substr(it,jt-it));
				}
				else if(jt==it){
					//
				}
				jt++;//越过coma
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
				cfg.bIMEIOutput=true;
			}
			else{
				cfg.bIMEIOutput=false;
			}
		}
		if(str.find("ComputeDistinctIMEI=")!=string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			if(trim(str.substr(j,str.length()-j))=="true"){
				cfg.bComputeDistinctIMEI=true;
			}
			else{
				cfg.bComputeDistinctIMEI=false;
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
			cfg.FileBatchNum=atoi(str.substr(j,str.length()-j).c_str());
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
			cfg.THREADNUM=atoi(str.substr(j,str.length()-j).c_str());
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
			cfg.HASH_NUM_IMEI=atoi(str.substr(j,str.length()-j).c_str());
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
			cfg.HASH_NUM_CELLID=atoi(str.substr(j,str.length()-j).c_str());
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
			cfg.START_HASH_INDEX_IMEI=atoi(str.substr(j,str.length()-j).c_str());
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
			cfg.filelist.push_back(trim(str.substr(j,str.length()-j)));
			continue;
		}
		if(str.find("ITEM=") != string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			cfg.itemlist.push_back(trim(str.substr(j,str.length()-j)));
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
			cfg.SHORTCALL_THRESHOLD_1=atoi(trim(str.substr(j,str.length()-j)).c_str());
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
			cfg.SHORTCALL_THRESHOLD_2=atoi(trim(str.substr(j,str.length()-j)).c_str());
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
			cfg.SHORTCALL_THRESHOLD_3=atoi(trim(str.substr(j,str.length()-j)).c_str());
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
			cfg.STATISTIC_START_TIME=FormatTime(trim(str.substr(j,str.length()-j)).c_str());
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
			cfg.STATISTIC_END_TIME=FormatTime(trim(str.substr(j,str.length()-j)).c_str());
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
				cfg.TIME_SECTION_UNIT=0;
			}
			else if(trim(str.substr(j,str.length()-j)).size()>3){
				if(trim(str.substr(j,str.length()-j)).substr(trim(str.substr(j,str.length()-j)).size()-3,3)=="min"){
					cfg.TIME_SECTION_UNIT=60*atoi(trim(str.substr(j,str.length()-j)).substr(0,trim(str.substr(j,str.length()-j)).size()-3).c_str());
				}
			}
			else{
				cfg.TIME_SECTION_UNIT=0;
			}
			continue;
		}
	}
	fi.close();
	return true;
}
bool ReadToCombineFileList(std::string tocombinefile){
	ifstream fi(tocombinefile.c_str());
	if(!fi){
		cout<<"No ToCombineConfigFile Information!"<<endl;
		return false;
	}
	
	string toCombineDir="";
	cfg.tacstatfilelist.clear();
	
	string str;

	while(getline(fi,str)){
		if(str.find("CombineMode=")!=string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			cfg.combinemode=trim(str.substr(j,str.length()-j));
		}
		if(str.find("ToCombineFileDirectory=")!=string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			toCombineDir=trim(str.substr(j,str.length()-j));
		}
		if(str.find("ToCombineFile=")!=string::npos){
			int j=0;
			while(str[j]!='='){
				j++;
			}
			j++;
			while(str[j]==' '){
				j++;
			}
			cfg.tacstatfilelist.push_back(toCombineDir+"\\"+trim(str.substr(j,str.length()-j)));
		}
	}

	return true;

}
bool ReadTACFile(string tacfile){
	ifstream fi(tacfile.c_str());
	if(!fi){
		cout<<"Reading File "<<tacfile<<" Error!!! "<<endl;
		return false;
	}
	
	taclist.clear();
	string sl;//每一行
	while(getline(fi,sl)){
		TAC_NAME temptn;
		temptn.TAC="";
		temptn.brand="";
		temptn.name="";
		temptn.type="";

		int i=0;//记录当前读取字段的开头
		int j=0;//记录当前读取字段的结束
		while(j<sl.size()&&sl[j]!=','){
			j++;//找寻下一个coma
		}
		if((j-i)>0){
			temptn.TAC=sl.substr(i,j-i);
		}
		j++;//越过coma
		i=j;//设置当前读取字段的新开头
		while(j<sl.size()&&sl[j]!=','){
			j++;//找寻下一个coma
		}
		if((j-i)>0){
			temptn.brand=sl.substr(i,j-i);
		}
		j++;//越过coma
		i=j;//设置当前读取字段的新开头
		while(j<sl.size()&&sl[j]!=','){
			j++;//找寻下一个coma
		}
		if((j-i)>0){
			temptn.name=sl.substr(i,j-i);
		}
		j++;//越过coma
		i=j;//设置当前读取字段的新开头
		j=(int)sl.size();//最后一个字段的长度
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

	for(int k=0;k<celltypelist.size();k++){//初始化所有
		celltypelist[k].cellid=0;
		celltypelist[k].type="";
	}
	string sl;//每一行
	int clist=0;
	while(getline(fi,sl)){

		CELL_TYPE tempct;
		tempct.cellid=0;
		tempct.type="";
		
		int i=0;//记录当前读取字段的开头
		int j=0;//记录当前读取字段的结束
		while(j<sl.size()&&sl[j]!=','){
			j++;//找寻下一个coma
		}
		if((j-i)>0){
			tempct.cellid=atoi(trim(sl.substr(i,j-i)).c_str());
		}
		j++;//越过coma
		i=j;//设置当前读取字段的新开头
		j=(int)sl.size();//最后一个字段的长度
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
		//开始读取指定的文件
	time_t start,end;
	ifstream fi(cdrfile.c_str());
	if(!fi){
		cout<<"Reading File "<<cdrfile<<" Error!!! "<<endl;
		//return false;
	}
	else{
		start=clock();
		
		cdr[fn].clear();
		string sl;//每一行
		while(getline(fi,sl)){
			CDR tempcdr;//临时
			tempcdr.report_time=0;//CDR上报时间
			tempcdr.A_BSSMAP_cause=DEFAULT_CAUSE_VALUE;//主叫释放原因（BSSMAP）
			tempcdr.A_BSSMAP_cause_ext=DEFAULT_CAUSE_VALUE;//TD的主叫释放原因(RANAP)
			tempcdr.A_cell=0;//主叫挂机时所在小区号
			tempcdr.A_sac=0;//主叫挂机时所在的TD小区号
			tempcdr.A_number="";//主叫号码
			tempcdr.A_first_cell=0;//主叫起呼时所在小区号
			tempcdr.A_first_sac=0;//主叫起呼时所在的TD小区号
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
			
			int i=0;//记录当前读取字段的开头
			int j=0;//记录当前读取字段的结束
			while(j<sl.size()){
				i=j;//设置当前读取字段的新开头
				while(j<sl.size()&&sl[j]!=','){
					j++;//找寻下一个coma
				}
				if((j-i)>0){
					readitem.push_back(sl.substr(i,j-i));
				}
				else if(j==i){
					readitem.push_back("empty");
				}
				j++;//越过coma
			}

			for(int k=0;k<cfg.itemlist.size();k++){
				int n=0;//记录=位置
				while(n<cfg.itemlist[k].size()&&cfg.itemlist[k][n]!='='){
					n++;//找寻=
				}
				if(n!=cfg.itemlist[k].size()){
					string item=cfg.itemlist[k].substr(0,n);
					int pos=atoi(trim(cfg.itemlist[k].substr(n+1,cfg.itemlist[k].size()-n-1)).c_str());

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
							if(cfg.TIME_SECTION_UNIT!=0){
								tempcdr.timeSection=(int)ceil(difftime(tempcdr.call_start_time,cfg.STATISTIC_START_TIME)/1000/cfg.TIME_SECTION_UNIT)+1;
								tempcdr.timeSectionStartTime=cfg.STATISTIC_START_TIME+tempcdr.timeSection*1000*cfg.TIME_SECTION_UNIT;
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
				cdr[fn].push_back(tempcdr);//压入cdr[fn]中。
			}
		}
	}
	end=clock();
	cout<<"Reading File "<<cfg.filelist[fn]<<" with "<<cdr[fn].size()<<" Records in "<<difftime(end,start)<<" ms\n";
	return true;
}
//读取tacstatfile到全局变量temptacstat
bool ReadTACSTATFile(string tacstatfile){
	
	temptacstat.clear();
	temptacstat.resize((int)pow((double)10,cfg.HASH_NUM_IMEI+cfg.HASH_NUM_CELLID));

	time_t start,end;
	ifstream fi(tacstatfile.c_str());
	if(!fi){
		cout<<"Reading File "<<tacstatfile<<" Error!!! "<<endl;
		//return false;
	}
	else{
		start=clock();
		string sl;//每一行
		getline(fi,sl);//取第一行xd
		ReadItemList(sl,cfg.itemlist);//读取第一行，存到itemlist里
		while(getline(fi,sl)){

			IMEI_CDR_Statistic tempcdrstat;
			tempcdrstat.IMEI="";
			tempcdrstat.TAC="";
			tempcdrstat.brand="";
			tempcdrstat.name="";
			tempcdrstat.type="";
			tempcdrstat.cellid=0;
			tempcdrstat.celltype="";
			tempcdrstat.network="";
			tempcdrstat.timeSection=0;
//			tempcdrstat.timeSectionStartTime=FormatTime("");
			tempcdrstat.A_call_attempt=0;
			tempcdrstat.A_call_attempt_GSM=0;
			tempcdrstat.A_call_attempt_TD=0;
			tempcdrstat.A_shortcall_1=0;
			tempcdrstat.A_shortcall_2=0;
			tempcdrstat.A_shortcall_3=0;
			tempcdrstat.B_call_attempt=0;
			tempcdrstat.B_call_attempt_GSM=0;
			tempcdrstat.B_call_attempt_TD=0;
			tempcdrstat.B_shortcall_3=0;
			tempcdrstat.B_shortcall_2=0;
			tempcdrstat.B_shortcall_1=0;
			tempcdrstat.A_BSSMAP_Cause.clear();
			tempcdrstat.B_BSSMAP_Cause.clear();
			tempcdrstat.A_RANAP_Cause.clear();
			tempcdrstat.B_RANAP_Cause.clear();
			tempcdrstat.A_DX_Cause_GSM.clear();
			tempcdrstat.A_DX_Cause_TD.clear();
			tempcdrstat.B_DX_Cause_GSM.clear();
			tempcdrstat.B_DX_Cause_TD.clear();
			tempcdrstat.A_BSSMAP_drop=0;
			tempcdrstat.A_RANAP_drop=0;
			tempcdrstat.B_BSSMAP_drop=0;
			tempcdrstat.B_RANAP_drop=0;
			tempcdrstat.A_DX_GSM_block=0;
			tempcdrstat.A_DX_TD_block=0;
			tempcdrstat.B_DX_GSM_block=0;
			tempcdrstat.B_DX_TD_block=0;
			tempcdrstat.A_call_first_cell_connected=0;
			tempcdrstat.A_call_first_cell_connected_GSM=0;
			tempcdrstat.A_call_first_cell_connected_TD=0;
			tempcdrstat.B_call_first_cell_connected=0;
			tempcdrstat.B_call_first_cell_connected_GSM=0;
			tempcdrstat.B_call_first_cell_connected_TD=0;
			tempcdrstat.A_call_last_cell_connected=0;
			tempcdrstat.A_call_last_cell_connected_GSM=0;
			tempcdrstat.A_call_last_cell_connected_TD=0;
			tempcdrstat.B_call_last_cell_connected=0;
			tempcdrstat.B_call_last_cell_connected_GSM=0;
			tempcdrstat.B_call_last_cell_connected_TD=0;

			vector<string> readitem;
			readitem.clear();
			
			int i=0;//记录当前读取字段的开头
			int j=0;//记录当前读取字段的结束
			while(j<sl.size()){
				i=j;//设置当前读取字段的新开头
				while(j<sl.size()&&sl[j]!=','){
					j++;//找寻下一个coma
				}
				if((j-i)>0){
					readitem.push_back(sl.substr(i,j-i));
				}
				else if(j==i){
					readitem.push_back("empty");
				}
				j++;//越过coma
			}

			for(int k=0;k<cfg.itemlist.size();k++){
				int n=0;//记录=位置
				while(n<cfg.itemlist[k].size()&&cfg.itemlist[k][n]!='='){
					n++;//找寻=
				}
				if(n!=cfg.itemlist[k].size()){
					string item=cfg.itemlist[k].substr(0,n);
					int pos=atoi(trim(cfg.itemlist[k].substr(n+1,cfg.itemlist[k].size()-n-1)).c_str());
					if(pos<readitem.size()){
						if(item=="TAC"&&readitem[pos]!="empty"){
							tempcdrstat.TAC=trim(readitem[pos]);
						}
						else if(item=="品牌"&&readitem[pos]!="empty"){
							tempcdrstat.brand=trim(readitem[pos]);
						}
						else if(item=="型号"&&readitem[pos]!="empty"){
							tempcdrstat.name=trim(readitem[pos]);
						}
						else if(item=="类别"&&readitem[pos]!="empty"){
							tempcdrstat.type=trim(readitem[pos]);
						}
						else if(item=="CellID"&&readitem[pos]!="empty"){
							tempcdrstat.cellid=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="小区分类"&&readitem[pos]!="empty"){
							tempcdrstat.celltype=trim(readitem[pos]);
						}
						else if(item=="网络类型"&&readitem[pos]!="empty"){
							tempcdrstat.network=trim(readitem[pos]);
						}
						else if(item=="timeSection"&&readitem[pos]!="empty"){
							tempcdrstat.timeSection=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="timeSectionStartTime"&&readitem[pos]!="empty"){
							tempcdrstat.timeSectionStartTime=FormatTime(trim(readitem[pos]).c_str());
						}
						else if(item=="A_shortcall_1"&&readitem[pos]!="empty"){
							tempcdrstat.A_shortcall_1=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="A_shortcall_2"&&readitem[pos]!="empty"){
							tempcdrstat.A_shortcall_2=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="A_shortcall_3"&&readitem[pos]!="empty"){
							tempcdrstat.A_shortcall_3=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="A_call_attempt"&&readitem[pos]!="empty"){
							tempcdrstat.A_call_attempt=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="A_call_attempt_GSM"&&readitem[pos]!="empty"){
							tempcdrstat.A_call_attempt_GSM=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="A_call_attempt_TD"&&readitem[pos]!="empty"){
							tempcdrstat.A_call_attempt_TD=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="B_shortcall_1"&&readitem[pos]!="empty"){
							tempcdrstat.B_shortcall_1=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="B_shortcall_2"&&readitem[pos]!="empty"){
							tempcdrstat.B_shortcall_2=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="B_shortcall_3"&&readitem[pos]!="empty"){
							tempcdrstat.B_shortcall_3=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="B_call_attempt"&&readitem[pos]!="empty"){
							tempcdrstat.B_call_attempt=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="B_call_attempt_GSM"&&readitem[pos]!="empty"){
							tempcdrstat.B_call_attempt_GSM=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="B_call_attempt_TD"&&readitem[pos]!="empty"){
							tempcdrstat.B_call_attempt_TD=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="A_call_first_cell_connected"&&readitem[pos]!="empty"){
							tempcdrstat.A_call_first_cell_connected=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="A_call_first_cell_connected_GSM"&&readitem[pos]!="empty"){
							tempcdrstat.A_call_first_cell_connected_GSM=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="A_call_first_cell_connected_TD"&&readitem[pos]!="empty"){
							tempcdrstat.A_call_first_cell_connected_TD=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="A_call_last_cell_connected"&&readitem[pos]!="empty"){
							tempcdrstat.A_call_last_cell_connected=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="A_call_last_cell_connected_GSM"&&readitem[pos]!="empty"){
							tempcdrstat.A_call_last_cell_connected_GSM=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="A_call_last_cell_connected_TD"&&readitem[pos]!="empty"){
							tempcdrstat.A_call_last_cell_connected_TD=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="B_call_last_cell_connected"&&readitem[pos]!="empty"){
							tempcdrstat.B_call_last_cell_connected=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="B_call_last_cell_connected_GSM"&&readitem[pos]!="empty"){
							tempcdrstat.B_call_last_cell_connected_GSM=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="B_call_last_cell_connected_TD"&&readitem[pos]!="empty"){
							tempcdrstat.B_call_last_cell_connected_TD=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="B_call_first_cell_connected"&&readitem[pos]!="empty"){
							tempcdrstat.B_call_first_cell_connected=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="B_call_first_cell_connected_GSM"&&readitem[pos]!="empty"){
							tempcdrstat.B_call_first_cell_connected_GSM=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="B_call_first_cell_connected_TD"&&readitem[pos]!="empty"){
							tempcdrstat.B_call_first_cell_connected_TD=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="A_BSSMAP_Cause"&&readitem[pos]!="empty"){
							vector<string> colonlist;
							colonlist.clear();
			
							int i=0;//记录当前读取字段的开头
							int j=0;//记录当前读取字段的结束
							while(j<readitem[pos].size()){
								i=j;//设置当前读取字段的新开头
								while(j<readitem[pos].size()&&readitem[pos][j]!=';'){
									j++;//找寻下一个coma
								}
								if((j-i)>0){
									/*cout<<readitem[pos].substr(i,j-i)<<endl;
									cout<<i<<endl;
									cout<<j<<endl;*/
									colonlist.push_back(readitem[pos].substr(i,j-i));
								}
								else if(j==i){
									colonlist.push_back("0");
								}
								j++;//越过分隔符
							}
							
							for(int k=0;k<colonlist.size();k=k+2){
								CAUSE_TYPE tempcause;
								tempcause.cause_id=atoi(colonlist[k].c_str());
								tempcause.cause_num=atoi(colonlist[k+1].c_str());
								tempcdrstat.A_BSSMAP_Cause.push_back(tempcause);
							}
						}
						else if(item=="A_RANAP_Cause"&&readitem[pos]!="empty"){
							vector<string> colonlist;
							colonlist.clear();
			
							int i=0;//记录当前读取字段的开头
							int j=0;//记录当前读取字段的结束
							while(j<readitem[pos].size()){
								i=j;//设置当前读取字段的新开头
								while(j<readitem[pos].size()&&readitem[pos][j]!=';'){
									j++;//找寻下一个coma
								}
								if((j-i)>0){
									colonlist.push_back(readitem[pos].substr(i,j-i));
								}
								else if(j==i){
									colonlist.push_back("0");
								}
								j++;//越过分隔符
							}

							for(int k=0;k<colonlist.size();k=k+2){
								CAUSE_TYPE tempcause;
								tempcause.cause_id=atoi(colonlist[k].c_str());
								tempcause.cause_num=atoi(colonlist[k+1].c_str());
								tempcdrstat.A_RANAP_Cause.push_back(tempcause);
							}
						}
						else if(item=="B_BSSMAP_Cause"&&readitem[pos]!="empty"){
							vector<string> colonlist;
							colonlist.clear();
			
							int i=0;//记录当前读取字段的开头
							int j=0;//记录当前读取字段的结束
							while(j<readitem[pos].size()){
								i=j;//设置当前读取字段的新开头
								while(j<readitem[pos].size()&&readitem[pos][j]!=';'){
									j++;//找寻下一个coma
								}
								if((j-i)>0){
									colonlist.push_back(readitem[pos].substr(i,j-i));
								}
								else if(j==i){
									colonlist.push_back("0");
								}
								j++;//越过分隔符
							}

							for(int k=0;k<colonlist.size();k=k+2){
								CAUSE_TYPE tempcause;
								tempcause.cause_id=atoi(colonlist[k].c_str());
								tempcause.cause_num=atoi(colonlist[k+1].c_str());
								tempcdrstat.B_BSSMAP_Cause.push_back(tempcause);
							}
						}
						else if(item=="B_RANAP_Cause"&&readitem[pos]!="empty"){
							vector<string> colonlist;
							colonlist.clear();
			
							int i=0;//记录当前读取字段的开头
							int j=0;//记录当前读取字段的结束
							while(j<readitem[pos].size()){
								i=j;//设置当前读取字段的新开头
								while(j<readitem[pos].size()&&readitem[pos][j]!=';'){
									j++;//找寻下一个coma
								}
								if((j-i)>0){
									colonlist.push_back(readitem[pos].substr(i,j-i));
								}
								else if(j==i){
									colonlist.push_back("0");
								}
								j++;//越过分隔符
							}

							for(int k=0;k<colonlist.size();k=k+2){
								CAUSE_TYPE tempcause;
								tempcause.cause_id=atoi(colonlist[k].c_str());
								tempcause.cause_num=atoi(colonlist[k+1].c_str());
								tempcdrstat.B_RANAP_Cause.push_back(tempcause);
							}
						}
						else if(item=="A_DX_Cause_GSM"&&readitem[pos]!="empty"){
							vector<string> colonlist;
							colonlist.clear();
			
							int i=0;//记录当前读取字段的开头
							int j=0;//记录当前读取字段的结束
							while(j<readitem[pos].size()){
								i=j;//设置当前读取字段的新开头
								while(j<readitem[pos].size()&&readitem[pos][j]!=';'){
									j++;//找寻下一个coma
								}
								if((j-i)>0){
									colonlist.push_back(readitem[pos].substr(i,j-i));
								}
								else if(j==i){
									colonlist.push_back("0");
								}
								j++;//越过分隔符
							}

							for(int k=0;k<colonlist.size();k=k+2){
								CAUSE_TYPE tempcause;
								tempcause.cause_id=atoi(colonlist[k].c_str());
								tempcause.cause_num=atoi(colonlist[k+1].c_str());
								tempcdrstat.A_DX_Cause_GSM.push_back(tempcause);
							}
						}
						else if(item=="A_DX_Cause_TD"&&readitem[pos]!="empty"){
							vector<string> colonlist;
							colonlist.clear();
			
							int i=0;//记录当前读取字段的开头
							int j=0;//记录当前读取字段的结束
							while(j<readitem[pos].size()){
								i=j;//设置当前读取字段的新开头
								while(j<readitem[pos].size()&&readitem[pos][j]!=';'){
									j++;//找寻下一个coma
								}
								if((j-i)>0){
									colonlist.push_back(readitem[pos].substr(i,j-i));
								}
								else if(j==i){
									colonlist.push_back("0");
								}
								j++;//越过分隔符
							}

							for(int k=0;k<colonlist.size();k=k+2){
								CAUSE_TYPE tempcause;
								tempcause.cause_id=atoi(colonlist[k].c_str());
								tempcause.cause_num=atoi(colonlist[k+1].c_str());
								tempcdrstat.A_DX_Cause_TD.push_back(tempcause);
							}
						}
						else if(item=="B_DX_Cause_GSM"&&readitem[pos]!="empty"){
							vector<string> colonlist;
							colonlist.clear();
			
							int i=0;//记录当前读取字段的开头
							int j=0;//记录当前读取字段的结束
							while(j<readitem[pos].size()){
								i=j;//设置当前读取字段的新开头
								while(j<readitem[pos].size()&&readitem[pos][j]!=';'){
									j++;//找寻下一个coma
								}
								if((j-i)>0){
									colonlist.push_back(readitem[pos].substr(i,j-i));
								}
								else if(j==i){
									colonlist.push_back("0");
								}
								j++;//越过分隔符
							}

							for(int k=0;k<colonlist.size();k=k+2){
								CAUSE_TYPE tempcause;
								tempcause.cause_id=atoi(colonlist[k].c_str());
								tempcause.cause_num=atoi(colonlist[k+1].c_str());
								tempcdrstat.B_DX_Cause_GSM.push_back(tempcause);
							}
						}
						else if(item=="B_DX_Cause_TD"&&readitem[pos]!="empty"){
							vector<string> colonlist;
							colonlist.clear();
			
							int i=0;//记录当前读取字段的开头
							int j=0;//记录当前读取字段的结束
							while(j<readitem[pos].size()){
								i=j;//设置当前读取字段的新开头
								while(j<readitem[pos].size()&&readitem[pos][j]!=';'){
									j++;//找寻下一个coma
								}
								if((j-i)>0){
									colonlist.push_back(readitem[pos].substr(i,j-i));
								}
								else if(j==i){
									colonlist.push_back("0");
								}
								j++;//越过分隔符
							}

							for(int k=0;k<colonlist.size();k=k+2){
								CAUSE_TYPE tempcause;
								tempcause.cause_id=atoi(colonlist[k].c_str());
								tempcause.cause_num=atoi(colonlist[k+1].c_str());
								tempcdrstat.B_DX_Cause_TD.push_back(tempcause);
							}
						}
						//else if(item=="A_IMEI_IMSI_GSM"&&readitem[pos]!="empty"){
						//	vector<string> colonlist;
						//	colonlist.clear();
			
						//	int i=0;//记录当前读取字段的开头
						//	int j=0;//记录当前读取字段的结束
						//	while(j<readitem[pos].size()){
						//		i=j;//设置当前读取字段的新开头
						//		while(j<readitem[pos].size()&&readitem[pos][j]!=';'){
						//			j++;//找寻下一个coma
						//		}
						//		if((j-i)>0){
						//			colonlist.push_back(readitem[pos].substr(i,j-i));
						//		}
						//		else if(j==i){
						//			colonlist.push_back("0");
						//		}
						//		j++;//越过分隔符
						//	}

						//	tempcdrstat.A_IMEI_IMSI_GSM.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
						//	for(int k=0;k<colonlist.size();k=k+2){
						//		IMEI_IMSI tempimei;
						//		tempimei.IMEI=trim(colonlist[k]);
						//		tempimei.IMSI=trim(colonlist[k+1]);
						//		int temp_hash_imei=atoi(tempimei.IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
						//		tempcdrstat.A_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempimei);
						//	}
						//}
						//else if(item=="A_IMEI_IMSI_TD"&&readitem[pos]!="empty"){
						//	vector<string> colonlist;
						//	colonlist.clear();
			
						//	int i=0;//记录当前读取字段的开头
						//	int j=0;//记录当前读取字段的结束
						//	while(j<readitem[pos].size()){
						//		i=j;//设置当前读取字段的新开头
						//		while(j<readitem[pos].size()&&readitem[pos][j]!=';'){
						//			j++;//找寻下一个coma
						//		}
						//		if((j-i)>0){
						//			colonlist.push_back(readitem[pos].substr(i,j-i));
						//		}
						//		else if(j==i){
						//			colonlist.push_back("0");
						//		}
						//		j++;//越过分隔符
						//	}
						//	tempcdrstat.A_IMEI_IMSI_TD.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
						//	for(int k=0;k<colonlist.size();k=k+2){
						//		IMEI_IMSI tempimei;
						//		tempimei.IMEI=trim(colonlist[k]);
						//		tempimei.IMSI=trim(colonlist[k+1]);
						//		int temp_hash_imei=atoi(tempimei.IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
						//		tempcdrstat.A_IMEI_IMSI_TD[temp_hash_imei].push_back(tempimei);
						//	}
						//}
						//else if(item=="B_IMEI_IMSI_GSM"&&readitem[pos]!="empty"){
						//	vector<string> colonlist;
						//	colonlist.clear();
			
						//	int i=0;//记录当前读取字段的开头
						//	int j=0;//记录当前读取字段的结束
						//	while(j<readitem[pos].size()){
						//		i=j;//设置当前读取字段的新开头
						//		while(j<readitem[pos].size()&&readitem[pos][j]!=';'){
						//			j++;//找寻下一个coma
						//		}
						//		if((j-i)>0){
						//			colonlist.push_back(readitem[pos].substr(i,j-i));
						//		}
						//		else if(j==i){
						//			colonlist.push_back("0");
						//		}
						//		j++;//越过分隔符
						//	}
						//	tempcdrstat.B_IMEI_IMSI_GSM.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
						//	for(int k=0;k<colonlist.size();k=k+2){
						//		IMEI_IMSI tempimei;
						//		tempimei.IMEI=trim(colonlist[k]);
						//		tempimei.IMSI=trim(colonlist[k+1]);
						//		int temp_hash_imei=atoi(tempimei.IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
						//		tempcdrstat.B_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempimei);
						//	}
						//}
						//else if(item=="B_IMEI_IMSI_TD"&&readitem[pos]!="empty"){
						//	vector<string> colonlist;
						//	colonlist.clear();
			
						//	int i=0;//记录当前读取字段的开头
						//	int j=0;//记录当前读取字段的结束
						//	while(j<readitem[pos].size()){
						//		i=j;//设置当前读取字段的新开头
						//		while(j<readitem[pos].size()&&readitem[pos][j]!=';'){
						//			j++;//找寻下一个coma
						//		}
						//		if((j-i)>0){
						//			colonlist.push_back(readitem[pos].substr(i,j-i));
						//		}
						//		else if(j==i){
						//			colonlist.push_back("0");
						//		}
						//		j++;//越过分隔符
						//	}
						//	tempcdrstat.B_IMEI_IMSI_TD.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
						//	for(int k=0;k<colonlist.size();k=k+2){
						//		IMEI_IMSI tempimei;
						//		tempimei.IMEI=trim(colonlist[k]);
						//		tempimei.IMSI=trim(colonlist[k+1]);
						//		int temp_hash_imei=atoi(tempimei.IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
						//		tempcdrstat.B_IMEI_IMSI_TD[temp_hash_imei].push_back(tempimei);
						//	}
						//}
					}
				}			
			}
			
			int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(tempcdrstat.TAC.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+tempcdrstat.cellid%((int)pow((double)10,cfg.HASH_NUM_CELLID));
			
			temptacstat[temp_hash].push_back(tempcdrstat);
		}
	}
	
	end=clock();
	cout<<"Reading TAC statistic File "<<tacstatfile<<" in "<<difftime(end,start)<<"ms"<<endl;
	return true;
}
