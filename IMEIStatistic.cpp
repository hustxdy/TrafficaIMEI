#include"stdafx.h"
#include"IMEIStatistic.h"
#include<omp.h>
//对进程fn的recordp列表中startnum到endnum对应的cdr进行统计，输出到imeicdrfile
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
		//查找现在的imeicdrfile[fn]中作为主叫是否已经有相应的IMEI记录
		
		if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.size()>=MIN_IMEI_LENGTH){

			//主叫的结束（掉话）小区
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell!=0){
				//结束在2G上
				int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell%((int)pow((double)10,cfg.HASH_NUM_CELLID));

				for(int cr=0;cr<imeicdrfile[fn][temp_hash].size();cr++){
					if(imeicdrfile[fn][temp_hash][cr].timeSection==cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection&&imeicdrfile[fn][temp_hash][cr].IMEI==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI&&imeicdrfile[fn][temp_hash][cr].cellid==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell&&imeicdrfile[fn][temp_hash][cr].network=="GSM"){
						isExistAcallendGSM=true;
						
						//if(cfg.bComputeDistinctIMEI==true){
						//	bool isExistIMEI=false;
						//	bool isExistIMEIandIMSI=false;
						//	if(imeicdrfile[fn][temp_hash][cr].A_IMEI_IMSI_GSM.size()==(int)pow((double)10,cfg.HASH_NUM_IMEI)){
						//		//按照IMEI进行hash
						//		int temp_hash_imei=atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
						//		for(int i=0;i<imeicdrfile[fn][temp_hash][cr].A_IMEI_IMSI_GSM[temp_hash_imei].size();i++){
						//			if(imeicdrfile[fn][temp_hash][cr].A_IMEI_IMSI_GSM[temp_hash_imei][i].IMEI==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI){
						//				isExistIMEI=true;
						//				if(imeicdrfile[fn][temp_hash][cr].A_IMEI_IMSI_GSM[temp_hash_imei][i].IMSI==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMSI){
						//					isExistIMEIandIMSI=true;
						//					break;
						//				}
						//			}
						//		}
						//		if(isExistIMEIandIMSI==false){
						//			//如果IMEI和IMSI组成的对不重复，那么新增一个
						//			IMEI_IMSI tempim;
						//			tempim.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI;
						//			tempim.IMSI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMSI;
						//			imeicdrfile[fn][temp_hash][cr].A_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
						//		}
						//		if(isExistIMEI==false){
						//			//如果IMEI不重复
						//			imeicdrfile[fn][temp_hash][cr].A_IMEI_GSM++;
						//		}
						//	}
						//	else{
						//		//初始化
						//		imeicdrfile[fn][temp_hash][cr].A_IMEI_IMSI_GSM.clear();
						//		imeicdrfile[fn][temp_hash][cr].A_IMEI_IMSI_GSM.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
						//		//加入到A_IMEI_IMSI_GSM中
						//		int temp_hash_imei=atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
						//		IMEI_IMSI tempim;
						//		tempim.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI;
						//		tempim.IMSI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMSI;
						//		imeicdrfile[fn][temp_hash][cr].A_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
						//		imeicdrfile[fn][temp_hash][cr].A_IMEI_GSM=1;
						//	}
						//}
						
						bool isExistCause=false;
						for(int i=0;i<imeicdrfile[fn][temp_hash][cr].A_BSSMAP_Cause.size();i++){
							if(imeicdrfile[fn][temp_hash][cr].A_BSSMAP_Cause[i].cause_id==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause){
								isExistCause=true;
								imeicdrfile[fn][temp_hash][cr].A_BSSMAP_Cause[i].cause_num++;
								break;
							}
						}
						if(isExistCause==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause!=DEFAULT_CAUSE_VALUE){
							//需要新加入一个cause计数单元
							CAUSE_TYPE tempcause;
							tempcause.cause_id=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause;
							tempcause.cause_num=1;
							imeicdrfile[fn][temp_hash][cr].A_BSSMAP_Cause.push_back(tempcause);
						}
						if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time!=0){
							imeicdrfile[fn][temp_hash][cr].A_call_last_cell_connected++;
							imeicdrfile[fn][temp_hash][cr].A_call_last_cell_connected_GSM++;
						}
						
						/*if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause==0){
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
						}*/
						break;
					}
				}
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell==0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_sac!=0){
				//结束在TD上
				int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_sac%((int)pow((double)10,cfg.HASH_NUM_CELLID));

				for(int cr=0;cr<imeicdrfile[fn][temp_hash].size();cr++){
					if(imeicdrfile[fn][temp_hash][cr].timeSection==cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection&&imeicdrfile[fn][temp_hash][cr].IMEI==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI&&imeicdrfile[fn][temp_hash][cr].cellid==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_sac&&imeicdrfile[fn][temp_hash][cr].network=="TD"){
						isExistAcallendTD=true;
						
						bool isExistCause=false;
						for(int i=0;i<imeicdrfile[fn][temp_hash][cr].A_RANAP_Cause.size();i++){
							if(imeicdrfile[fn][temp_hash][cr].A_RANAP_Cause[i].cause_id==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext){
								imeicdrfile[fn][temp_hash][cr].A_RANAP_Cause[i].cause_num++;
								break;
							}
						}
						if(isExistCause==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext!=DEFAULT_CAUSE_VALUE){
							//需要新加入一个cause计数单元
							CAUSE_TYPE tempcause;
							tempcause.cause_id=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext;
							tempcause.cause_num=1;
							imeicdrfile[fn][temp_hash][cr].A_RANAP_Cause.push_back(tempcause);
						}
						if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time!=0){
							imeicdrfile[fn][temp_hash][cr].A_call_last_cell_connected++;
							imeicdrfile[fn][temp_hash][cr].A_call_last_cell_connected_TD++;
						}
						break;
					}
				}
			}
			//主叫的起呼小区
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_cell!=0){
				//起呼在2G上
				int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_cell%((int)pow((double)10,cfg.HASH_NUM_CELLID));

				for(int cr=0;cr<imeicdrfile[fn][temp_hash].size();cr++){
					if(imeicdrfile[fn][temp_hash][cr].timeSection==cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection&&imeicdrfile[fn][temp_hash][cr].IMEI==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI&&imeicdrfile[fn][temp_hash][cr].cellid==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_cell&&imeicdrfile[fn][temp_hash][cr].network=="GSM"){
						isExistAcallstartGSM=true;
						
						bool isExistDXCause=false;
						for(int i=0;i<imeicdrfile[fn][temp_hash][cr].A_DX_Cause_GSM.size();i++){
							if(imeicdrfile[fn][temp_hash][cr].A_DX_Cause_GSM[i].cause_id==cdr[rp[cdrcount].fn][rp[cdrcount].rn].DX_cause){
								isExistDXCause=true;
								imeicdrfile[fn][temp_hash][cr].A_DX_Cause_GSM[i].cause_num++;
								break;
							}
						}
						if(isExistDXCause==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].DX_cause!=DEFAULT_CAUSE_VALUE){
							//需要新加入一个cause计数单元
							CAUSE_TYPE tempcause;
							tempcause.cause_id=cdr[rp[cdrcount].fn][rp[cdrcount].rn].DX_cause;
							tempcause.cause_num=1;
							imeicdrfile[fn][temp_hash][cr].A_DX_Cause_GSM.push_back(tempcause);
						}
						if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time!=0){
							imeicdrfile[fn][temp_hash][cr].A_call_first_cell_connected++;
							imeicdrfile[fn][temp_hash][cr].A_call_first_cell_connected_GSM++;
						}
						//记录短呼数
						imeicdrfile[fn][temp_hash][cr].A_call_attempt++;
						imeicdrfile[fn][temp_hash][cr].A_call_attempt_GSM++;
						if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_1){
							imeicdrfile[fn][temp_hash][cr].A_shortcall_1++;
						}
						else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_2){
							imeicdrfile[fn][temp_hash][cr].A_shortcall_2++;
						}
						else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_3){
							imeicdrfile[fn][temp_hash][cr].A_shortcall_3++;
						}

						break;
					}
				}
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_cell==0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_sac!=0){
				//起呼在TD上
				int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_sac%((int)pow((double)10,cfg.HASH_NUM_CELLID));

				for(int cr=0;cr<imeicdrfile[fn][temp_hash].size();cr++){
					if(imeicdrfile[fn][temp_hash][cr].timeSection==cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection&&imeicdrfile[fn][temp_hash][cr].IMEI==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI&&imeicdrfile[fn][temp_hash][cr].cellid==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_sac&&imeicdrfile[fn][temp_hash][cr].network=="TD"){
						isExistAcallstartTD=true;
						if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time!=0){
							imeicdrfile[fn][temp_hash][cr].A_call_first_cell_connected++;
							imeicdrfile[fn][temp_hash][cr].A_call_first_cell_connected_TD++;
						}
						bool isExistDXCause=false;
						for(int i=0;i<imeicdrfile[fn][temp_hash][cr].A_DX_Cause_TD.size();i++){
							if(imeicdrfile[fn][temp_hash][cr].A_DX_Cause_TD[i].cause_id==cdr[rp[cdrcount].fn][rp[cdrcount].rn].DX_cause){
								isExistDXCause=true;
								imeicdrfile[fn][temp_hash][cr].A_DX_Cause_TD[i].cause_num++;
								break;
							}
						}
						if(isExistDXCause==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].DX_cause!=DEFAULT_CAUSE_VALUE){
							//需要新加入一个cause计数单元
							CAUSE_TYPE tempcause;
							tempcause.cause_id=cdr[rp[cdrcount].fn][rp[cdrcount].rn].DX_cause;
							tempcause.cause_num=1;
							imeicdrfile[fn][temp_hash][cr].A_DX_Cause_TD.push_back(tempcause);
						}
						//记录短呼数
						imeicdrfile[fn][temp_hash][cr].A_call_attempt++;
						imeicdrfile[fn][temp_hash][cr].A_call_attempt_TD++;
						if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_1){
							imeicdrfile[fn][temp_hash][cr].A_shortcall_1++;
						}
						else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_2){
							imeicdrfile[fn][temp_hash][cr].A_shortcall_2++;
						}
						else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_3){
							imeicdrfile[fn][temp_hash][cr].A_shortcall_3++;
						}

						break;
					}
				}
			}
		}
					
		//查找现在的imeicdrfile[fn]中作为被叫是否已经有相应的IMEI记录
		
		if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.size()>=MIN_IMEI_LENGTH){
			
			//被叫的结束小区
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell!=0){
				//结束在2G小区
				int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell%((int)pow((double)10,cfg.HASH_NUM_CELLID));

				for(int cr=0;cr<imeicdrfile[fn][temp_hash].size();cr++){
					if(imeicdrfile[fn][temp_hash][cr].timeSection==cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection&&imeicdrfile[fn][temp_hash][cr].IMEI==cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI&&imeicdrfile[fn][temp_hash][cr].cellid==cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell&&imeicdrfile[fn][temp_hash][cr].network=="GSM"){
						isExistBcallendGSM=true;
			
						bool isExistCause=false;
						for(int i=0;i<imeicdrfile[fn][temp_hash][cr].B_BSSMAP_Cause.size();i++){
							if(imeicdrfile[fn][temp_hash][cr].B_BSSMAP_Cause[i].cause_id==cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause){
								isExistCause=true;
								imeicdrfile[fn][temp_hash][cr].B_BSSMAP_Cause[i].cause_num++;
								break;
							}
						}
						if(isExistCause==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause!=DEFAULT_CAUSE_VALUE){
							//需要新加入一个cause计数单元
							CAUSE_TYPE tempcause;
							tempcause.cause_id=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause;
							tempcause.cause_num=1;
							imeicdrfile[fn][temp_hash][cr].B_BSSMAP_Cause.push_back(tempcause);
						}
						if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time!=0){
							imeicdrfile[fn][temp_hash][cr].B_call_last_cell_connected++;
							imeicdrfile[fn][temp_hash][cr].B_call_last_cell_connected_GSM++;
						}
						break;
					}
				}
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell==0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_sac!=0){
				//结束在TD小区
				int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_sac%((int)pow((double)10,cfg.HASH_NUM_CELLID));

				for(int cr=0;cr<imeicdrfile[fn][temp_hash].size();cr++){
					if(imeicdrfile[fn][temp_hash][cr].timeSection==cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection&&imeicdrfile[fn][temp_hash][cr].IMEI==cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI&&imeicdrfile[fn][temp_hash][cr].cellid==cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_sac&&imeicdrfile[fn][temp_hash][cr].network=="TD"){
						isExistBcallendTD=true;
						
						bool isExistCause=false;
						for(int i=0;i<imeicdrfile[fn][temp_hash][cr].B_RANAP_Cause.size();i++){
							if(imeicdrfile[fn][temp_hash][cr].B_RANAP_Cause[i].cause_id==cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext){
								isExistCause=true;
								imeicdrfile[fn][temp_hash][cr].B_RANAP_Cause[i].cause_num++;
								break;
							}
						}
						if(isExistCause==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext!=DEFAULT_CAUSE_VALUE){
							//需要新加入一个cause计数单元
							CAUSE_TYPE tempcause;
							tempcause.cause_id=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext;
							tempcause.cause_num=1;
							imeicdrfile[fn][temp_hash][cr].B_RANAP_Cause.push_back(tempcause);
						}
						if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time!=0){
							imeicdrfile[fn][temp_hash][cr].B_call_last_cell_connected++;
							imeicdrfile[fn][temp_hash][cr].B_call_last_cell_connected_TD++;
						}
						break;
					}
				}
			}
			//被叫的接听小区
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_cell!=0){
				//在GSM小区开始接听
				int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_cell%((int)pow((double)10,cfg.HASH_NUM_CELLID));

				for(int cr=0;cr<imeicdrfile[fn][temp_hash].size();cr++){
					if(imeicdrfile[fn][temp_hash][cr].timeSection==cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection&&imeicdrfile[fn][temp_hash][cr].IMEI==cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI&&imeicdrfile[fn][temp_hash][cr].cellid==cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_cell&&imeicdrfile[fn][temp_hash][cr].network=="GSM"){
						isExistBcallstartGSM=true;
						
						bool isExistDXCause=false;
						for(int i=0;i<imeicdrfile[fn][temp_hash][cr].B_DX_Cause_GSM.size();i++){
							if(imeicdrfile[fn][temp_hash][cr].B_DX_Cause_GSM[i].cause_id==cdr[rp[cdrcount].fn][rp[cdrcount].rn].DX_cause){
								isExistDXCause=true;
								imeicdrfile[fn][temp_hash][cr].B_DX_Cause_GSM[i].cause_num++;
								break;
							}
						}
						if(isExistDXCause==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].DX_cause!=DEFAULT_CAUSE_VALUE){
							//需要新加入一个cause计数单元
							CAUSE_TYPE tempcause;
							tempcause.cause_id=cdr[rp[cdrcount].fn][rp[cdrcount].rn].DX_cause;
							tempcause.cause_num=1;
							imeicdrfile[fn][temp_hash][cr].B_DX_Cause_GSM.push_back(tempcause);
						}
						if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time!=0){
							imeicdrfile[fn][temp_hash][cr].B_call_first_cell_connected++;
							imeicdrfile[fn][temp_hash][cr].B_call_first_cell_connected_GSM++;
						}
						//记录短呼数
						imeicdrfile[fn][temp_hash][cr].B_call_attempt++;
						imeicdrfile[fn][temp_hash][cr].B_call_attempt_GSM++;
						if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_1){
							imeicdrfile[fn][temp_hash][cr].B_shortcall_1++;
						}
						else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_2){
							imeicdrfile[fn][temp_hash][cr].B_shortcall_2++;
						}
						else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_3){
							imeicdrfile[fn][temp_hash][cr].B_shortcall_3++;
						}
						break;
					}
				}
			}
			else if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_cell==0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_sac!=0){
				//在TD小区开始接听
				int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_sac%((int)pow((double)10,cfg.HASH_NUM_CELLID));

				for(int cr=0;cr<imeicdrfile[fn][temp_hash].size();cr++){
					if(imeicdrfile[fn][temp_hash][cr].timeSection==cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection&&imeicdrfile[fn][temp_hash][cr].IMEI==cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI&&imeicdrfile[fn][temp_hash][cr].cellid==cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_sac&&imeicdrfile[fn][temp_hash][cr].network=="TD"){
						isExistBcallstartTD=true;
						
						bool isExistDXCause=false;
						for(int i=0;i<imeicdrfile[fn][temp_hash][cr].B_DX_Cause_TD.size();i++){
							if(imeicdrfile[fn][temp_hash][cr].B_DX_Cause_TD[i].cause_id==cdr[rp[cdrcount].fn][rp[cdrcount].rn].DX_cause){
								isExistDXCause=true;
								imeicdrfile[fn][temp_hash][cr].B_DX_Cause_TD[i].cause_num++;
								break;
							}
						}
						if(isExistDXCause==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].DX_cause!=DEFAULT_CAUSE_VALUE){
							//需要新加入一个cause计数单元
							CAUSE_TYPE tempcause;
							tempcause.cause_id=cdr[rp[cdrcount].fn][rp[cdrcount].rn].DX_cause;
							tempcause.cause_num=1;
							imeicdrfile[fn][temp_hash][cr].B_DX_Cause_TD.push_back(tempcause);
						}
						if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time!=0){
							imeicdrfile[fn][temp_hash][cr].B_call_first_cell_connected++;
							imeicdrfile[fn][temp_hash][cr].B_call_first_cell_connected_TD++;
						}
						//记录短呼数
						imeicdrfile[fn][temp_hash][cr].B_call_attempt++;
						imeicdrfile[fn][temp_hash][cr].B_call_attempt_TD++;
						if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_1){
							imeicdrfile[fn][temp_hash][cr].B_shortcall_1++;
						}
						else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_2){
							imeicdrfile[fn][temp_hash][cr].B_shortcall_2++;
						}
						else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_3){
							imeicdrfile[fn][temp_hash][cr].B_shortcall_3++;
						}
						break;
					}
				}
			}
		}
		
		if(isExistAcallendGSM==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell!=0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.size()>=MIN_IMEI_LENGTH){
			//不存在主叫结束时的GSM小区的统计
			IMEI_CDR_Statistic tempcdrstat;
			tempcdrstat.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI;
			tempcdrstat.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(0,TAC_LENGTH);
			tempcdrstat.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell;
			tempcdrstat.network="GSM";
			tempcdrstat.timeSection=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection;
			tempcdrstat.timeSectionStartTime=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSectionStartTime;
			tempcdrstat.A_call_attempt=0;
			tempcdrstat.A_call_attempt_GSM=0;
			tempcdrstat.A_call_attempt_TD=0;			
			tempcdrstat.A_shortcall_1=0;
			tempcdrstat.A_shortcall_2=0;
			tempcdrstat.A_shortcall_3=0;
			tempcdrstat.B_call_attempt=0;
			tempcdrstat.B_call_attempt_GSM=0;
			tempcdrstat.B_call_attempt_TD=0;
			tempcdrstat.B_shortcall_1=0;
			tempcdrstat.B_shortcall_2=0;
			tempcdrstat.B_shortcall_3=0;
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

			CAUSE_TYPE tempcause;
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause!=DEFAULT_CAUSE_VALUE){
				tempcause.cause_id=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause;
				tempcause.cause_num=1;
				tempcdrstat.A_BSSMAP_Cause.push_back(tempcause);
			}
			/*if(cfg.bComputeDistinctIMEI==true){
				tempcdrstat.A_IMEI_IMSI_GSM.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
				int temp_hash_imei=atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
				IMEI_IMSI tempim;
				tempim.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI;
				tempim.IMSI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMSI;
				tempcdrstat.A_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
				tempcdrstat.A_IMEI_GSM=1;
			}*/
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time!=0){
				tempcdrstat.A_call_last_cell_connected=1;
				tempcdrstat.A_call_last_cell_connected_GSM=1;
			}
			int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell%((int)pow((double)10,cfg.HASH_NUM_CELLID));
			imeicdrfile[fn][temp_hash].push_back(tempcdrstat);
		}

		if(isExistAcallendTD==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_sac!=0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell==0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.size()>=MIN_IMEI_LENGTH){
			//不存在主叫结束时的TD小区的统计
			IMEI_CDR_Statistic tempcdrstat;
			tempcdrstat.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI;
			tempcdrstat.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(0,TAC_LENGTH);
			tempcdrstat.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_sac;
			tempcdrstat.network="TD";
			tempcdrstat.timeSection=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection;
			tempcdrstat.timeSectionStartTime=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSectionStartTime;
			tempcdrstat.A_call_attempt=0;
			tempcdrstat.A_call_attempt_GSM=0;
			tempcdrstat.A_call_attempt_TD=0;
			tempcdrstat.A_shortcall_1=0;
			tempcdrstat.A_shortcall_2=0;
			tempcdrstat.A_shortcall_3=0;
			tempcdrstat.B_call_attempt=0;
			tempcdrstat.B_call_attempt_GSM=0;
			tempcdrstat.B_call_attempt_TD=0;
			tempcdrstat.B_shortcall_1=0;
			tempcdrstat.B_shortcall_2=0;
			tempcdrstat.B_shortcall_3=0;
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

			CAUSE_TYPE tempcause;
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext!=DEFAULT_CAUSE_VALUE){
				tempcause.cause_id=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_BSSMAP_cause_ext;
				tempcause.cause_num=1;
				tempcdrstat.A_RANAP_Cause.push_back(tempcause);
			}
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time!=0){
				tempcdrstat.A_call_last_cell_connected=1;
				tempcdrstat.A_call_last_cell_connected_TD=1;
			}
			int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_sac%((int)pow((double)10,cfg.HASH_NUM_CELLID));
			imeicdrfile[fn][temp_hash].push_back(tempcdrstat);
		}

		if(isExistAcallstartGSM==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_cell!=0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.size()>=MIN_IMEI_LENGTH){
			//不存在主叫起呼时的GSM小区的统计
			IMEI_CDR_Statistic tempcdrstat;
			tempcdrstat.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI;
			tempcdrstat.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(0,TAC_LENGTH);
			tempcdrstat.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_cell;
			tempcdrstat.network="GSM";
			tempcdrstat.timeSection=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection;
			tempcdrstat.timeSectionStartTime=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSectionStartTime;
			tempcdrstat.A_call_attempt=1;
			tempcdrstat.A_call_attempt_GSM=1;
			tempcdrstat.A_call_attempt_TD=0;
			tempcdrstat.B_call_attempt=0;
			tempcdrstat.B_call_attempt_GSM=0;
			tempcdrstat.B_call_attempt_TD=0;
			tempcdrstat.B_shortcall_1=0;
			tempcdrstat.B_shortcall_2=0;
			tempcdrstat.B_shortcall_3=0;
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
			
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].DX_cause!=DEFAULT_CAUSE_VALUE){
				CAUSE_TYPE tempDXcause;
				tempDXcause.cause_id=cdr[rp[cdrcount].fn][rp[cdrcount].rn].DX_cause;
				tempDXcause.cause_num=1;
				tempcdrstat.A_DX_Cause_GSM.push_back(tempDXcause);
			}
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time!=0){
				tempcdrstat.A_call_first_cell_connected=1;
				tempcdrstat.A_call_first_cell_connected_GSM=1;
			}

			if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_1){
				tempcdrstat.A_shortcall_1=1;
				tempcdrstat.A_shortcall_2=0;
				tempcdrstat.A_shortcall_3=0;
			}
			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_2&&difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)>=cfg.SHORTCALL_THRESHOLD_1){
				tempcdrstat.A_shortcall_2=1;
				tempcdrstat.A_shortcall_1=0;
				tempcdrstat.A_shortcall_3=0;
			}
			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_3&&difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)>=cfg.SHORTCALL_THRESHOLD_2){
				tempcdrstat.A_shortcall_3=1;
				tempcdrstat.A_shortcall_2=0;
				tempcdrstat.A_shortcall_1=0;
			}
			else{
				tempcdrstat.A_shortcall_3=0;
				tempcdrstat.A_shortcall_2=0;
				tempcdrstat.A_shortcall_1=0;
			}
			int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_cell%((int)pow((double)10,cfg.HASH_NUM_CELLID));
			imeicdrfile[fn][temp_hash].push_back(tempcdrstat);
		}

		if(isExistAcallstartTD==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_sac!=0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_cell==0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.size()>=MIN_IMEI_LENGTH){
			//不存在主叫起呼时的TD小区的统计
			IMEI_CDR_Statistic tempcdrstat;
			tempcdrstat.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI;
			tempcdrstat.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(0,TAC_LENGTH);
			tempcdrstat.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_sac;
			tempcdrstat.network="TD";
			tempcdrstat.timeSection=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection;
			tempcdrstat.timeSectionStartTime=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSectionStartTime;
			tempcdrstat.A_call_attempt=1;
			tempcdrstat.A_call_attempt_GSM=0;
			tempcdrstat.A_call_attempt_TD=1;
			tempcdrstat.B_call_attempt=0;
			tempcdrstat.B_call_attempt_GSM=0;
			tempcdrstat.B_call_attempt_TD=0;
			tempcdrstat.B_shortcall_1=0;
			tempcdrstat.B_shortcall_2=0;
			tempcdrstat.B_shortcall_3=0;
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

			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].DX_cause!=DEFAULT_CAUSE_VALUE){
				CAUSE_TYPE tempDXcause;
				tempDXcause.cause_id=cdr[rp[cdrcount].fn][rp[cdrcount].rn].DX_cause;
				tempDXcause.cause_num=1;
				tempcdrstat.A_DX_Cause_TD.push_back(tempDXcause);
			}
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time!=0){
				tempcdrstat.A_call_first_cell_connected=1;
				tempcdrstat.A_call_first_cell_connected_TD=1;
			}

			if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_1){
				tempcdrstat.A_shortcall_1=1;
				tempcdrstat.A_shortcall_2=0;
				tempcdrstat.A_shortcall_3=0;
			}
			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_2&&difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)>=cfg.SHORTCALL_THRESHOLD_1){
				tempcdrstat.A_shortcall_2=1;
				tempcdrstat.A_shortcall_1=0;
				tempcdrstat.A_shortcall_3=0;
			}
			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_3&&difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)>=cfg.SHORTCALL_THRESHOLD_2){
				tempcdrstat.A_shortcall_3=1;
				tempcdrstat.A_shortcall_2=0;
				tempcdrstat.A_shortcall_1=0;
			}
			else{
				tempcdrstat.A_shortcall_3=0;
				tempcdrstat.A_shortcall_2=0;
				tempcdrstat.A_shortcall_1=0;
			}
			int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_first_sac%((int)pow((double)10,cfg.HASH_NUM_CELLID));
			imeicdrfile[fn][temp_hash].push_back(tempcdrstat);
		}

		if(isExistBcallendGSM==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell!=0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.size()>=MIN_IMEI_LENGTH){
			//不存在被叫结束时的GSM小区的统计
			IMEI_CDR_Statistic tempcdrstat;
			tempcdrstat.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI;
			tempcdrstat.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(0,TAC_LENGTH);
			tempcdrstat.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell;
			tempcdrstat.network="GSM";
			tempcdrstat.timeSection=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection;
			tempcdrstat.timeSectionStartTime=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSectionStartTime;
			tempcdrstat.A_call_attempt=0;
			tempcdrstat.A_call_attempt_GSM=0;
			tempcdrstat.A_call_attempt_TD=0;
			tempcdrstat.A_shortcall_1=0;
			tempcdrstat.A_shortcall_2=0;
			tempcdrstat.A_shortcall_3=0;
			tempcdrstat.B_call_attempt=0;
			tempcdrstat.B_call_attempt_GSM=0;
			tempcdrstat.B_call_attempt_TD=0;
			tempcdrstat.B_shortcall_1=0;
			tempcdrstat.B_shortcall_2=0;
			tempcdrstat.B_shortcall_3=0;
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
			
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause!=DEFAULT_CAUSE_VALUE){
				CAUSE_TYPE tempcause;
				tempcause.cause_id=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause;
				tempcause.cause_num=1;
				tempcdrstat.B_BSSMAP_Cause.push_back(tempcause);
			}
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time!=0){
				tempcdrstat.B_call_last_cell_connected=1;
				tempcdrstat.B_call_last_cell_connected_GSM=1;
			}
			int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell%((int)pow((double)10,cfg.HASH_NUM_CELLID));
			imeicdrfile[fn][temp_hash].push_back(tempcdrstat);
		}

		if(isExistBcallendTD==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_sac!=0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_cell==0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.size()>=MIN_IMEI_LENGTH){
			//不存在被叫结束时的TD小区的统计
			IMEI_CDR_Statistic tempcdrstat;
			tempcdrstat.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI;
			tempcdrstat.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(0,TAC_LENGTH);
			tempcdrstat.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_sac;
			tempcdrstat.network="TD";
			tempcdrstat.timeSection=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection;
			tempcdrstat.timeSectionStartTime=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSectionStartTime;
			tempcdrstat.A_call_attempt=0;
			tempcdrstat.A_call_attempt_GSM=0;
			tempcdrstat.A_call_attempt_TD=0;
			tempcdrstat.A_shortcall_1=0;
			tempcdrstat.A_shortcall_2=0;
			tempcdrstat.A_shortcall_3=0;
			tempcdrstat.B_call_attempt=0;
			tempcdrstat.B_call_attempt_GSM=0;
			tempcdrstat.B_call_attempt_TD=0;		
			tempcdrstat.B_shortcall_1=0;
			tempcdrstat.B_shortcall_2=0;
			tempcdrstat.B_shortcall_3=0;
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
						
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext!=DEFAULT_CAUSE_VALUE){
				CAUSE_TYPE tempcause;
				tempcause.cause_id=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_BSSMAP_cause_ext;
				tempcause.cause_num=1;
				tempcdrstat.B_RANAP_Cause.push_back(tempcause);
			}
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time!=0){
				tempcdrstat.B_call_last_cell_connected=1;
				tempcdrstat.B_call_last_cell_connected_TD=1;
			}
			int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_sac%((int)pow((double)10,cfg.HASH_NUM_CELLID));
			imeicdrfile[fn][temp_hash].push_back(tempcdrstat);
		}

		if(isExistBcallstartGSM==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_cell!=0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.size()>=MIN_IMEI_LENGTH){
			//不存在被叫接听时的GSM小区的统计
			IMEI_CDR_Statistic tempcdrstat;
			tempcdrstat.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI;
			tempcdrstat.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(0,TAC_LENGTH);
			tempcdrstat.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_cell;
			tempcdrstat.network="GSM";
			tempcdrstat.timeSection=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection;
			tempcdrstat.timeSectionStartTime=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSectionStartTime;
			tempcdrstat.A_call_attempt=0;
			tempcdrstat.A_call_attempt_GSM=0;
			tempcdrstat.A_call_attempt_TD=0;
			tempcdrstat.A_shortcall_1=0;
			tempcdrstat.A_shortcall_2=0;
			tempcdrstat.A_shortcall_3=0;
			tempcdrstat.B_call_attempt=1;
			tempcdrstat.B_call_attempt_GSM=1;
			tempcdrstat.B_call_attempt_TD=0;	
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
			
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].DX_cause!=DEFAULT_CAUSE_VALUE){
				CAUSE_TYPE tempDXcause;
				tempDXcause.cause_id=cdr[rp[cdrcount].fn][rp[cdrcount].rn].DX_cause;
				tempDXcause.cause_num=1;
				tempcdrstat.B_DX_Cause_GSM.push_back(tempDXcause);
			}
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time!=0){
				tempcdrstat.B_call_first_cell_connected=1;
				tempcdrstat.B_call_first_cell_connected_GSM=1;
			}

			if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_1){
				tempcdrstat.B_shortcall_1=1;
				tempcdrstat.B_shortcall_2=0;
				tempcdrstat.B_shortcall_3=0;
			}
			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_2&&difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)>=cfg.SHORTCALL_THRESHOLD_1){
				tempcdrstat.B_shortcall_2=1;
				tempcdrstat.B_shortcall_1=0;
				tempcdrstat.B_shortcall_3=0;
			}
			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_3&&difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)>=cfg.SHORTCALL_THRESHOLD_2){
				tempcdrstat.B_shortcall_3=1;
				tempcdrstat.B_shortcall_2=0;
				tempcdrstat.B_shortcall_1=0;
			}
			else{
				tempcdrstat.B_shortcall_3=0;
				tempcdrstat.B_shortcall_2=0;
				tempcdrstat.B_shortcall_1=0;
			}
			int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_cell%((int)pow((double)10,cfg.HASH_NUM_CELLID));
			imeicdrfile[fn][temp_hash].push_back(tempcdrstat);
		}

		if(isExistBcallstartTD==false&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_sac!=0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_cell==0&&cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.size()>=MIN_IMEI_LENGTH){
			//不存在被叫接听时的TD小区的统计
			IMEI_CDR_Statistic tempcdrstat;
			tempcdrstat.IMEI=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI;
			tempcdrstat.TAC=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(0,TAC_LENGTH);
			tempcdrstat.cellid=cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_sac;
			tempcdrstat.network="TD";
			tempcdrstat.timeSection=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection;
			tempcdrstat.timeSectionStartTime=cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSectionStartTime;
			tempcdrstat.A_call_attempt=0;
			tempcdrstat.A_call_attempt_GSM=0;
			tempcdrstat.A_call_attempt_TD=0;
			tempcdrstat.A_shortcall_1=0;
			tempcdrstat.A_shortcall_2=0;
			tempcdrstat.A_shortcall_3=0;
			tempcdrstat.B_call_attempt=1;
			tempcdrstat.B_call_attempt_GSM=0;
			tempcdrstat.B_call_attempt_TD=1;
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

			CAUSE_TYPE tempDXcause;
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].DX_cause!=DEFAULT_CAUSE_VALUE){
				tempDXcause.cause_id=cdr[rp[cdrcount].fn][rp[cdrcount].rn].DX_cause;
				tempDXcause.cause_num=1;
				tempcdrstat.B_DX_Cause_TD.push_back(tempDXcause);
			}
			if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time!=0){
				tempcdrstat.B_call_first_cell_connected=1;
				tempcdrstat.B_call_first_cell_connected_TD=1;
			}

			if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_1){
				tempcdrstat.B_shortcall_1=1;
				tempcdrstat.B_shortcall_2=0;
				tempcdrstat.B_shortcall_3=0;
			}
			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_2&&difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)>=cfg.SHORTCALL_THRESHOLD_1){
				tempcdrstat.B_shortcall_2=1;
				tempcdrstat.B_shortcall_1=0;
				tempcdrstat.B_shortcall_3=0;
			}
			else if(difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)<cfg.SHORTCALL_THRESHOLD_3&&difftime(cdr[rp[cdrcount].fn][rp[cdrcount].rn].charging_end_time,cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_answered_time)>=cfg.SHORTCALL_THRESHOLD_2){
				tempcdrstat.B_shortcall_3=1;
				tempcdrstat.B_shortcall_2=0;
				tempcdrstat.B_shortcall_1=0;
			}
			else{
				tempcdrstat.B_shortcall_3=0;
				tempcdrstat.B_shortcall_2=0;
				tempcdrstat.B_shortcall_1=0;
			}
			int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].B_first_sac%((int)pow((double)10,cfg.HASH_NUM_CELLID));
			imeicdrfile[fn][temp_hash].push_back(tempcdrstat);
		}

		//if(isExistA==false&&isExistB==true){
		//	//不存在A，新起一个记录
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
		//	//不存在B，新起一个记录
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
		//		//一样的IMEI,且一样的cellid
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
		//			//不一样的IMEI,分开加入
		//			//生成A的IMEI条目
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
		//			//生成B的IMEI条目
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

bool ComputeDistinctIMEI(int fn,int startnum,int endnum){
	time_t start,end;
	start=clock();
	for(int cdrcount=startnum;cdrcount<=endnum;cdrcount++){
		bool isExistA=false;
		bool isExistB=false;
		if(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.size()>=MIN_IMEI_LENGTH){
			int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell%((int)pow((double)10,cfg.HASH_NUM_CELLID));

			for(int cr=0;cr<imeidistinct[fn][temp_hash].size();cr++){
				if(imeicdrfile[fn][temp_hash][cr].timeSection==cdr[rp[cdrcount].fn][rp[cdrcount].rn].timeSection&&imeicdrfile[fn][temp_hash][cr].IMEI==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_IMEI&&imeicdrfile[fn][temp_hash][cr].cellid==cdr[rp[cdrcount].fn][rp[cdrcount].rn].A_cell&&imeicdrfile[fn][temp_hash][cr].network=="GSM"){
					isExistA=true;
				}
			}
		}
	}
}