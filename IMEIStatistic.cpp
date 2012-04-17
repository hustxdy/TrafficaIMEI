#include"stdafx.h"
#include"IMEIStatistic.h"
#include<omp.h>
//�Խ���fn��recordp�б���startnum��endnum��Ӧ��cdr����ͳ�ƣ������imeicdrfile
bool ComputeIMEIStatistic(int fn,int startnum,int endnum){
	time_t start,end;
	start=clock();
	for(int cdrcount=startnum;cdrcount<=endnum;cdrcount++){
		bool isExistAcallendGSM=false;
		bool isExistAcallstartGSM=false;
		bool isExistBcallendGSM=false;
		bool isExistBcallstartGSM=false;
		bool isExistAcallendTD=false;
		bool isExistAcallstartTD=false;
		bool isExistBcallendTD=false;
		bool isExistBcallstartTD=false;
		//�������ڵ�imeicdrfile[fn]����Ϊ�����Ƿ��Ѿ�����Ӧ��IMEI��¼
		
		if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.size()>=MIN_IMEI_LENGTH){

			//���еĽ�����������С��
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell!=0){
				//������2G��
				int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell%((int)pow((double)10,HASH_NUM_CELLID));

				for(int cr=0;cr<imeicdrfile[fn][temp_hash].size();cr++){
					if(imeicdrfile[fn][temp_hash][cr].timeSection==cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection&&imeicdrfile[fn][temp_hash][cr].IMEI==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI&&imeicdrfile[fn][temp_hash][cr].cellid==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell&&imeicdrfile[fn][temp_hash][cr].network=="GSM"){
						isExistAcallendGSM=true;
				
						if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==0){
							imeicdrfile[fn][temp_hash][cr].A_cause0++;
							imeicdrfile[fn][temp_hash][cr].A_causeGSM++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==1){
							imeicdrfile[fn][temp_hash][cr].A_cause1++;
							imeicdrfile[fn][temp_hash][cr].A_causeGSM++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==20){
							imeicdrfile[fn][temp_hash][cr].A_cause20++;
							imeicdrfile[fn][temp_hash][cr].A_causeGSM++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==60){
							imeicdrfile[fn][temp_hash][cr].A_cause60++;
							imeicdrfile[fn][temp_hash][cr].A_causeGSM++;
						}
						break;
					}
				}
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell==0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_sac!=0){
				//������TD��
				int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_sac%((int)pow((double)10,HASH_NUM_CELLID));

				for(int cr=0;cr<imeicdrfile[fn][temp_hash].size();cr++){
					if(imeicdrfile[fn][temp_hash][cr].timeSection==cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection&&imeicdrfile[fn][temp_hash][cr].IMEI==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI&&imeicdrfile[fn][temp_hash][cr].cellid==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_sac&&imeicdrfile[fn][temp_hash][cr].network=="TD"){
						isExistAcallendTD=true;
				
						if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext==46){
							imeicdrfile[fn][temp_hash][cr].A_causeTD46++;
							imeicdrfile[fn][temp_hash][cr].A_causeTDRadioNetwork++;
							imeicdrfile[fn][temp_hash][cr].A_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext!=46&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext>=1&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext<=64){
							imeicdrfile[fn][temp_hash][cr].A_causeTDRadioNetwork++;
							imeicdrfile[fn][temp_hash][cr].A_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext>=257&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext<=512){
							imeicdrfile[fn][temp_hash][cr].A_causeTDRadioNetwork++;
							imeicdrfile[fn][temp_hash][cr].A_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext>=65&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext<=80){
							imeicdrfile[fn][temp_hash][cr].A_causeTDTransport++;
							imeicdrfile[fn][temp_hash][cr].A_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext>=81&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext<=96){
							imeicdrfile[fn][temp_hash][cr].A_causeTDNAS++;
							imeicdrfile[fn][temp_hash][cr].A_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext>=97&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext<=112){
							imeicdrfile[fn][temp_hash][cr].A_causeTDProtocol++;
							imeicdrfile[fn][temp_hash][cr].A_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext>=113&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext<=128){
							imeicdrfile[fn][temp_hash][cr].A_causeTDMisc++;
							imeicdrfile[fn][temp_hash][cr].A_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext==176){
							imeicdrfile[fn][temp_hash][cr].A_causeTD176++;
							imeicdrfile[fn][temp_hash][cr].A_causeTDNonStandard++;
							imeicdrfile[fn][temp_hash][cr].A_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext==192){
							imeicdrfile[fn][temp_hash][cr].A_causeTD192++;
							imeicdrfile[fn][temp_hash][cr].A_causeTDNonStandard++;
							imeicdrfile[fn][temp_hash][cr].A_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext==209){
							imeicdrfile[fn][temp_hash][cr].A_causeTD209++;
							imeicdrfile[fn][temp_hash][cr].A_causeTDNonStandard++;
							imeicdrfile[fn][temp_hash][cr].A_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext==239){
							imeicdrfile[fn][temp_hash][cr].A_causeTD239++;
							imeicdrfile[fn][temp_hash][cr].A_causeTDNonStandard++;
							imeicdrfile[fn][temp_hash][cr].A_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext!=176&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext!=192&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext!=209&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext!=239&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext>=129&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext<=256){
							imeicdrfile[fn][temp_hash][cr].A_causeTDNonStandard++;
							imeicdrfile[fn][temp_hash][cr].A_causeTD++;
						}
						break;
					}
				}
			}
			//���е����С��
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_cell!=0){
				//�����2G��
				int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_cell%((int)pow((double)10,HASH_NUM_CELLID));

				for(int cr=0;cr<imeicdrfile[fn][temp_hash].size();cr++){
					if(imeicdrfile[fn][temp_hash][cr].timeSection==cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection&&imeicdrfile[fn][temp_hash][cr].IMEI==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI&&imeicdrfile[fn][temp_hash][cr].cellid==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_cell&&imeicdrfile[fn][temp_hash][cr].network=="GSM"){
						isExistAcallstartGSM=true;
				
						imeicdrfile[fn][temp_hash][cr].A_call_attempt++;
						imeicdrfile[fn][temp_hash][cr].A_call_attempt_GSM++;
						if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_1){
							imeicdrfile[fn][temp_hash][cr].A_shortcall_1++;
						}
						else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_2){
							imeicdrfile[fn][temp_hash][cr].A_shortcall_2++;
						}
						else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_3){
							imeicdrfile[fn][temp_hash][cr].A_shortcall_3++;
						}

						break;
					}
				}
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_cell==0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_sac!=0){
				//�����TD��
				int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_sac%((int)pow((double)10,HASH_NUM_CELLID));

				for(int cr=0;cr<imeicdrfile[fn][temp_hash].size();cr++){
					if(imeicdrfile[fn][temp_hash][cr].timeSection==cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection&&imeicdrfile[fn][temp_hash][cr].IMEI==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI&&imeicdrfile[fn][temp_hash][cr].cellid==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_sac&&imeicdrfile[fn][temp_hash][cr].network=="TD"){
						isExistAcallstartTD=true;
				
						imeicdrfile[fn][temp_hash][cr].A_call_attempt++;
						imeicdrfile[fn][temp_hash][cr].A_call_attempt_TD++;
						if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_1){
							imeicdrfile[fn][temp_hash][cr].A_shortcall_1++;
						}
						else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_2){
							imeicdrfile[fn][temp_hash][cr].A_shortcall_2++;
						}
						else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_3){
							imeicdrfile[fn][temp_hash][cr].A_shortcall_3++;
						}

						break;
					}
				}
			}
		}
					
		//�������ڵ�imeicdrfile[fn]����Ϊ�����Ƿ��Ѿ�����Ӧ��IMEI��¼
		
		if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.size()>=MIN_IMEI_LENGTH){
			
			//���еĽ���С��
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell!=0){
				//������2GС��
				int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell%((int)pow((double)10,HASH_NUM_CELLID));

				for(int cr=0;cr<imeicdrfile[fn][temp_hash].size();cr++){
					if(imeicdrfile[fn][temp_hash][cr].timeSection==cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection&&imeicdrfile[fn][temp_hash][cr].IMEI==cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI&&imeicdrfile[fn][temp_hash][cr].cellid==cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell&&imeicdrfile[fn][temp_hash][cr].network=="GSM"){
						isExistBcallendGSM=true;
					
						if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause==0){
							imeicdrfile[fn][temp_hash][cr].B_cause0++;
							imeicdrfile[fn][temp_hash][cr].B_causeGSM++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause==1){
							imeicdrfile[fn][temp_hash][cr].B_cause1++;
							imeicdrfile[fn][temp_hash][cr].B_causeGSM++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause==20){
							imeicdrfile[fn][temp_hash][cr].B_cause20++;
							imeicdrfile[fn][temp_hash][cr].B_causeGSM++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause==60){
							imeicdrfile[fn][temp_hash][cr].B_cause60++;
							imeicdrfile[fn][temp_hash][cr].B_causeGSM++;
						}
						break;
					}
				}
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell==0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_sac!=0){
				//������TDС��
				int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_sac%((int)pow((double)10,HASH_NUM_CELLID));

				for(int cr=0;cr<imeicdrfile[fn][temp_hash].size();cr++){
					if(imeicdrfile[fn][temp_hash][cr].timeSection==cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection&&imeicdrfile[fn][temp_hash][cr].IMEI==cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI&&imeicdrfile[fn][temp_hash][cr].cellid==cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_sac&&imeicdrfile[fn][temp_hash][cr].network=="TD"){
						isExistBcallendTD=true;
					
						if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext==46){
							imeicdrfile[fn][temp_hash][cr].B_causeTD46++;
							imeicdrfile[fn][temp_hash][cr].B_causeTDRadioNetwork++;
							imeicdrfile[fn][temp_hash][cr].B_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext!=46&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext>=1&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext<=64){
							imeicdrfile[fn][temp_hash][cr].B_causeTDRadioNetwork++;
							imeicdrfile[fn][temp_hash][cr].B_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext>=257&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext<=512){
							imeicdrfile[fn][temp_hash][cr].B_causeTDRadioNetwork++;
							imeicdrfile[fn][temp_hash][cr].B_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext>=65&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext<=80){
							imeicdrfile[fn][temp_hash][cr].B_causeTDTransport++;
							imeicdrfile[fn][temp_hash][cr].B_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext>=81&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext<=96){
							imeicdrfile[fn][temp_hash][cr].B_causeTDNAS++;
							imeicdrfile[fn][temp_hash][cr].B_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext>=97&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext<=112){
							imeicdrfile[fn][temp_hash][cr].B_causeTDProtocol++;
							imeicdrfile[fn][temp_hash][cr].B_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext>=113&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext<=128){
							imeicdrfile[fn][temp_hash][cr].B_causeTDMisc++;
							imeicdrfile[fn][temp_hash][cr].B_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext==176){
							imeicdrfile[fn][temp_hash][cr].B_causeTD176++;
							imeicdrfile[fn][temp_hash][cr].B_causeTDNonStandard++;
							imeicdrfile[fn][temp_hash][cr].B_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext==192){
							imeicdrfile[fn][temp_hash][cr].B_causeTD192++;
							imeicdrfile[fn][temp_hash][cr].B_causeTDNonStandard++;
							imeicdrfile[fn][temp_hash][cr].B_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext==209){
							imeicdrfile[fn][temp_hash][cr].B_causeTD209++;
							imeicdrfile[fn][temp_hash][cr].B_causeTDNonStandard++;
							imeicdrfile[fn][temp_hash][cr].B_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext==239){
							imeicdrfile[fn][temp_hash][cr].B_causeTD239++;
							imeicdrfile[fn][temp_hash][cr].B_causeTDNonStandard++;
							imeicdrfile[fn][temp_hash][cr].B_causeTD++;
						}
						else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext!=176&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext!=192&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext!=209&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext!=239&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext>=129&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext<=256){
							imeicdrfile[fn][temp_hash][cr].B_causeTDNonStandard++;
							imeicdrfile[fn][temp_hash][cr].B_causeTD++;
						}
						break;
					}
				}
			}
			//���еĽ���С��
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_cell!=0){
				//��GSMС����ʼ����
				int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_cell%((int)pow((double)10,HASH_NUM_CELLID));

				for(int cr=0;cr<imeicdrfile[fn][temp_hash].size();cr++){
					if(imeicdrfile[fn][temp_hash][cr].timeSection==cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection&&imeicdrfile[fn][temp_hash][cr].IMEI==cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI&&imeicdrfile[fn][temp_hash][cr].cellid==cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_cell&&imeicdrfile[fn][temp_hash][cr].network=="GSM"){
						isExistBcallstartGSM=true;
				
						imeicdrfile[fn][temp_hash][cr].B_call_attempt++;
						imeicdrfile[fn][temp_hash][cr].B_call_attempt_GSM++;
						if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_1){
							imeicdrfile[fn][temp_hash][cr].B_shortcall_1++;
						}
						else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_2){
							imeicdrfile[fn][temp_hash][cr].B_shortcall_2++;
						}
						else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_3){
							imeicdrfile[fn][temp_hash][cr].B_shortcall_3++;
						}
						break;
					}
				}
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_cell==0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_sac!=0){
				//��TDС����ʼ����
				int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_sac%((int)pow((double)10,HASH_NUM_CELLID));

				for(int cr=0;cr<imeicdrfile[fn][temp_hash].size();cr++){
					if(imeicdrfile[fn][temp_hash][cr].timeSection==cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection&&imeicdrfile[fn][temp_hash][cr].IMEI==cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI&&imeicdrfile[fn][temp_hash][cr].cellid==cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_sac&&imeicdrfile[fn][temp_hash][cr].network=="TD"){
						isExistBcallstartTD=true;
				
						imeicdrfile[fn][temp_hash][cr].B_call_attempt++;
						imeicdrfile[fn][temp_hash][cr].B_call_attempt_TD++;
						if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_1){
							imeicdrfile[fn][temp_hash][cr].B_shortcall_1++;
						}
						else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_2){
							imeicdrfile[fn][temp_hash][cr].B_shortcall_2++;
						}
						else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_3){
							imeicdrfile[fn][temp_hash][cr].B_shortcall_3++;
						}
						break;
					}
				}
			}
		}
		
		if(isExistAcallendGSM==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell!=0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.size()>=MIN_IMEI_LENGTH){
			//���������н���ʱ��GSMС����ͳ��
			IMEI_CDR_Statistic tempcdrstat;
			tempcdrstat.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI;
			tempcdrstat.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(0,TAC_LENGTH);
			tempcdrstat.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell;
			tempcdrstat.network="GSM";
			tempcdrstat.timeSection=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection;
			tempcdrstat.A_call_attempt=0;
			tempcdrstat.A_call_attempt_GSM=0;
			tempcdrstat.A_call_attempt_TD=0;
			tempcdrstat.A_causeTD=0;
			tempcdrstat.A_causeTDMisc=0;
			tempcdrstat.A_causeTD46=0;
			tempcdrstat.A_causeTD176=0;
			tempcdrstat.A_causeTD192=0;
			tempcdrstat.A_causeTD209=0;
			tempcdrstat.A_causeTD239=0;
			tempcdrstat.A_causeTDNAS=0;
			tempcdrstat.A_causeTDNonStandard=0;
			tempcdrstat.A_causeTDProtocol=0;
			tempcdrstat.A_causeTDRadioNetwork=0;
			tempcdrstat.A_causeTDTransport=0;
			tempcdrstat.A_shortcall_1=0;
			tempcdrstat.A_shortcall_2=0;
			tempcdrstat.A_shortcall_3=0;
			tempcdrstat.B_call_attempt=0;
			tempcdrstat.B_call_attempt_GSM=0;
			tempcdrstat.B_call_attempt_TD=0;
			tempcdrstat.B_cause0=0;
			tempcdrstat.B_cause1=0;
			tempcdrstat.B_cause20=0;
			tempcdrstat.B_cause60=0;
			tempcdrstat.B_causeGSM=0;
			tempcdrstat.B_causeTD=0;
			tempcdrstat.B_causeTD46=0;
			tempcdrstat.B_causeTD176=0;
			tempcdrstat.B_causeTD192=0;
			tempcdrstat.B_causeTD209=0;
			tempcdrstat.B_causeTD239=0;
			tempcdrstat.B_causeTDMisc=0;
			tempcdrstat.B_causeTDNAS=0;
			tempcdrstat.B_causeTDNonStandard=0;
			tempcdrstat.B_causeTDProtocol=0;
			tempcdrstat.B_causeTDRadioNetwork=0;
			tempcdrstat.B_causeTDTransport=0;
			tempcdrstat.B_shortcall_1=0;
			tempcdrstat.B_shortcall_2=0;
			tempcdrstat.B_shortcall_3=0;

			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==0){
				tempcdrstat.A_cause0=1;
				tempcdrstat.A_causeGSM=1;
				tempcdrstat.A_cause1=0;
				tempcdrstat.A_cause20=0;
				tempcdrstat.A_cause60=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==1){
				tempcdrstat.A_cause1=1;
				tempcdrstat.A_causeGSM=1;
				tempcdrstat.A_cause0=0;
				tempcdrstat.A_cause20=0;
				tempcdrstat.A_cause60=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==20){
				tempcdrstat.A_cause20=1;
				tempcdrstat.A_causeGSM=1;
				tempcdrstat.A_cause1=0;
				tempcdrstat.A_cause0=0;
				tempcdrstat.A_cause60=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==60){
				tempcdrstat.A_cause60=1;
				tempcdrstat.A_causeGSM=1;
				tempcdrstat.A_cause1=0;
				tempcdrstat.A_cause20=0;
				tempcdrstat.A_cause0=0;
			}
			else{
				tempcdrstat.A_cause60=0;
				tempcdrstat.A_causeGSM=0;
				tempcdrstat.A_cause1=0;
				tempcdrstat.A_cause20=0;
				tempcdrstat.A_cause0=0;
			}
			
			int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell%((int)pow((double)10,HASH_NUM_CELLID));
			imeicdrfile[fn][temp_hash].push_back(tempcdrstat);
		}

		if(isExistAcallendTD==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_sac!=0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell==0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.size()>=MIN_IMEI_LENGTH){
			//���������н���ʱ��TDС����ͳ��
			IMEI_CDR_Statistic tempcdrstat;
			tempcdrstat.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI;
			tempcdrstat.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(0,TAC_LENGTH);
			tempcdrstat.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_sac;
			tempcdrstat.network="TD";
			tempcdrstat.timeSection=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection;
			tempcdrstat.A_call_attempt=0;
			tempcdrstat.A_call_attempt_GSM=0;
			tempcdrstat.A_call_attempt_TD=0;
			tempcdrstat.A_cause0=0;
			tempcdrstat.A_cause1=0;
			tempcdrstat.A_cause20=0;
			tempcdrstat.A_cause60=0;
			tempcdrstat.A_causeGSM=0;
			tempcdrstat.A_shortcall_1=0;
			tempcdrstat.A_shortcall_2=0;
			tempcdrstat.A_shortcall_3=0;
			tempcdrstat.B_call_attempt=0;
			tempcdrstat.B_call_attempt_GSM=0;
			tempcdrstat.B_call_attempt_TD=0;
			tempcdrstat.B_cause0=0;
			tempcdrstat.B_cause1=0;
			tempcdrstat.B_cause20=0;
			tempcdrstat.B_cause60=0;
			tempcdrstat.B_causeGSM=0;
			tempcdrstat.B_causeTD=0;
			tempcdrstat.B_causeTD46=0;
			tempcdrstat.B_causeTD176=0;
			tempcdrstat.B_causeTD192=0;
			tempcdrstat.B_causeTD209=0;
			tempcdrstat.B_causeTD239=0;
			tempcdrstat.B_causeTDMisc=0;
			tempcdrstat.B_causeTDNAS=0;
			tempcdrstat.B_causeTDNonStandard=0;
			tempcdrstat.B_causeTDProtocol=0;
			tempcdrstat.B_causeTDRadioNetwork=0;
			tempcdrstat.B_causeTDTransport=0;
			tempcdrstat.B_shortcall_1=0;
			tempcdrstat.B_shortcall_2=0;
			tempcdrstat.B_shortcall_3=0;

			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext==46){
				tempcdrstat.A_causeTD46=1;
				tempcdrstat.A_causeTD176=0;
				tempcdrstat.A_causeTD192=0;
				tempcdrstat.A_causeTD209=0;
				tempcdrstat.A_causeTD239=0;
				tempcdrstat.A_causeTDRadioNetwork=1;
				tempcdrstat.A_causeTD=1;
				tempcdrstat.A_causeTDMisc=0;
				tempcdrstat.A_causeTDNAS=0;
				tempcdrstat.A_causeTDNonStandard=0;
				tempcdrstat.A_causeTDProtocol=0;
				tempcdrstat.A_causeTDTransport=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext!=46&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext>=1&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext<=64){
				tempcdrstat.A_causeTDRadioNetwork=1;
				tempcdrstat.A_causeTD=1;
				tempcdrstat.A_causeTD46=0;
				tempcdrstat.A_causeTD176=0;
				tempcdrstat.A_causeTD192=0;
				tempcdrstat.A_causeTD209=0;
				tempcdrstat.A_causeTD239=0;
				tempcdrstat.A_causeTDMisc=0;
				tempcdrstat.A_causeTDNAS=0;
				tempcdrstat.A_causeTDNonStandard=0;
				tempcdrstat.A_causeTDProtocol=0;
				tempcdrstat.A_causeTDTransport=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext>=257&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext<=512){
				tempcdrstat.A_causeTDRadioNetwork=1;
				tempcdrstat.A_causeTD=1;
				tempcdrstat.A_causeTD46=0;
				tempcdrstat.A_causeTD176=0;
				tempcdrstat.A_causeTD192=0;
				tempcdrstat.A_causeTD209=0;
				tempcdrstat.A_causeTD239=0;
				tempcdrstat.A_causeTDMisc=0;
				tempcdrstat.A_causeTDNAS=0;
				tempcdrstat.A_causeTDNonStandard=0;
				tempcdrstat.A_causeTDProtocol=0;
				tempcdrstat.A_causeTDTransport=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext>=65&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext<=80){
				tempcdrstat.A_causeTDTransport=1;
				tempcdrstat.A_causeTDRadioNetwork=0;
				tempcdrstat.A_causeTD=1;
				tempcdrstat.A_causeTD46=0;
				tempcdrstat.A_causeTD176=0;
				tempcdrstat.A_causeTD192=0;
				tempcdrstat.A_causeTD209=0;
				tempcdrstat.A_causeTD239=0;
				tempcdrstat.A_causeTDMisc=0;
				tempcdrstat.A_causeTDNAS=0;
				tempcdrstat.A_causeTDNonStandard=0;
				tempcdrstat.A_causeTDProtocol=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext>=81&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext<=96){
				tempcdrstat.A_causeTDNAS=1;
				tempcdrstat.A_causeTD=1;
				tempcdrstat.A_causeTDRadioNetwork=0;
				tempcdrstat.A_causeTD46=0;
				tempcdrstat.A_causeTD176=0;
				tempcdrstat.A_causeTD192=0;
				tempcdrstat.A_causeTD209=0;
				tempcdrstat.A_causeTD239=0;
				tempcdrstat.A_causeTDMisc=0;
				tempcdrstat.A_causeTDNonStandard=0;
				tempcdrstat.A_causeTDProtocol=0;
				tempcdrstat.A_causeTDTransport=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext>=97&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext<=112){
				tempcdrstat.A_causeTDProtocol=1;
				tempcdrstat.A_causeTD=1;
				tempcdrstat.A_causeTDRadioNetwork=0;
				tempcdrstat.A_causeTD46=0;
				tempcdrstat.A_causeTD176=0;
				tempcdrstat.A_causeTD192=0;
				tempcdrstat.A_causeTD209=0;
				tempcdrstat.A_causeTD239=0;
				tempcdrstat.A_causeTDMisc=0;
				tempcdrstat.A_causeTDNAS=0;
				tempcdrstat.A_causeTDNonStandard=0;
				tempcdrstat.A_causeTDTransport=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext>=113&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext<=128){
				tempcdrstat.A_causeTDMisc=1;
				tempcdrstat.A_causeTD=1;
				tempcdrstat.A_causeTDRadioNetwork=0;
				tempcdrstat.A_causeTD46=0;
				tempcdrstat.A_causeTD176=0;
				tempcdrstat.A_causeTD192=0;
				tempcdrstat.A_causeTD209=0;
				tempcdrstat.A_causeTD239=0;
				tempcdrstat.A_causeTDNAS=0;
				tempcdrstat.A_causeTDNonStandard=0;
				tempcdrstat.A_causeTDProtocol=0;
				tempcdrstat.A_causeTDTransport=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext==176){
				tempcdrstat.A_causeTDNonStandard=1;
				tempcdrstat.A_causeTD=1;
				tempcdrstat.A_causeTDRadioNetwork=0;
				tempcdrstat.A_causeTD46=0;
				tempcdrstat.A_causeTD176=1;
				tempcdrstat.A_causeTD192=0;
				tempcdrstat.A_causeTD209=0;
				tempcdrstat.A_causeTD239=0;
				tempcdrstat.A_causeTDMisc=0;
				tempcdrstat.A_causeTDNAS=0;
				tempcdrstat.A_causeTDProtocol=0;
				tempcdrstat.A_causeTDTransport=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext==192){
				tempcdrstat.A_causeTDNonStandard=1;
				tempcdrstat.A_causeTD=1;
				tempcdrstat.A_causeTDRadioNetwork=0;
				tempcdrstat.A_causeTD46=0;
				tempcdrstat.A_causeTD176=0;
				tempcdrstat.A_causeTD192=1;
				tempcdrstat.A_causeTD209=0;
				tempcdrstat.A_causeTD239=0;
				tempcdrstat.A_causeTDMisc=0;
				tempcdrstat.A_causeTDNAS=0;
				tempcdrstat.A_causeTDProtocol=0;
				tempcdrstat.A_causeTDTransport=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext==209){
				tempcdrstat.A_causeTDNonStandard=1;
				tempcdrstat.A_causeTD=1;
				tempcdrstat.A_causeTDRadioNetwork=0;
				tempcdrstat.A_causeTD46=0;
				tempcdrstat.A_causeTD176=0;
				tempcdrstat.A_causeTD192=0;
				tempcdrstat.A_causeTD209=1;
				tempcdrstat.A_causeTD239=0;
				tempcdrstat.A_causeTDMisc=0;
				tempcdrstat.A_causeTDNAS=0;
				tempcdrstat.A_causeTDProtocol=0;
				tempcdrstat.A_causeTDTransport=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext==239){
				tempcdrstat.A_causeTDNonStandard=1;
				tempcdrstat.A_causeTD=1;
				tempcdrstat.A_causeTDRadioNetwork=0;
				tempcdrstat.A_causeTD46=0;
				tempcdrstat.A_causeTD176=0;
				tempcdrstat.A_causeTD192=0;
				tempcdrstat.A_causeTD209=0;
				tempcdrstat.A_causeTD239=1;
				tempcdrstat.A_causeTDMisc=0;
				tempcdrstat.A_causeTDNAS=0;
				tempcdrstat.A_causeTDProtocol=0;
				tempcdrstat.A_causeTDTransport=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext!=176&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext!=192&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext!=209&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext!=239&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext>=129&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext<=256){
				tempcdrstat.A_causeTDNonStandard=1;
				tempcdrstat.A_causeTD=1;
				tempcdrstat.A_causeTDRadioNetwork=0;
				tempcdrstat.A_causeTD46=0;
				tempcdrstat.A_causeTD176=0;
				tempcdrstat.A_causeTD192=0;
				tempcdrstat.A_causeTD209=0;
				tempcdrstat.A_causeTD239=0;
				tempcdrstat.A_causeTDMisc=0;
				tempcdrstat.A_causeTDNAS=0;
				tempcdrstat.A_causeTDProtocol=0;
				tempcdrstat.A_causeTDTransport=0;
			}
			else{
				tempcdrstat.A_causeTDNonStandard=0;
				tempcdrstat.A_causeTD=0;
				tempcdrstat.A_causeTDRadioNetwork=0;
				tempcdrstat.A_causeTD46=0;
				tempcdrstat.A_causeTD176=0;
				tempcdrstat.A_causeTD192=0;
				tempcdrstat.A_causeTD209=0;
				tempcdrstat.A_causeTD239=0;
				tempcdrstat.A_causeTDMisc=0;
				tempcdrstat.A_causeTDNAS=0;
				tempcdrstat.A_causeTDProtocol=0;
				tempcdrstat.A_causeTDTransport=0;
			}
			int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_sac%((int)pow((double)10,HASH_NUM_CELLID));
			imeicdrfile[fn][temp_hash].push_back(tempcdrstat);
		}

		if(isExistAcallstartGSM==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_cell!=0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.size()>=MIN_IMEI_LENGTH){
			//�������������ʱ��GSMС����ͳ��
			IMEI_CDR_Statistic tempcdrstat;
			tempcdrstat.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI;
			tempcdrstat.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(0,TAC_LENGTH);
			tempcdrstat.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_cell;
			tempcdrstat.network="GSM";
			tempcdrstat.timeSection=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection;
			tempcdrstat.A_call_attempt=1;
			tempcdrstat.A_call_attempt_GSM=1;
			tempcdrstat.A_call_attempt_TD=0;
			tempcdrstat.A_cause0=0;
			tempcdrstat.A_cause1=0;
			tempcdrstat.A_cause20=0;
			tempcdrstat.A_cause60=0;
			tempcdrstat.A_causeGSM=0;
			tempcdrstat.A_causeTDNonStandard=0;
			tempcdrstat.A_causeTD=0;
			tempcdrstat.A_causeTDRadioNetwork=0;
			tempcdrstat.A_causeTD46=0;
			tempcdrstat.A_causeTD176=0;
			tempcdrstat.A_causeTD192=0;
			tempcdrstat.A_causeTD209=0;
			tempcdrstat.A_causeTD239=0;
			tempcdrstat.A_causeTDMisc=0;
			tempcdrstat.A_causeTDNAS=0;
			tempcdrstat.A_causeTDProtocol=0;
			tempcdrstat.A_causeTDTransport=0;
			tempcdrstat.B_call_attempt=0;
			tempcdrstat.B_call_attempt_GSM=0;
			tempcdrstat.B_call_attempt_TD=0;
			tempcdrstat.B_cause0=0;
			tempcdrstat.B_cause1=0;
			tempcdrstat.B_cause20=0;
			tempcdrstat.B_cause60=0;
			tempcdrstat.B_causeGSM=0;
			tempcdrstat.B_causeTD=0;
			tempcdrstat.B_causeTD46=0;
			tempcdrstat.B_causeTD176=0;
			tempcdrstat.B_causeTD192=0;
			tempcdrstat.B_causeTD209=0;
			tempcdrstat.B_causeTD239=0;
			tempcdrstat.B_causeTDMisc=0;
			tempcdrstat.B_causeTDNAS=0;
			tempcdrstat.B_causeTDNonStandard=0;
			tempcdrstat.B_causeTDProtocol=0;
			tempcdrstat.B_causeTDRadioNetwork=0;
			tempcdrstat.B_causeTDTransport=0;
			tempcdrstat.B_shortcall_1=0;
			tempcdrstat.B_shortcall_2=0;
			tempcdrstat.B_shortcall_3=0;

			if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_1){
				tempcdrstat.A_shortcall_1=1;
				tempcdrstat.A_shortcall_2=0;
				tempcdrstat.A_shortcall_3=0;
			}
			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_2&&difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)>=SHORTCALL_THRESHOLD_1){
				tempcdrstat.A_shortcall_2=1;
				tempcdrstat.A_shortcall_1=0;
				tempcdrstat.A_shortcall_3=0;
			}
			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_3&&difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)>=SHORTCALL_THRESHOLD_2){
				tempcdrstat.A_shortcall_3=1;
				tempcdrstat.A_shortcall_2=0;
				tempcdrstat.A_shortcall_1=0;
			}
			else{
				tempcdrstat.A_shortcall_3=0;
				tempcdrstat.A_shortcall_2=0;
				tempcdrstat.A_shortcall_1=0;
			}
			int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_cell%((int)pow((double)10,HASH_NUM_CELLID));
			imeicdrfile[fn][temp_hash].push_back(tempcdrstat);
		}

		if(isExistAcallstartTD==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_sac!=0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_cell==0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.size()>=MIN_IMEI_LENGTH){
			//�������������ʱ��TDС����ͳ��
			IMEI_CDR_Statistic tempcdrstat;
			tempcdrstat.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI;
			tempcdrstat.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(0,TAC_LENGTH);
			tempcdrstat.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_sac;
			tempcdrstat.network="TD";
			tempcdrstat.timeSection=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection;
			tempcdrstat.A_call_attempt=1;
			tempcdrstat.A_call_attempt_GSM=0;
			tempcdrstat.A_call_attempt_TD=1;
			tempcdrstat.A_cause0=0;
			tempcdrstat.A_cause1=0;
			tempcdrstat.A_cause20=0;
			tempcdrstat.A_cause60=0;
			tempcdrstat.A_causeGSM=0;
			tempcdrstat.A_causeTDNonStandard=0;
			tempcdrstat.A_causeTD=0;
			tempcdrstat.A_causeTDRadioNetwork=0;
			tempcdrstat.A_causeTD46=0;
			tempcdrstat.A_causeTD176=0;
			tempcdrstat.A_causeTD192=0;
			tempcdrstat.A_causeTD209=0;
			tempcdrstat.A_causeTD239=0;
			tempcdrstat.A_causeTDMisc=0;
			tempcdrstat.A_causeTDNAS=0;
			tempcdrstat.A_causeTDProtocol=0;
			tempcdrstat.A_causeTDTransport=0;
			tempcdrstat.B_call_attempt=0;
			tempcdrstat.B_call_attempt_GSM=0;
			tempcdrstat.B_call_attempt_TD=0;
			tempcdrstat.B_cause0=0;
			tempcdrstat.B_cause1=0;
			tempcdrstat.B_cause20=0;
			tempcdrstat.B_cause60=0;
			tempcdrstat.B_causeGSM=0;
			tempcdrstat.B_causeTD=0;
			tempcdrstat.B_causeTD46=0;
			tempcdrstat.B_causeTD176=0;
			tempcdrstat.B_causeTD192=0;
			tempcdrstat.B_causeTD209=0;
			tempcdrstat.B_causeTD239=0;
			tempcdrstat.B_causeTDMisc=0;
			tempcdrstat.B_causeTDNAS=0;
			tempcdrstat.B_causeTDNonStandard=0;
			tempcdrstat.B_causeTDProtocol=0;
			tempcdrstat.B_causeTDRadioNetwork=0;
			tempcdrstat.B_causeTDTransport=0;
			tempcdrstat.B_shortcall_1=0;
			tempcdrstat.B_shortcall_2=0;
			tempcdrstat.B_shortcall_3=0;

			if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_1){
				tempcdrstat.A_shortcall_1=1;
				tempcdrstat.A_shortcall_2=0;
				tempcdrstat.A_shortcall_3=0;
			}
			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_2&&difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)>=SHORTCALL_THRESHOLD_1){
				tempcdrstat.A_shortcall_2=1;
				tempcdrstat.A_shortcall_1=0;
				tempcdrstat.A_shortcall_3=0;
			}
			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_3&&difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)>=SHORTCALL_THRESHOLD_2){
				tempcdrstat.A_shortcall_3=1;
				tempcdrstat.A_shortcall_2=0;
				tempcdrstat.A_shortcall_1=0;
			}
			else{
				tempcdrstat.A_shortcall_3=0;
				tempcdrstat.A_shortcall_2=0;
				tempcdrstat.A_shortcall_1=0;
			}
			int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_sac%((int)pow((double)10,HASH_NUM_CELLID));
			imeicdrfile[fn][temp_hash].push_back(tempcdrstat);
		}

		if(isExistBcallendGSM==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell!=0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.size()>=MIN_IMEI_LENGTH){
			//�����ڱ��н���ʱ��GSMС����ͳ��
			IMEI_CDR_Statistic tempcdrstat;
			tempcdrstat.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI;
			tempcdrstat.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(0,TAC_LENGTH);
			tempcdrstat.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell;
			tempcdrstat.network="GSM";
			tempcdrstat.timeSection=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection;
			tempcdrstat.A_call_attempt=0;
			tempcdrstat.A_call_attempt_GSM=0;
			tempcdrstat.A_call_attempt_TD=0;
			tempcdrstat.A_cause0=0;
			tempcdrstat.A_cause1=0;
			tempcdrstat.A_cause20=0;
			tempcdrstat.A_cause60=0;
			tempcdrstat.A_causeGSM=0;
			tempcdrstat.A_causeTD=0;
			tempcdrstat.A_causeTDMisc=0;
			tempcdrstat.A_causeTD46=0;
			tempcdrstat.A_causeTD176=0;
			tempcdrstat.A_causeTD192=0;
			tempcdrstat.A_causeTD209=0;
			tempcdrstat.A_causeTD239=0;
			tempcdrstat.A_causeTDNAS=0;
			tempcdrstat.A_causeTDNonStandard=0;
			tempcdrstat.A_causeTDProtocol=0;
			tempcdrstat.A_causeTDRadioNetwork=0;
			tempcdrstat.A_causeTDTransport=0;
			tempcdrstat.A_shortcall_1=0;
			tempcdrstat.A_shortcall_2=0;
			tempcdrstat.A_shortcall_3=0;
			tempcdrstat.B_call_attempt=0;
			tempcdrstat.B_call_attempt_GSM=0;
			tempcdrstat.B_call_attempt_TD=0;
			tempcdrstat.B_causeTD=0;
			tempcdrstat.B_causeTD46=0;
			tempcdrstat.B_causeTD176=0;
			tempcdrstat.B_causeTD192=0;
			tempcdrstat.B_causeTD209=0;
			tempcdrstat.B_causeTD239=0;
			tempcdrstat.B_causeTDMisc=0;
			tempcdrstat.B_causeTDNAS=0;
			tempcdrstat.B_causeTDNonStandard=0;
			tempcdrstat.B_causeTDProtocol=0;
			tempcdrstat.B_causeTDRadioNetwork=0;
			tempcdrstat.B_causeTDTransport=0;
			tempcdrstat.B_shortcall_1=0;
			tempcdrstat.B_shortcall_2=0;
			tempcdrstat.B_shortcall_3=0;

			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause==0){
				tempcdrstat.B_cause0=1;
				tempcdrstat.B_causeGSM=1;
				tempcdrstat.B_cause1=0;
				tempcdrstat.B_cause20=0;
				tempcdrstat.B_cause60=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause==1){
				tempcdrstat.B_cause1=1;
				tempcdrstat.B_causeGSM=1;
				tempcdrstat.B_cause0=0;
				tempcdrstat.B_cause20=0;
				tempcdrstat.B_cause60=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause==20){
				tempcdrstat.B_cause20=1;
				tempcdrstat.B_causeGSM=1;
				tempcdrstat.B_cause1=0;
				tempcdrstat.B_cause0=0;
				tempcdrstat.B_cause60=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause==60){
				tempcdrstat.B_cause60=1;
				tempcdrstat.B_causeGSM=1;
				tempcdrstat.B_cause1=0;
				tempcdrstat.B_cause20=0;
				tempcdrstat.B_cause0=0;
			}
			else{
				tempcdrstat.B_cause60=0;
				tempcdrstat.B_causeGSM=0;
				tempcdrstat.B_cause1=0;
				tempcdrstat.B_cause20=0;
				tempcdrstat.B_cause0=0;
			}
			
			int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell%((int)pow((double)10,HASH_NUM_CELLID));
			imeicdrfile[fn][temp_hash].push_back(tempcdrstat);
		}

		if(isExistBcallendTD==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_sac!=0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell==0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.size()>=MIN_IMEI_LENGTH){
			//�����ڱ��н���ʱ��TDС����ͳ��
			IMEI_CDR_Statistic tempcdrstat;
			tempcdrstat.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI;
			tempcdrstat.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(0,TAC_LENGTH);
			tempcdrstat.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_sac;
			tempcdrstat.network="TD";
			tempcdrstat.timeSection=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection;
			tempcdrstat.A_call_attempt=0;
			tempcdrstat.A_call_attempt_GSM=0;
			tempcdrstat.A_call_attempt_TD=0;
			tempcdrstat.A_cause0=0;
			tempcdrstat.A_cause1=0;
			tempcdrstat.A_cause20=0;
			tempcdrstat.A_cause60=0;
			tempcdrstat.A_causeGSM=0;
			tempcdrstat.A_causeTD=0;
			tempcdrstat.A_causeTD46=0;
			tempcdrstat.A_causeTD176=0;
			tempcdrstat.A_causeTD192=0;
			tempcdrstat.A_causeTD209=0;
			tempcdrstat.A_causeTD239=0;
			tempcdrstat.A_causeTDMisc=0;
			tempcdrstat.A_causeTDNAS=0;
			tempcdrstat.A_causeTDNonStandard=0;
			tempcdrstat.A_causeTDProtocol=0;
			tempcdrstat.A_causeTDRadioNetwork=0;
			tempcdrstat.A_causeTDTransport=0;
			tempcdrstat.A_shortcall_1=0;
			tempcdrstat.A_shortcall_2=0;
			tempcdrstat.A_shortcall_3=0;
			tempcdrstat.B_call_attempt=0;
			tempcdrstat.B_call_attempt_GSM=0;
			tempcdrstat.B_call_attempt_TD=0;
			tempcdrstat.B_cause0=0;
			tempcdrstat.B_cause1=0;
			tempcdrstat.B_cause20=0;
			tempcdrstat.B_cause60=0;
			tempcdrstat.B_causeGSM=0;			
			tempcdrstat.B_shortcall_1=0;
			tempcdrstat.B_shortcall_2=0;
			tempcdrstat.B_shortcall_3=0;

			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext==46){
				tempcdrstat.B_causeTD46=1;
				tempcdrstat.B_causeTD176=0;
				tempcdrstat.B_causeTD192=0;
				tempcdrstat.B_causeTD209=0;
				tempcdrstat.B_causeTD239=0;
				tempcdrstat.B_causeTDRadioNetwork=1;
				tempcdrstat.B_causeTD=1;
				tempcdrstat.B_causeTDMisc=0;
				tempcdrstat.B_causeTDNAS=0;
				tempcdrstat.B_causeTDNonStandard=0;
				tempcdrstat.B_causeTDProtocol=0;
				tempcdrstat.B_causeTDTransport=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext!=46&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext>=1&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext<=64){
				tempcdrstat.B_causeTDRadioNetwork=1;
				tempcdrstat.B_causeTD=1;
				tempcdrstat.B_causeTD46=0;
				tempcdrstat.B_causeTD176=0;
				tempcdrstat.B_causeTD192=0;
				tempcdrstat.B_causeTD209=0;
				tempcdrstat.B_causeTD239=0;
				tempcdrstat.B_causeTDMisc=0;
				tempcdrstat.B_causeTDNAS=0;
				tempcdrstat.B_causeTDNonStandard=0;
				tempcdrstat.B_causeTDProtocol=0;
				tempcdrstat.B_causeTDTransport=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext>=257&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext<=512){
				tempcdrstat.B_causeTDRadioNetwork=1;
				tempcdrstat.B_causeTD=1;
				tempcdrstat.B_causeTD46=0;
				tempcdrstat.B_causeTD176=0;
				tempcdrstat.B_causeTD192=0;
				tempcdrstat.B_causeTD209=0;
				tempcdrstat.B_causeTD239=0;
				tempcdrstat.B_causeTDMisc=0;
				tempcdrstat.B_causeTDNAS=0;
				tempcdrstat.B_causeTDNonStandard=0;
				tempcdrstat.B_causeTDProtocol=0;
				tempcdrstat.B_causeTDTransport=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext>=65&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext<=80){
				tempcdrstat.B_causeTDTransport=1;
				tempcdrstat.B_causeTDRadioNetwork=0;
				tempcdrstat.B_causeTD=1;
				tempcdrstat.B_causeTD46=0;
				tempcdrstat.B_causeTD176=0;
				tempcdrstat.B_causeTD192=0;
				tempcdrstat.B_causeTD209=0;
				tempcdrstat.B_causeTD239=0;
				tempcdrstat.B_causeTDMisc=0;
				tempcdrstat.B_causeTDNAS=0;
				tempcdrstat.B_causeTDNonStandard=0;
				tempcdrstat.B_causeTDProtocol=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext>=81&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext<=96){
				tempcdrstat.B_causeTDNAS=1;
				tempcdrstat.B_causeTD=1;
				tempcdrstat.B_causeTDRadioNetwork=0;
				tempcdrstat.B_causeTD46=0;
				tempcdrstat.B_causeTD176=0;
				tempcdrstat.B_causeTD192=0;
				tempcdrstat.B_causeTD209=0;
				tempcdrstat.B_causeTD239=0;
				tempcdrstat.B_causeTDMisc=0;
				tempcdrstat.B_causeTDNonStandard=0;
				tempcdrstat.B_causeTDProtocol=0;
				tempcdrstat.B_causeTDTransport=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext>=97&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext<=112){
				tempcdrstat.B_causeTDProtocol=1;
				tempcdrstat.B_causeTD=1;
				tempcdrstat.B_causeTDRadioNetwork=0;
				tempcdrstat.B_causeTD46=0;
				tempcdrstat.B_causeTD176=0;
				tempcdrstat.B_causeTD192=0;
				tempcdrstat.B_causeTD209=0;
				tempcdrstat.B_causeTD239=0;
				tempcdrstat.B_causeTDMisc=0;
				tempcdrstat.B_causeTDNAS=0;
				tempcdrstat.B_causeTDNonStandard=0;
				tempcdrstat.B_causeTDTransport=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext>=113&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext<=128){
				tempcdrstat.B_causeTDMisc=1;
				tempcdrstat.B_causeTD=1;
				tempcdrstat.B_causeTDRadioNetwork=0;
				tempcdrstat.B_causeTD46=0;
				tempcdrstat.B_causeTD176=0;
				tempcdrstat.B_causeTD192=0;
				tempcdrstat.B_causeTD209=0;
				tempcdrstat.B_causeTD239=0;
				tempcdrstat.B_causeTDNAS=0;
				tempcdrstat.B_causeTDNonStandard=0;
				tempcdrstat.B_causeTDProtocol=0;
				tempcdrstat.B_causeTDTransport=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext==176){
				tempcdrstat.B_causeTDNonStandard=1;
				tempcdrstat.B_causeTD=1;
				tempcdrstat.B_causeTDRadioNetwork=0;
				tempcdrstat.B_causeTD46=0;
				tempcdrstat.B_causeTD176=1;
				tempcdrstat.B_causeTD192=0;
				tempcdrstat.B_causeTD209=0;
				tempcdrstat.B_causeTD239=0;
				tempcdrstat.B_causeTDMisc=0;
				tempcdrstat.B_causeTDNAS=0;
				tempcdrstat.B_causeTDProtocol=0;
				tempcdrstat.B_causeTDTransport=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext==192){
				tempcdrstat.B_causeTDNonStandard=1;
				tempcdrstat.B_causeTD=1;
				tempcdrstat.B_causeTDRadioNetwork=0;
				tempcdrstat.B_causeTD46=0;
				tempcdrstat.B_causeTD176=0;
				tempcdrstat.B_causeTD192=1;
				tempcdrstat.B_causeTD209=0;
				tempcdrstat.B_causeTD239=0;
				tempcdrstat.B_causeTDMisc=0;
				tempcdrstat.B_causeTDNAS=0;
				tempcdrstat.B_causeTDProtocol=0;
				tempcdrstat.B_causeTDTransport=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext==209){
				tempcdrstat.B_causeTDNonStandard=1;
				tempcdrstat.B_causeTD=1;
				tempcdrstat.B_causeTDRadioNetwork=0;
				tempcdrstat.B_causeTD46=0;
				tempcdrstat.B_causeTD176=0;
				tempcdrstat.B_causeTD192=0;
				tempcdrstat.B_causeTD209=1;
				tempcdrstat.B_causeTD239=0;
				tempcdrstat.B_causeTDMisc=0;
				tempcdrstat.B_causeTDNAS=0;
				tempcdrstat.B_causeTDProtocol=0;
				tempcdrstat.B_causeTDTransport=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext==239){
				tempcdrstat.B_causeTDNonStandard=1;
				tempcdrstat.B_causeTD=1;
				tempcdrstat.B_causeTDRadioNetwork=0;
				tempcdrstat.B_causeTD46=0;
				tempcdrstat.B_causeTD176=0;
				tempcdrstat.B_causeTD192=0;
				tempcdrstat.B_causeTD209=0;
				tempcdrstat.B_causeTD239=1;
				tempcdrstat.B_causeTDMisc=0;
				tempcdrstat.B_causeTDNAS=0;
				tempcdrstat.B_causeTDProtocol=0;
				tempcdrstat.B_causeTDTransport=0;
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext!=176&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext!=192&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext!=209&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext!=239&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext>=129&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext<=256){
				tempcdrstat.B_causeTDNonStandard=1;
				tempcdrstat.B_causeTD=1;
				tempcdrstat.B_causeTDRadioNetwork=0;
				tempcdrstat.B_causeTD46=0;
				tempcdrstat.B_causeTD176=0;
				tempcdrstat.B_causeTD192=0;
				tempcdrstat.B_causeTD209=0;
				tempcdrstat.B_causeTD239=0;
				tempcdrstat.B_causeTDMisc=0;
				tempcdrstat.B_causeTDNAS=0;
				tempcdrstat.B_causeTDProtocol=0;
				tempcdrstat.B_causeTDTransport=0;
			}
			else{
				tempcdrstat.B_causeTDNonStandard=0;
				tempcdrstat.B_causeTD=0;
				tempcdrstat.B_causeTDRadioNetwork=0;
				tempcdrstat.B_causeTD46=0;
				tempcdrstat.B_causeTD176=0;
				tempcdrstat.B_causeTD192=0;
				tempcdrstat.B_causeTD209=0;
				tempcdrstat.B_causeTD239=0;
				tempcdrstat.B_causeTDMisc=0;
				tempcdrstat.B_causeTDNAS=0;
				tempcdrstat.B_causeTDProtocol=0;
				tempcdrstat.B_causeTDTransport=0;
			}
			int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_sac%((int)pow((double)10,HASH_NUM_CELLID));
			imeicdrfile[fn][temp_hash].push_back(tempcdrstat);
		}

		if(isExistBcallstartGSM==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_cell!=0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.size()>=MIN_IMEI_LENGTH){
			//�����ڱ��н���ʱ��GSMС����ͳ��
			IMEI_CDR_Statistic tempcdrstat;
			tempcdrstat.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI;
			tempcdrstat.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(0,TAC_LENGTH);
			tempcdrstat.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_cell;
			tempcdrstat.network="GSM";
			tempcdrstat.timeSection=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection;
			tempcdrstat.A_call_attempt=0;
			tempcdrstat.A_call_attempt_GSM=0;
			tempcdrstat.A_call_attempt_TD=0;
			tempcdrstat.A_shortcall_1=0;
			tempcdrstat.A_shortcall_2=0;
			tempcdrstat.A_shortcall_3=0;
			tempcdrstat.A_cause0=0;
			tempcdrstat.A_cause1=0;
			tempcdrstat.A_cause20=0;
			tempcdrstat.A_cause60=0;
			tempcdrstat.A_causeGSM=0;
			tempcdrstat.A_causeTDNonStandard=0;
			tempcdrstat.A_causeTD=0;
			tempcdrstat.A_causeTDRadioNetwork=0;
			tempcdrstat.A_causeTD46=0;
			tempcdrstat.A_causeTD176=0;
			tempcdrstat.A_causeTD192=0;
			tempcdrstat.A_causeTD209=0;
			tempcdrstat.A_causeTD239=0;
			tempcdrstat.A_causeTDMisc=0;
			tempcdrstat.A_causeTDNAS=0;
			tempcdrstat.A_causeTDProtocol=0;
			tempcdrstat.A_causeTDTransport=0;
			tempcdrstat.B_call_attempt=1;
			tempcdrstat.B_call_attempt_GSM=1;
			tempcdrstat.B_call_attempt_TD=0;
			tempcdrstat.B_cause0=0;
			tempcdrstat.B_cause1=0;
			tempcdrstat.B_cause20=0;
			tempcdrstat.B_cause60=0;
			tempcdrstat.B_causeGSM=0;
			tempcdrstat.B_causeTD=0;
			tempcdrstat.B_causeTD46=0;
			tempcdrstat.B_causeTD176=0;
			tempcdrstat.B_causeTD192=0;
			tempcdrstat.B_causeTD209=0;
			tempcdrstat.B_causeTD239=0;
			tempcdrstat.B_causeTDMisc=0;
			tempcdrstat.B_causeTDNAS=0;
			tempcdrstat.B_causeTDNonStandard=0;
			tempcdrstat.B_causeTDProtocol=0;
			tempcdrstat.B_causeTDRadioNetwork=0;
			tempcdrstat.B_causeTDTransport=0;			

			if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_1){
				tempcdrstat.B_shortcall_1=1;
				tempcdrstat.B_shortcall_2=0;
				tempcdrstat.B_shortcall_3=0;
			}
			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_2&&difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)>=SHORTCALL_THRESHOLD_1){
				tempcdrstat.B_shortcall_2=1;
				tempcdrstat.B_shortcall_1=0;
				tempcdrstat.B_shortcall_3=0;
			}
			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_3&&difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)>=SHORTCALL_THRESHOLD_2){
				tempcdrstat.B_shortcall_3=1;
				tempcdrstat.B_shortcall_2=0;
				tempcdrstat.B_shortcall_1=0;
			}
			else{
				tempcdrstat.B_shortcall_3=0;
				tempcdrstat.B_shortcall_2=0;
				tempcdrstat.B_shortcall_1=0;
			}
			int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_cell%((int)pow((double)10,HASH_NUM_CELLID));
			imeicdrfile[fn][temp_hash].push_back(tempcdrstat);
		}

		if(isExistBcallstartTD==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_sac!=0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_cell==0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.size()>=MIN_IMEI_LENGTH){
			//�����ڱ��н���ʱ��TDС����ͳ��
			IMEI_CDR_Statistic tempcdrstat;
			tempcdrstat.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI;
			tempcdrstat.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(0,TAC_LENGTH);
			tempcdrstat.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_sac;
			tempcdrstat.network="TD";
			tempcdrstat.timeSection=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection;
			tempcdrstat.A_call_attempt=0;
			tempcdrstat.A_call_attempt_GSM=0;
			tempcdrstat.A_call_attempt_TD=0;
			tempcdrstat.A_shortcall_1=0;
			tempcdrstat.A_shortcall_2=0;
			tempcdrstat.A_shortcall_3=0;
			tempcdrstat.A_cause0=0;
			tempcdrstat.A_cause1=0;
			tempcdrstat.A_cause20=0;
			tempcdrstat.A_cause60=0;
			tempcdrstat.A_causeGSM=0;
			tempcdrstat.A_causeTDNonStandard=0;
			tempcdrstat.A_causeTD=0;
			tempcdrstat.A_causeTDRadioNetwork=0;
			tempcdrstat.A_causeTD46=0;
			tempcdrstat.A_causeTD176=0;
			tempcdrstat.A_causeTD192=0;
			tempcdrstat.A_causeTD209=0;
			tempcdrstat.A_causeTD239=0;
			tempcdrstat.A_causeTDMisc=0;
			tempcdrstat.A_causeTDNAS=0;
			tempcdrstat.A_causeTDProtocol=0;
			tempcdrstat.A_causeTDTransport=0;
			tempcdrstat.B_call_attempt=1;
			tempcdrstat.B_call_attempt_GSM=0;
			tempcdrstat.B_call_attempt_TD=1;
			tempcdrstat.B_cause0=0;
			tempcdrstat.B_cause1=0;
			tempcdrstat.B_cause20=0;
			tempcdrstat.B_cause60=0;
			tempcdrstat.B_causeGSM=0;
			tempcdrstat.B_causeTD=0;
			tempcdrstat.B_causeTD46=0;
			tempcdrstat.B_causeTD176=0;
			tempcdrstat.B_causeTD192=0;
			tempcdrstat.B_causeTD209=0;
			tempcdrstat.B_causeTD239=0;
			tempcdrstat.B_causeTDMisc=0;
			tempcdrstat.B_causeTDNAS=0;
			tempcdrstat.B_causeTDNonStandard=0;
			tempcdrstat.B_causeTDProtocol=0;
			tempcdrstat.B_causeTDRadioNetwork=0;
			tempcdrstat.B_causeTDTransport=0;

			if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_1){
				tempcdrstat.B_shortcall_1=1;
				tempcdrstat.B_shortcall_2=0;
				tempcdrstat.B_shortcall_3=0;
			}
			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_2&&difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)>=SHORTCALL_THRESHOLD_1){
				tempcdrstat.B_shortcall_2=1;
				tempcdrstat.B_shortcall_1=0;
				tempcdrstat.B_shortcall_3=0;
			}
			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_3&&difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)>=SHORTCALL_THRESHOLD_2){
				tempcdrstat.B_shortcall_3=1;
				tempcdrstat.B_shortcall_2=0;
				tempcdrstat.B_shortcall_1=0;
			}
			else{
				tempcdrstat.B_shortcall_3=0;
				tempcdrstat.B_shortcall_2=0;
				tempcdrstat.B_shortcall_1=0;
			}
			int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_sac%((int)pow((double)10,HASH_NUM_CELLID));
			imeicdrfile[fn][temp_hash].push_back(tempcdrstat);
		}

		//if(isExistA==false&&isExistB==true){
		//	//������A������һ����¼
		//	if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.size()>=MIN_IMEI_LENGTH&&isValidCDR(cdr[rp[cdrcount].fn][rp[cdrcount].rn])){
		//		IMEI_CDR_Statistic tempcdrstat;
		//		tempcdrstat.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI;
		//		tempcdrstat.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(0,8);
		//		tempcdrstat.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell;
		//			
		//		if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==0){
		//			tempcdrstat.A_cause0=1;
		//			tempcdrstat.A_cause1=0;
		//			tempcdrstat.A_cause20=0;
		//			tempcdrstat.A_cause60=0;
		//		}
		//		else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==1){
		//			tempcdrstat.A_cause0=0;
		//			tempcdrstat.A_cause1=1;
		//			tempcdrstat.A_cause20=0;
		//			tempcdrstat.A_cause60=0;
		//		}
		//		else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==20){
		//			tempcdrstat.A_cause0=0;
		//			tempcdrstat.A_cause1=0;
		//			tempcdrstat.A_cause20=1;
		//			tempcdrstat.A_cause60=0;
		//		}
		//		else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==60){
		//			tempcdrstat.A_cause0=0;
		//			tempcdrstat.A_cause1=0;
		//			tempcdrstat.A_cause20=0;
		//			tempcdrstat.A_cause60=1;
		//		}
		//		else{
		//			tempcdrstat.A_cause0=0;
		//			tempcdrstat.A_cause1=0;
		//			tempcdrstat.A_cause20=0;
		//			tempcdrstat.A_cause60=0;
		//		}
		//		
		//		if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time==0||cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time==0){
		//			tempcdrstat.A_call_attempt=1;
		//			tempcdrstat.A_call_not_connected=1;
		//			tempcdrstat.A_shortcall_1=0;
		//			tempcdrstat.A_shortcall_2=0;
		//			tempcdrstat.A_shortcall_3=0;
		//		}
		//		else{
		//			tempcdrstat.A_call_attempt=1;
		//			tempcdrstat.A_call_not_connected=0;
		//			if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_1){
		//				tempcdrstat.A_shortcall_1=1;
		//				tempcdrstat.A_shortcall_2=0;
		//				tempcdrstat.A_shortcall_3=0;
		//			}
		//			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_2){
		//				tempcdrstat.A_shortcall_2=1;
		//				tempcdrstat.A_shortcall_1=0;
		//				tempcdrstat.A_shortcall_3=0;
		//			}
		//			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_3){
		//				tempcdrstat.A_shortcall_3=1;
		//				tempcdrstat.A_shortcall_2=0;
		//				tempcdrstat.A_shortcall_1=0;
		//			}
		//			else{
		//				tempcdrstat.A_shortcall_1=0;
		//				tempcdrstat.A_shortcall_2=0;
		//				tempcdrstat.A_shortcall_3=0;
		//			}
		//		}

		//		tempcdrstat.B_cause0=0;
		//		tempcdrstat.B_cause1=0;
		//		tempcdrstat.B_cause20=0;
		//		tempcdrstat.B_cause60=0;
		//		tempcdrstat.B_shortcall_1=0;
		//		tempcdrstat.B_shortcall_2=0;
		//		tempcdrstat.B_shortcall_3=0;
		//		tempcdrstat.B_call_attempt=0;
		//		tempcdrstat.B_call_not_connected=0;

		//		int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell%((int)pow((double)10,HASH_NUM_CELLID));

		//		imeicdrfile[fn][temp_hash].push_back(tempcdrstat);
		//	}
		//}
		//else if(isExistB==false&&isExistA==true){
		//	//������B������һ����¼
		//		
		//	if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.size()>=MIN_IMEI_LENGTH&&isValidCDR(cdr[rp[cdrcount].fn][rp[cdrcount].rn])){
		//		IMEI_CDR_Statistic tempcdrstatB;

		//		tempcdrstatB.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI;
		//		tempcdrstatB.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(0,8);
		//		tempcdrstatB.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell;
		//		tempcdrstatB.A_cause0=0;
		//		tempcdrstatB.A_cause1=0;
		//		tempcdrstatB.A_cause20=0;
		//		tempcdrstatB.A_cause60=0;
		//		tempcdrstatB.A_shortcall_1=0;
		//		tempcdrstatB.A_shortcall_2=0;
		//		tempcdrstatB.A_shortcall_3=0;
		//		tempcdrstatB.A_call_attempt=0;
		//		tempcdrstatB.A_call_not_connected=0;
		//			
		//		
		//		if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause==0){
		//			tempcdrstatB.B_cause0=1;
		//			tempcdrstatB.B_cause1=0;
		//			tempcdrstatB.B_cause20=0;
		//			tempcdrstatB.B_cause60=0;
		//		}
		//		else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause==1){
		//			tempcdrstatB.B_cause0=0;
		//			tempcdrstatB.B_cause1=1;
		//			tempcdrstatB.B_cause20=0;
		//			tempcdrstatB.B_cause60=0;
		//		}
		//		else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause==20){
		//			tempcdrstatB.B_cause0=0;
		//			tempcdrstatB.B_cause1=0;
		//			tempcdrstatB.B_cause20=1;
		//			tempcdrstatB.B_cause60=0;
		//		}
		//		else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause==60){
		//			tempcdrstatB.B_cause0=0;
		//			tempcdrstatB.B_cause1=0;
		//			tempcdrstatB.B_cause20=0;
		//			tempcdrstatB.B_cause60=1;
		//		}
		//		else{
		//			tempcdrstatB.B_cause0=0;
		//			tempcdrstatB.B_cause1=0;
		//			tempcdrstatB.B_cause20=0;
		//			tempcdrstatB.B_cause60=0;
		//		}
		//		
		//		if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time==0||cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time==0){
		//			tempcdrstatB.B_call_attempt=1;
		//			tempcdrstatB.B_call_not_connected=1;
		//			tempcdrstatB.B_shortcall_1=0;
		//			tempcdrstatB.B_shortcall_2=0;
		//			tempcdrstatB.B_shortcall_3=0;
		//		}
		//		else{
		//			tempcdrstatB.B_call_attempt=1;
		//			tempcdrstatB.B_call_not_connected=0;
		//			if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_1){
		//				tempcdrstatB.B_shortcall_1=1;
		//				tempcdrstatB.B_shortcall_3=0;
		//				tempcdrstatB.B_shortcall_2=0;
		//			}
		//			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_2){
		//				tempcdrstatB.B_shortcall_2=1;
		//				tempcdrstatB.B_shortcall_3=0;
		//				tempcdrstatB.B_shortcall_1=0;
		//			}
		//			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_3){
		//				tempcdrstatB.B_shortcall_3=1;
		//				tempcdrstatB.B_shortcall_1=0;
		//				tempcdrstatB.B_shortcall_2=0;
		//			}
		//			else{
		//				tempcdrstatB.B_shortcall_1=0;
		//				tempcdrstatB.B_shortcall_2=0;
		//				tempcdrstatB.B_shortcall_3=0;
		//			}
		//		}

		//		int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell%((int)pow((double)10,HASH_NUM_CELLID));

		//		imeicdrfile[fn][temp_hash].push_back(tempcdrstatB);
		//	}
		//}
		//else if(isExistA==false&&isExistB==false){
		//	if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI==cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell==cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.size()>=MIN_IMEI_LENGTH&&isValidCDR(cdr[rp[cdrcount].fn][rp[cdrcount].rn])){
		//		//һ����IMEI,��һ����cellid
		//		IMEI_CDR_Statistic tempcdrstat;
		//		tempcdrstat.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI;
		//		tempcdrstat.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(0,8);
		//		tempcdrstat.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell;
		//			
		//		if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==0){
		//			tempcdrstat.A_cause0=1;
		//			tempcdrstat.A_cause1=0;
		//			tempcdrstat.A_cause20=0;
		//			tempcdrstat.A_cause60=0;
		//		}
		//		else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==1){
		//			tempcdrstat.A_cause0=0;
		//			tempcdrstat.A_cause1=1;
		//			tempcdrstat.A_cause20=0;
		//			tempcdrstat.A_cause60=0;
		//		}
		//		else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==20){
		//			tempcdrstat.A_cause0=0;
		//			tempcdrstat.A_cause1=0;
		//			tempcdrstat.A_cause20=1;
		//			tempcdrstat.A_cause60=0;
		//		}
		//		else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==60){
		//			tempcdrstat.A_cause0=0;
		//			tempcdrstat.A_cause1=0;
		//			tempcdrstat.A_cause20=0;
		//			tempcdrstat.A_cause60=1;
		//		}
		//		else{
		//			tempcdrstat.A_cause0=0;
		//			tempcdrstat.A_cause1=0;
		//			tempcdrstat.A_cause20=0;
		//			tempcdrstat.A_cause60=0;
		//		}
		//	
		//		if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time==0||cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time==0){
		//			tempcdrstat.A_call_attempt=1;
		//			tempcdrstat.B_call_attempt=1;
		//			tempcdrstat.A_call_not_connected=1;
		//			tempcdrstat.B_call_not_connected=1;
		//			tempcdrstat.A_shortcall_1=0;
		//			tempcdrstat.A_shortcall_2=0;
		//			tempcdrstat.A_shortcall_3=0;
		//			tempcdrstat.B_shortcall_1=0;
		//			tempcdrstat.B_shortcall_2=0;
		//			tempcdrstat.B_shortcall_3=0;
		//		}
		//		else{
		//			tempcdrstat.A_call_attempt=1;
		//			tempcdrstat.B_call_attempt=1;
		//			tempcdrstat.A_call_not_connected=0;
		//			tempcdrstat.B_call_not_connected=0;
		//			if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_1){
		//				tempcdrstat.A_shortcall_1=1;
		//				tempcdrstat.A_shortcall_2=0;
		//				tempcdrstat.A_shortcall_3=0;
		//				tempcdrstat.B_shortcall_1=1;
		//				tempcdrstat.B_shortcall_3=0;
		//				tempcdrstat.B_shortcall_2=0;
		//			}
		//			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_2){
		//				tempcdrstat.A_shortcall_1=0;
		//				tempcdrstat.A_shortcall_2=1;
		//				tempcdrstat.A_shortcall_3=0;
		//				tempcdrstat.B_shortcall_1=0;
		//				tempcdrstat.B_shortcall_2=1;
		//				tempcdrstat.B_shortcall_3=0;
		//				
		//			}
		//			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_3){
		//				tempcdrstat.A_shortcall_1=0;
		//				tempcdrstat.A_shortcall_2=0;
		//				tempcdrstat.A_shortcall_3=1;
		//				tempcdrstat.B_shortcall_3=1;
		//				tempcdrstat.B_shortcall_1=0;
		//				tempcdrstat.B_shortcall_2=0;
		//			}
		//			else{
		//				tempcdrstat.A_shortcall_1=0;
		//				tempcdrstat.A_shortcall_2=0;
		//				tempcdrstat.A_shortcall_3=0;
		//				tempcdrstat.B_shortcall_1=0;
		//				tempcdrstat.B_shortcall_2=0;
		//				tempcdrstat.B_shortcall_3=0;
		//			}
		//		}

		//		if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause==0){
		//			tempcdrstat.B_cause0=1;
		//			tempcdrstat.B_cause1=0;
		//			tempcdrstat.B_cause20=0;
		//			tempcdrstat.B_cause60=0;
		//		}
		//		else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause==1){
		//			tempcdrstat.B_cause0=0;
		//			tempcdrstat.B_cause1=1;
		//			tempcdrstat.B_cause20=0;
		//			tempcdrstat.B_cause60=0;
		//		}
		//		else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause==20){
		//			tempcdrstat.B_cause0=0;
		//			tempcdrstat.B_cause1=0;
		//			tempcdrstat.B_cause20=1;
		//			tempcdrstat.B_cause60=0;
		//		}
		//		else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause==60){
		//			tempcdrstat.B_cause0=0;
		//			tempcdrstat.B_cause1=0;
		//			tempcdrstat.B_cause20=0;
		//			tempcdrstat.B_cause60=1;
		//		}
		//		else{
		//			tempcdrstat.B_cause0=0;
		//			tempcdrstat.B_cause1=0;
		//			tempcdrstat.B_cause20=0;
		//			tempcdrstat.B_cause60=0;
		//		}

		//		int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell%((int)pow((double)10,HASH_NUM_CELLID));

		//		imeicdrfile[fn][temp_hash].push_back(tempcdrstat);
		//	}
		//	else{
		//			
		//		if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.size()>=MIN_IMEI_LENGTH&&isValidCDR(cdr[rp[cdrcount].fn][rp[cdrcount].rn])){
		//			//��һ����IMEI,�ֿ�����
		//			//����A��IMEI��Ŀ
		//			IMEI_CDR_Statistic tempcdrstat;
		//			tempcdrstat.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI;
		//			tempcdrstat.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(0,8);
		//			tempcdrstat.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell;
		//		
		//			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==0){
		//				tempcdrstat.A_cause0=1;
		//				tempcdrstat.A_cause1=0;
		//				tempcdrstat.A_cause20=0;
		//				tempcdrstat.A_cause60=0;
		//			}
		//			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==1){
		//				tempcdrstat.A_cause0=0;
		//				tempcdrstat.A_cause1=1;
		//				tempcdrstat.A_cause20=0;
		//				tempcdrstat.A_cause60=0;
		//			}
		//			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==20){
		//				tempcdrstat.A_cause0=0;
		//				tempcdrstat.A_cause1=0;
		//				tempcdrstat.A_cause20=1;
		//				tempcdrstat.A_cause60=0;
		//			}
		//			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==60){
		//				tempcdrstat.A_cause0=0;
		//				tempcdrstat.A_cause1=0;
		//				tempcdrstat.A_cause20=0;
		//				tempcdrstat.A_cause60=1;
		//			}
		//			else{
		//				tempcdrstat.A_cause0=0;
		//				tempcdrstat.A_cause1=0;
		//				tempcdrstat.A_cause20=0;
		//				tempcdrstat.A_cause60=0;
		//			}
		//	
		//			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time==0||cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time==0){
		//				tempcdrstat.A_call_attempt=1;
		//				tempcdrstat.A_call_not_connected=1;
		//				tempcdrstat.A_shortcall_1=0;
		//				tempcdrstat.A_shortcall_2=0;
		//				tempcdrstat.A_shortcall_3=0;
		//			}
		//			else{
		//				tempcdrstat.A_call_attempt=1;
		//				tempcdrstat.A_call_not_connected=0;
		//				if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_1){
		//					tempcdrstat.A_shortcall_1=1;
		//					tempcdrstat.A_shortcall_2=0;
		//					tempcdrstat.A_shortcall_3=0;
		//				}
		//				else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_2){
		//					tempcdrstat.A_shortcall_2=1;
		//					tempcdrstat.A_shortcall_1=0;
		//					tempcdrstat.A_shortcall_3=0;
		//				}
		//				else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_3){
		//					tempcdrstat.A_shortcall_3=1;
		//					tempcdrstat.A_shortcall_2=0;
		//					tempcdrstat.A_shortcall_1=0;
		//				}
		//				else{
		//					tempcdrstat.A_shortcall_1=0;
		//					tempcdrstat.A_shortcall_2=0;
		//					tempcdrstat.A_shortcall_3=0;
		//				}
		//			}

		//			tempcdrstat.B_cause0=0;
		//			tempcdrstat.B_cause1=0;
		//			tempcdrstat.B_cause20=0;
		//			tempcdrstat.B_cause60=0;
		//			tempcdrstat.B_shortcall_1=0;
		//			tempcdrstat.B_shortcall_2=0;
		//			tempcdrstat.B_shortcall_3=0;
		//			tempcdrstat.B_call_attempt=0;
		//			tempcdrstat.B_call_not_connected=0;

		//			int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell%((int)pow((double)10,HASH_NUM_CELLID));

		//			imeicdrfile[fn][temp_hash].push_back(tempcdrstat);
		//		}
		//		
		//		if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.size()>=MIN_IMEI_LENGTH&&isValidCDR(cdr[rp[cdrcount].fn][rp[cdrcount].rn])){
		//			//����B��IMEI��Ŀ
		//			IMEI_CDR_Statistic tempcdrstatB;

		//			tempcdrstatB.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI;
		//			tempcdrstatB.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(0,8);
		//			tempcdrstatB.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell;
		//			tempcdrstatB.A_cause0=0;
		//			tempcdrstatB.A_cause1=0;
		//			tempcdrstatB.A_cause20=0;
		//			tempcdrstatB.A_cause60=0;
		//			tempcdrstatB.A_shortcall_1=0;
		//			tempcdrstatB.A_shortcall_2=0;
		//			tempcdrstatB.A_shortcall_3=0;
		//			tempcdrstatB.A_call_attempt=0;
		//			tempcdrstatB.A_call_not_connected=0;
		//		
		//			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause==0){
		//				tempcdrstatB.B_cause0=1;
		//				tempcdrstatB.B_cause1=0;
		//				tempcdrstatB.B_cause20=0;
		//				tempcdrstatB.B_cause60=0;
		//			}
		//			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause==1){
		//				tempcdrstatB.B_cause0=0;
		//				tempcdrstatB.B_cause1=1;
		//				tempcdrstatB.B_cause20=0;
		//				tempcdrstatB.B_cause60=0;
		//			}
		//			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause==20){
		//				tempcdrstatB.B_cause0=0;
		//				tempcdrstatB.B_cause1=0;
		//				tempcdrstatB.B_cause20=1;
		//				tempcdrstatB.B_cause60=0;
		//			}
		//			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause==60){
		//				tempcdrstatB.B_cause0=0;
		//				tempcdrstatB.B_cause1=0;
		//				tempcdrstatB.B_cause20=0;
		//				tempcdrstatB.B_cause60=1;
		//			}
		//			else{
		//				tempcdrstatB.B_cause0=0;
		//				tempcdrstatB.B_cause1=0;
		//				tempcdrstatB.B_cause20=0;
		//				tempcdrstatB.B_cause60=0;
		//			}
		//			
		//			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time==0||cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time==0){
		//				tempcdrstatB.B_call_attempt=1;
		//				tempcdrstatB.B_call_not_connected=1;
		//				tempcdrstatB.B_shortcall_1=0;
		//				tempcdrstatB.B_shortcall_2=0;
		//				tempcdrstatB.B_shortcall_3=0;
		//			}
		//			else{
		//				tempcdrstatB.B_call_attempt=1;
		//				tempcdrstatB.B_call_not_connected=0;
		//				if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_1){
		//					tempcdrstatB.B_shortcall_1=1;
		//					tempcdrstatB.B_shortcall_3=0;
		//					tempcdrstatB.B_shortcall_2=0;
		//				}
		//				else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_2){
		//					tempcdrstatB.B_shortcall_2=1;
		//					tempcdrstatB.B_shortcall_3=0;
		//					tempcdrstatB.B_shortcall_1=0;
		//				}
		//				else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<SHORTCALL_THRESHOLD_3){
		//					tempcdrstatB.B_shortcall_3=1;
		//					tempcdrstatB.B_shortcall_1=0;
		//					tempcdrstatB.B_shortcall_2=0;
		//				}
		//				else{
		//					tempcdrstatB.B_shortcall_1=0;
		//					tempcdrstatB.B_shortcall_2=0;
		//					tempcdrstatB.B_shortcall_3=0;
		//				}
		//			}
		//			
		//			int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell%((int)pow((double)10,HASH_NUM_CELLID));

		//			imeicdrfile[fn][temp_hash].push_back(tempcdrstatB);
		//		}
		//	}
		
		if(cdrcount%PROGRESS_THRES==0){
			if((rp[cdrcount].fn-rp[startnum].fn)>=2){
				if(cdr[rp[cdrcount].fn-1].size()>0){
					cdr[rp[cdrcount].fn-1].clear();
				}
			}
			end=clock();
			cout<<"Thread #"<<fn<<" Compute IMEI statistic of Records complete "<<(cdrcount-startnum)*100/(endnum-startnum)<<"% in "<<difftime(end,start)<<" ms\n";
			//cout<<"Compute IMEI statistic of Records No."<<startnum<<" to "<<endnum<<"  in "<<difftime(end,start)<<" ms\n";
		}
	}
	return true;
}
//���imeistat
bool WriteIMEIFile_Combine(std::string temp_result_path_name){
	ofstream fo(temp_result_path_name.c_str(),'w');
	if(fo.is_open()==true){
		fo<<"TAC"<<","<<"IMEI"<<","<<"CellID"<<","<<"A_count0"<<","<<"A_count1"<<","\
			<<"A_count20"<<","<<"A_count60"<<","\
			<<"A_shortcall_1"<<","<<"A_shortcall_2"<<","<<"A_shortcall_3"<<","\
			<<"A_call_attempt"<<","\
			<<"B_count0"<<","<<"B_count1"<<","\
			<<"B_count20"<<","<<"B_count60"<<","\
			<<"B_shortcall_1"<<","<<"B_shortcall_2"<<","<<"B_shortcall_3"<<","\
			<<"B_call_attempt"<<endl;
		for(int fn=0;fn<imeistat.size();fn++){
			for(int i=0;i<imeistat[fn].size();i++){
				if(imeistat[fn][i].IMEI!=""){
					fo<<imeistat[fn][i].TAC<<","<<imeistat[fn][i].IMEI<<","<<imeistat[fn][i].cellid<<","<<imeistat[fn][i].A_cause0<<","<<imeistat[fn][i].A_cause1<<","\
					<<imeistat[fn][i].A_cause20<<","<<imeistat[fn][i].A_cause60<<","\
					<<imeistat[fn][i].A_shortcall_1<<","<<imeistat[fn][i].A_shortcall_2<<","<<imeistat[fn][i].A_shortcall_3<<","\
					<<imeistat[fn][i].A_call_attempt<<","\
					<<imeistat[fn][i].B_cause0<<","<<imeistat[fn][i].B_cause1<<","\
					<<imeistat[fn][i].B_cause20<<","<<imeistat[fn][i].B_cause60<<","\
					<<imeistat[fn][i].B_shortcall_1<<","<<imeistat[fn][i].B_shortcall_2<<","<<imeistat[fn][i].B_shortcall_3<<","\
					<<imeistat[fn][i].B_call_attempt<<endl;
				}
			}	
		}
	}
		
	fo.close();
	return true;
}
//���imeistat_cell
bool WriteIMEIFile_CombineCell(std::string temp_result_path_name){
ofstream fo(temp_result_path_name.c_str(),'w');
	if(fo.is_open()==true){
		fo<<"TAC"<<","<<"IMEI"<<","<<"A_count0"<<","<<"A_count1"<<","\
			<<"A_count20"<<","<<"A_count60"<<","\
			<<"A_shortcall_1"<<","<<"A_shortcall_2"<<","<<"A_shortcall_3"<<","\
			<<"A_call_attempt"<<","\
			<<"B_count0"<<","<<"B_count1"<<","\
			<<"B_count20"<<","<<"B_count60"<<","\
			<<"B_shortcall_1"<<","<<"B_shortcall_2"<<","<<"B_shortcall_3"<<","\
			<<"B_call_attempt"<<endl;
		for(int fn=0;fn<imeistat.size();fn++){
			for(int i=0;i<imeistat[fn].size();i++){
				if(imeistat_cell[fn][i].IMEI!=""){
					fo<<imeistat_cell[fn][i].TAC<<","<<imeistat_cell[fn][i].IMEI<<","<<imeistat_cell[fn][i].A_cause0<<","<<imeistat_cell[fn][i].A_cause1<<","\
					<<imeistat_cell[fn][i].A_cause20<<","<<imeistat_cell[fn][i].A_cause60<<","\
					<<imeistat_cell[fn][i].A_shortcall_1<<","<<imeistat_cell[fn][i].A_shortcall_2<<","<<imeistat_cell[fn][i].A_shortcall_3<<","\
					<<imeistat_cell[fn][i].A_call_attempt<<","\
					<<imeistat_cell[fn][i].B_cause0<<","<<imeistat_cell[fn][i].B_cause1<<","\
					<<imeistat_cell[fn][i].B_cause20<<","<<imeistat_cell[fn][i].B_cause60<<","\
					<<imeistat_cell[fn][i].B_shortcall_1<<","<<imeistat_cell[fn][i].B_shortcall_2<<","<<imeistat_cell[fn][i].B_shortcall_3<<","\
					<<imeistat_cell[fn][i].B_call_attempt<<endl;
				}
			}	
		}
	}
		
	fo.close();
	return true;
}
//������õ�imeicdrfile�в�ͬ��fn�ϲ�����imeistat
bool CombineIMEI(){

	imeistat.clear();
	imeistat.resize((int)pow((double)10,HASH_NUM_IMEI+HASH_NUM_CELLID));

	time_t start,end;
	
	for(int fn=0;fn<imeicdrfile.size();fn++){
		start=clock();
		//��ʼ�ϲ������̲߳�����imei_cdr_statistic
		for(int hn=0;hn<imeicdrfile[fn].size();hn++){
			for(int cr=0;cr<imeicdrfile[fn][hn].size();cr++){
				//��ѯ�Ƿ��Ѿ�����Ӧ��IMEI��¼��
				if(imeicdrfile[fn][hn][cr].IMEI.size()>=MIN_IMEI_LENGTH){
					bool isExistIMEI=false;
					int temp_hash=(int)pow((double)10,HASH_NUM_CELLID)*atoi(imeicdrfile[fn][hn][cr].IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str())+imeicdrfile[fn][hn][cr].cellid%((int)pow((double)10,HASH_NUM_CELLID));

					for(int im=0;im<imeistat[temp_hash].size();im++){
						if(imeistat[temp_hash][im].IMEI==imeicdrfile[fn][hn][cr].IMEI&&imeistat[temp_hash][im].cellid==imeicdrfile[fn][hn][cr].cellid){
							isExistIMEI=true;
							imeistat[temp_hash][im].A_cause0+=imeicdrfile[fn][hn][cr].A_cause0;
							imeistat[temp_hash][im].A_cause1+=imeicdrfile[fn][hn][cr].A_cause1;
							imeistat[temp_hash][im].A_cause20+=imeicdrfile[fn][hn][cr].A_cause20;
							imeistat[temp_hash][im].A_cause60+=imeicdrfile[fn][hn][cr].A_cause60;
							imeistat[temp_hash][im].B_cause0+=imeicdrfile[fn][hn][cr].B_cause0;
							imeistat[temp_hash][im].B_cause1+=imeicdrfile[fn][hn][cr].B_cause1;
							imeistat[temp_hash][im].B_cause20+=imeicdrfile[fn][hn][cr].B_cause20;
							imeistat[temp_hash][im].B_cause60+=imeicdrfile[fn][hn][cr].B_cause60;
							imeistat[temp_hash][im].B_shortcall_1+=imeicdrfile[fn][hn][cr].B_shortcall_1;
							imeistat[temp_hash][im].A_shortcall_1+=imeicdrfile[fn][hn][cr].A_shortcall_1;
							imeistat[temp_hash][im].B_shortcall_2+=imeicdrfile[fn][hn][cr].B_shortcall_2;
							imeistat[temp_hash][im].A_shortcall_2+=imeicdrfile[fn][hn][cr].A_shortcall_2;
							imeistat[temp_hash][im].B_shortcall_3+=imeicdrfile[fn][hn][cr].B_shortcall_3;
							imeistat[temp_hash][im].A_shortcall_3+=imeicdrfile[fn][hn][cr].A_shortcall_3;
							imeistat[temp_hash][im].B_call_attempt+=imeicdrfile[fn][hn][cr].B_call_attempt;
							imeistat[temp_hash][im].A_call_attempt+=imeicdrfile[fn][hn][cr].A_call_attempt;
							//imeistat[temp_hash][im].A_call_not_connected+=imeicdrfile[fn][hn][cr].A_call_not_connected;
							//imeistat[temp_hash][im].B_call_not_connected+=imeicdrfile[fn][hn][cr].B_call_not_connected;
							break;
						}
					}
					if(isExistIMEI==false){
						//���û�еĻ�������
						IMEI_CDR_Statistic tempimei;
						tempimei.IMEI=imeicdrfile[fn][hn][cr].IMEI;
						tempimei.TAC=imeicdrfile[fn][hn][cr].TAC;
						tempimei.cellid=imeicdrfile[fn][hn][cr].cellid;
						tempimei.A_cause0=imeicdrfile[fn][hn][cr].A_cause0;
						tempimei.A_cause1=imeicdrfile[fn][hn][cr].A_cause1;
						tempimei.A_cause20=imeicdrfile[fn][hn][cr].A_cause20;
						tempimei.A_cause60=imeicdrfile[fn][hn][cr].A_cause60;
						tempimei.B_cause0=imeicdrfile[fn][hn][cr].B_cause0;
						tempimei.B_cause1=imeicdrfile[fn][hn][cr].B_cause1;
						tempimei.B_cause20=imeicdrfile[fn][hn][cr].B_cause20;
						tempimei.B_cause60=imeicdrfile[fn][hn][cr].B_cause60;
						tempimei.A_shortcall_1=imeicdrfile[fn][hn][cr].A_shortcall_1;
						tempimei.B_shortcall_1=imeicdrfile[fn][hn][cr].B_shortcall_1;
						tempimei.A_shortcall_2=imeicdrfile[fn][hn][cr].A_shortcall_2;
						tempimei.B_shortcall_2=imeicdrfile[fn][hn][cr].B_shortcall_2;
						tempimei.A_shortcall_3=imeicdrfile[fn][hn][cr].A_shortcall_3;
						tempimei.B_shortcall_3=imeicdrfile[fn][hn][cr].B_shortcall_3;
						tempimei.A_call_attempt=imeicdrfile[fn][hn][cr].A_call_attempt;
						tempimei.B_call_attempt=imeicdrfile[fn][hn][cr].B_call_attempt;
//						tempimei.A_call_not_connected=imeicdrfile[fn][hn][cr].A_call_not_connected;
//						tempimei.B_call_not_connected=imeicdrfile[fn][hn][cr].B_call_not_connected;
						imeistat[temp_hash].push_back(tempimei);
					}
				}
			}
		}
		
		end=clock();
		cout<<"Combine IMEI statistic Records of Thread#"<<fn<<" in "<<difftime(end,start)<<" ms\n";
	}
	
	return true;
}
//��imeistat�в�ͬ��cell�ϲ�����imeistat_cell
bool CombineIMEI_Cell(){
	imeistat_cell.clear();
	imeistat_cell.resize((int)pow((double)10,HASH_NUM_IMEI));

	time_t start,end;
#pragma omp parallel for	
	for(int hn=0;hn<imeistat.size();hn++){
		start=clock();
			for(int cr=0;cr<imeistat[hn].size();cr++){
				//��ѯ�Ƿ��Ѿ�����Ӧ��IMEI��¼��
				if(imeistat[hn][cr].IMEI.size()>=MIN_IMEI_LENGTH){
					bool isExistIMEI=false;
					int temp_hash=atoi(imeistat[hn][cr].IMEI.substr(START_HASH_INDEX_IMEI,HASH_NUM_IMEI).c_str());
					for(int im=0;im<imeistat_cell[temp_hash].size();im++){
						if(imeistat_cell[temp_hash][im].IMEI==imeistat[hn][cr].IMEI){
							isExistIMEI=true;
							imeistat_cell[temp_hash][im].A_cause0+=imeistat[hn][cr].A_cause0;
							imeistat_cell[temp_hash][im].A_cause1+=imeistat[hn][cr].A_cause1;
							imeistat_cell[temp_hash][im].A_cause20+=imeistat[hn][cr].A_cause20;
							imeistat_cell[temp_hash][im].A_cause60+=imeistat[hn][cr].A_cause60;
							imeistat_cell[temp_hash][im].B_cause0+=imeistat[hn][cr].B_cause0;
							imeistat_cell[temp_hash][im].B_cause1+=imeistat[hn][cr].B_cause1;
							imeistat_cell[temp_hash][im].B_cause20+=imeistat[hn][cr].B_cause20;
							imeistat_cell[temp_hash][im].B_cause60+=imeistat[hn][cr].B_cause60;
							imeistat_cell[temp_hash][im].B_shortcall_1+=imeistat[hn][cr].B_shortcall_1;
							imeistat_cell[temp_hash][im].A_shortcall_1+=imeistat[hn][cr].A_shortcall_1;
							imeistat_cell[temp_hash][im].B_shortcall_2+=imeistat[hn][cr].B_shortcall_2;
							imeistat_cell[temp_hash][im].A_shortcall_2+=imeistat[hn][cr].A_shortcall_2;
							imeistat_cell[temp_hash][im].B_shortcall_3+=imeistat[hn][cr].B_shortcall_3;
							imeistat_cell[temp_hash][im].A_shortcall_3+=imeistat[hn][cr].A_shortcall_3;
							imeistat_cell[temp_hash][im].B_call_attempt+=imeistat[hn][cr].B_call_attempt;
							imeistat_cell[temp_hash][im].A_call_attempt+=imeistat[hn][cr].A_call_attempt;
//							imeistat_cell[temp_hash][im].A_call_not_connected+=imeistat[hn][cr].A_call_not_connected;
//							imeistat_cell[temp_hash][im].B_call_not_connected+=imeistat[hn][cr].B_call_not_connected;
							break;
						}
					}
					if(isExistIMEI==false){
						//���û�еĻ�������
						IMEI_CDR_Statistic tempimei;
						tempimei.IMEI=imeistat[hn][cr].IMEI;
						tempimei.TAC=imeistat[hn][cr].TAC;
						tempimei.cellid=-1;
						tempimei.A_cause0=imeistat[hn][cr].A_cause0;
						tempimei.A_cause1=imeistat[hn][cr].A_cause1;
						tempimei.A_cause20=imeistat[hn][cr].A_cause20;
						tempimei.A_cause60=imeistat[hn][cr].A_cause60;
						tempimei.B_cause0=imeistat[hn][cr].B_cause0;
						tempimei.B_cause1=imeistat[hn][cr].B_cause1;
						tempimei.B_cause20=imeistat[hn][cr].B_cause20;
						tempimei.B_cause60=imeistat[hn][cr].B_cause60;
						tempimei.A_shortcall_1=imeistat[hn][cr].A_shortcall_1;
						tempimei.B_shortcall_1=imeistat[hn][cr].B_shortcall_1;
						tempimei.A_shortcall_2=imeistat[hn][cr].A_shortcall_2;
						tempimei.B_shortcall_2=imeistat[hn][cr].B_shortcall_2;
						tempimei.A_shortcall_3=imeistat[hn][cr].A_shortcall_3;
						tempimei.B_shortcall_3=imeistat[hn][cr].B_shortcall_3;
						tempimei.A_call_attempt=imeistat[hn][cr].A_call_attempt;
						tempimei.B_call_attempt=imeistat[hn][cr].B_call_attempt;
//						tempimei.A_call_not_connected=imeistat[hn][cr].A_call_not_connected;
//						tempimei.B_call_not_connected=imeistat[hn][cr].B_call_not_connected;
						imeistat_cell[temp_hash].push_back(tempimei);
					}
				}
			}
		
		end=clock();
		cout<<"Combine IMEI statistic Records with Cell of HASHKEY#"<<hn<<" with "<<imeistat[hn].size()<< " Records in "<<difftime(end,start)<<" ms\n";
	}
	
	return true;
}
