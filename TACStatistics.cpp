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
	taccdrfile[fn].resize((int)pow((double)10,cfg.HASH_NUM_IMEI+cfg.HASH_NUM_CELLID));

	for(int hn=0;hn<imeicdrfile[fn].size();hn++){
		
		for(int cr=0;cr<imeicdrfile[fn][hn].size();cr++){
			//查询是否已经有相应的TAC记录
			
			bool isExistTAC=false;
			int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(imeicdrfile[fn][hn][cr].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+imeicdrfile[fn][hn][cr].cellid%((int)pow((double)10,cfg.HASH_NUM_CELLID));

			for(int i=0;i<taccdrfile[fn][temp_hash].size();i++){
				if(taccdrfile[fn][temp_hash][i].timeSection==imeicdrfile[fn][hn][cr].timeSection&&taccdrfile[fn][temp_hash][i].TAC==imeicdrfile[fn][hn][cr].TAC&&taccdrfile[fn][temp_hash][i].cellid==imeicdrfile[fn][hn][cr].cellid&&taccdrfile[fn][temp_hash][i].network==imeicdrfile[fn][hn][cr].network){
					isExistTAC=true;
					/*taccdrfile[fn][temp_hash][i].A_cause0+=imeicdrfile[fn][hn][cr].A_cause0;
					taccdrfile[fn][temp_hash][i].A_cause1+=imeicdrfile[fn][hn][cr].A_cause1;
					taccdrfile[fn][temp_hash][i].A_cause20+=imeicdrfile[fn][hn][cr].A_cause20;
					taccdrfile[fn][temp_hash][i].A_cause60+=imeicdrfile[fn][hn][cr].A_cause60;
					taccdrfile[fn][temp_hash][i].B_cause0+=imeicdrfile[fn][hn][cr].B_cause0;
					taccdrfile[fn][temp_hash][i].B_cause1+=imeicdrfile[fn][hn][cr].B_cause1;
					taccdrfile[fn][temp_hash][i].B_cause20+=imeicdrfile[fn][hn][cr].B_cause20;
					taccdrfile[fn][temp_hash][i].B_cause60+=imeicdrfile[fn][hn][cr].B_cause60;
					taccdrfile[fn][temp_hash][i].A_causeGSM+=imeicdrfile[fn][hn][cr].A_causeGSM;
					taccdrfile[fn][temp_hash][i].B_causeGSM+=imeicdrfile[fn][hn][cr].B_causeGSM;
					*/
					
					for(int j=0;j<imeicdrfile[fn][hn][cr].A_BSSMAP_Cause.size();j++){
						bool isExistCause=false;
						for(int k=0;k<taccdrfile[fn][temp_hash][i].A_BSSMAP_Cause.size();k++){
							if(taccdrfile[fn][temp_hash][i].A_BSSMAP_Cause[k].cause_id==imeicdrfile[fn][hn][cr].A_BSSMAP_Cause[j].cause_id){
								isExistCause=true;
								taccdrfile[fn][temp_hash][i].A_BSSMAP_Cause[k].cause_num+=imeicdrfile[fn][hn][cr].A_BSSMAP_Cause[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=imeicdrfile[fn][hn][cr].A_BSSMAP_Cause[j].cause_id;
							tempcause.cause_num=imeicdrfile[fn][hn][cr].A_BSSMAP_Cause[j].cause_num;
							taccdrfile[fn][temp_hash][i].A_BSSMAP_Cause.push_back(tempcause);
						}
					}
					for(int j=0;j<imeicdrfile[fn][hn][cr].B_BSSMAP_Cause.size();j++){
						bool isExistCause=false;
						for(int k=0;k<taccdrfile[fn][temp_hash][i].B_BSSMAP_Cause.size();k++){
							if(taccdrfile[fn][temp_hash][i].B_BSSMAP_Cause[k].cause_id==imeicdrfile[fn][hn][cr].B_BSSMAP_Cause[j].cause_id){
								isExistCause=true;
								taccdrfile[fn][temp_hash][i].B_BSSMAP_Cause[k].cause_num+=imeicdrfile[fn][hn][cr].B_BSSMAP_Cause[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=imeicdrfile[fn][hn][cr].B_BSSMAP_Cause[j].cause_id;
							tempcause.cause_num=imeicdrfile[fn][hn][cr].B_BSSMAP_Cause[j].cause_num;
							taccdrfile[fn][temp_hash][i].B_BSSMAP_Cause.push_back(tempcause);
						}
					}
					for(int j=0;j<imeicdrfile[fn][hn][cr].A_RANAP_Cause.size();j++){
						bool isExistCause=false;
						for(int k=0;k<taccdrfile[fn][temp_hash][i].A_RANAP_Cause.size();k++){
							if(taccdrfile[fn][temp_hash][i].A_RANAP_Cause[k].cause_id==imeicdrfile[fn][hn][cr].A_RANAP_Cause[j].cause_id){
								isExistCause=true;
								taccdrfile[fn][temp_hash][i].A_RANAP_Cause[k].cause_num+=imeicdrfile[fn][hn][cr].A_RANAP_Cause[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=imeicdrfile[fn][hn][cr].A_RANAP_Cause[j].cause_id;
							tempcause.cause_num=imeicdrfile[fn][hn][cr].A_RANAP_Cause[j].cause_num;
							taccdrfile[fn][temp_hash][i].A_RANAP_Cause.push_back(tempcause);
						}
					}
					for(int j=0;j<imeicdrfile[fn][hn][cr].B_RANAP_Cause.size();j++){
						bool isExistCause=false;
						for(int k=0;k<taccdrfile[fn][temp_hash][i].B_RANAP_Cause.size();k++){
							if(taccdrfile[fn][temp_hash][i].B_RANAP_Cause[k].cause_id==imeicdrfile[fn][hn][cr].B_RANAP_Cause[j].cause_id){
								isExistCause=true;
								taccdrfile[fn][temp_hash][i].B_RANAP_Cause[k].cause_num+=imeicdrfile[fn][hn][cr].B_RANAP_Cause[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=imeicdrfile[fn][hn][cr].B_RANAP_Cause[j].cause_id;
							tempcause.cause_num=imeicdrfile[fn][hn][cr].B_RANAP_Cause[j].cause_num;
							taccdrfile[fn][temp_hash][i].B_RANAP_Cause.push_back(tempcause);
						}
					}
					for(int j=0;j<imeicdrfile[fn][hn][cr].A_DX_Cause_GSM.size();j++){
						bool isExistCause=false;
						for(int k=0;k<taccdrfile[fn][temp_hash][i].A_DX_Cause_GSM.size();k++){
							if(taccdrfile[fn][temp_hash][i].A_DX_Cause_GSM[k].cause_id==imeicdrfile[fn][hn][cr].A_DX_Cause_GSM[j].cause_id){
								isExistCause=true;
								taccdrfile[fn][temp_hash][i].A_DX_Cause_GSM[k].cause_num+=imeicdrfile[fn][hn][cr].A_DX_Cause_GSM[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=imeicdrfile[fn][hn][cr].A_DX_Cause_GSM[j].cause_id;
							tempcause.cause_num=imeicdrfile[fn][hn][cr].A_DX_Cause_GSM[j].cause_num;
							taccdrfile[fn][temp_hash][i].A_DX_Cause_GSM.push_back(tempcause);
						}
					}
					for(int j=0;j<imeicdrfile[fn][hn][cr].A_DX_Cause_TD.size();j++){
						bool isExistCause=false;
						for(int k=0;k<taccdrfile[fn][temp_hash][i].A_DX_Cause_TD.size();k++){
							if(taccdrfile[fn][temp_hash][i].A_DX_Cause_TD[k].cause_id==imeicdrfile[fn][hn][cr].A_DX_Cause_TD[j].cause_id){
								isExistCause=true;
								taccdrfile[fn][temp_hash][i].A_DX_Cause_TD[k].cause_num+=imeicdrfile[fn][hn][cr].A_DX_Cause_TD[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=imeicdrfile[fn][hn][cr].A_DX_Cause_TD[j].cause_id;
							tempcause.cause_num=imeicdrfile[fn][hn][cr].A_DX_Cause_TD[j].cause_num;
							taccdrfile[fn][temp_hash][i].A_DX_Cause_TD.push_back(tempcause);
						}
					}
					for(int j=0;j<imeicdrfile[fn][hn][cr].B_DX_Cause_GSM.size();j++){
						bool isExistCause=false;
						for(int k=0;k<taccdrfile[fn][temp_hash][i].B_DX_Cause_GSM.size();k++){
							if(taccdrfile[fn][temp_hash][i].B_DX_Cause_GSM[k].cause_id==imeicdrfile[fn][hn][cr].B_DX_Cause_GSM[j].cause_id){
								isExistCause=true;
								taccdrfile[fn][temp_hash][i].B_DX_Cause_GSM[k].cause_num+=imeicdrfile[fn][hn][cr].B_DX_Cause_GSM[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=imeicdrfile[fn][hn][cr].B_DX_Cause_GSM[j].cause_id;
							tempcause.cause_num=imeicdrfile[fn][hn][cr].B_DX_Cause_GSM[j].cause_num;
							taccdrfile[fn][temp_hash][i].B_DX_Cause_GSM.push_back(tempcause);
						}
					}
					for(int j=0;j<imeicdrfile[fn][hn][cr].B_DX_Cause_TD.size();j++){
						bool isExistCause=false;
						for(int k=0;k<taccdrfile[fn][temp_hash][i].B_DX_Cause_TD.size();k++){
							if(taccdrfile[fn][temp_hash][i].B_DX_Cause_TD[k].cause_id==imeicdrfile[fn][hn][cr].B_DX_Cause_TD[j].cause_id){
								isExistCause=true;
								taccdrfile[fn][temp_hash][i].B_DX_Cause_TD[k].cause_num+=imeicdrfile[fn][hn][cr].B_DX_Cause_TD[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=imeicdrfile[fn][hn][cr].B_DX_Cause_TD[j].cause_id;
							tempcause.cause_num=imeicdrfile[fn][hn][cr].B_DX_Cause_TD[j].cause_num;
							taccdrfile[fn][temp_hash][i].B_DX_Cause_TD.push_back(tempcause);
						}
					}
					
					//for(int j=0;j<imeicdrfile[fn][hn][cr].A_IMEI_IMSI_GSM.size();j++){
					//	for(int k=0;k<imeicdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j].size();k++){
					//		//对每一个IMEI和IMSI组合，查询是否已有记录
					//		bool isExistIMEI=false;
					//		bool isExistIMEIandIMSI=false;
					//		int temp_hash_imei=atoi(imeicdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					//		for(int m=0;m<taccdrfile[fn][temp_hash][i].A_IMEI_IMSI_GSM[temp_hash_imei].size();m++){
					//			if(imeicdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI==taccdrfile[fn][temp_hash][i].A_IMEI_IMSI_GSM[temp_hash_imei][m].IMEI){
					//				isExistIMEI=true;
					//				if(imeicdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMSI==taccdrfile[fn][temp_hash][i].A_IMEI_IMSI_GSM[temp_hash_imei][m].IMSI){
					//					isExistIMEIandIMSI=true;
					//					break;
					//				}
					//			}
					//		}

					//		if(isExistIMEIandIMSI==false){
					//			//如果IMEI和IMSI组成的对不重复，那么新增一个
					//			IMEI_IMSI tempim;
					//			tempim.IMEI=imeicdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI;
					//			tempim.IMSI=imeicdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMSI;
					//			taccdrfile[fn][temp_hash][i].A_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
					//		}

					//		if(isExistIMEI==false){
					//			//如果IMEI不重复
					//			taccdrfile[fn][temp_hash][i].A_IMEI_GSM++;
					//		}
					//	}
					//}
					//for(int j=0;j<imeicdrfile[fn][hn][cr].A_IMEI_IMSI_TD.size();j++){
					//	for(int k=0;k<imeicdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j].size();k++){
					//		//对每一个IMEI和IMSI组合，查询是否已有记录
					//		bool isExistIMEI=false;
					//		bool isExistIMEIandIMSI=false;
					//		int temp_hash_imei=atoi(imeicdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					//		for(int m=0;m<taccdrfile[fn][temp_hash][i].A_IMEI_IMSI_TD[temp_hash_imei].size();m++){
					//			if(imeicdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMEI==taccdrfile[fn][temp_hash][i].A_IMEI_IMSI_TD[temp_hash_imei][m].IMEI){
					//				isExistIMEI=true;
					//				if(imeicdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMSI==taccdrfile[fn][temp_hash][i].A_IMEI_IMSI_TD[temp_hash_imei][m].IMSI){
					//					isExistIMEIandIMSI=true;
					//					break;
					//				}
					//			}
					//		}

					//		if(isExistIMEIandIMSI==false){
					//			//如果IMEI和IMSI组成的对不重复，那么新增一个
					//			IMEI_IMSI tempim;
					//			tempim.IMEI=imeicdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMEI;
					//			tempim.IMSI=imeicdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMSI;
					//			taccdrfile[fn][temp_hash][i].A_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
					//		}

					//		if(isExistIMEI==false){
					//			//如果IMEI不重复
					//			taccdrfile[fn][temp_hash][i].A_IMEI_TD++;
					//		}
					//	}
					//}
					//for(int j=0;j<imeicdrfile[fn][hn][cr].B_IMEI_IMSI_GSM.size();j++){
					//	for(int k=0;k<imeicdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j].size();k++){
					//		//对每一个IMEI和IMSI组合，查询是否已有记录
					//		bool isExistIMEI=false;
					//		bool isExistIMEIandIMSI=false;
					//		int temp_hash_imei=atoi(imeicdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					//		for(int m=0;m<taccdrfile[fn][temp_hash][i].B_IMEI_IMSI_GSM[temp_hash_imei].size();m++){
					//			if(imeicdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI==taccdrfile[fn][temp_hash][i].B_IMEI_IMSI_GSM[temp_hash_imei][m].IMEI){
					//				isExistIMEI=true;
					//				if(imeicdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMSI==taccdrfile[fn][temp_hash][i].B_IMEI_IMSI_GSM[temp_hash_imei][m].IMSI){
					//					isExistIMEIandIMSI=true;
					//					break;
					//				}
					//			}
					//		}

					//		if(isExistIMEIandIMSI==false){
					//			//如果IMEI和IMSI组成的对不重复，那么新增一个
					//			IMEI_IMSI tempim;
					//			tempim.IMEI=imeicdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI;
					//			tempim.IMSI=imeicdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMSI;
					//			taccdrfile[fn][temp_hash][i].B_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
					//		}

					//		if(isExistIMEI==false){
					//			//如果IMEI不重复
					//			taccdrfile[fn][temp_hash][i].B_IMEI_GSM++;
					//		}
					//	}
					//}
					//for(int j=0;j<imeicdrfile[fn][hn][cr].B_IMEI_IMSI_TD.size();j++){
					//	for(int k=0;k<imeicdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j].size();k++){
					//		//对每一个IMEI和IMSI组合，查询是否已有记录
					//		bool isExistIMEI=false;
					//		bool isExistIMEIandIMSI=false;
					//		int temp_hash_imei=atoi(imeicdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					//		for(int m=0;m<taccdrfile[fn][temp_hash][i].B_IMEI_IMSI_TD[temp_hash_imei].size();m++){
					//			if(imeicdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMEI==taccdrfile[fn][temp_hash][i].B_IMEI_IMSI_TD[temp_hash_imei][m].IMEI){
					//				isExistIMEI=true;
					//				if(imeicdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMSI==taccdrfile[fn][temp_hash][i].B_IMEI_IMSI_TD[temp_hash_imei][m].IMSI){
					//					isExistIMEIandIMSI=true;
					//					break;
					//				}
					//			}
					//		}

					//		if(isExistIMEIandIMSI==false){
					//			//如果IMEI和IMSI组成的对不重复，那么新增一个
					//			IMEI_IMSI tempim;
					//			tempim.IMEI=imeicdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMEI;
					//			tempim.IMSI=imeicdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMSI;
					//			taccdrfile[fn][temp_hash][i].B_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
					//		}

					//		if(isExistIMEI==false){
					//			//如果IMEI不重复
					//			taccdrfile[fn][temp_hash][i].B_IMEI_TD++;
					//		}
					//	}
					//}
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
					taccdrfile[fn][temp_hash][i].A_call_first_cell_connected+=imeicdrfile[fn][hn][cr].A_call_first_cell_connected;
					taccdrfile[fn][temp_hash][i].A_call_first_cell_connected_TD+=imeicdrfile[fn][hn][cr].A_call_first_cell_connected_TD;
					taccdrfile[fn][temp_hash][i].A_call_first_cell_connected_GSM+=imeicdrfile[fn][hn][cr].A_call_first_cell_connected_GSM;
					taccdrfile[fn][temp_hash][i].B_call_first_cell_connected+=imeicdrfile[fn][hn][cr].B_call_first_cell_connected;
					taccdrfile[fn][temp_hash][i].B_call_first_cell_connected_TD+=imeicdrfile[fn][hn][cr].B_call_first_cell_connected_TD;
					taccdrfile[fn][temp_hash][i].B_call_first_cell_connected_GSM+=imeicdrfile[fn][hn][cr].B_call_first_cell_connected_GSM;
					taccdrfile[fn][temp_hash][i].A_call_last_cell_connected+=imeicdrfile[fn][hn][cr].A_call_last_cell_connected;
					taccdrfile[fn][temp_hash][i].A_call_last_cell_connected_TD+=imeicdrfile[fn][hn][cr].A_call_last_cell_connected_TD;
					taccdrfile[fn][temp_hash][i].A_call_last_cell_connected_GSM+=imeicdrfile[fn][hn][cr].A_call_last_cell_connected_GSM;
					taccdrfile[fn][temp_hash][i].B_call_last_cell_connected+=imeicdrfile[fn][hn][cr].B_call_last_cell_connected;
					taccdrfile[fn][temp_hash][i].B_call_last_cell_connected_TD+=imeicdrfile[fn][hn][cr].B_call_last_cell_connected_TD;
					taccdrfile[fn][temp_hash][i].B_call_last_cell_connected_GSM+=imeicdrfile[fn][hn][cr].B_call_last_cell_connected_GSM;
						
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
				tempimei.timeSection=imeicdrfile[fn][hn][cr].timeSection;
				tempimei.timeSectionStartTime=imeicdrfile[fn][hn][cr].timeSectionStartTime;
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
				tempimei.A_call_first_cell_connected=imeicdrfile[fn][hn][cr].A_call_first_cell_connected;
				tempimei.A_call_first_cell_connected_TD=imeicdrfile[fn][hn][cr].A_call_first_cell_connected_TD;
				tempimei.A_call_first_cell_connected_GSM=imeicdrfile[fn][hn][cr].A_call_first_cell_connected_GSM;
				tempimei.B_call_first_cell_connected=imeicdrfile[fn][hn][cr].B_call_first_cell_connected;
				tempimei.B_call_first_cell_connected_TD=imeicdrfile[fn][hn][cr].B_call_first_cell_connected_TD;
				tempimei.B_call_first_cell_connected_GSM=imeicdrfile[fn][hn][cr].B_call_first_cell_connected_GSM;
				tempimei.A_call_last_cell_connected=imeicdrfile[fn][hn][cr].A_call_last_cell_connected;
				tempimei.A_call_last_cell_connected_TD=imeicdrfile[fn][hn][cr].A_call_last_cell_connected_TD;
				tempimei.A_call_last_cell_connected_GSM=imeicdrfile[fn][hn][cr].A_call_last_cell_connected_GSM;
				tempimei.B_call_last_cell_connected=imeicdrfile[fn][hn][cr].B_call_last_cell_connected;
				tempimei.B_call_last_cell_connected_TD=imeicdrfile[fn][hn][cr].B_call_last_cell_connected_TD;
				tempimei.B_call_last_cell_connected_GSM=imeicdrfile[fn][hn][cr].B_call_last_cell_connected_GSM;
				tempimei.A_BSSMAP_Cause.clear();
				tempimei.A_RANAP_Cause.clear();
				tempimei.B_BSSMAP_Cause.clear();
				tempimei.B_RANAP_Cause.clear();
				tempimei.A_DX_Cause_GSM.clear();
				tempimei.A_DX_Cause_TD.clear();
				tempimei.B_DX_Cause_GSM.clear();
				tempimei.B_DX_Cause_TD.clear();
				tempimei.A_BSSMAP_drop=0;
				tempimei.A_RANAP_drop=0;
				tempimei.B_BSSMAP_drop=0;
				tempimei.B_RANAP_drop=0;
				tempimei.A_DX_GSM_block=0;
				tempimei.A_DX_TD_block=0;
				tempimei.B_DX_GSM_block=0;
				tempimei.B_DX_TD_block=0;
				
				for(int j=0;j<imeicdrfile[fn][hn][cr].A_BSSMAP_Cause.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=imeicdrfile[fn][hn][cr].A_BSSMAP_Cause[j].cause_id;
					tempcause.cause_num=imeicdrfile[fn][hn][cr].A_BSSMAP_Cause[j].cause_num;
					tempimei.A_BSSMAP_Cause.push_back(tempcause);
				}
				for(int j=0;j<imeicdrfile[fn][hn][cr].B_BSSMAP_Cause.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=imeicdrfile[fn][hn][cr].B_BSSMAP_Cause[j].cause_id;
					tempcause.cause_num=imeicdrfile[fn][hn][cr].B_BSSMAP_Cause[j].cause_num;
					tempimei.B_BSSMAP_Cause.push_back(tempcause);
					
				}
				for(int j=0;j<imeicdrfile[fn][hn][cr].A_RANAP_Cause.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=imeicdrfile[fn][hn][cr].A_RANAP_Cause[j].cause_id;
					tempcause.cause_num=imeicdrfile[fn][hn][cr].A_RANAP_Cause[j].cause_num;
					tempimei.A_RANAP_Cause.push_back(tempcause);
				}
				for(int j=0;j<imeicdrfile[fn][hn][cr].B_RANAP_Cause.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=imeicdrfile[fn][hn][cr].B_RANAP_Cause[j].cause_id;
					tempcause.cause_num=imeicdrfile[fn][hn][cr].B_RANAP_Cause[j].cause_num;
					tempimei.B_RANAP_Cause.push_back(tempcause);
				}
				for(int j=0;j<imeicdrfile[fn][hn][cr].A_DX_Cause_GSM.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=imeicdrfile[fn][hn][cr].A_DX_Cause_GSM[j].cause_id;
					tempcause.cause_num=imeicdrfile[fn][hn][cr].A_DX_Cause_GSM[j].cause_num;
					tempimei.A_DX_Cause_GSM.push_back(tempcause);
				}
				for(int j=0;j<imeicdrfile[fn][hn][cr].A_DX_Cause_TD.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=imeicdrfile[fn][hn][cr].A_DX_Cause_TD[j].cause_id;
					tempcause.cause_num=imeicdrfile[fn][hn][cr].A_DX_Cause_TD[j].cause_num;
					tempimei.A_DX_Cause_TD.push_back(tempcause);
				}
				for(int j=0;j<imeicdrfile[fn][hn][cr].B_DX_Cause_GSM.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=imeicdrfile[fn][hn][cr].B_DX_Cause_GSM[j].cause_id;
					tempcause.cause_num=imeicdrfile[fn][hn][cr].B_DX_Cause_GSM[j].cause_num;
					tempimei.B_DX_Cause_GSM.push_back(tempcause);
				}
				for(int j=0;j<imeicdrfile[fn][hn][cr].B_DX_Cause_TD.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=imeicdrfile[fn][hn][cr].B_DX_Cause_TD[j].cause_id;
					tempcause.cause_num=imeicdrfile[fn][hn][cr].B_DX_Cause_TD[j].cause_num;
					tempimei.B_DX_Cause_TD.push_back(tempcause);
				}
			
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
	//hash tac用后四位
	tacstat.clear();
	tacstat.resize((int)pow((double)10,cfg.HASH_NUM_IMEI+cfg.HASH_NUM_CELLID));
	
	time_t start,end;
	
	for(int fn=0;fn<cfg.THREADNUM;fn++){
		start=clock();
		int hsize=0;
		for(int hn=0;hn<taccdrfile[fn].size();hn++){
			hsize+=(int)taccdrfile[fn][hn].size();
			for(int cr=0;cr<taccdrfile[fn][hn].size();cr++){
				//cout<<"HASHKEY Num is "<<taccdrfile[fn].size()<<endl;
				//cout<<"HASKKEY"<<hn<<" has "<<taccdrfile[fn][hn].size()<<" records"<<endl;
				//查询是否已经有相应的TAC记录。
				bool isExistTAC=false;
				int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(taccdrfile[fn][hn][cr].TAC.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+taccdrfile[fn][hn][cr].cellid%((int)pow((double)10,cfg.HASH_NUM_CELLID));
				//cout<<"temp_hash is "<<temp_hash<<" with IMEI="<<taccdrfile[fn][hn][cr].IMEI<<" and cellid="<<taccdrfile[fn][hn][cr].cellid<<endl;
				
				for(int im=0;im<tacstat[temp_hash].size();im++){
					if(tacstat[temp_hash][im].timeSection==taccdrfile[fn][hn][cr].timeSection&&tacstat[temp_hash][im].TAC==taccdrfile[fn][hn][cr].TAC&&tacstat[temp_hash][im].cellid==taccdrfile[fn][hn][cr].cellid&&tacstat[temp_hash][im].network==taccdrfile[fn][hn][cr].network){
						isExistTAC=true;
						
					for(int j=0;j<taccdrfile[fn][hn][cr].A_BSSMAP_Cause.size();j++){
						bool isExistCause=false;
						for(int k=0;k<tacstat[temp_hash][im].A_BSSMAP_Cause.size();k++){
							if(tacstat[temp_hash][im].A_BSSMAP_Cause[k].cause_id==taccdrfile[fn][hn][cr].A_BSSMAP_Cause[j].cause_id){
								isExistCause=true;
								tacstat[temp_hash][im].A_BSSMAP_Cause[k].cause_num+=taccdrfile[fn][hn][cr].A_BSSMAP_Cause[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=taccdrfile[fn][hn][cr].A_BSSMAP_Cause[j].cause_id;
							tempcause.cause_num=taccdrfile[fn][hn][cr].A_BSSMAP_Cause[j].cause_num;
							tacstat[temp_hash][im].A_BSSMAP_Cause.push_back(tempcause);
						}
					}
					for(int j=0;j<taccdrfile[fn][hn][cr].B_BSSMAP_Cause.size();j++){
						bool isExistCause=false;
						for(int k=0;k<tacstat[temp_hash][im].B_BSSMAP_Cause.size();k++){
							if(tacstat[temp_hash][im].B_BSSMAP_Cause[k].cause_id==taccdrfile[fn][hn][cr].B_BSSMAP_Cause[j].cause_id){
								isExistCause=true;
								tacstat[temp_hash][im].B_BSSMAP_Cause[k].cause_num+=taccdrfile[fn][hn][cr].B_BSSMAP_Cause[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=taccdrfile[fn][hn][cr].B_BSSMAP_Cause[j].cause_id;
							tempcause.cause_num=taccdrfile[fn][hn][cr].B_BSSMAP_Cause[j].cause_num;
							tacstat[temp_hash][im].B_BSSMAP_Cause.push_back(tempcause);
						}
					}
					for(int j=0;j<taccdrfile[fn][hn][cr].A_RANAP_Cause.size();j++){
						bool isExistCause=false;
						for(int k=0;k<tacstat[temp_hash][im].A_RANAP_Cause.size();k++){
							if(tacstat[temp_hash][im].A_RANAP_Cause[k].cause_id==taccdrfile[fn][hn][cr].A_RANAP_Cause[j].cause_id){
								isExistCause=true;
								tacstat[temp_hash][im].A_RANAP_Cause[k].cause_num+=taccdrfile[fn][hn][cr].A_RANAP_Cause[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=taccdrfile[fn][hn][cr].A_RANAP_Cause[j].cause_id;
							tempcause.cause_num=taccdrfile[fn][hn][cr].A_RANAP_Cause[j].cause_num;
							tacstat[temp_hash][im].A_RANAP_Cause.push_back(tempcause);
						}
					}
					for(int j=0;j<taccdrfile[fn][hn][cr].B_RANAP_Cause.size();j++){
						bool isExistCause=false;
						for(int k=0;k<tacstat[temp_hash][im].B_RANAP_Cause.size();k++){
							if(tacstat[temp_hash][im].B_RANAP_Cause[k].cause_id==taccdrfile[fn][hn][cr].B_RANAP_Cause[j].cause_id){
								isExistCause=true;
								tacstat[temp_hash][im].B_RANAP_Cause[k].cause_num+=taccdrfile[fn][hn][cr].B_RANAP_Cause[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=taccdrfile[fn][hn][cr].B_RANAP_Cause[j].cause_id;
							tempcause.cause_num=taccdrfile[fn][hn][cr].B_RANAP_Cause[j].cause_num;
							tacstat[temp_hash][im].B_RANAP_Cause.push_back(tempcause);
						}
					}
					for(int j=0;j<taccdrfile[fn][hn][cr].A_DX_Cause_GSM.size();j++){
						bool isExistCause=false;
						for(int k=0;k<tacstat[temp_hash][im].A_DX_Cause_GSM.size();k++){
							if(tacstat[temp_hash][im].A_DX_Cause_GSM[k].cause_id==taccdrfile[fn][hn][cr].A_DX_Cause_GSM[j].cause_id){
								isExistCause=true;
								tacstat[temp_hash][im].A_DX_Cause_GSM[k].cause_num+=taccdrfile[fn][hn][cr].A_DX_Cause_GSM[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=taccdrfile[fn][hn][cr].A_DX_Cause_GSM[j].cause_id;
							tempcause.cause_num=taccdrfile[fn][hn][cr].A_DX_Cause_GSM[j].cause_num;
							tacstat[temp_hash][im].A_DX_Cause_GSM.push_back(tempcause);
						}
					}
					for(int j=0;j<taccdrfile[fn][hn][cr].A_DX_Cause_TD.size();j++){
						bool isExistCause=false;
						for(int k=0;k<tacstat[temp_hash][im].A_DX_Cause_TD.size();k++){
							if(tacstat[temp_hash][im].A_DX_Cause_TD[k].cause_id==taccdrfile[fn][hn][cr].A_DX_Cause_TD[j].cause_id){
								isExistCause=true;
								tacstat[temp_hash][im].A_DX_Cause_TD[k].cause_num+=taccdrfile[fn][hn][cr].A_DX_Cause_TD[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=taccdrfile[fn][hn][cr].A_DX_Cause_TD[j].cause_id;
							tempcause.cause_num=taccdrfile[fn][hn][cr].A_DX_Cause_TD[j].cause_num;
							tacstat[temp_hash][im].A_DX_Cause_TD.push_back(tempcause);
						}
					}
					for(int j=0;j<taccdrfile[fn][hn][cr].B_DX_Cause_GSM.size();j++){
						bool isExistCause=false;
						for(int k=0;k<tacstat[temp_hash][im].B_DX_Cause_GSM.size();k++){
							if(tacstat[temp_hash][im].B_DX_Cause_GSM[k].cause_id==taccdrfile[fn][hn][cr].B_DX_Cause_GSM[j].cause_id){
								isExistCause=true;
								tacstat[temp_hash][im].B_DX_Cause_GSM[k].cause_num+=taccdrfile[fn][hn][cr].B_DX_Cause_GSM[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=taccdrfile[fn][hn][cr].B_DX_Cause_GSM[j].cause_id;
							tempcause.cause_num=taccdrfile[fn][hn][cr].B_DX_Cause_GSM[j].cause_num;
							tacstat[temp_hash][im].B_DX_Cause_GSM.push_back(tempcause);
						}
					}
					for(int j=0;j<taccdrfile[fn][hn][cr].B_DX_Cause_TD.size();j++){
						bool isExistCause=false;
						for(int k=0;k<tacstat[temp_hash][im].B_DX_Cause_TD.size();k++){
							if(tacstat[temp_hash][im].B_DX_Cause_TD[k].cause_id==taccdrfile[fn][hn][cr].B_DX_Cause_TD[j].cause_id){
								isExistCause=true;
								tacstat[temp_hash][im].B_DX_Cause_TD[k].cause_num+=taccdrfile[fn][hn][cr].B_DX_Cause_TD[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=taccdrfile[fn][hn][cr].B_DX_Cause_TD[j].cause_id;
							tempcause.cause_num=taccdrfile[fn][hn][cr].B_DX_Cause_TD[j].cause_num;
							tacstat[temp_hash][im].B_DX_Cause_TD.push_back(tempcause);
						}
					}
					
					tacstat[temp_hash][im].B_shortcall_1+=taccdrfile[fn][hn][cr].B_shortcall_1;
					tacstat[temp_hash][im].A_shortcall_1+=taccdrfile[fn][hn][cr].A_shortcall_1;
					tacstat[temp_hash][im].B_shortcall_2+=taccdrfile[fn][hn][cr].B_shortcall_2;
					tacstat[temp_hash][im].A_shortcall_2+=taccdrfile[fn][hn][cr].A_shortcall_2;
					tacstat[temp_hash][im].B_shortcall_3+=taccdrfile[fn][hn][cr].B_shortcall_3;
					tacstat[temp_hash][im].A_shortcall_3+=taccdrfile[fn][hn][cr].A_shortcall_3;
					tacstat[temp_hash][im].B_call_attempt+=taccdrfile[fn][hn][cr].B_call_attempt;
					tacstat[temp_hash][im].A_call_attempt+=taccdrfile[fn][hn][cr].A_call_attempt;
					tacstat[temp_hash][im].B_call_attempt_GSM+=taccdrfile[fn][hn][cr].B_call_attempt_GSM;
					tacstat[temp_hash][im].A_call_attempt_GSM+=taccdrfile[fn][hn][cr].A_call_attempt_GSM;
					tacstat[temp_hash][im].A_call_attempt_TD+=taccdrfile[fn][hn][cr].A_call_attempt_TD;
					tacstat[temp_hash][im].B_call_attempt_TD+=taccdrfile[fn][hn][cr].B_call_attempt_TD;
					tacstat[temp_hash][im].A_call_first_cell_connected+=taccdrfile[fn][hn][cr].A_call_first_cell_connected;
					tacstat[temp_hash][im].A_call_first_cell_connected_TD+=taccdrfile[fn][hn][cr].A_call_first_cell_connected_TD;
					tacstat[temp_hash][im].A_call_first_cell_connected_GSM+=taccdrfile[fn][hn][cr].A_call_first_cell_connected_GSM;
					tacstat[temp_hash][im].B_call_first_cell_connected+=taccdrfile[fn][hn][cr].B_call_first_cell_connected;
					tacstat[temp_hash][im].B_call_first_cell_connected_TD+=taccdrfile[fn][hn][cr].B_call_first_cell_connected_TD;
					tacstat[temp_hash][im].B_call_first_cell_connected_GSM+=taccdrfile[fn][hn][cr].B_call_first_cell_connected_GSM;
					tacstat[temp_hash][im].A_call_last_cell_connected+=taccdrfile[fn][hn][cr].A_call_last_cell_connected;
					tacstat[temp_hash][im].A_call_last_cell_connected_TD+=taccdrfile[fn][hn][cr].A_call_last_cell_connected_TD;
					tacstat[temp_hash][im].A_call_last_cell_connected_GSM+=taccdrfile[fn][hn][cr].A_call_last_cell_connected_GSM;
					tacstat[temp_hash][im].B_call_last_cell_connected+=taccdrfile[fn][hn][cr].B_call_last_cell_connected;
					tacstat[temp_hash][im].B_call_last_cell_connected_TD+=taccdrfile[fn][hn][cr].B_call_last_cell_connected_TD;
					tacstat[temp_hash][im].B_call_last_cell_connected_GSM+=taccdrfile[fn][hn][cr].B_call_last_cell_connected_GSM;
					
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
					tempimei.timeSection=taccdrfile[fn][hn][cr].timeSection;
					tempimei.timeSectionStartTime=taccdrfile[fn][hn][cr].timeSectionStartTime;
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
					tempimei.A_call_first_cell_connected=taccdrfile[fn][hn][cr].A_call_first_cell_connected;
					tempimei.A_call_first_cell_connected_TD=taccdrfile[fn][hn][cr].A_call_first_cell_connected_TD;
					tempimei.A_call_first_cell_connected_GSM=taccdrfile[fn][hn][cr].A_call_first_cell_connected_GSM;
					tempimei.B_call_first_cell_connected=taccdrfile[fn][hn][cr].B_call_first_cell_connected;
					tempimei.B_call_first_cell_connected_TD=taccdrfile[fn][hn][cr].B_call_first_cell_connected_TD;
					tempimei.B_call_first_cell_connected_GSM=taccdrfile[fn][hn][cr].B_call_first_cell_connected_GSM;
					tempimei.A_call_last_cell_connected=taccdrfile[fn][hn][cr].A_call_last_cell_connected;
					tempimei.A_call_last_cell_connected_TD=taccdrfile[fn][hn][cr].A_call_last_cell_connected_TD;
					tempimei.A_call_last_cell_connected_GSM=taccdrfile[fn][hn][cr].A_call_last_cell_connected_GSM;
					tempimei.B_call_last_cell_connected=taccdrfile[fn][hn][cr].B_call_last_cell_connected;
					tempimei.B_call_last_cell_connected_TD=taccdrfile[fn][hn][cr].B_call_last_cell_connected_TD;
					tempimei.B_call_last_cell_connected_GSM=taccdrfile[fn][hn][cr].B_call_last_cell_connected_GSM;
					tempimei.A_BSSMAP_Cause.clear();
					tempimei.A_RANAP_Cause.clear();
					tempimei.B_BSSMAP_Cause.clear();
					tempimei.B_RANAP_Cause.clear();
					tempimei.A_DX_Cause_GSM.clear();
					tempimei.A_DX_Cause_TD.clear();
					tempimei.B_DX_Cause_GSM.clear();
					tempimei.B_DX_Cause_TD.clear();
					tempimei.A_BSSMAP_drop=0;
					tempimei.A_RANAP_drop=0;
					tempimei.B_BSSMAP_drop=0;
					tempimei.B_RANAP_drop=0;
					tempimei.A_DX_GSM_block=0;
					tempimei.A_DX_TD_block=0;
					tempimei.B_DX_GSM_block=0;
					tempimei.B_DX_TD_block=0;

					for(int j=0;j<taccdrfile[fn][hn][cr].A_BSSMAP_Cause.size();j++){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=taccdrfile[fn][hn][cr].A_BSSMAP_Cause[j].cause_id;
						tempcause.cause_num=taccdrfile[fn][hn][cr].A_BSSMAP_Cause[j].cause_num;
						tempimei.A_BSSMAP_Cause.push_back(tempcause);
					}
					for(int j=0;j<taccdrfile[fn][hn][cr].B_BSSMAP_Cause.size();j++){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=taccdrfile[fn][hn][cr].B_BSSMAP_Cause[j].cause_id;
						tempcause.cause_num=taccdrfile[fn][hn][cr].B_BSSMAP_Cause[j].cause_num;
						tempimei.B_BSSMAP_Cause.push_back(tempcause);
					
					}
					for(int j=0;j<taccdrfile[fn][hn][cr].A_RANAP_Cause.size();j++){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=taccdrfile[fn][hn][cr].A_RANAP_Cause[j].cause_id;
						tempcause.cause_num=taccdrfile[fn][hn][cr].A_RANAP_Cause[j].cause_num;
						tempimei.A_RANAP_Cause.push_back(tempcause);
					}
					for(int j=0;j<taccdrfile[fn][hn][cr].B_RANAP_Cause.size();j++){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=taccdrfile[fn][hn][cr].B_RANAP_Cause[j].cause_id;
						tempcause.cause_num=taccdrfile[fn][hn][cr].B_RANAP_Cause[j].cause_num;
						tempimei.B_RANAP_Cause.push_back(tempcause);
					}
					for(int j=0;j<taccdrfile[fn][hn][cr].A_DX_Cause_GSM.size();j++){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=taccdrfile[fn][hn][cr].A_DX_Cause_GSM[j].cause_id;
						tempcause.cause_num=taccdrfile[fn][hn][cr].A_DX_Cause_GSM[j].cause_num;
						tempimei.A_DX_Cause_GSM.push_back(tempcause);
					}
					for(int j=0;j<taccdrfile[fn][hn][cr].A_DX_Cause_TD.size();j++){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=taccdrfile[fn][hn][cr].A_DX_Cause_TD[j].cause_id;
						tempcause.cause_num=taccdrfile[fn][hn][cr].A_DX_Cause_TD[j].cause_num;
						tempimei.A_DX_Cause_TD.push_back(tempcause);
					}
					for(int j=0;j<taccdrfile[fn][hn][cr].B_DX_Cause_GSM.size();j++){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=taccdrfile[fn][hn][cr].B_DX_Cause_GSM[j].cause_id;
						tempcause.cause_num=taccdrfile[fn][hn][cr].B_DX_Cause_GSM[j].cause_num;
						tempimei.B_DX_Cause_GSM.push_back(tempcause);
					}
					for(int j=0;j<taccdrfile[fn][hn][cr].B_DX_Cause_TD.size();j++){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=taccdrfile[fn][hn][cr].B_DX_Cause_TD[j].cause_id;
						tempcause.cause_num=taccdrfile[fn][hn][cr].B_DX_Cause_TD[j].cause_num;
						tempimei.B_DX_Cause_TD.push_back(tempcause);
					}
				
				

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

//________________将不同的批次合并__________________________	
//将不同批次产生的tacstat文件合并成一个tacstat
bool CombineMultiTACStat(vector<string> tacstatfilelist){
	time_t start,end;
	
	cout<<"Start Combining "<<cfg.tacstatfilelist.size()<<"TAC STAT FILE"<<endl;
	tacstat.clear();
	tacstat.resize((int)pow((double)10,cfg.HASH_NUM_IMEI+cfg.HASH_NUM_CELLID));
	
	for(int i=0;i<tacstatfilelist.size();i++){
		//vector<vector<IMEI_CDR_Statistic>> temptacstat;
		temptacstat.clear();
		
		if(!ReadTACSTATFile(tacstatfilelist[i])){
			cout<<"Read File "<<tacstatfilelist[i]<<" Error."<<endl;
		}
		else{
			start=clock();
			int hsize=0;
			//combine tacstat和temptacstat
			omp_set_num_threads(cfg.THREADNUM);
#pragma omp parallel for reduction(+:hsize)		
		for(int hn=0;hn<temptacstat.size();hn++){
			hsize+=(int)temptacstat[hn].size();
			for(int cr=0;cr<temptacstat[hn].size();cr++){
				//查询是否已经有相应的TAC记录。
				bool isExistTAC=false;
				int temp_hash=(int)pow((double)10,cfg.HASH_NUM_CELLID)*atoi(temptacstat[hn][cr].TAC.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str())+temptacstat[hn][cr].cellid%((int)pow((double)10,cfg.HASH_NUM_CELLID));
				for(int im=0;im<tacstat[temp_hash].size();im++){
					if(tacstat[temp_hash][im].timeSection==temptacstat[hn][cr].timeSection&&tacstat[temp_hash][im].cellid==temptacstat[hn][cr].cellid&&tacstat[temp_hash][im].TAC==temptacstat[hn][cr].TAC){
						isExistTAC=true;
					for(int j=0;j<temptacstat[hn][cr].A_BSSMAP_Cause.size();j++){
						bool isExistCause=false;
						for(int k=0;k<tacstat[temp_hash][im].A_BSSMAP_Cause.size();k++){
							if(tacstat[temp_hash][im].A_BSSMAP_Cause[k].cause_id==temptacstat[hn][cr].A_BSSMAP_Cause[j].cause_id){
								isExistCause=true;
								tacstat[temp_hash][im].A_BSSMAP_Cause[k].cause_num+=temptacstat[hn][cr].A_BSSMAP_Cause[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=temptacstat[hn][cr].A_BSSMAP_Cause[j].cause_id;
							tempcause.cause_num=temptacstat[hn][cr].A_BSSMAP_Cause[j].cause_num;
							tacstat[temp_hash][im].A_BSSMAP_Cause.push_back(tempcause);
						}
					}
					for(int j=0;j<temptacstat[hn][cr].B_BSSMAP_Cause.size();j++){
						bool isExistCause=false;
						for(int k=0;k<tacstat[temp_hash][im].B_BSSMAP_Cause.size();k++){
							if(tacstat[temp_hash][im].B_BSSMAP_Cause[k].cause_id==temptacstat[hn][cr].B_BSSMAP_Cause[j].cause_id){
								isExistCause=true;
								tacstat[temp_hash][im].B_BSSMAP_Cause[k].cause_num+=temptacstat[hn][cr].B_BSSMAP_Cause[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=temptacstat[hn][cr].B_BSSMAP_Cause[j].cause_id;
							tempcause.cause_num=temptacstat[hn][cr].B_BSSMAP_Cause[j].cause_num;
							tacstat[temp_hash][im].B_BSSMAP_Cause.push_back(tempcause);
						}
					}
					for(int j=0;j<temptacstat[hn][cr].A_RANAP_Cause.size();j++){
						bool isExistCause=false;
						for(int k=0;k<tacstat[temp_hash][im].A_RANAP_Cause.size();k++){
							if(tacstat[temp_hash][im].A_RANAP_Cause[k].cause_id==temptacstat[hn][cr].A_RANAP_Cause[j].cause_id){
								isExistCause=true;
								tacstat[temp_hash][im].A_RANAP_Cause[k].cause_num+=temptacstat[hn][cr].A_RANAP_Cause[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=temptacstat[hn][cr].A_RANAP_Cause[j].cause_id;
							tempcause.cause_num=temptacstat[hn][cr].A_RANAP_Cause[j].cause_num;
							tacstat[temp_hash][im].A_RANAP_Cause.push_back(tempcause);
						}
					}
					for(int j=0;j<temptacstat[hn][cr].B_RANAP_Cause.size();j++){
						bool isExistCause=false;
						for(int k=0;k<tacstat[temp_hash][im].B_RANAP_Cause.size();k++){
							if(tacstat[temp_hash][im].B_RANAP_Cause[k].cause_id==temptacstat[hn][cr].B_RANAP_Cause[j].cause_id){
								isExistCause=true;
								tacstat[temp_hash][im].B_RANAP_Cause[k].cause_num+=temptacstat[hn][cr].B_RANAP_Cause[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=temptacstat[hn][cr].B_RANAP_Cause[j].cause_id;
							tempcause.cause_num=temptacstat[hn][cr].B_RANAP_Cause[j].cause_num;
							tacstat[temp_hash][im].B_RANAP_Cause.push_back(tempcause);
						}
					}
					for(int j=0;j<temptacstat[hn][cr].A_DX_Cause_GSM.size();j++){
						bool isExistCause=false;
						for(int k=0;k<tacstat[temp_hash][im].A_DX_Cause_GSM.size();k++){
							if(tacstat[temp_hash][im].A_DX_Cause_GSM[k].cause_id==temptacstat[hn][cr].A_DX_Cause_GSM[j].cause_id){
								isExistCause=true;
								tacstat[temp_hash][im].A_DX_Cause_GSM[k].cause_num+=temptacstat[hn][cr].A_DX_Cause_GSM[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=temptacstat[hn][cr].A_DX_Cause_GSM[j].cause_id;
							tempcause.cause_num=temptacstat[hn][cr].A_DX_Cause_GSM[j].cause_num;
							tacstat[temp_hash][im].A_DX_Cause_GSM.push_back(tempcause);
						}
					}
					for(int j=0;j<temptacstat[hn][cr].A_DX_Cause_TD.size();j++){
						bool isExistCause=false;
						for(int k=0;k<tacstat[temp_hash][im].A_DX_Cause_TD.size();k++){
							if(tacstat[temp_hash][im].A_DX_Cause_TD[k].cause_id==temptacstat[hn][cr].A_DX_Cause_TD[j].cause_id){
								isExistCause=true;
								tacstat[temp_hash][im].A_DX_Cause_TD[k].cause_num+=temptacstat[hn][cr].A_DX_Cause_TD[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=temptacstat[hn][cr].A_DX_Cause_TD[j].cause_id;
							tempcause.cause_num=temptacstat[hn][cr].A_DX_Cause_TD[j].cause_num;
							tacstat[temp_hash][im].A_DX_Cause_TD.push_back(tempcause);
						}
					}
					for(int j=0;j<temptacstat[hn][cr].B_DX_Cause_GSM.size();j++){
						bool isExistCause=false;
						for(int k=0;k<tacstat[temp_hash][im].B_DX_Cause_GSM.size();k++){
							if(tacstat[temp_hash][im].B_DX_Cause_GSM[k].cause_id==temptacstat[hn][cr].B_DX_Cause_GSM[j].cause_id){
								isExistCause=true;
								tacstat[temp_hash][im].B_DX_Cause_GSM[k].cause_num+=temptacstat[hn][cr].B_DX_Cause_GSM[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=temptacstat[hn][cr].B_DX_Cause_GSM[j].cause_id;
							tempcause.cause_num=temptacstat[hn][cr].B_DX_Cause_GSM[j].cause_num;
							tacstat[temp_hash][im].B_DX_Cause_GSM.push_back(tempcause);
						}
					}
					for(int j=0;j<temptacstat[hn][cr].B_DX_Cause_TD.size();j++){
						bool isExistCause=false;
						for(int k=0;k<tacstat[temp_hash][im].B_DX_Cause_TD.size();k++){
							if(tacstat[temp_hash][im].B_DX_Cause_TD[k].cause_id==temptacstat[hn][cr].B_DX_Cause_TD[j].cause_id){
								isExistCause=true;
								tacstat[temp_hash][im].B_DX_Cause_TD[k].cause_num+=temptacstat[hn][cr].B_DX_Cause_TD[j].cause_num;
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=temptacstat[hn][cr].B_DX_Cause_TD[j].cause_id;
							tempcause.cause_num=temptacstat[hn][cr].B_DX_Cause_TD[j].cause_num;
							tacstat[temp_hash][im].B_DX_Cause_TD.push_back(tempcause);
						}
					}
					
					tacstat[temp_hash][im].B_shortcall_1+=temptacstat[hn][cr].B_shortcall_1;
					tacstat[temp_hash][im].A_shortcall_1+=temptacstat[hn][cr].A_shortcall_1;
					tacstat[temp_hash][im].B_shortcall_2+=temptacstat[hn][cr].B_shortcall_2;
					tacstat[temp_hash][im].A_shortcall_2+=temptacstat[hn][cr].A_shortcall_2;
					tacstat[temp_hash][im].B_shortcall_3+=temptacstat[hn][cr].B_shortcall_3;
					tacstat[temp_hash][im].A_shortcall_3+=temptacstat[hn][cr].A_shortcall_3;
					tacstat[temp_hash][im].B_call_attempt+=temptacstat[hn][cr].B_call_attempt;
					tacstat[temp_hash][im].A_call_attempt+=temptacstat[hn][cr].A_call_attempt;
					tacstat[temp_hash][im].B_call_attempt_GSM+=temptacstat[hn][cr].B_call_attempt_GSM;
					tacstat[temp_hash][im].A_call_attempt_GSM+=temptacstat[hn][cr].A_call_attempt_GSM;
					tacstat[temp_hash][im].A_call_attempt_TD+=temptacstat[hn][cr].A_call_attempt_TD;
					tacstat[temp_hash][im].B_call_attempt_TD+=temptacstat[hn][cr].B_call_attempt_TD;
					tacstat[temp_hash][im].A_call_first_cell_connected+=temptacstat[hn][cr].A_call_first_cell_connected;
					tacstat[temp_hash][im].A_call_first_cell_connected_TD+=temptacstat[hn][cr].A_call_first_cell_connected_TD;
					tacstat[temp_hash][im].A_call_first_cell_connected_GSM+=temptacstat[hn][cr].A_call_first_cell_connected_GSM;
					tacstat[temp_hash][im].B_call_first_cell_connected+=temptacstat[hn][cr].B_call_first_cell_connected;
					tacstat[temp_hash][im].B_call_first_cell_connected_TD+=temptacstat[hn][cr].B_call_first_cell_connected_TD;
					tacstat[temp_hash][im].B_call_first_cell_connected_GSM+=temptacstat[hn][cr].B_call_first_cell_connected_GSM;
					tacstat[temp_hash][im].A_call_last_cell_connected+=temptacstat[hn][cr].A_call_last_cell_connected;
					tacstat[temp_hash][im].A_call_last_cell_connected_TD+=temptacstat[hn][cr].A_call_last_cell_connected_TD;
					tacstat[temp_hash][im].A_call_last_cell_connected_GSM+=temptacstat[hn][cr].A_call_last_cell_connected_GSM;
					tacstat[temp_hash][im].B_call_last_cell_connected+=temptacstat[hn][cr].B_call_last_cell_connected;
					tacstat[temp_hash][im].B_call_last_cell_connected_TD+=temptacstat[hn][cr].B_call_last_cell_connected_TD;
					tacstat[temp_hash][im].B_call_last_cell_connected_GSM+=temptacstat[hn][cr].B_call_last_cell_connected_GSM;
					
						break;
					}
				}
				if(isExistTAC==false){
					//如果没有的话，增加
					IMEI_CDR_Statistic tempimei;
					tempimei.IMEI="";
					tempimei.TAC=temptacstat[hn][cr].TAC;
					tempimei.brand=temptacstat[hn][cr].brand;
					tempimei.type=temptacstat[hn][cr].type;
					tempimei.name=temptacstat[hn][cr].name;
					tempimei.cellid=temptacstat[hn][cr].cellid;
					tempimei.network=temptacstat[hn][cr].network;
					tempimei.celltype=temptacstat[hn][cr].celltype;
					tempimei.A_shortcall_1=temptacstat[hn][cr].A_shortcall_1;
					tempimei.B_shortcall_1=temptacstat[hn][cr].B_shortcall_1;
					tempimei.A_shortcall_2=temptacstat[hn][cr].A_shortcall_2;
					tempimei.B_shortcall_2=temptacstat[hn][cr].B_shortcall_2;
					tempimei.A_shortcall_3=temptacstat[hn][cr].A_shortcall_3;
					tempimei.B_shortcall_3=temptacstat[hn][cr].B_shortcall_3;
					tempimei.A_call_attempt=temptacstat[hn][cr].A_call_attempt;
					tempimei.B_call_attempt=temptacstat[hn][cr].B_call_attempt;
					tempimei.B_call_attempt_GSM=temptacstat[hn][cr].B_call_attempt_GSM;
					tempimei.A_call_attempt_GSM=temptacstat[hn][cr].A_call_attempt_GSM;
					tempimei.A_call_attempt_TD=temptacstat[hn][cr].A_call_attempt_TD;
					tempimei.B_call_attempt_TD=temptacstat[hn][cr].B_call_attempt_TD;
					tempimei.A_BSSMAP_Cause.clear();
					tempimei.A_RANAP_Cause.clear();
					tempimei.B_BSSMAP_Cause.clear();
					tempimei.B_RANAP_Cause.clear();
					tempimei.A_DX_Cause_GSM.clear();
					tempimei.A_DX_Cause_TD.clear();
					tempimei.B_DX_Cause_GSM.clear();
					tempimei.B_DX_Cause_TD.clear();
					tempimei.A_BSSMAP_drop=0;
					tempimei.A_RANAP_drop=0;
					tempimei.B_BSSMAP_drop=0;
					tempimei.B_RANAP_drop=0;
					tempimei.A_DX_GSM_block=0;
					tempimei.A_DX_TD_block=0;
					tempimei.B_DX_GSM_block=0;
					tempimei.B_DX_TD_block=0;
					tempimei.A_call_first_cell_connected=temptacstat[hn][cr].A_call_first_cell_connected;
					tempimei.A_call_first_cell_connected_TD=temptacstat[hn][cr].A_call_first_cell_connected_TD;
					tempimei.A_call_first_cell_connected_GSM=temptacstat[hn][cr].A_call_first_cell_connected_GSM;
					tempimei.B_call_first_cell_connected=temptacstat[hn][cr].B_call_first_cell_connected;
					tempimei.B_call_first_cell_connected_TD=temptacstat[hn][cr].B_call_first_cell_connected_TD;
					tempimei.B_call_first_cell_connected_GSM=temptacstat[hn][cr].B_call_first_cell_connected_GSM;
					tempimei.A_call_last_cell_connected=temptacstat[hn][cr].A_call_last_cell_connected;
					tempimei.A_call_last_cell_connected_TD=temptacstat[hn][cr].A_call_last_cell_connected_TD;
					tempimei.A_call_last_cell_connected_GSM=temptacstat[hn][cr].A_call_last_cell_connected_GSM;
					tempimei.B_call_last_cell_connected=temptacstat[hn][cr].B_call_last_cell_connected;
					tempimei.B_call_last_cell_connected_TD=temptacstat[hn][cr].B_call_last_cell_connected_TD;
					tempimei.B_call_last_cell_connected_GSM=temptacstat[hn][cr].B_call_last_cell_connected_GSM;
					
					for(int j=0;j<temptacstat[hn][cr].A_BSSMAP_Cause.size();j++){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=temptacstat[hn][cr].A_BSSMAP_Cause[j].cause_id;
						tempcause.cause_num=temptacstat[hn][cr].A_BSSMAP_Cause[j].cause_num;
						tempimei.A_BSSMAP_Cause.push_back(tempcause);
					}
					for(int j=0;j<temptacstat[hn][cr].B_BSSMAP_Cause.size();j++){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=temptacstat[hn][cr].B_BSSMAP_Cause[j].cause_id;
						tempcause.cause_num=temptacstat[hn][cr].B_BSSMAP_Cause[j].cause_num;
						tempimei.B_BSSMAP_Cause.push_back(tempcause);
					
					}
					for(int j=0;j<temptacstat[hn][cr].A_RANAP_Cause.size();j++){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=temptacstat[hn][cr].A_RANAP_Cause[j].cause_id;
						tempcause.cause_num=temptacstat[hn][cr].A_RANAP_Cause[j].cause_num;
						tempimei.A_RANAP_Cause.push_back(tempcause);
					}
					for(int j=0;j<temptacstat[hn][cr].B_RANAP_Cause.size();j++){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=temptacstat[hn][cr].B_RANAP_Cause[j].cause_id;
						tempcause.cause_num=temptacstat[hn][cr].B_RANAP_Cause[j].cause_num;
						tempimei.B_RANAP_Cause.push_back(tempcause);
					}
					for(int j=0;j<temptacstat[hn][cr].A_DX_Cause_GSM.size();j++){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=temptacstat[hn][cr].A_DX_Cause_GSM[j].cause_id;
						tempcause.cause_num=temptacstat[hn][cr].A_DX_Cause_GSM[j].cause_num;
						tempimei.A_DX_Cause_GSM.push_back(tempcause);
					}
					for(int j=0;j<temptacstat[hn][cr].A_DX_Cause_TD.size();j++){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=temptacstat[hn][cr].A_DX_Cause_TD[j].cause_id;
						tempcause.cause_num=temptacstat[hn][cr].A_DX_Cause_TD[j].cause_num;
						tempimei.A_DX_Cause_TD.push_back(tempcause);
					}
					for(int j=0;j<temptacstat[hn][cr].B_DX_Cause_GSM.size();j++){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=temptacstat[hn][cr].B_DX_Cause_GSM[j].cause_id;
						tempcause.cause_num=temptacstat[hn][cr].B_DX_Cause_GSM[j].cause_num;
						tempimei.B_DX_Cause_GSM.push_back(tempcause);
					}
					for(int j=0;j<temptacstat[hn][cr].B_DX_Cause_TD.size();j++){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=temptacstat[hn][cr].B_DX_Cause_TD[j].cause_id;
						tempcause.cause_num=temptacstat[hn][cr].B_DX_Cause_TD[j].cause_num;
						tempimei.B_DX_Cause_TD.push_back(tempcause);
					}
				
				
					//for(int j=0;j<temptacstat[hn][cr].A_IMEI_IMSI_GSM.size();j++){
					//	if(j==0){
					//		//只初始化一次
					//		tempimei.A_IMEI_IMSI_GSM.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
					//	}
					//	for(int k=0;k<temptacstat[hn][cr].A_IMEI_IMSI_GSM[j].size();k++){
					//		int temp_hash_imei=atoi(temptacstat[hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					//
					//		IMEI_IMSI tempim;
					//		tempim.IMEI=temptacstat[hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI;
					//		tempim.IMSI=temptacstat[hn][cr].A_IMEI_IMSI_GSM[j][k].IMSI;
					//		tempimei.A_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
					//		tempimei.A_IMEI_GSM++;
					//	}
					//}
					//for(int j=0;j<temptacstat[hn][cr].A_IMEI_IMSI_TD.size();j++){
					//	if(j==0){
					//		//只初始化一次
					//		tempimei.A_IMEI_IMSI_TD.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
					//	}
					//	for(int k=0;k<temptacstat[hn][cr].A_IMEI_IMSI_TD[j].size();k++){
					//		int temp_hash_imei=atoi(temptacstat[hn][cr].A_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					//
					//		IMEI_IMSI tempim;
					//		tempim.IMEI=temptacstat[hn][cr].A_IMEI_IMSI_TD[j][k].IMEI;
					//		tempim.IMSI=temptacstat[hn][cr].A_IMEI_IMSI_TD[j][k].IMSI;
					//		tempimei.A_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
					//		tempimei.A_IMEI_TD++;
					//	}
					//}
					//for(int j=0;j<temptacstat[hn][cr].B_IMEI_IMSI_GSM.size();j++){
					//	if(j==0){
					//		//只初始化一次
					//		tempimei.B_IMEI_IMSI_GSM.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
					//	}
					//	for(int k=0;k<temptacstat[hn][cr].B_IMEI_IMSI_GSM[j].size();k++){
					//		int temp_hash_imei=atoi(temptacstat[hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					//
					//		IMEI_IMSI tempim;
					//		tempim.IMEI=temptacstat[hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI;
					//		tempim.IMSI=temptacstat[hn][cr].B_IMEI_IMSI_GSM[j][k].IMSI;
					//		tempimei.B_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
					//		tempimei.B_IMEI_GSM++;
					//	}
					//}
					//for(int j=0;j<temptacstat[hn][cr].B_IMEI_IMSI_TD.size();j++){
					//	if(j==0){
					//		//只初始化一次
					//		tempimei.B_IMEI_IMSI_TD.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
					//	}
					//	for(int k=0;k<temptacstat[hn][cr].B_IMEI_IMSI_TD[j].size();k++){
					//		int temp_hash_imei=atoi(temptacstat[hn][cr].B_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					//
					//		IMEI_IMSI tempim;
					//		tempim.IMEI=temptacstat[hn][cr].B_IMEI_IMSI_TD[j][k].IMEI;
					//		tempim.IMSI=temptacstat[hn][cr].B_IMEI_IMSI_TD[j][k].IMSI;
					//		tempimei.B_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
					//		tempimei.B_IMEI_TD++;
					//	}
					//}
					tacstat[temp_hash].push_back(tempimei);
				}
			}
		}
		//clear temptacstat
		cout<<"Start Clear Temp TAC STAT vector"<<endl;
		temptacstat.clear();
		vector<vector<IMEI_CDR_Statistic>>().swap(temptacstat);
		cout<<"Temp TAC STAT vector is cleared"<<endl;

		end=clock();
		cout<<"Combine TAC statistic with File "<<tacstatfilelist[i]<<" in "<<difftime(end,start)<<"ms"<<endl;
	
		}
	}
	//最后输出combine后的文件
	//生成tacstat本轮的输出文件名
	string result_combinetacfile_name=cfg.OutputDirectory+"\\ToCombineTACstat_Result";
	string result_combinetacfile_name1=cfg.OutputDirectory+"\\ToCombineTACstat_Result.csv";
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
	cout<<"Start Writing TAC Stat Combine Result File "<<result_combinetacfile_name1<<endl;
	WriteTACFile(result_combinetacfile_name1);
	return true;
}

//______________________最后进行tacstat和输入的taclist和celltypelist合并__________________________
//将tacstat和taclist进行join操作
bool MatchTACList(){
	time_t start,end;
	start=clock();
	int hsize=0;
	omp_set_num_threads(cfg.THREADNUM);
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
	omp_set_num_threads(cfg.THREADNUM);
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

//-----------------不同级别的合并-----------------------
//将计算好的tacstat中不同的TimeSection合并生成tacstat_timesection
bool CombineTAC_TimeSection(){
	//hash tac用后四位
	tacstat_timesection.clear();
	tacstat_timesection.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
	time_t start,end;
	int hsize=0;
	int csize=0;
	start=clock();
	omp_set_num_threads(cfg.THREADNUM);
//#pragma omp parallel for reduction(+:hsize,csize)	
#pragma omp parallel for
	for(int hn=0;hn<tacstat.size();hn++){
		
		//hsize+=(int)tacstat[hn].size();
		for(int cr=0;cr<tacstat[hn].size();cr++){
			//查询是否已经有相应的TAC记录。
			bool isExistTAC=false;
			int temp_hash=atoi(tacstat[hn][cr].TAC.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
			for(int im=0;im<tacstat_timesection[temp_hash].size();im++){
				if(tacstat_timesection[temp_hash][im].cellid==tacstat[hn][cr].cellid&&tacstat_timesection[temp_hash][im].TAC==tacstat[hn][cr].TAC){
					isExistTAC=true;
					/*tacstat_cell[temp_hash][im].A_cause0+=tacstat[hn][cr].A_cause0;
					tacstat_cell[temp_hash][im].A_cause1+=tacstat[hn][cr].A_cause1;
					tacstat_cell[temp_hash][im].A_cause20+=tacstat[hn][cr].A_cause20;
					tacstat_cell[temp_hash][im].A_cause60+=tacstat[hn][cr].A_cause60;
					tacstat_cell[temp_hash][im].B_cause0+=tacstat[hn][cr].B_cause0;
					tacstat_cell[temp_hash][im].B_cause1+=tacstat[hn][cr].B_cause1;
					tacstat_cell[temp_hash][im].B_cause20+=tacstat[hn][cr].B_cause20;
					tacstat_cell[temp_hash][im].B_cause60+=tacstat[hn][cr].B_cause60;
					tacstat_cell[temp_hash][im].A_causeGSM+=tacstat[hn][cr].A_causeGSM;
					tacstat_cell[temp_hash][im].B_causeGSM+=tacstat[hn][cr].B_causeGSM;*/
				for(int j=0;j<tacstat[hn][cr].A_BSSMAP_Cause.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesection[temp_hash][im].A_BSSMAP_Cause.size();k++){
						if(tacstat_timesection[temp_hash][im].A_BSSMAP_Cause[k].cause_id==tacstat[hn][cr].A_BSSMAP_Cause[j].cause_id){
							isExistCause=true;
							tacstat_timesection[temp_hash][im].A_BSSMAP_Cause[k].cause_num+=tacstat[hn][cr].A_BSSMAP_Cause[j].cause_num;
							if(IsDropCauseGSM(tacstat[hn][cr].A_BSSMAP_Cause[j].cause_id)){
								tacstat_timesection[temp_hash][im].A_BSSMAP_drop+=tacstat[hn][cr].A_BSSMAP_Cause[j].cause_num;
							}
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].A_BSSMAP_Cause[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].A_BSSMAP_Cause[j].cause_num;
						if(IsDropCauseGSM(tacstat[hn][cr].A_BSSMAP_Cause[j].cause_id)){
							tacstat_timesection[temp_hash][im].A_BSSMAP_drop+=tacstat[hn][cr].A_BSSMAP_Cause[j].cause_num;
						}
						tacstat_timesection[temp_hash][im].A_BSSMAP_Cause.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat[hn][cr].B_BSSMAP_Cause.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesection[temp_hash][im].B_BSSMAP_Cause.size();k++){
						if(tacstat_timesection[temp_hash][im].B_BSSMAP_Cause[k].cause_id==tacstat[hn][cr].B_BSSMAP_Cause[j].cause_id){
							isExistCause=true;
							tacstat_timesection[temp_hash][im].B_BSSMAP_Cause[k].cause_num+=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_num;
							if(IsDropCauseGSM(tacstat[hn][cr].B_BSSMAP_Cause[j].cause_id)){
								tacstat_timesection[temp_hash][im].B_BSSMAP_drop+=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_num;
							}
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_num;
						if(IsDropCauseGSM(tacstat[hn][cr].B_BSSMAP_Cause[j].cause_id)){
							tacstat_timesection[temp_hash][im].B_BSSMAP_drop+=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_num;
						}
						tacstat_timesection[temp_hash][im].B_BSSMAP_Cause.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat[hn][cr].A_RANAP_Cause.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesection[temp_hash][im].A_RANAP_Cause.size();k++){
						if(tacstat_timesection[temp_hash][im].A_RANAP_Cause[k].cause_id==tacstat[hn][cr].A_RANAP_Cause[j].cause_id){
							isExistCause=true;
							tacstat_timesection[temp_hash][im].A_RANAP_Cause[k].cause_num+=tacstat[hn][cr].A_RANAP_Cause[j].cause_num;
							if(IsDropCauseTD(tacstat[hn][cr].A_RANAP_Cause[j].cause_id)){
								tacstat_timesection[temp_hash][im].A_RANAP_drop+=tacstat[hn][cr].A_RANAP_Cause[j].cause_num;
							}
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].A_RANAP_Cause[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].A_RANAP_Cause[j].cause_num;
						if(IsDropCauseTD(tacstat[hn][cr].A_RANAP_Cause[j].cause_id)){
							tacstat_timesection[temp_hash][im].A_RANAP_drop+=tacstat[hn][cr].A_RANAP_Cause[j].cause_num;
						}
						tacstat_timesection[temp_hash][im].A_RANAP_Cause.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat[hn][cr].B_RANAP_Cause.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesection[temp_hash][im].B_RANAP_Cause.size();k++){
						if(tacstat_timesection[temp_hash][im].B_RANAP_Cause[k].cause_id==tacstat[hn][cr].B_RANAP_Cause[j].cause_id){
							isExistCause=true;
							tacstat_timesection[temp_hash][im].B_RANAP_Cause[k].cause_num+=tacstat[hn][cr].B_RANAP_Cause[j].cause_num;
							if(IsDropCauseTD(tacstat[hn][cr].B_RANAP_Cause[j].cause_id)){
								tacstat_timesection[temp_hash][im].B_RANAP_drop+=tacstat[hn][cr].B_RANAP_Cause[j].cause_num;
							}
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].B_RANAP_Cause[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].B_RANAP_Cause[j].cause_num;
						if(IsDropCauseTD(tacstat[hn][cr].B_RANAP_Cause[j].cause_id)){
							tacstat_timesection[temp_hash][im].B_RANAP_drop+=tacstat[hn][cr].B_RANAP_Cause[j].cause_num;
						}
						tacstat_timesection[temp_hash][im].B_RANAP_Cause.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat[hn][cr].A_DX_Cause_GSM.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesection[temp_hash][im].A_DX_Cause_GSM.size();k++){
						if(tacstat_timesection[temp_hash][im].A_DX_Cause_GSM[k].cause_id==tacstat[hn][cr].A_DX_Cause_GSM[j].cause_id){
							isExistCause=true;
							tacstat_timesection[temp_hash][im].A_DX_Cause_GSM[k].cause_num+=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_num;
							if(IsDXblockGSM(tacstat[hn][cr].A_DX_Cause_GSM[j].cause_id)){
								tacstat_timesection[temp_hash][im].A_DX_GSM_block+=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_num;
							}
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_num;
						if(IsDXblockGSM(tacstat[hn][cr].A_DX_Cause_GSM[j].cause_id)){
							tacstat_timesection[temp_hash][im].A_DX_GSM_block+=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_num;
						}
						tacstat_timesection[temp_hash][im].A_DX_Cause_GSM.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat[hn][cr].A_DX_Cause_TD.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesection[temp_hash][im].A_DX_Cause_TD.size();k++){
						if(tacstat_timesection[temp_hash][im].A_DX_Cause_TD[k].cause_id==tacstat[hn][cr].A_DX_Cause_TD[j].cause_id){
							isExistCause=true;
							tacstat_timesection[temp_hash][im].A_DX_Cause_TD[k].cause_num+=tacstat[hn][cr].A_DX_Cause_TD[j].cause_num;
							if(IsDXblockTD(tacstat[hn][cr].A_DX_Cause_TD[j].cause_id)){
								tacstat_timesection[temp_hash][im].A_DX_TD_block+=tacstat[hn][cr].A_DX_Cause_TD[j].cause_num;
							}
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].A_DX_Cause_TD[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].A_DX_Cause_TD[j].cause_num;
						if(IsDXblockTD(tacstat[hn][cr].A_DX_Cause_TD[j].cause_id)){
							tacstat_timesection[temp_hash][im].A_DX_TD_block+=tacstat[hn][cr].A_DX_Cause_TD[j].cause_num;
						}
						tacstat_timesection[temp_hash][im].A_DX_Cause_TD.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat[hn][cr].B_DX_Cause_GSM.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesection[temp_hash][im].B_DX_Cause_GSM.size();k++){
						if(tacstat_timesection[temp_hash][im].B_DX_Cause_GSM[k].cause_id==tacstat[hn][cr].B_DX_Cause_GSM[j].cause_id){
							isExistCause=true;
							tacstat_timesection[temp_hash][im].B_DX_Cause_GSM[k].cause_num+=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_num;
							if(IsDXblockGSM(tacstat[hn][cr].B_DX_Cause_GSM[j].cause_id)){
								tacstat_timesection[temp_hash][im].B_DX_GSM_block+=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_num;
							}
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_num;
						if(IsDXblockGSM(tacstat[hn][cr].B_DX_Cause_GSM[j].cause_id)){
							tacstat_timesection[temp_hash][im].B_DX_GSM_block+=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_num;
						}
						tacstat_timesection[temp_hash][im].B_DX_Cause_GSM.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat[hn][cr].B_DX_Cause_TD.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesection[temp_hash][im].B_DX_Cause_TD.size();k++){
						if(tacstat_timesection[temp_hash][im].B_DX_Cause_TD[k].cause_id==tacstat[hn][cr].B_DX_Cause_TD[j].cause_id){
							isExistCause=true;
							tacstat_timesection[temp_hash][im].B_DX_Cause_TD[k].cause_num+=tacstat[hn][cr].B_DX_Cause_TD[j].cause_num;
							if(IsDXblockTD(tacstat[hn][cr].B_DX_Cause_TD[j].cause_id)){
								tacstat_timesection[temp_hash][im].B_DX_TD_block+=tacstat[hn][cr].B_DX_Cause_TD[j].cause_num;
							}
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].B_DX_Cause_TD[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].B_DX_Cause_TD[j].cause_num;
						if(IsDXblockTD(tacstat[hn][cr].B_DX_Cause_TD[j].cause_id)){
							tacstat_timesection[temp_hash][im].B_DX_TD_block+=tacstat[hn][cr].B_DX_Cause_TD[j].cause_num;
						}
						tacstat_timesection[temp_hash][im].B_DX_Cause_TD.push_back(tempcause);
					}
				}
					
				tacstat_timesection[temp_hash][im].B_shortcall_1+=tacstat[hn][cr].B_shortcall_1;
				tacstat_timesection[temp_hash][im].A_shortcall_1+=tacstat[hn][cr].A_shortcall_1;
				tacstat_timesection[temp_hash][im].B_shortcall_2+=tacstat[hn][cr].B_shortcall_2;
				tacstat_timesection[temp_hash][im].A_shortcall_2+=tacstat[hn][cr].A_shortcall_2;
				tacstat_timesection[temp_hash][im].B_shortcall_3+=tacstat[hn][cr].B_shortcall_3;
				tacstat_timesection[temp_hash][im].A_shortcall_3+=tacstat[hn][cr].A_shortcall_3;
				tacstat_timesection[temp_hash][im].B_call_attempt+=tacstat[hn][cr].B_call_attempt;
				tacstat_timesection[temp_hash][im].A_call_attempt+=tacstat[hn][cr].A_call_attempt;
				tacstat_timesection[temp_hash][im].B_call_attempt_GSM+=tacstat[hn][cr].B_call_attempt_GSM;
				tacstat_timesection[temp_hash][im].A_call_attempt_GSM+=tacstat[hn][cr].A_call_attempt_GSM;
				tacstat_timesection[temp_hash][im].A_call_attempt_TD+=tacstat[hn][cr].A_call_attempt_TD;
				tacstat_timesection[temp_hash][im].B_call_attempt_TD+=tacstat[hn][cr].B_call_attempt_TD;
				tacstat_timesection[temp_hash][im].A_call_first_cell_connected+=tacstat[hn][cr].A_call_first_cell_connected;
				tacstat_timesection[temp_hash][im].A_call_first_cell_connected_TD+=tacstat[hn][cr].A_call_first_cell_connected_TD;
				tacstat_timesection[temp_hash][im].A_call_first_cell_connected_GSM+=tacstat[hn][cr].A_call_first_cell_connected_GSM;
				tacstat_timesection[temp_hash][im].B_call_first_cell_connected+=tacstat[hn][cr].B_call_first_cell_connected;
				tacstat_timesection[temp_hash][im].B_call_first_cell_connected_TD+=tacstat[hn][cr].B_call_first_cell_connected_TD;
				tacstat_timesection[temp_hash][im].B_call_first_cell_connected_GSM+=tacstat[hn][cr].B_call_first_cell_connected_GSM;
				tacstat_timesection[temp_hash][im].A_call_last_cell_connected+=tacstat[hn][cr].A_call_last_cell_connected;
				tacstat_timesection[temp_hash][im].A_call_last_cell_connected_TD+=tacstat[hn][cr].A_call_last_cell_connected_TD;
				tacstat_timesection[temp_hash][im].A_call_last_cell_connected_GSM+=tacstat[hn][cr].A_call_last_cell_connected_GSM;
				tacstat_timesection[temp_hash][im].B_call_last_cell_connected+=tacstat[hn][cr].B_call_last_cell_connected;
				tacstat_timesection[temp_hash][im].B_call_last_cell_connected_TD+=tacstat[hn][cr].B_call_last_cell_connected_TD;
				tacstat_timesection[temp_hash][im].B_call_last_cell_connected_GSM+=tacstat[hn][cr].B_call_last_cell_connected_GSM;
					
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
				tempimei.A_BSSMAP_Cause.clear();
				tempimei.A_RANAP_Cause.clear();
				tempimei.B_BSSMAP_Cause.clear();
				tempimei.B_RANAP_Cause.clear();
				tempimei.A_DX_Cause_GSM.clear();
				tempimei.A_DX_Cause_TD.clear();
				tempimei.B_DX_Cause_GSM.clear();
				tempimei.B_DX_Cause_TD.clear();
				tempimei.A_call_first_cell_connected=tacstat[hn][cr].A_call_first_cell_connected;
				tempimei.A_call_first_cell_connected_TD=tacstat[hn][cr].A_call_first_cell_connected_TD;
				tempimei.A_call_first_cell_connected_GSM=tacstat[hn][cr].A_call_first_cell_connected_GSM;
				tempimei.B_call_first_cell_connected=tacstat[hn][cr].B_call_first_cell_connected;
				tempimei.B_call_first_cell_connected_TD=tacstat[hn][cr].B_call_first_cell_connected_TD;
				tempimei.B_call_first_cell_connected_GSM=tacstat[hn][cr].B_call_first_cell_connected_GSM;
				tempimei.A_call_last_cell_connected=tacstat[hn][cr].A_call_last_cell_connected;
				tempimei.A_call_last_cell_connected_TD=tacstat[hn][cr].A_call_last_cell_connected_TD;
				tempimei.A_call_last_cell_connected_GSM=tacstat[hn][cr].A_call_last_cell_connected_GSM;
				tempimei.B_call_last_cell_connected=tacstat[hn][cr].B_call_last_cell_connected;
				tempimei.B_call_last_cell_connected_TD=tacstat[hn][cr].B_call_last_cell_connected_TD;
				tempimei.B_call_last_cell_connected_GSM=tacstat[hn][cr].B_call_last_cell_connected_GSM;
				tempimei.A_BSSMAP_drop=0;
				tempimei.A_RANAP_drop=0;
				tempimei.B_BSSMAP_drop=0;
				tempimei.B_RANAP_drop=0;
				tempimei.A_DX_GSM_block=0;
				tempimei.A_DX_TD_block=0;
				tempimei.B_DX_GSM_block=0;
				tempimei.B_DX_TD_block=0;
					
				for(int j=0;j<tacstat[hn][cr].A_BSSMAP_Cause.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].A_BSSMAP_Cause[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].A_BSSMAP_Cause[j].cause_num;
					if(IsDropCauseGSM(tacstat[hn][cr].A_BSSMAP_Cause[j].cause_id)){
						tempimei.A_BSSMAP_drop+=tacstat[hn][cr].A_BSSMAP_Cause[j].cause_num;
					}
					tempimei.A_BSSMAP_Cause.push_back(tempcause);
				}
				for(int j=0;j<tacstat[hn][cr].B_BSSMAP_Cause.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_num;
					if(IsDropCauseGSM(tacstat[hn][cr].B_BSSMAP_Cause[j].cause_id)){
						tempimei.B_BSSMAP_drop+=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_num;
					}
					tempimei.B_BSSMAP_Cause.push_back(tempcause);
				}
				for(int j=0;j<tacstat[hn][cr].A_RANAP_Cause.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].A_RANAP_Cause[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].A_RANAP_Cause[j].cause_num;
					if(IsDropCauseTD(tacstat[hn][cr].A_RANAP_Cause[j].cause_id)){
						tempimei.A_RANAP_drop+=tacstat[hn][cr].A_RANAP_Cause[j].cause_num;
					}
					tempimei.A_RANAP_Cause.push_back(tempcause);
				}
				for(int j=0;j<tacstat[hn][cr].B_RANAP_Cause.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].B_RANAP_Cause[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].B_RANAP_Cause[j].cause_num;
					if(IsDropCauseTD(tacstat[hn][cr].B_RANAP_Cause[j].cause_id)){
						tempimei.B_RANAP_drop+=tacstat[hn][cr].B_RANAP_Cause[j].cause_num;
					}
					tempimei.B_RANAP_Cause.push_back(tempcause);
				}
				for(int j=0;j<tacstat[hn][cr].A_DX_Cause_GSM.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_num;
					if(IsDXblockGSM(tacstat[hn][cr].A_DX_Cause_GSM[j].cause_id)){
						tempimei.A_DX_GSM_block+=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_num;
					}
					tempimei.A_DX_Cause_GSM.push_back(tempcause);
				}
				for(int j=0;j<tacstat[hn][cr].A_DX_Cause_TD.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].A_DX_Cause_TD[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].A_DX_Cause_TD[j].cause_num;
					if(IsDXblockTD(tacstat[hn][cr].A_DX_Cause_TD[j].cause_id)){
						tempimei.A_DX_TD_block+=tacstat[hn][cr].A_DX_Cause_TD[j].cause_num;
					}
					tempimei.A_DX_Cause_TD.push_back(tempcause);
				}
				for(int j=0;j<tacstat[hn][cr].B_DX_Cause_GSM.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_num;
					if(IsDXblockGSM(tacstat[hn][cr].B_DX_Cause_GSM[j].cause_id)){
						tempimei.B_DX_GSM_block+=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_num;
					}
					tempimei.B_DX_Cause_GSM.push_back(tempcause);
				}
				for(int j=0;j<tacstat[hn][cr].B_DX_Cause_TD.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].B_DX_Cause_TD[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].B_DX_Cause_TD[j].cause_num;
					if(IsDXblockTD(tacstat[hn][cr].B_DX_Cause_TD[j].cause_id)){
						tempimei.B_DX_TD_block+=tacstat[hn][cr].B_DX_Cause_TD[j].cause_num;
					}
					tempimei.B_DX_Cause_TD.push_back(tempcause);
				}
				
				tacstat_timesection[temp_hash].push_back(tempimei);
			}
		}
		
		//hn/cfg.THREADNUM

		if(hn%100==0){
			end=clock();
			//cout<<"Combine TAC statistic with TimeSection with "<<hsize<<" Records to "<<csize<<" Records in "<<difftime(end,start)<<"ms"<<endl;
			cout<<"Combine TAC statistic with TimeSection with HASHKEY "<<hn<<" in "<<difftime(end,start)<<"ms"<<endl;
			start=clock();
		}
	}
		
	return true;
}
//将tacstat中不同的cell合并生成tacstat_timesectioncell
bool CombineTAC_TimeSectionCell(){
	//hash tac用后四位
	tacstat_timesectioncell.clear();
	tacstat_timesectioncell.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
	time_t start,end;
	int hsize=0;
	int csize=0;
	start=clock();
	omp_set_num_threads(cfg.THREADNUM);
#pragma omp parallel for reduction(+:hsize,csize)		
	for(int hn=0;hn<tacstat.size();hn++){
		
		//hsize+=(int)tacstat[hn].size();
		for(int cr=0;cr<tacstat[hn].size();cr++){
			//查询是否已经有相应的TAC记录。
			bool isExistTAC=false;
			int temp_hash=atoi(tacstat[hn][cr].TAC.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
			for(int im=0;im<tacstat_timesectioncell[temp_hash].size();im++){
				if(tacstat_timesectioncell[temp_hash][im].TAC==tacstat[hn][cr].TAC){
					isExistTAC=true;
					for(int j=0;j<tacstat[hn][cr].A_BSSMAP_Cause.size();j++){
						bool isExistCause=false;
						for(int k=0;k<tacstat_timesectioncell[temp_hash][im].A_BSSMAP_Cause.size();k++){
							if(tacstat_timesectioncell[temp_hash][im].A_BSSMAP_Cause[k].cause_id==tacstat[hn][cr].A_BSSMAP_Cause[j].cause_id){
								isExistCause=true;
								tacstat_timesectioncell[temp_hash][im].A_BSSMAP_Cause[k].cause_num+=tacstat[hn][cr].A_BSSMAP_Cause[j].cause_num;
								if(IsDropCauseGSM(tacstat[hn][cr].A_BSSMAP_Cause[j].cause_id)){
									tacstat_timesectioncell[temp_hash][im].A_BSSMAP_drop+=tacstat[hn][cr].A_BSSMAP_Cause[j].cause_num;
								}
								break;
							}
						}
						
						if(isExistCause==false){
							CAUSE_TYPE tempcause;
							tempcause.cause_id=tacstat[hn][cr].A_BSSMAP_Cause[j].cause_id;
							tempcause.cause_num=tacstat[hn][cr].A_BSSMAP_Cause[j].cause_num;
							if(IsDropCauseGSM(tacstat[hn][cr].A_BSSMAP_Cause[j].cause_id)){
								tacstat_timesectioncell[temp_hash][im].A_BSSMAP_drop+=tacstat[hn][cr].A_BSSMAP_Cause[j].cause_num;
							}
							tacstat_timesectioncell[temp_hash][im].A_BSSMAP_Cause.push_back(tempcause);
						}
					}
				for(int j=0;j<tacstat[hn][cr].B_BSSMAP_Cause.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesectioncell[temp_hash][im].B_BSSMAP_Cause.size();k++){
						if(tacstat_timesectioncell[temp_hash][im].B_BSSMAP_Cause[k].cause_id==tacstat[hn][cr].B_BSSMAP_Cause[j].cause_id){
							isExistCause=true;
							tacstat_timesectioncell[temp_hash][im].B_BSSMAP_Cause[k].cause_num+=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_num;
							if(IsDropCauseGSM(tacstat[hn][cr].B_BSSMAP_Cause[j].cause_id)){
								tacstat_timesectioncell[temp_hash][im].B_BSSMAP_drop+=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_num;
							}
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_num;
						if(IsDropCauseGSM(tacstat[hn][cr].B_BSSMAP_Cause[j].cause_id)){
							tacstat_timesectioncell[temp_hash][im].B_BSSMAP_drop+=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_num;
						}
						tacstat_timesectioncell[temp_hash][im].B_BSSMAP_Cause.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat[hn][cr].A_RANAP_Cause.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesectioncell[temp_hash][im].A_RANAP_Cause.size();k++){
						if(tacstat_timesectioncell[temp_hash][im].A_RANAP_Cause[k].cause_id==tacstat[hn][cr].A_RANAP_Cause[j].cause_id){
							isExistCause=true;
							tacstat_timesectioncell[temp_hash][im].A_RANAP_Cause[k].cause_num+=tacstat[hn][cr].A_RANAP_Cause[j].cause_num;
							if(IsDropCauseTD(tacstat[hn][cr].A_RANAP_Cause[j].cause_id)){
								tacstat_timesectioncell[temp_hash][im].A_RANAP_drop+=tacstat[hn][cr].A_RANAP_Cause[j].cause_num;
							}
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].A_RANAP_Cause[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].A_RANAP_Cause[j].cause_num;
						if(IsDropCauseTD(tacstat[hn][cr].A_RANAP_Cause[j].cause_id)){
							tacstat_timesectioncell[temp_hash][im].A_RANAP_drop+=tacstat[hn][cr].A_RANAP_Cause[j].cause_num;
						}
						tacstat_timesectioncell[temp_hash][im].A_RANAP_Cause.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat[hn][cr].B_RANAP_Cause.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesectioncell[temp_hash][im].B_RANAP_Cause.size();k++){
						if(tacstat_timesectioncell[temp_hash][im].B_RANAP_Cause[k].cause_id==tacstat[hn][cr].B_RANAP_Cause[j].cause_id){
							isExistCause=true;
							tacstat_timesectioncell[temp_hash][im].B_RANAP_Cause[k].cause_num+=tacstat[hn][cr].B_RANAP_Cause[j].cause_num;
							if(IsDropCauseTD(tacstat[hn][cr].B_RANAP_Cause[j].cause_id)){
								tacstat_timesectioncell[temp_hash][im].B_RANAP_drop+=tacstat[hn][cr].B_RANAP_Cause[j].cause_num;
							}
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].B_RANAP_Cause[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].B_RANAP_Cause[j].cause_num;
						if(IsDropCauseTD(tacstat[hn][cr].B_RANAP_Cause[j].cause_id)){
							tacstat_timesectioncell[temp_hash][im].B_RANAP_drop+=tacstat[hn][cr].B_RANAP_Cause[j].cause_num;
						}
						tacstat_timesectioncell[temp_hash][im].B_RANAP_Cause.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat[hn][cr].A_DX_Cause_GSM.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesectioncell[temp_hash][im].A_DX_Cause_GSM.size();k++){
						if(tacstat_timesectioncell[temp_hash][im].A_DX_Cause_GSM[k].cause_id==tacstat[hn][cr].A_DX_Cause_GSM[j].cause_id){
							isExistCause=true;
							tacstat_timesectioncell[temp_hash][im].A_DX_Cause_GSM[k].cause_num+=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_num;
							if(IsDXblockGSM(tacstat[hn][cr].A_DX_Cause_GSM[j].cause_id)){
								tacstat_timesectioncell[temp_hash][im].A_DX_GSM_block+=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_num;
							}
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_num;
						if(IsDXblockGSM(tacstat[hn][cr].A_DX_Cause_GSM[j].cause_id)){
							tacstat_timesectioncell[temp_hash][im].A_DX_GSM_block+=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_num;
						}
						tacstat_timesectioncell[temp_hash][im].A_DX_Cause_GSM.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat[hn][cr].A_DX_Cause_TD.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesectioncell[temp_hash][im].A_DX_Cause_TD.size();k++){
						if(tacstat_timesectioncell[temp_hash][im].A_DX_Cause_TD[k].cause_id==tacstat[hn][cr].A_DX_Cause_TD[j].cause_id){
							isExistCause=true;
							tacstat_timesectioncell[temp_hash][im].A_DX_Cause_TD[k].cause_num+=tacstat[hn][cr].A_DX_Cause_TD[j].cause_num;
							if(IsDXblockTD(tacstat[hn][cr].A_DX_Cause_TD[j].cause_id)){
								tacstat_timesectioncell[temp_hash][im].A_DX_TD_block+=tacstat[hn][cr].A_DX_Cause_TD[j].cause_num;
							}
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].A_DX_Cause_TD[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].A_DX_Cause_TD[j].cause_num;
						if(IsDXblockTD(tacstat[hn][cr].A_DX_Cause_TD[j].cause_id)){
							tacstat_timesectioncell[temp_hash][im].A_DX_TD_block+=tacstat[hn][cr].A_DX_Cause_TD[j].cause_num;
						}
						tacstat_timesectioncell[temp_hash][im].A_DX_Cause_TD.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat[hn][cr].B_DX_Cause_GSM.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesectioncell[temp_hash][im].B_DX_Cause_GSM.size();k++){
						if(tacstat_timesectioncell[temp_hash][im].B_DX_Cause_GSM[k].cause_id==tacstat[hn][cr].B_DX_Cause_GSM[j].cause_id){
							isExistCause=true;
							tacstat_timesectioncell[temp_hash][im].B_DX_Cause_GSM[k].cause_num+=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_num;
							if(IsDXblockGSM(tacstat[hn][cr].B_DX_Cause_GSM[j].cause_id)){
								tacstat_timesectioncell[temp_hash][im].B_DX_GSM_block+=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_num;
							}
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_num;
						if(IsDXblockGSM(tacstat[hn][cr].B_DX_Cause_GSM[j].cause_id)){
							tacstat_timesectioncell[temp_hash][im].B_DX_GSM_block+=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_num;
						}
						tacstat_timesectioncell[temp_hash][im].B_DX_Cause_GSM.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat[hn][cr].B_DX_Cause_TD.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesectioncell[temp_hash][im].B_DX_Cause_TD.size();k++){
						if(tacstat_timesectioncell[temp_hash][im].B_DX_Cause_TD[k].cause_id==tacstat[hn][cr].B_DX_Cause_TD[j].cause_id){
							isExistCause=true;
							tacstat_timesectioncell[temp_hash][im].B_DX_Cause_TD[k].cause_num+=tacstat[hn][cr].B_DX_Cause_TD[j].cause_num;
							if(IsDXblockTD(tacstat[hn][cr].B_DX_Cause_TD[j].cause_id)){
								tacstat_timesectioncell[temp_hash][im].B_DX_TD_block+=tacstat[hn][cr].B_DX_Cause_TD[j].cause_num;
							}
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].B_DX_Cause_TD[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].B_DX_Cause_TD[j].cause_num;
						if(IsDXblockTD(tacstat[hn][cr].B_DX_Cause_TD[j].cause_id)){
							tacstat_timesectioncell[temp_hash][im].B_DX_TD_block+=tacstat[hn][cr].B_DX_Cause_TD[j].cause_num;
						}
						tacstat_timesectioncell[temp_hash][im].B_DX_Cause_TD.push_back(tempcause);
					}
				}
					
				//for(int j=0;j<tacstat_timesection[hn][cr].A_IMEI_IMSI_GSM.size();j++){
				//	for(int k=0;k<tacstat_timesection[hn][cr].A_IMEI_IMSI_GSM[j].size();k++){
				//		//对每一个IMEI和IMSI组合，查询是否已有记录
				//		bool isExistIMEI=false;
				//		bool isExistIMEIandIMSI=false;
				//		int temp_hash_imei=atoi(tacstat_timesection[hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
				//		for(int m=0;m<tacstat_timesectioncell[temp_hash][im].A_IMEI_IMSI_GSM[temp_hash_imei].size();m++){
				//			if(tacstat_timesection[hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI==tacstat_timesectioncell[temp_hash][im].A_IMEI_IMSI_GSM[temp_hash_imei][m].IMEI){
				//				isExistIMEI=true;
				//				if(tacstat_timesection[hn][cr].A_IMEI_IMSI_GSM[j][k].IMSI==tacstat_timesectioncell[temp_hash][im].A_IMEI_IMSI_GSM[temp_hash_imei][m].IMSI){
				//					isExistIMEIandIMSI=true;
				//					break;
				//				}
				//			}
				//		}

				//		if(isExistIMEIandIMSI==false){
				//			//如果IMEI和IMSI组成的对不重复，那么新增一个
				//			IMEI_IMSI tempim;
				//			tempim.IMEI=tacstat_timesection[hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI;
				//			tempim.IMSI=tacstat_timesection[hn][cr].A_IMEI_IMSI_GSM[j][k].IMSI;
				//			tacstat_timesectioncell[temp_hash][im].A_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
				//		}

				//		if(isExistIMEI==false){
				//			//如果IMEI不重复
				//			tacstat_timesectioncell[temp_hash][im].A_IMEI_GSM++;
				//		}
				//	}
				//}
				//for(int j=0;j<tacstat_timesection[hn][cr].A_IMEI_IMSI_TD.size();j++){
				//	for(int k=0;k<tacstat_timesection[hn][cr].A_IMEI_IMSI_TD[j].size();k++){
				//		//对每一个IMEI和IMSI组合，查询是否已有记录
				//		bool isExistIMEI=false;
				//		bool isExistIMEIandIMSI=false;
				//		int temp_hash_imei=atoi(tacstat_timesection[hn][cr].A_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
				//		for(int m=0;m<tacstat_timesectioncell[temp_hash][im].A_IMEI_IMSI_TD[temp_hash_imei].size();m++){
				//			if(tacstat_timesection[hn][cr].A_IMEI_IMSI_TD[j][k].IMEI==tacstat_timesectioncell[temp_hash][im].A_IMEI_IMSI_TD[temp_hash_imei][m].IMEI){
				//				isExistIMEI=true;
				//				if(tacstat_timesection[hn][cr].A_IMEI_IMSI_TD[j][k].IMSI==tacstat_timesectioncell[temp_hash][im].A_IMEI_IMSI_TD[temp_hash_imei][m].IMSI){
				//					isExistIMEIandIMSI=true;
				//					break;
				//				}
				//			}
				//		}

				//		if(isExistIMEIandIMSI==false){
				//			//如果IMEI和IMSI组成的对不重复，那么新增一个
				//			IMEI_IMSI tempim;
				//			tempim.IMEI=tacstat_timesection[hn][cr].A_IMEI_IMSI_TD[j][k].IMEI;
				//			tempim.IMSI=tacstat_timesection[hn][cr].A_IMEI_IMSI_TD[j][k].IMSI;
				//			tacstat_timesectioncell[temp_hash][im].A_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
				//		}

				//		if(isExistIMEI==false){
				//			//如果IMEI不重复
				//			tacstat_timesectioncell[temp_hash][im].A_IMEI_TD++;
				//		}
				//	}
				//}
				//for(int j=0;j<tacstat_timesection[hn][cr].B_IMEI_IMSI_GSM.size();j++){
				//	for(int k=0;k<tacstat_timesection[hn][cr].B_IMEI_IMSI_GSM[j].size();k++){
				//		//对每一个IMEI和IMSI组合，查询是否已有记录
				//		bool isExistIMEI=false;
				//		bool isExistIMEIandIMSI=false;
				//		int temp_hash_imei=atoi(tacstat_timesection[hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
				//		for(int m=0;m<tacstat_timesectioncell[temp_hash][im].B_IMEI_IMSI_GSM[temp_hash_imei].size();m++){
				//			if(tacstat_timesection[hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI==tacstat_timesectioncell[temp_hash][im].B_IMEI_IMSI_GSM[temp_hash_imei][m].IMEI){
				//				isExistIMEI=true;
				//				if(tacstat_timesection[hn][cr].B_IMEI_IMSI_GSM[j][k].IMSI==tacstat_timesectioncell[temp_hash][im].B_IMEI_IMSI_GSM[temp_hash_imei][m].IMSI){
				//					isExistIMEIandIMSI=true;
				//					break;
				//				}
				//			}
				//		}

				//		if(isExistIMEIandIMSI==false){
				//			//如果IMEI和IMSI组成的对不重复，那么新增一个
				//			IMEI_IMSI tempim;
				//			tempim.IMEI=tacstat_timesection[hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI;
				//			tempim.IMSI=tacstat_timesection[hn][cr].B_IMEI_IMSI_GSM[j][k].IMSI;
				//			tacstat_timesectioncell[temp_hash][im].B_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
				//		}

				//		if(isExistIMEI==false){
				//			//如果IMEI不重复
				//			tacstat_timesectioncell[temp_hash][im].B_IMEI_GSM++;
				//		}
				//	}
				//}
				//for(int j=0;j<tacstat_timesection[hn][cr].B_IMEI_IMSI_TD.size();j++){
				//	for(int k=0;k<tacstat_timesection[hn][cr].B_IMEI_IMSI_TD[j].size();k++){
				//		//对每一个IMEI和IMSI组合，查询是否已有记录
				//		bool isExistIMEI=false;
				//		bool isExistIMEIandIMSI=false;
				//		int temp_hash_imei=atoi(tacstat_timesection[hn][cr].B_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
				//		for(int m=0;m<tacstat_timesectioncell[temp_hash][im].B_IMEI_IMSI_TD[temp_hash_imei].size();m++){
				//			if(tacstat_timesection[hn][cr].B_IMEI_IMSI_TD[j][k].IMEI==tacstat_timesectioncell[temp_hash][im].B_IMEI_IMSI_TD[temp_hash_imei][m].IMEI){
				//				isExistIMEI=true;
				//				if(tacstat_timesection[hn][cr].B_IMEI_IMSI_TD[j][k].IMSI==tacstat_timesectioncell[temp_hash][im].B_IMEI_IMSI_TD[temp_hash_imei][m].IMSI){
				//					isExistIMEIandIMSI=true;
				//					break;
				//				}
				//			}
				//		}

				//		if(isExistIMEIandIMSI==false){
				//			//如果IMEI和IMSI组成的对不重复，那么新增一个
				//			IMEI_IMSI tempim;
				//			tempim.IMEI=tacstat_timesection[hn][cr].B_IMEI_IMSI_TD[j][k].IMEI;
				//			tempim.IMSI=tacstat_timesection[hn][cr].B_IMEI_IMSI_TD[j][k].IMSI;
				//			tacstat_timesectioncell[temp_hash][im].B_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
				//		}

				//		if(isExistIMEI==false){
				//			//如果IMEI不重复
				//			tacstat_timesectioncell[temp_hash][im].B_IMEI_TD++;
				//		}
				//	}
				//}
				tacstat_timesectioncell[temp_hash][im].B_shortcall_1+=tacstat[hn][cr].B_shortcall_1;
				tacstat_timesectioncell[temp_hash][im].A_shortcall_1+=tacstat[hn][cr].A_shortcall_1;
				tacstat_timesectioncell[temp_hash][im].B_shortcall_2+=tacstat[hn][cr].B_shortcall_2;
				tacstat_timesectioncell[temp_hash][im].A_shortcall_2+=tacstat[hn][cr].A_shortcall_2;
				tacstat_timesectioncell[temp_hash][im].B_shortcall_3+=tacstat[hn][cr].B_shortcall_3;
				tacstat_timesectioncell[temp_hash][im].A_shortcall_3+=tacstat[hn][cr].A_shortcall_3;
				tacstat_timesectioncell[temp_hash][im].B_call_attempt+=tacstat[hn][cr].B_call_attempt;
				tacstat_timesectioncell[temp_hash][im].A_call_attempt+=tacstat[hn][cr].A_call_attempt;
				tacstat_timesectioncell[temp_hash][im].B_call_attempt_GSM+=tacstat[hn][cr].B_call_attempt_GSM;
				tacstat_timesectioncell[temp_hash][im].A_call_attempt_GSM+=tacstat[hn][cr].A_call_attempt_GSM;
				tacstat_timesectioncell[temp_hash][im].A_call_attempt_TD+=tacstat[hn][cr].A_call_attempt_TD;
				tacstat_timesectioncell[temp_hash][im].B_call_attempt_TD+=tacstat[hn][cr].B_call_attempt_TD;
				tacstat_timesectioncell[temp_hash][im].A_call_first_cell_connected+=tacstat[hn][cr].A_call_first_cell_connected;
				tacstat_timesectioncell[temp_hash][im].A_call_first_cell_connected_TD+=tacstat[hn][cr].A_call_first_cell_connected_TD;
				tacstat_timesectioncell[temp_hash][im].A_call_first_cell_connected_GSM+=tacstat[hn][cr].A_call_first_cell_connected_GSM;
				tacstat_timesectioncell[temp_hash][im].B_call_first_cell_connected+=tacstat[hn][cr].B_call_first_cell_connected;
				tacstat_timesectioncell[temp_hash][im].B_call_first_cell_connected_TD+=tacstat[hn][cr].B_call_first_cell_connected_TD;
				tacstat_timesectioncell[temp_hash][im].B_call_first_cell_connected_GSM+=tacstat[hn][cr].B_call_first_cell_connected_GSM;
				tacstat_timesectioncell[temp_hash][im].A_call_last_cell_connected+=tacstat[hn][cr].A_call_last_cell_connected;
				tacstat_timesectioncell[temp_hash][im].A_call_last_cell_connected_TD+=tacstat[hn][cr].A_call_last_cell_connected_TD;
				tacstat_timesectioncell[temp_hash][im].A_call_last_cell_connected_GSM+=tacstat[hn][cr].A_call_last_cell_connected_GSM;
				tacstat_timesectioncell[temp_hash][im].B_call_last_cell_connected+=tacstat[hn][cr].B_call_last_cell_connected;
				tacstat_timesectioncell[temp_hash][im].B_call_last_cell_connected_TD+=tacstat[hn][cr].B_call_last_cell_connected_TD;
				tacstat_timesectioncell[temp_hash][im].B_call_last_cell_connected_GSM+=tacstat[hn][cr].B_call_last_cell_connected_GSM;
				
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
				tempimei.A_call_first_cell_connected=tacstat[hn][cr].A_call_first_cell_connected;
				tempimei.A_call_first_cell_connected_TD=tacstat[hn][cr].A_call_first_cell_connected_TD;
				tempimei.A_call_first_cell_connected_GSM=tacstat[hn][cr].A_call_first_cell_connected_GSM;
				tempimei.B_call_first_cell_connected=tacstat[hn][cr].B_call_first_cell_connected;
				tempimei.B_call_first_cell_connected_TD=tacstat[hn][cr].B_call_first_cell_connected_TD;
				tempimei.B_call_first_cell_connected_GSM=tacstat[hn][cr].B_call_first_cell_connected_GSM;
				tempimei.A_call_last_cell_connected=tacstat[hn][cr].A_call_last_cell_connected;
				tempimei.A_call_last_cell_connected_TD=tacstat[hn][cr].A_call_last_cell_connected_TD;
				tempimei.A_call_last_cell_connected_GSM=tacstat[hn][cr].A_call_last_cell_connected_GSM;
				tempimei.B_call_last_cell_connected=tacstat[hn][cr].B_call_last_cell_connected;
				tempimei.B_call_last_cell_connected_TD=tacstat[hn][cr].B_call_last_cell_connected_TD;
				tempimei.B_call_last_cell_connected_GSM=tacstat[hn][cr].B_call_last_cell_connected_GSM;
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
				tempimei.A_BSSMAP_Cause.clear();
				tempimei.A_RANAP_Cause.clear();
				tempimei.B_BSSMAP_Cause.clear();
				tempimei.B_RANAP_Cause.clear();
				tempimei.A_DX_Cause_GSM.clear();
				tempimei.A_DX_Cause_TD.clear();
				tempimei.B_DX_Cause_GSM.clear();
				tempimei.B_DX_Cause_TD.clear();
				tempimei.A_BSSMAP_drop=0;
				tempimei.A_RANAP_drop=0;
				tempimei.B_BSSMAP_drop=0;
				tempimei.B_RANAP_drop=0;
				tempimei.A_DX_GSM_block=0;
				tempimei.A_DX_TD_block=0;
				tempimei.B_DX_GSM_block=0;
				tempimei.B_DX_TD_block=0;
					
				for(int j=0;j<tacstat[hn][cr].A_BSSMAP_Cause.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].A_BSSMAP_Cause[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].A_BSSMAP_Cause[j].cause_num;
					if(IsDropCauseGSM(tacstat[hn][cr].A_BSSMAP_Cause[j].cause_id)){
						tempimei.A_BSSMAP_drop+=tacstat[hn][cr].A_BSSMAP_Cause[j].cause_num;
					}
					tempimei.A_BSSMAP_Cause.push_back(tempcause);
				}
				for(int j=0;j<tacstat[hn][cr].B_BSSMAP_Cause.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_num;
					if(IsDropCauseTD(tacstat[hn][cr].B_BSSMAP_Cause[j].cause_id)){
						tempimei.B_BSSMAP_drop+=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_num;
					}
					tempimei.B_BSSMAP_Cause.push_back(tempcause);
					
				}
				for(int j=0;j<tacstat[hn][cr].A_RANAP_Cause.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].A_RANAP_Cause[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].A_RANAP_Cause[j].cause_num;
					if(IsDropCauseGSM(tacstat[hn][cr].A_RANAP_Cause[j].cause_id)){
						tempimei.A_RANAP_drop+=tacstat[hn][cr].A_RANAP_Cause[j].cause_num;
					}
					tempimei.A_RANAP_Cause.push_back(tempcause);
				}
				for(int j=0;j<tacstat[hn][cr].B_RANAP_Cause.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].B_RANAP_Cause[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].B_RANAP_Cause[j].cause_num;
					if(IsDropCauseTD(tacstat[hn][cr].B_RANAP_Cause[j].cause_id)){
						tempimei.B_RANAP_drop+=tacstat[hn][cr].B_RANAP_Cause[j].cause_num;
					}
					tempimei.B_RANAP_Cause.push_back(tempcause);
				}
				for(int j=0;j<tacstat[hn][cr].A_DX_Cause_GSM.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_num;
					if(IsDXblockGSM(tacstat[hn][cr].A_DX_Cause_GSM[j].cause_id)){
						tempimei.A_DX_GSM_block+=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_num;
					}
					tempimei.A_DX_Cause_GSM.push_back(tempcause);
				}
				for(int j=0;j<tacstat[hn][cr].A_DX_Cause_TD.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].A_DX_Cause_TD[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].A_DX_Cause_TD[j].cause_num;
					if(IsDXblockTD(tacstat[hn][cr].A_DX_Cause_TD[j].cause_id)){
						tempimei.A_DX_TD_block+=tacstat[hn][cr].A_DX_Cause_TD[j].cause_num;
					}
					tempimei.A_DX_Cause_TD.push_back(tempcause);
				}
				for(int j=0;j<tacstat[hn][cr].B_DX_Cause_GSM.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_num;
					if(IsDXblockGSM(tacstat[hn][cr].B_DX_Cause_GSM[j].cause_id)){
						tempimei.B_DX_GSM_block+=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_num;
					}
					tempimei.B_DX_Cause_GSM.push_back(tempcause);
				}
				for(int j=0;j<tacstat[hn][cr].B_DX_Cause_TD.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].B_DX_Cause_TD[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].B_DX_Cause_TD[j].cause_num;
					if(IsDXblockTD(tacstat[hn][cr].B_DX_Cause_TD[j].cause_id)){
						tempimei.B_DX_TD_block+=tacstat[hn][cr].B_DX_Cause_TD[j].cause_num;
					}
					tempimei.B_DX_Cause_TD.push_back(tempcause);
				}
				
				
				tacstat_timesectioncell[temp_hash].push_back(tempimei);
			}
		}
		if(hn%100==0){
			end=clock();
			//cout<<"Combine TAC statistic with Cell with "<<hsize<<" Records to "<<csize<<" Records in "<<difftime(end,start)<<"ms"<<endl;
			cout<<"Combine TAC statistic with Cell with HASHKEY "<<hn<<" in "<<difftime(end,start)<<"ms"<<endl;
			start=clock();
		}
	}
	return true;
}

//--------------------原因分类--------
bool IsDropCauseGSM(int causeid){
	if(causeid==0||causeid==1||causeid==20||causeid==60){
		return true;
	}
	return false;
}

bool IsDropCauseTD(int causeid){
	if(causeid!=0){
		return true;
	}
	return false;
}

bool IsDXblockGSM(int causeid){
	return false;
}

bool IsDXblockTD(int causeid){
	return false;
}