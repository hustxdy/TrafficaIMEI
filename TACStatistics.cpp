#include"stdafx.h"
#include"TACStatistic.h"
#include<omp.h>

//从计算好的imeicdrfile中根据TAC合并生成taccdrfile
bool ComputeTACStatistic(int fn){
	cout<<"Start Compute TAC Statistics of Thread#"<<fn<<endl;
	time_t start,end;
	start=clock();
	//hash tac用后四位
	taccdrfile[fn].clear();
	taccdrfile[fn].resize((int)pow((double)10,HASH_NUM_IMEI+HASH_NUM_CELLID));

	for(int hn=0;hn<imeicdrfile[fn].size();hn++){
		
		for(int cr=0;cr<imeicdrfile[fn][hn].size();cr++){
			//查询是否已经有相应的TAC记录
			
			bool isExistTAC=false;
			int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(imeicdrfile[fn][hn][cr].IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+imeicdrfile[fn][hn][cr].cellid%((int)pow((double)10,HASH_NUM_CELLID));

			for(int i=0;i<taccdrfile[fn][temp_hash].size();i++){
				if(taccdrfile[fn][temp_hash][i].TAC==imeicdrfile[fn][hn][cr].TAC&&taccdrfile[fn][temp_hash][i].cellid==imeicdrfile[fn][hn][cr].cellid&&taccdrfile[fn][temp_hash][i].network==imeicdrfile[fn][hn][cr].network){
					isExistTAC=true;
					taccdrfile[fn][temp_hash][i].A_cause0+=imeicdrfile[fn][hn][cr].A_cause0;
					taccdrfile[fn][temp_hash][i].A_cause1+=imeicdrfile[fn][hn][cr].A_cause1;
					taccdrfile[fn][temp_hash][i].A_cause20+=imeicdrfile[fn][hn][cr].A_cause20;
					taccdrfile[fn][temp_hash][i].A_cause60+=imeicdrfile[fn][hn][cr].A_cause60;
					taccdrfile[fn][temp_hash][i].B_cause0+=imeicdrfile[fn][hn][cr].B_cause0;
					taccdrfile[fn][temp_hash][i].B_cause1+=imeicdrfile[fn][hn][cr].B_cause1;
					taccdrfile[fn][temp_hash][i].B_cause20+=imeicdrfile[fn][hn][cr].B_cause20;
					taccdrfile[fn][temp_hash][i].B_cause60+=imeicdrfile[fn][hn][cr].B_cause60;
					taccdrfile[fn][temp_hash][i].A_causeGSM+=imeicdrfile[fn][hn][cr].A_causeGSM;
					taccdrfile[fn][temp_hash][i].B_causeGSM+=imeicdrfile[fn][hn][cr].B_causeGSM;
					taccdrfile[fn][temp_hash][i].B_shortcall_1+=imeicdrfile[fn][hn][cr].B_shortcall_1;
					taccdrfile[fn][temp_hash][i].A_shortcall_1+=imeicdrfile[fn][hn][cr].A_shortcall_1;
					taccdrfile[fn][temp_hash][i].B_shortcall_2+=imeicdrfile[fn][hn][cr].B_shortcall_2;
					taccdrfile[fn][temp_hash][i].A_shortcall_2+=imeicdrfile[fn][hn][cr].A_shortcall_2;
					taccdrfile[fn][temp_hash][i].B_shortcall_3+=imeicdrfile[fn][hn][cr].B_shortcall_3;
					taccdrfile[fn][temp_hash][i].A_shortcall_3+=imeicdrfile[fn][hn][cr].A_shortcall_3;
					taccdrfile[fn][temp_hash][i].B_call_attempt+=imeicdrfile[fn][hn][cr].B_call_attempt;
					taccdrfile[fn][temp_hash][i].A_call_attempt+=imeicdrfile[fn][hn][cr].A_call_attempt;
					taccdrfile[fn][temp_hash][i].B_call_attempt_GSM+=imeicdrfile[fn][hn][cr].B_call_attempt_GSM;
					taccdrfile[fn][temp_hash][i].A_call_attempt_GSM+=imeicdrfile[fn][hn][cr].A_call_attempt_GSM;
					taccdrfile[fn][temp_hash][i].A_call_attempt_TD+=imeicdrfile[fn][hn][cr].A_call_attempt_TD;
					taccdrfile[fn][temp_hash][i].B_call_attempt_TD+=imeicdrfile[fn][hn][cr].B_call_attempt_TD;
					taccdrfile[fn][temp_hash][i].A_causeTD+=imeicdrfile[fn][hn][cr].A_causeTD;
					taccdrfile[fn][temp_hash][i].A_causeTD46+=imeicdrfile[fn][hn][cr].A_causeTD46;
					taccdrfile[fn][temp_hash][i].A_causeTD176+=imeicdrfile[fn][hn][cr].A_causeTD176;
					taccdrfile[fn][temp_hash][i].A_causeTD192+=imeicdrfile[fn][hn][cr].A_causeTD192;
					taccdrfile[fn][temp_hash][i].A_causeTD209+=imeicdrfile[fn][hn][cr].A_causeTD209;
					taccdrfile[fn][temp_hash][i].A_causeTD239+=imeicdrfile[fn][hn][cr].A_causeTD239;
					taccdrfile[fn][temp_hash][i].A_causeTDMisc+=imeicdrfile[fn][hn][cr].A_causeTDMisc;
					taccdrfile[fn][temp_hash][i].A_causeTDNAS+=imeicdrfile[fn][hn][cr].A_causeTDNAS;
					taccdrfile[fn][temp_hash][i].A_causeTDNonStandard+=imeicdrfile[fn][hn][cr].A_causeTDNonStandard;
					taccdrfile[fn][temp_hash][i].A_causeTDProtocol+=imeicdrfile[fn][hn][cr].A_causeTDProtocol;
					taccdrfile[fn][temp_hash][i].A_causeTDRadioNetwork+=imeicdrfile[fn][hn][cr].A_causeTDRadioNetwork;
					taccdrfile[fn][temp_hash][i].A_causeTDTransport+=imeicdrfile[fn][hn][cr].A_causeTDTransport;
					taccdrfile[fn][temp_hash][i].B_causeTD+=imeicdrfile[fn][hn][cr].B_causeTD;
					taccdrfile[fn][temp_hash][i].B_causeTD46+=imeicdrfile[fn][hn][cr].B_causeTD46;
					taccdrfile[fn][temp_hash][i].B_causeTD176+=imeicdrfile[fn][hn][cr].B_causeTD176;
					taccdrfile[fn][temp_hash][i].B_causeTD192+=imeicdrfile[fn][hn][cr].B_causeTD192;
					taccdrfile[fn][temp_hash][i].B_causeTD209+=imeicdrfile[fn][hn][cr].B_causeTD209;
					taccdrfile[fn][temp_hash][i].B_causeTD239+=imeicdrfile[fn][hn][cr].B_causeTD239;
					taccdrfile[fn][temp_hash][i].B_causeTDMisc+=imeicdrfile[fn][hn][cr].B_causeTDMisc;
					taccdrfile[fn][temp_hash][i].B_causeTDNAS+=imeicdrfile[fn][hn][cr].B_causeTDNAS;
					taccdrfile[fn][temp_hash][i].B_causeTDNonStandard+=imeicdrfile[fn][hn][cr].B_causeTDNonStandard;
					taccdrfile[fn][temp_hash][i].B_causeTDProtocol+=imeicdrfile[fn][hn][cr].B_causeTDProtocol;
					taccdrfile[fn][temp_hash][i].B_causeTDRadioNetwork+=imeicdrfile[fn][hn][cr].B_causeTDRadioNetwork;
					taccdrfile[fn][temp_hash][i].B_causeTDTransport+=imeicdrfile[fn][hn][cr].B_causeTDTransport;
					//taccdrfile[fn][temp_hash][i].A_call_not_connected+=imeicdrfile[fn][hn][cr].A_call_not_connected;
					//taccdrfile[fn][temp_hash][i].B_call_not_connected+=imeicdrfile[fn][hn][cr].B_call_not_connected;
					break;
				}
			}
			if(isExistTAC==false){
				//如果没有的话，增加
				IMEI_CDR_Statistic tempimei;
				tempimei.IMEI="";
				tempimei.TAC=imeicdrfile[fn][hn][cr].TAC;
				tempimei.cellid=imeicdrfile[fn][hn][cr].cellid;
				tempimei.network=imeicdrfile[fn][hn][cr].network;
				tempimei.A_cause0=imeicdrfile[fn][hn][cr].A_cause0;
				tempimei.A_cause1=imeicdrfile[fn][hn][cr].A_cause1;
				tempimei.A_cause20=imeicdrfile[fn][hn][cr].A_cause20;
				tempimei.A_cause60=imeicdrfile[fn][hn][cr].A_cause60;
				tempimei.B_cause0=imeicdrfile[fn][hn][cr].B_cause0;
				tempimei.B_cause1=imeicdrfile[fn][hn][cr].B_cause1;
				tempimei.B_cause20=imeicdrfile[fn][hn][cr].B_cause20;
				tempimei.B_cause60=imeicdrfile[fn][hn][cr].B_cause60;
				tempimei.A_causeGSM=imeicdrfile[fn][hn][cr].A_causeGSM;
				tempimei.B_causeGSM=imeicdrfile[fn][hn][cr].B_causeGSM;
				tempimei.A_shortcall_1=imeicdrfile[fn][hn][cr].A_shortcall_1;
				tempimei.B_shortcall_1=imeicdrfile[fn][hn][cr].B_shortcall_1;
				tempimei.A_shortcall_2=imeicdrfile[fn][hn][cr].A_shortcall_2;
				tempimei.B_shortcall_2=imeicdrfile[fn][hn][cr].B_shortcall_2;
				tempimei.A_shortcall_3=imeicdrfile[fn][hn][cr].A_shortcall_3;
				tempimei.B_shortcall_3=imeicdrfile[fn][hn][cr].B_shortcall_3;
				tempimei.A_call_attempt=imeicdrfile[fn][hn][cr].A_call_attempt;
				tempimei.B_call_attempt=imeicdrfile[fn][hn][cr].B_call_attempt;
				tempimei.B_call_attempt_GSM=imeicdrfile[fn][hn][cr].B_call_attempt_GSM;
				tempimei.A_call_attempt_GSM=imeicdrfile[fn][hn][cr].A_call_attempt_GSM;
				tempimei.A_call_attempt_TD=imeicdrfile[fn][hn][cr].A_call_attempt_TD;
				tempimei.B_call_attempt_TD=imeicdrfile[fn][hn][cr].B_call_attempt_TD;
				tempimei.A_causeTD=imeicdrfile[fn][hn][cr].A_causeTD;
				tempimei.A_causeTD46=imeicdrfile[fn][hn][cr].A_causeTD46;
				tempimei.A_causeTD176=imeicdrfile[fn][hn][cr].A_causeTD176;
				tempimei.A_causeTD192=imeicdrfile[fn][hn][cr].A_causeTD192;
				tempimei.A_causeTD209=imeicdrfile[fn][hn][cr].A_causeTD209;
				tempimei.A_causeTD239=imeicdrfile[fn][hn][cr].A_causeTD239;
				tempimei.A_causeTDMisc=imeicdrfile[fn][hn][cr].A_causeTDMisc;
				tempimei.A_causeTDNAS=imeicdrfile[fn][hn][cr].A_causeTDNAS;
				tempimei.A_causeTDNonStandard=imeicdrfile[fn][hn][cr].A_causeTDNonStandard;
				tempimei.A_causeTDProtocol=imeicdrfile[fn][hn][cr].A_causeTDProtocol;
				tempimei.A_causeTDRadioNetwork=imeicdrfile[fn][hn][cr].A_causeTDRadioNetwork;
				tempimei.A_causeTDTransport=imeicdrfile[fn][hn][cr].A_causeTDTransport;
				tempimei.B_causeTD=imeicdrfile[fn][hn][cr].B_causeTD;
				tempimei.B_causeTD46=imeicdrfile[fn][hn][cr].B_causeTD46;
				tempimei.B_causeTD176=imeicdrfile[fn][hn][cr].B_causeTD176;
				tempimei.B_causeTD192=imeicdrfile[fn][hn][cr].B_causeTD192;
				tempimei.B_causeTD209=imeicdrfile[fn][hn][cr].B_causeTD209;
				tempimei.B_causeTD239=imeicdrfile[fn][hn][cr].B_causeTD239;
				tempimei.B_causeTDMisc=imeicdrfile[fn][hn][cr].B_causeTDMisc;
				tempimei.B_causeTDNAS=imeicdrfile[fn][hn][cr].B_causeTDNAS;
				tempimei.B_causeTDNonStandard=imeicdrfile[fn][hn][cr].B_causeTDNonStandard;
				tempimei.B_causeTDProtocol=imeicdrfile[fn][hn][cr].B_causeTDProtocol;
				tempimei.B_causeTDRadioNetwork=imeicdrfile[fn][hn][cr].B_causeTDRadioNetwork;
				tempimei.B_causeTDTransport=imeicdrfile[fn][hn][cr].B_causeTDTransport;
				//tempimei.A_call_not_connected=imeicdrfile[fn][hn][cr].A_call_not_connected;
				//tempimei.B_call_not_connected=imeicdrfile[fn][hn][cr].B_call_not_connected;
			
				taccdrfile[fn][temp_hash].push_back(tempimei);
			}
		}
	}
	end=clock();
	cout<<"Compute Thread#"<<fn<<" TAC statistic in "<<difftime(end,start)<<" ms\n";
	return true;
}
//将计算好的taccdrfile中不同的线程fn合并生成tacstat
bool CombineTAC_Thread(){
	tacstat.clear();
	//hash tac用后四位
	tacstat.clear();
	tacstat.resize((int)pow((double)10,HASH_NUM_IMEI+HASH_NUM_CELLID));
	
	time_t start,end;
	
	for(int fn=0;fn<THREADNUM;fn++){
		start=clock();
		int hsize=0;
		for(int hn=0;hn<taccdrfile[fn].size();hn++){
			hsize+=(int)taccdrfile[fn][hn].size();
			for(int cr=0;cr<taccdrfile[fn][hn].size();cr++){
				//cout<<"HASHKEY Num is "<<taccdrfile[fn].size()<<endl;
				//cout<<"HASKKEY"<<hn<<" has "<<taccdrfile[fn][hn].size()<<" records"<<endl;
				//查询是否已经有相应的TAC记录。
				bool isExistTAC=false;
				int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(taccdrfile[fn][hn][cr].TAC.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+taccdrfile[fn][hn][cr].cellid%((int)pow((double)10,HASH_NUM_CELLID));
				//cout<<"temp_hash is "<<temp_hash<<" with IMEI="<<taccdrfile[fn][hn][cr].IMEI<<" and cellid="<<taccdrfile[fn][hn][cr].cellid<<endl;
				
				for(int im=0;im<tacstat[temp_hash].size();im++){
					if(tacstat[temp_hash][im].TAC==taccdrfile[fn][hn][cr].TAC&&tacstat[temp_hash][im].cellid==taccdrfile[fn][hn][cr].cellid&&tacstat[temp_hash][im].network==taccdrfile[fn][hn][cr].network){
						isExistTAC=true;
						tacstat[temp_hash][im].A_cause0+=taccdrfile[fn][hn][cr].A_cause0;
						tacstat[temp_hash][im].A_cause1+=taccdrfile[fn][hn][cr].A_cause1;
						tacstat[temp_hash][im].A_cause20+=taccdrfile[fn][hn][cr].A_cause20;
						tacstat[temp_hash][im].A_cause60+=taccdrfile[fn][hn][cr].A_cause60;
						tacstat[temp_hash][im].B_cause0+=taccdrfile[fn][hn][cr].B_cause0;
						tacstat[temp_hash][im].B_cause1+=taccdrfile[fn][hn][cr].B_cause1;
						tacstat[temp_hash][im].B_cause20+=taccdrfile[fn][hn][cr].B_cause20;
						tacstat[temp_hash][im].B_cause60+=taccdrfile[fn][hn][cr].B_cause60;
						tacstat[temp_hash][im].A_causeGSM+=taccdrfile[fn][hn][cr].A_causeGSM;
						tacstat[temp_hash][im].B_causeGSM+=taccdrfile[fn][hn][cr].B_causeGSM;
						tacstat[temp_hash][im].B_shortcall_1+=taccdrfile[fn][hn][cr].B_shortcall_1;
						tacstat[temp_hash][im].A_shortcall_1+=taccdrfile[fn][hn][cr].A_shortcall_1;
						tacstat[temp_hash][im].B_shortcall_2+=taccdrfile[fn][hn][cr].B_shortcall_2;
						tacstat[temp_hash][im].A_shortcall_2+=taccdrfile[fn][hn][cr].A_shortcall_2;
						tacstat[temp_hash][im].B_shortcall_3+=taccdrfile[fn][hn][cr].B_shortcall_3;
						tacstat[temp_hash][im].A_shortcall_3+=taccdrfile[fn][hn][cr].A_shortcall_3;
						tacstat[temp_hash][im].B_call_attempt+=taccdrfile[fn][hn][cr].B_call_attempt;
						tacstat[temp_hash][im].A_call_attempt+=taccdrfile[fn][hn][cr].A_call_attempt;
//						tacstat[temp_hash][im].A_call_not_connected+=taccdrfile[fn][hn][cr].A_call_not_connected;
//						tacstat[temp_hash][im].B_call_not_connected+=taccdrfile[fn][hn][cr].B_call_not_connected;
						tacstat[temp_hash][im].B_call_attempt_GSM+=taccdrfile[fn][hn][cr].B_call_attempt_GSM;
						tacstat[temp_hash][im].A_call_attempt_GSM+=taccdrfile[fn][hn][cr].A_call_attempt_GSM;
						tacstat[temp_hash][im].A_call_attempt_TD+=taccdrfile[fn][hn][cr].A_call_attempt_TD;
						tacstat[temp_hash][im].B_call_attempt_TD+=taccdrfile[fn][hn][cr].B_call_attempt_TD;
						tacstat[temp_hash][im].A_causeTD+=taccdrfile[fn][hn][cr].A_causeTD;
						tacstat[temp_hash][im].A_causeTD46+=taccdrfile[fn][hn][cr].A_causeTD46;
						tacstat[temp_hash][im].A_causeTD176+=taccdrfile[fn][hn][cr].A_causeTD176;
						tacstat[temp_hash][im].A_causeTD192+=taccdrfile[fn][hn][cr].A_causeTD192;
						tacstat[temp_hash][im].A_causeTD209+=taccdrfile[fn][hn][cr].A_causeTD209;
						tacstat[temp_hash][im].A_causeTD239+=taccdrfile[fn][hn][cr].A_causeTD239;
						tacstat[temp_hash][im].A_causeTDMisc+=taccdrfile[fn][hn][cr].A_causeTDMisc;
						tacstat[temp_hash][im].A_causeTDNAS+=taccdrfile[fn][hn][cr].A_causeTDNAS;
						tacstat[temp_hash][im].A_causeTDNonStandard+=taccdrfile[fn][hn][cr].A_causeTDNonStandard;
						tacstat[temp_hash][im].A_causeTDProtocol+=taccdrfile[fn][hn][cr].A_causeTDProtocol;
						tacstat[temp_hash][im].A_causeTDRadioNetwork+=taccdrfile[fn][hn][cr].A_causeTDRadioNetwork;
						tacstat[temp_hash][im].A_causeTDTransport+=taccdrfile[fn][hn][cr].A_causeTDTransport;
						tacstat[temp_hash][im].B_causeTD+=taccdrfile[fn][hn][cr].B_causeTD;
						tacstat[temp_hash][im].B_causeTD46+=taccdrfile[fn][hn][cr].B_causeTD46;
						tacstat[temp_hash][im].B_causeTD176+=taccdrfile[fn][hn][cr].B_causeTD176;
						tacstat[temp_hash][im].B_causeTD192+=taccdrfile[fn][hn][cr].B_causeTD192;
						tacstat[temp_hash][im].B_causeTD209+=taccdrfile[fn][hn][cr].B_causeTD209;
						tacstat[temp_hash][im].B_causeTD239+=taccdrfile[fn][hn][cr].B_causeTD239;
						tacstat[temp_hash][im].B_causeTDMisc+=taccdrfile[fn][hn][cr].B_causeTDMisc;
						tacstat[temp_hash][im].B_causeTDNAS+=taccdrfile[fn][hn][cr].B_causeTDNAS;
						tacstat[temp_hash][im].B_causeTDNonStandard+=taccdrfile[fn][hn][cr].B_causeTDNonStandard;
						tacstat[temp_hash][im].B_causeTDProtocol+=taccdrfile[fn][hn][cr].B_causeTDProtocol;
						tacstat[temp_hash][im].B_causeTDRadioNetwork+=taccdrfile[fn][hn][cr].B_causeTDRadioNetwork;
						tacstat[temp_hash][im].B_causeTDTransport+=taccdrfile[fn][hn][cr].B_causeTDTransport;
					
						break;
					}
				}
				if(isExistTAC==false){
					//如果没有的话，增加
					IMEI_CDR_Statistic tempimei;
					tempimei.IMEI="";
					tempimei.TAC=taccdrfile[fn][hn][cr].TAC;
					tempimei.cellid=taccdrfile[fn][hn][cr].cellid;
					tempimei.network=taccdrfile[fn][hn][cr].network;
					tempimei.A_cause0=taccdrfile[fn][hn][cr].A_cause0;
					tempimei.A_cause1=taccdrfile[fn][hn][cr].A_cause1;
					tempimei.A_cause20=taccdrfile[fn][hn][cr].A_cause20;
					tempimei.A_cause60=taccdrfile[fn][hn][cr].A_cause60;
					tempimei.B_cause0=taccdrfile[fn][hn][cr].B_cause0;
					tempimei.B_cause1=taccdrfile[fn][hn][cr].B_cause1;
					tempimei.B_cause20=taccdrfile[fn][hn][cr].B_cause20;
					tempimei.B_cause60=taccdrfile[fn][hn][cr].B_cause60;
					tempimei.A_causeGSM=taccdrfile[fn][hn][cr].A_causeGSM;
					tempimei.B_causeGSM=taccdrfile[fn][hn][cr].B_causeGSM;
					tempimei.A_shortcall_1=taccdrfile[fn][hn][cr].A_shortcall_1;
					tempimei.B_shortcall_1=taccdrfile[fn][hn][cr].B_shortcall_1;
					tempimei.A_shortcall_2=taccdrfile[fn][hn][cr].A_shortcall_2;
					tempimei.B_shortcall_2=taccdrfile[fn][hn][cr].B_shortcall_2;
					tempimei.A_shortcall_3=taccdrfile[fn][hn][cr].A_shortcall_3;
					tempimei.B_shortcall_3=taccdrfile[fn][hn][cr].B_shortcall_3;
					tempimei.A_call_attempt=taccdrfile[fn][hn][cr].A_call_attempt;
					tempimei.B_call_attempt=taccdrfile[fn][hn][cr].B_call_attempt;
					tempimei.B_call_attempt_GSM=taccdrfile[fn][hn][cr].B_call_attempt_GSM;
					tempimei.A_call_attempt_GSM=taccdrfile[fn][hn][cr].A_call_attempt_GSM;
					tempimei.A_call_attempt_TD=taccdrfile[fn][hn][cr].A_call_attempt_TD;
					tempimei.B_call_attempt_TD=taccdrfile[fn][hn][cr].B_call_attempt_TD;
					tempimei.A_causeTD=taccdrfile[fn][hn][cr].A_causeTD;
					tempimei.A_causeTD46=taccdrfile[fn][hn][cr].A_causeTD46;
					tempimei.A_causeTD176=taccdrfile[fn][hn][cr].A_causeTD176;
					tempimei.A_causeTD192=taccdrfile[fn][hn][cr].A_causeTD192;
					tempimei.A_causeTD209=taccdrfile[fn][hn][cr].A_causeTD209;
					tempimei.A_causeTD239=taccdrfile[fn][hn][cr].A_causeTD239;
					tempimei.A_causeTDMisc=taccdrfile[fn][hn][cr].A_causeTDMisc;
					tempimei.A_causeTDNAS=taccdrfile[fn][hn][cr].A_causeTDNAS;
					tempimei.A_causeTDNonStandard=taccdrfile[fn][hn][cr].A_causeTDNonStandard;
					tempimei.A_causeTDProtocol=taccdrfile[fn][hn][cr].A_causeTDProtocol;
					tempimei.A_causeTDRadioNetwork=taccdrfile[fn][hn][cr].A_causeTDRadioNetwork;
					tempimei.A_causeTDTransport=taccdrfile[fn][hn][cr].A_causeTDTransport;
					tempimei.B_causeTD=taccdrfile[fn][hn][cr].B_causeTD;
					tempimei.B_causeTD46=taccdrfile[fn][hn][cr].B_causeTD46;
					tempimei.B_causeTD176=taccdrfile[fn][hn][cr].B_causeTD176;
					tempimei.B_causeTD192=taccdrfile[fn][hn][cr].B_causeTD192;
					tempimei.B_causeTD209=taccdrfile[fn][hn][cr].B_causeTD209;
					tempimei.B_causeTD239=taccdrfile[fn][hn][cr].B_causeTD239;
					tempimei.B_causeTDMisc=taccdrfile[fn][hn][cr].B_causeTDMisc;
					tempimei.B_causeTDNAS=taccdrfile[fn][hn][cr].B_causeTDNAS;
					tempimei.B_causeTDNonStandard=taccdrfile[fn][hn][cr].B_causeTDNonStandard;
					tempimei.B_causeTDProtocol=taccdrfile[fn][hn][cr].B_causeTDProtocol;
					tempimei.B_causeTDRadioNetwork=taccdrfile[fn][hn][cr].B_causeTDRadioNetwork;
					tempimei.B_causeTDTransport=taccdrfile[fn][hn][cr].B_causeTDTransport;
					
					tacstat[temp_hash].push_back(tempimei);
				}
				//cout<<"THREAD#"<<fn<<" with HASHKEY"<<hn<<"has processed "<<hsize<<"/"<<taccdrfile[fn][hn].size()<<" records."<<endl;
			}
		}
		end=clock();
		cout<<"Combine TAC statistic of THREAD#"<<fn<<" with "<<hsize<< " Records in "<<difftime(end,start)<<" ms\n";
	}	
	return true;
}
//将计算好的tacstat中不同的TimeSection合并生成tacstat
bool ComputeTAC_TimeSection(){
	
}

//将tacstat和taclist进行join操作
bool MatchTACList(){
	time_t start,end;
	start=clock();
	int hsize=0;
	omp_set_num_threads(THREADNUM);
#pragma omp parallel for reduction(+:hsize)
	for(int i=0;i<tacstat.size();i++){
		hsize+=(int)tacstat[i].size();
		for(int j=0;j<tacstat[i].size();j++){
			for(int k=0;k<taclist.size();k++){
				if(tacstat[i][j].TAC==taclist[k].TAC){
					tacstat[i][j].brand=taclist[k].brand;
					tacstat[i][j].name=taclist[k].name;
					tacstat[i][j].type=taclist[k].type;
				}
			}	
		}
	}
	end=clock();
	cout<<"Match TAC with Brand List with "<<hsize<<" Records in "<<difftime(end,start)<<" ms\n";
	return true;
}
//将tacstat和celltypelist进行join操作
bool MatchCellTypeList(){
	time_t start,end;
	start=clock();
	int hsize=0;
	omp_set_num_threads(THREADNUM);
#pragma omp parallel for reduction(+:hsize)
	for(int i=0;i<tacstat.size();i++){
		hsize+=(int)tacstat[i].size();
		for(int j=0;j<tacstat[i].size();j++){
			for(int k=0;k<celltypelist.size();k++){
				if(tacstat[i][j].cellid==celltypelist[k].cellid){
					tacstat[i][j].celltype=celltypelist[k].type;
				}
			}	
		}
	}
	end=clock();
	cout<<"Match Cell with Cell Type with "<<hsize<<" Records in "<<difftime(end,start)<<" ms\n";
	
return true;
}
//将tacstat中不同的cell合并生成tacstat_cell
bool CombineTAC_Cell(){
	tacstat_cell.clear();
	//hash tac用后四位
	tacstat_cell.clear();
	tacstat_cell.resize((int)pow((double)10,HASH_NUM_IMEI));
	time_t start,end;
	int hsize=0;
	int csize=0;
	start=clock();
	omp_set_num_threads(THREADNUM);
#pragma omp parallel for reduction(+:hsize,csize)		
		for(int hn=0;hn<tacstat.size();hn++){
			hsize+=(int)tacstat[hn].size();
			for(int cr=0;cr<tacstat[hn].size();cr++){
				//查询是否已经有相应的TAC记录。
				bool isExistTAC=false;
				int temp_hash=atoi(tacstat[hn][cr].TAC.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str());
				for(int im=0;im<tacstat_cell[temp_hash].size();im++){
					if(tacstat_cell[temp_hash][im].TAC==tacstat[hn][cr].TAC){
						isExistTAC=true;
						tacstat_cell[temp_hash][im].A_cause0+=tacstat[hn][cr].A_cause0;
						tacstat_cell[temp_hash][im].A_cause1+=tacstat[hn][cr].A_cause1;
						tacstat_cell[temp_hash][im].A_cause20+=tacstat[hn][cr].A_cause20;
						tacstat_cell[temp_hash][im].A_cause60+=tacstat[hn][cr].A_cause60;
						tacstat_cell[temp_hash][im].B_cause0+=tacstat[hn][cr].B_cause0;
						tacstat_cell[temp_hash][im].B_cause1+=tacstat[hn][cr].B_cause1;
						tacstat_cell[temp_hash][im].B_cause20+=tacstat[hn][cr].B_cause20;
						tacstat_cell[temp_hash][im].B_cause60+=tacstat[hn][cr].B_cause60;
						tacstat_cell[temp_hash][im].A_causeGSM+=tacstat[hn][cr].A_causeGSM;
						tacstat_cell[temp_hash][im].B_causeGSM+=tacstat[hn][cr].B_causeGSM;
						tacstat_cell[temp_hash][im].B_shortcall_1+=tacstat[hn][cr].B_shortcall_1;
						tacstat_cell[temp_hash][im].A_shortcall_1+=tacstat[hn][cr].A_shortcall_1;
						tacstat_cell[temp_hash][im].B_shortcall_2+=tacstat[hn][cr].B_shortcall_2;
						tacstat_cell[temp_hash][im].A_shortcall_2+=tacstat[hn][cr].A_shortcall_2;
						tacstat_cell[temp_hash][im].B_shortcall_3+=tacstat[hn][cr].B_shortcall_3;
						tacstat_cell[temp_hash][im].A_shortcall_3+=tacstat[hn][cr].A_shortcall_3;
						tacstat_cell[temp_hash][im].B_call_attempt+=tacstat[hn][cr].B_call_attempt;
						tacstat_cell[temp_hash][im].A_call_attempt+=tacstat[hn][cr].A_call_attempt;
						tacstat_cell[temp_hash][im].B_call_attempt_GSM+=tacstat[hn][cr].B_call_attempt_GSM;
						tacstat_cell[temp_hash][im].A_call_attempt_GSM+=tacstat[hn][cr].A_call_attempt_GSM;
						tacstat_cell[temp_hash][im].A_call_attempt_TD+=tacstat[hn][cr].A_call_attempt_TD;
						tacstat_cell[temp_hash][im].B_call_attempt_TD+=tacstat[hn][cr].B_call_attempt_TD;
						tacstat_cell[temp_hash][im].A_causeTD+=tacstat[hn][cr].A_causeTD;
						tacstat_cell[temp_hash][im].A_causeTD46+=tacstat[hn][cr].A_causeTD46;
						tacstat_cell[temp_hash][im].A_causeTD176+=tacstat[hn][cr].A_causeTD176;
						tacstat_cell[temp_hash][im].A_causeTD192+=tacstat[hn][cr].A_causeTD192;
						tacstat_cell[temp_hash][im].A_causeTD209+=tacstat[hn][cr].A_causeTD209;
						tacstat_cell[temp_hash][im].A_causeTD239+=tacstat[hn][cr].A_causeTD239;
						tacstat_cell[temp_hash][im].A_causeTDMisc+=tacstat[hn][cr].A_causeTDMisc;
						tacstat_cell[temp_hash][im].A_causeTDNAS+=tacstat[hn][cr].A_causeTDNAS;
						tacstat_cell[temp_hash][im].A_causeTDNonStandard+=tacstat[hn][cr].A_causeTDNonStandard;
						tacstat_cell[temp_hash][im].A_causeTDProtocol+=tacstat[hn][cr].A_causeTDProtocol;
						tacstat_cell[temp_hash][im].A_causeTDRadioNetwork+=tacstat[hn][cr].A_causeTDRadioNetwork;
						tacstat_cell[temp_hash][im].A_causeTDTransport+=tacstat[hn][cr].A_causeTDTransport;
						tacstat_cell[temp_hash][im].B_causeTD+=tacstat[hn][cr].B_causeTD;
						tacstat_cell[temp_hash][im].B_causeTD46+=tacstat[hn][cr].B_causeTD46;
						tacstat_cell[temp_hash][im].B_causeTD176+=tacstat[hn][cr].B_causeTD176;
						tacstat_cell[temp_hash][im].B_causeTD192+=tacstat[hn][cr].B_causeTD192;
						tacstat_cell[temp_hash][im].B_causeTD209+=tacstat[hn][cr].B_causeTD209;
						tacstat_cell[temp_hash][im].B_causeTD239+=tacstat[hn][cr].B_causeTD239;
						tacstat_cell[temp_hash][im].B_causeTDMisc+=tacstat[hn][cr].B_causeTDMisc;
						tacstat_cell[temp_hash][im].B_causeTDNAS+=tacstat[hn][cr].B_causeTDNAS;
						tacstat_cell[temp_hash][im].B_causeTDNonStandard+=tacstat[hn][cr].B_causeTDNonStandard;
						tacstat_cell[temp_hash][im].B_causeTDProtocol+=tacstat[hn][cr].B_causeTDProtocol;
						tacstat_cell[temp_hash][im].B_causeTDRadioNetwork+=tacstat[hn][cr].B_causeTDRadioNetwork;
						tacstat_cell[temp_hash][im].B_causeTDTransport+=tacstat[hn][cr].B_causeTDTransport;
						//tacstat_cell[temp_hash][im].A_call_not_connected+=tacstat[hn][cr].A_call_not_connected;
						//tacstat_cell[temp_hash][im].B_call_not_connected+=tacstat[hn][cr].B_call_not_connected;
						break;
					}
				}
				if(isExistTAC==false){
					//如果没有的话，增加
					IMEI_CDR_Statistic tempimei;
					tempimei.IMEI="";
					tempimei.TAC=tacstat[hn][cr].TAC;
					tempimei.brand=tacstat[hn][cr].brand;
					tempimei.type=tacstat[hn][cr].type;
					tempimei.name=tacstat[hn][cr].name;
					tempimei.cellid=tacstat[hn][cr].cellid;
					tempimei.network=tacstat[hn][cr].network;
					tempimei.celltype=tacstat[hn][cr].celltype;
					tempimei.A_cause0=tacstat[hn][cr].A_cause0;
					tempimei.A_cause1=tacstat[hn][cr].A_cause1;
					tempimei.A_cause20=tacstat[hn][cr].A_cause20;
					tempimei.A_cause60=tacstat[hn][cr].A_cause60;
					tempimei.B_cause0=tacstat[hn][cr].B_cause0;
					tempimei.B_cause1=tacstat[hn][cr].B_cause1;
					tempimei.B_cause20=tacstat[hn][cr].B_cause20;
					tempimei.B_cause60=tacstat[hn][cr].B_cause60;
					tempimei.A_causeGSM=tacstat[hn][cr].A_causeGSM;
					tempimei.B_causeGSM=tacstat[hn][cr].B_causeGSM;
					tempimei.A_shortcall_1=tacstat[hn][cr].A_shortcall_1;
					tempimei.B_shortcall_1=tacstat[hn][cr].B_shortcall_1;
					tempimei.A_shortcall_2=tacstat[hn][cr].A_shortcall_2;
					tempimei.B_shortcall_2=tacstat[hn][cr].B_shortcall_2;
					tempimei.A_shortcall_3=tacstat[hn][cr].A_shortcall_3;
					tempimei.B_shortcall_3=tacstat[hn][cr].B_shortcall_3;
					tempimei.A_call_attempt=tacstat[hn][cr].A_call_attempt;
					tempimei.B_call_attempt=tacstat[hn][cr].B_call_attempt;
					tempimei.B_call_attempt_GSM=tacstat[hn][cr].B_call_attempt_GSM;
					tempimei.A_call_attempt_GSM=tacstat[hn][cr].A_call_attempt_GSM;
					tempimei.A_call_attempt_TD=tacstat[hn][cr].A_call_attempt_TD;
					tempimei.B_call_attempt_TD=tacstat[hn][cr].B_call_attempt_TD;
					tempimei.A_causeTD=tacstat[hn][cr].A_causeTD;
					tempimei.A_causeTD46=tacstat[hn][cr].A_causeTD46;
					tempimei.A_causeTD176=tacstat[hn][cr].A_causeTD176;
					tempimei.A_causeTD192=tacstat[hn][cr].A_causeTD192;
					tempimei.A_causeTD209=tacstat[hn][cr].A_causeTD209;
					tempimei.A_causeTD239=tacstat[hn][cr].A_causeTD239;
					tempimei.A_causeTDMisc=tacstat[hn][cr].A_causeTDMisc;
					tempimei.A_causeTDNAS=tacstat[hn][cr].A_causeTDNAS;
					tempimei.A_causeTDNonStandard=tacstat[hn][cr].A_causeTDNonStandard;
					tempimei.A_causeTDProtocol=tacstat[hn][cr].A_causeTDProtocol;
					tempimei.A_causeTDRadioNetwork=tacstat[hn][cr].A_causeTDRadioNetwork;
					tempimei.A_causeTDTransport=tacstat[hn][cr].A_causeTDTransport;
					tempimei.B_causeTD=tacstat[hn][cr].B_causeTD;
					tempimei.B_causeTD46=tacstat[hn][cr].B_causeTD46;
					tempimei.B_causeTD176=tacstat[hn][cr].B_causeTD176;
					tempimei.B_causeTD192=tacstat[hn][cr].B_causeTD192;
					tempimei.B_causeTD209=tacstat[hn][cr].B_causeTD209;
					tempimei.B_causeTD239=tacstat[hn][cr].B_causeTD239;
					tempimei.B_causeTDMisc=tacstat[hn][cr].B_causeTDMisc;
					tempimei.B_causeTDNAS=tacstat[hn][cr].B_causeTDNAS;
					tempimei.B_causeTDNonStandard=tacstat[hn][cr].B_causeTDNonStandard;
					tempimei.B_causeTDProtocol=tacstat[hn][cr].B_causeTDProtocol;
					tempimei.B_causeTDRadioNetwork=tacstat[hn][cr].B_causeTDRadioNetwork;
					tempimei.B_causeTDTransport=tacstat[hn][cr].B_causeTDTransport;
					//tempimei.A_call_not_connected=tacstat[hn][cr].A_call_not_connected;
					//tempimei.B_call_not_connected=tacstat[hn][cr].B_call_not_connected;
					csize++;
					tacstat_cell[temp_hash].push_back(tempimei);
				}
			}
		}

	end=clock();
	cout<<"Combine TAC statistic with Cell with "<<hsize<<" Records to "<<csize<<" Records in "<<difftime(end,start)<<"ms"<<endl;
	
	return true;
}
//将不同批次产生的tacstat文件合并成一个tacstat
bool CombineMultiTACStat(vector<string> tacstatfilelist){
	for(int i=0;i<tacstatfilelist.size();i++){
		vector<vector<IMEI_CDR_Statistic>> temptacstat;
		temptacstat.clear();
		
		if(!ReadTACSTATFile(tacstatfilelist[i],temptacstat)){
			cout<<"Read File "<<tacstatfilelist[i]<<" Error."<<endl;
		}


	}
}
//读取tacstatfile
bool ReadTACSTATFile(string tacstatfile, vector<vector<IMEI_CDR_Statistic>>& tacstat_temp){

}
//输出tacstat
bool WriteTACFile_Combine(std::string temp_result_path_name){
	ofstream fo(temp_result_path_name.c_str(),'w');
	if(fo.is_open()==true){
		fo<<"TAC"<<","<<"品牌"<<","<<"型号"<<","<<"类别"<<","<<"CellID"<<","<<"小区类别"<<","<<"网络类别"<<","\
			<<"A_count0"<<","<<"A_count1"<<","\
			<<"A_count20"<<","<<"A_count60"<<","\
			<<"A_countGSM"<<","<<"A_countTD"<<","\
			<<"A_causeTD46"<<","<<"A_causeTD176"<<","<<"A_causeTD192"<<","<<"A_causeTD209"<<","<<"A_causeTD239"<<","\
			<<"A_causeTDMisc"<<","<<"A_causeTDNAS"<<","\
			<<"A_causeTDNonStandard"<<","<<"A_causeTDProtocol"<<","\
			<<"A_causeTDRadioNetwork"<<","<<"A_causeTDTransport"<<","\
			<<"A_shortcall_1"<<","<<"A_shortcall_2"<<","<<"A_shortcall_3"<<","\
			<<"A_call_attempt"<<","<<"A_call_attemp_GSM"<<","<<"A_call_attemp_TD"<<","\
			<<"B_count0"<<","<<"B_count1"<<","\
			<<"B_count20"<<","<<"B_count60"<<","\
			<<"B_countGSM"<<","<<"B_countTD"<<","\
			<<"B_causeTD46"<<","<<"B_causeTD176"<<","<<"B_causeTD192"<<","<<"B_causeTD209"<<","<<"B_causeTD239"<<","\
			<<"B_causeTDMisc"<<","<<"B_causeTDNAS"<<","\
			<<"B_causeTDNonStandard"<<","<<"B_causeTDProtocol"<<","\
			<<"B_causeTDRadioNetwork"<<","<<"B_causeTDTransport"<<","\
			<<"B_shortcall_1"<<","<<"B_shortcall_2"<<","<<"B_shortcall_3"<<","\
			<<"B_call_attempt"<<","<<"A_call_attemp_GSM"<<","<<"A_call_attemp_TD"<<endl;
		for(int hn=0;hn<tacstat.size();hn++){
			for(int i=0;i<tacstat[hn].size();i++){
				fo<<tacstat[hn][i].TAC<<","<<tacstat[hn][i].brand<<","<<tacstat[hn][i].name<<","<<tacstat[hn][i].type<<","\
					<<tacstat[hn][i].cellid<<","<<tacstat[hn][i].celltype<<","<<tacstat[hn][i].network<<","\
					<<tacstat[hn][i].A_cause0<<","<<tacstat[hn][i].A_cause1<<","\
					<<tacstat[hn][i].A_cause20<<","<<tacstat[hn][i].A_cause60<<","\
					<<tacstat[hn][i].A_causeGSM<<","<<tacstat[hn][i].A_causeTD<<","\
					<<tacstat[hn][i].A_causeTD46<<","<<tacstat[hn][i].A_causeTD176<<","<<tacstat[hn][i].A_causeTD192<<","<<tacstat[hn][i].A_causeTD209<<","<<tacstat[hn][i].A_causeTD239<<","\
					<<tacstat[hn][i].A_causeTDMisc<<","<<tacstat[hn][i].A_causeTDNAS<<","\
					<<tacstat[hn][i].A_causeTDNonStandard<<","<<tacstat[hn][i].A_causeTDProtocol<<","\
					<<tacstat[hn][i].A_causeTDRadioNetwork<<","<<tacstat[hn][i].A_causeTDTransport<<","\
					<<tacstat[hn][i].A_shortcall_1<<","<<tacstat[hn][i].A_shortcall_2<<","<<tacstat[hn][i].A_shortcall_3<<","\
					<<tacstat[hn][i].A_call_attempt<<","<<tacstat[hn][i].A_call_attempt_GSM<<","<<tacstat[hn][i].A_call_attempt_TD<<","\
					<<tacstat[hn][i].B_cause0<<","<<tacstat[hn][i].B_cause1<<","\
					<<tacstat[hn][i].B_cause20<<","<<tacstat[hn][i].B_cause60<<","\
					<<tacstat[hn][i].B_causeGSM<<","<<tacstat[hn][i].B_causeTD<<","\
					<<tacstat[hn][i].B_causeTD46<<","<<tacstat[hn][i].B_causeTD176<<","<<tacstat[hn][i].B_causeTD192<<","<<tacstat[hn][i].B_causeTD209<<","<<tacstat[hn][i].B_causeTD239<<","\
					<<tacstat[hn][i].B_causeTDMisc<<","<<tacstat[hn][i].B_causeTDNAS<<","\
					<<tacstat[hn][i].B_causeTDNonStandard<<","<<tacstat[hn][i].B_causeTDProtocol<<","\
					<<tacstat[hn][i].B_causeTDRadioNetwork<<","<<tacstat[hn][i].B_causeTDTransport<<","\
					<<tacstat[hn][i].B_shortcall_1<<","<<tacstat[hn][i].B_shortcall_2<<","<<tacstat[hn][i].B_shortcall_3<<","\
					<<tacstat[hn][i].B_call_attempt<<","<<tacstat[hn][i].B_call_attempt_GSM<<","<<tacstat[hn][i].B_call_attempt_TD<<endl;
			}
		}
	}
	fo.close();
	return true;
}
//输出tacstat_cell
bool WriteTACFile_CombineCell(std::string temp_result_path_name){
	ofstream fo(temp_result_path_name.c_str(),'w');
	if(fo.is_open()==true){
		fo<<"TAC"<<","<<"品牌"<<","<<"型号"<<","<<"类别"<<","\
			<<"A_count0"<<","<<"A_count1"<<","\
			<<"A_count20"<<","<<"A_count60"<<","\
			<<"A_countGSM"<<","<<"A_countTD"<<","\
			<<"A_causeTD46"<<","<<"A_causeTD176"<<","<<"A_causeTD192"<<","<<"A_causeTD209"<<","<<"A_causeTD239"<<","\
			<<"A_causeTDMisc"<<","<<"A_causeTDNAS"<<","\
			<<"A_causeTDNonStandard"<<","<<"A_causeTDProtocol"<<","\
			<<"A_causeTDRadioNetwork"<<","<<"A_causeTDTransport"<<","\
			<<"A_shortcall_1"<<","<<"A_shortcall_2"<<","<<"A_shortcall_3"<<","\
			<<"A_call_attempt"<<","<<"A_call_attemp_GSM"<<","<<"A_call_attemp_TD"<<","\
			<<"B_count0"<<","<<"B_count1"<<","\
			<<"B_count20"<<","<<"B_count60"<<","\
			<<"B_countGSM"<<","<<"B_countTD"<<","\
			<<"B_causeTD46"<<","<<"B_causeTD176"<<","<<"B_causeTD192"<<","<<"B_causeTD209"<<","<<"B_causeTD239"<<","\
			<<"B_causeTDMisc"<<","<<"B_causeTDNAS"<<","\
			<<"B_causeTDNonStandard"<<","<<"B_causeTDProtocol"<<","\
			<<"B_causeTDRadioNetwork"<<","<<"B_causeTDTransport"<<","\
			<<"B_shortcall_1"<<","<<"B_shortcall_2"<<","<<"B_shortcall_3"<<","\
			<<"B_call_attempt"<<","<<"B_call_attemp_GSM"<<","<<"B_call_attemp_TD"<<endl;
		for(int hn=0;hn<tacstat_cell.size();hn++){
			for(int i=0;i<tacstat_cell[hn].size();i++){
				fo<<tacstat_cell[hn][i].TAC<<","<<tacstat_cell[hn][i].brand<<","<<tacstat_cell[hn][i].name<<","<<tacstat_cell[hn][i].type<<","\
					<<tacstat_cell[hn][i].A_cause0<<","<<tacstat_cell[hn][i].A_cause1<<","\
					<<tacstat_cell[hn][i].A_cause20<<","<<tacstat_cell[hn][i].A_cause60<<","\
					<<tacstat_cell[hn][i].A_causeGSM<<","<<tacstat_cell[hn][i].A_causeTD<<","\
					<<tacstat_cell[hn][i].A_causeTD46<<","<<tacstat_cell[hn][i].A_causeTD176<<","<<tacstat_cell[hn][i].A_causeTD192<<","<<tacstat_cell[hn][i].A_causeTD209<<","<<tacstat_cell[hn][i].A_causeTD239<<","\
					<<tacstat_cell[hn][i].A_causeTDMisc<<","<<tacstat_cell[hn][i].A_causeTDNAS<<","\
					<<tacstat_cell[hn][i].A_causeTDNonStandard<<","<<tacstat_cell[hn][i].A_causeTDProtocol<<","\
					<<tacstat_cell[hn][i].A_causeTDRadioNetwork<<","<<tacstat_cell[hn][i].A_causeTDTransport<<","\
					<<tacstat_cell[hn][i].A_shortcall_1<<","<<tacstat_cell[hn][i].A_shortcall_2<<","<<tacstat_cell[hn][i].A_shortcall_3<<","\
					<<tacstat_cell[hn][i].A_call_attempt<<","<<tacstat_cell[hn][i].A_call_attempt_GSM<<","<<tacstat_cell[hn][i].A_call_attempt_TD<<","\
					<<tacstat_cell[hn][i].B_cause0<<","<<tacstat_cell[hn][i].B_cause1<<","\
					<<tacstat_cell[hn][i].B_cause20<<","<<tacstat_cell[hn][i].B_cause60<<","\
					<<tacstat_cell[hn][i].B_causeGSM<<","<<tacstat_cell[hn][i].B_causeTD<<","\
					<<tacstat_cell[hn][i].B_causeTD46<<","<<tacstat_cell[hn][i].B_causeTD176<<","<<tacstat_cell[hn][i].B_causeTD192<<","<<tacstat_cell[hn][i].B_causeTD209<<","<<tacstat_cell[hn][i].B_causeTD239<<","\
					<<tacstat_cell[hn][i].B_causeTDMisc<<","<<tacstat_cell[hn][i].B_causeTDNAS<<","\
					<<tacstat_cell[hn][i].B_causeTDNonStandard<<","<<tacstat_cell[hn][i].B_causeTDProtocol<<","\
					<<tacstat_cell[hn][i].B_causeTDRadioNetwork<<","<<tacstat_cell[hn][i].B_causeTDTransport<<","\
					<<tacstat_cell[hn][i].B_shortcall_1<<","<<tacstat_cell[hn][i].B_shortcall_2<<","<<tacstat_cell[hn][i].B_shortcall_3<<","\
					<<tacstat_cell[hn][i].B_call_attempt<<","<<tacstat_cell[hn][i].B_call_attempt_GSM<<","<<tacstat_cell[hn][i].B_call_attempt_TD<<endl;
			}
		}
	}
	fo.close();
	return true;
}