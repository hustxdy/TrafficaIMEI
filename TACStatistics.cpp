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
					
					for(int j=0;j<imeicdrfile[fn][hn][cr].A_IMEI_IMSI_GSM.size();j++){
						for(int k=0;k<imeicdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j].size();k++){
							//对每一个IMEI和IMSI组合，查询是否已有记录
							bool isExistIMEI=false;
							bool isExistIMEIandIMSI=false;
							int temp_hash_imei=atoi(imeicdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
							for(int m=0;m<taccdrfile[fn][temp_hash][i].A_IMEI_IMSI_GSM[temp_hash_imei].size();m++){
								if(imeicdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI==taccdrfile[fn][temp_hash][i].A_IMEI_IMSI_GSM[temp_hash_imei][m].IMEI){
									isExistIMEI=true;
									if(imeicdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMSI==taccdrfile[fn][temp_hash][i].A_IMEI_IMSI_GSM[temp_hash_imei][m].IMSI){
										isExistIMEIandIMSI=true;
										break;
									}
								}
							}

							if(isExistIMEIandIMSI==false){
								//如果IMEI和IMSI组成的对不重复，那么新增一个
								IMEI_IMSI tempim;
								tempim.IMEI=imeicdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI;
								tempim.IMSI=imeicdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMSI;
								taccdrfile[fn][temp_hash][i].A_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
							}

							if(isExistIMEI==false){
								//如果IMEI不重复
								taccdrfile[fn][temp_hash][i].A_IMEI_GSM++;
							}
						}
					}
					for(int j=0;j<imeicdrfile[fn][hn][cr].A_IMEI_IMSI_TD.size();j++){
						for(int k=0;k<imeicdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j].size();k++){
							//对每一个IMEI和IMSI组合，查询是否已有记录
							bool isExistIMEI=false;
							bool isExistIMEIandIMSI=false;
							int temp_hash_imei=atoi(imeicdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
							for(int m=0;m<taccdrfile[fn][temp_hash][i].A_IMEI_IMSI_TD[temp_hash_imei].size();m++){
								if(imeicdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMEI==taccdrfile[fn][temp_hash][i].A_IMEI_IMSI_TD[temp_hash_imei][m].IMEI){
									isExistIMEI=true;
									if(imeicdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMSI==taccdrfile[fn][temp_hash][i].A_IMEI_IMSI_TD[temp_hash_imei][m].IMSI){
										isExistIMEIandIMSI=true;
										break;
									}
								}
							}

							if(isExistIMEIandIMSI==false){
								//如果IMEI和IMSI组成的对不重复，那么新增一个
								IMEI_IMSI tempim;
								tempim.IMEI=imeicdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMEI;
								tempim.IMSI=imeicdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMSI;
								taccdrfile[fn][temp_hash][i].A_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
							}

							if(isExistIMEI==false){
								//如果IMEI不重复
								taccdrfile[fn][temp_hash][i].A_IMEI_TD++;
							}
						}
					}
					for(int j=0;j<imeicdrfile[fn][hn][cr].B_IMEI_IMSI_GSM.size();j++){
						for(int k=0;k<imeicdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j].size();k++){
							//对每一个IMEI和IMSI组合，查询是否已有记录
							bool isExistIMEI=false;
							bool isExistIMEIandIMSI=false;
							int temp_hash_imei=atoi(imeicdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
							for(int m=0;m<taccdrfile[fn][temp_hash][i].B_IMEI_IMSI_GSM[temp_hash_imei].size();m++){
								if(imeicdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI==taccdrfile[fn][temp_hash][i].B_IMEI_IMSI_GSM[temp_hash_imei][m].IMEI){
									isExistIMEI=true;
									if(imeicdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMSI==taccdrfile[fn][temp_hash][i].B_IMEI_IMSI_GSM[temp_hash_imei][m].IMSI){
										isExistIMEIandIMSI=true;
										break;
									}
								}
							}

							if(isExistIMEIandIMSI==false){
								//如果IMEI和IMSI组成的对不重复，那么新增一个
								IMEI_IMSI tempim;
								tempim.IMEI=imeicdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI;
								tempim.IMSI=imeicdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMSI;
								taccdrfile[fn][temp_hash][i].B_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
							}

							if(isExistIMEI==false){
								//如果IMEI不重复
								taccdrfile[fn][temp_hash][i].B_IMEI_GSM++;
							}
						}
					}
					for(int j=0;j<imeicdrfile[fn][hn][cr].B_IMEI_IMSI_TD.size();j++){
						for(int k=0;k<imeicdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j].size();k++){
							//对每一个IMEI和IMSI组合，查询是否已有记录
							bool isExistIMEI=false;
							bool isExistIMEIandIMSI=false;
							int temp_hash_imei=atoi(imeicdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
							for(int m=0;m<taccdrfile[fn][temp_hash][i].B_IMEI_IMSI_TD[temp_hash_imei].size();m++){
								if(imeicdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMEI==taccdrfile[fn][temp_hash][i].B_IMEI_IMSI_TD[temp_hash_imei][m].IMEI){
									isExistIMEI=true;
									if(imeicdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMSI==taccdrfile[fn][temp_hash][i].B_IMEI_IMSI_TD[temp_hash_imei][m].IMSI){
										isExistIMEIandIMSI=true;
										break;
									}
								}
							}

							if(isExistIMEIandIMSI==false){
								//如果IMEI和IMSI组成的对不重复，那么新增一个
								IMEI_IMSI tempim;
								tempim.IMEI=imeicdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMEI;
								tempim.IMSI=imeicdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMSI;
								taccdrfile[fn][temp_hash][i].B_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
							}

							if(isExistIMEI==false){
								//如果IMEI不重复
								taccdrfile[fn][temp_hash][i].B_IMEI_TD++;
							}
						}
					}
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
					/*taccdrfile[fn][temp_hash][i].A_causeTD+=imeicdrfile[fn][hn][cr].A_causeTD;
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
					*/
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
				tempimei.timeSection=imeicdrfile[fn][hn][cr].timeSection;
				tempimei.timeSectionStartTime=imeicdrfile[fn][hn][cr].timeSectionStartTime;
				/*tempimei.A_cause0=imeicdrfile[fn][hn][cr].A_cause0;
				tempimei.A_cause1=imeicdrfile[fn][hn][cr].A_cause1;
				tempimei.A_cause20=imeicdrfile[fn][hn][cr].A_cause20;
				tempimei.A_cause60=imeicdrfile[fn][hn][cr].A_cause60;
				tempimei.B_cause0=imeicdrfile[fn][hn][cr].B_cause0;
				tempimei.B_cause1=imeicdrfile[fn][hn][cr].B_cause1;
				tempimei.B_cause20=imeicdrfile[fn][hn][cr].B_cause20;
				tempimei.B_cause60=imeicdrfile[fn][hn][cr].B_cause60;
				tempimei.A_causeGSM=imeicdrfile[fn][hn][cr].A_causeGSM;
				tempimei.B_causeGSM=imeicdrfile[fn][hn][cr].B_causeGSM;*/
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
				tempimei.A_BSSMAP_Cause.clear();
				tempimei.A_RANAP_Cause.clear();
				tempimei.B_BSSMAP_Cause.clear();
				tempimei.B_RANAP_Cause.clear();
				tempimei.A_DX_Cause_GSM.clear();
				tempimei.A_DX_Cause_TD.clear();
				tempimei.B_DX_Cause_GSM.clear();
				tempimei.B_DX_Cause_TD.clear();
				tempimei.A_IMEI_IMSI_GSM.clear();
				tempimei.A_IMEI_IMSI_TD.clear();
				tempimei.B_IMEI_IMSI_GSM.clear();
				tempimei.B_IMEI_IMSI_TD.clear();
				tempimei.A_IMEI_GSM=0;
				tempimei.A_IMEI_TD=0;
				tempimei.B_IMEI_GSM=0;
				tempimei.B_IMEI_TD=0;
				
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
				
				
				for(int j=0;j<imeicdrfile[fn][hn][cr].A_IMEI_IMSI_GSM.size();j++){
					if(j==0){
						//只初始化一次
						tempimei.A_IMEI_IMSI_GSM.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
					}
					for(int k=0;k<imeicdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j].size();k++){
						int temp_hash_imei=atoi(imeicdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					
						IMEI_IMSI tempim;
						tempim.IMEI=imeicdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI;
						tempim.IMSI=imeicdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMSI;
						tempimei.A_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
						tempimei.A_IMEI_GSM++;
					}
				}
				for(int j=0;j<imeicdrfile[fn][hn][cr].A_IMEI_IMSI_TD.size();j++){
					if(j==0){
						//只初始化一次
						tempimei.A_IMEI_IMSI_TD.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
					}
					for(int k=0;k<imeicdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j].size();k++){
						int temp_hash_imei=atoi(imeicdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					
						IMEI_IMSI tempim;
						tempim.IMEI=imeicdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMEI;
						tempim.IMSI=imeicdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMSI;
						tempimei.A_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
						tempimei.A_IMEI_TD++;
					}
				}
				for(int j=0;j<imeicdrfile[fn][hn][cr].B_IMEI_IMSI_GSM.size();j++){
					if(j==0){
						//只初始化一次
						tempimei.B_IMEI_IMSI_GSM.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
					}
					for(int k=0;k<imeicdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j].size();k++){
						int temp_hash_imei=atoi(imeicdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					
						IMEI_IMSI tempim;
						tempim.IMEI=imeicdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI;
						tempim.IMSI=imeicdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMSI;
						tempimei.B_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
						tempimei.B_IMEI_GSM++;
					}
				}
				for(int j=0;j<imeicdrfile[fn][hn][cr].B_IMEI_IMSI_TD.size();j++){
					if(j==0){
						//只初始化一次
						tempimei.B_IMEI_IMSI_TD.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
					}
					for(int k=0;k<imeicdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j].size();k++){
						int temp_hash_imei=atoi(imeicdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					
						IMEI_IMSI tempim;
						tempim.IMEI=imeicdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMEI;
						tempim.IMSI=imeicdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMSI;
						tempimei.B_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
						tempimei.B_IMEI_TD++;
					}
				}

				/*tempimei.A_causeTD=imeicdrfile[fn][hn][cr].A_causeTD;
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
				tempimei.B_causeTDTransport=imeicdrfile[fn][hn][cr].B_causeTDTransport;*/
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
						/*tacstat[temp_hash][im].A_cause0+=taccdrfile[fn][hn][cr].A_cause0;
						tacstat[temp_hash][im].A_cause1+=taccdrfile[fn][hn][cr].A_cause1;
						tacstat[temp_hash][im].A_cause20+=taccdrfile[fn][hn][cr].A_cause20;
						tacstat[temp_hash][im].A_cause60+=taccdrfile[fn][hn][cr].A_cause60;
						tacstat[temp_hash][im].B_cause0+=taccdrfile[fn][hn][cr].B_cause0;
						tacstat[temp_hash][im].B_cause1+=taccdrfile[fn][hn][cr].B_cause1;
						tacstat[temp_hash][im].B_cause20+=taccdrfile[fn][hn][cr].B_cause20;
						tacstat[temp_hash][im].B_cause60+=taccdrfile[fn][hn][cr].B_cause60;
						tacstat[temp_hash][im].A_causeGSM+=taccdrfile[fn][hn][cr].A_causeGSM;
						tacstat[temp_hash][im].B_causeGSM+=taccdrfile[fn][hn][cr].B_causeGSM;*/
						
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
					
					for(int j=0;j<taccdrfile[fn][hn][cr].A_IMEI_IMSI_GSM.size();j++){
						for(int k=0;k<taccdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j].size();k++){
							//对每一个IMEI和IMSI组合，查询是否已有记录
							bool isExistIMEI=false;
							bool isExistIMEIandIMSI=false;
							int temp_hash_imei=atoi(taccdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
							for(int m=0;m<tacstat[temp_hash][im].A_IMEI_IMSI_GSM[temp_hash_imei].size();m++){
								if(taccdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI==tacstat[temp_hash][im].A_IMEI_IMSI_GSM[temp_hash_imei][m].IMEI){
									isExistIMEI=true;
									if(taccdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMSI==tacstat[temp_hash][im].A_IMEI_IMSI_GSM[temp_hash_imei][m].IMSI){
										isExistIMEIandIMSI=true;
										break;
									}
								}
							}

							if(isExistIMEIandIMSI==false){
								//如果IMEI和IMSI组成的对不重复，那么新增一个
								IMEI_IMSI tempim;
								tempim.IMEI=taccdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI;
								tempim.IMSI=taccdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMSI;
								tacstat[temp_hash][im].A_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
							}

							if(isExistIMEI==false){
								//如果IMEI不重复
								tacstat[temp_hash][im].A_IMEI_GSM++;
							}
						}
					}
					for(int j=0;j<taccdrfile[fn][hn][cr].A_IMEI_IMSI_TD.size();j++){
						for(int k=0;k<taccdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j].size();k++){
							//对每一个IMEI和IMSI组合，查询是否已有记录
							bool isExistIMEI=false;
							bool isExistIMEIandIMSI=false;
							int temp_hash_imei=atoi(taccdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
							for(int m=0;m<tacstat[temp_hash][im].A_IMEI_IMSI_TD[temp_hash_imei].size();m++){
								if(taccdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMEI==tacstat[temp_hash][im].A_IMEI_IMSI_TD[temp_hash_imei][m].IMEI){
									isExistIMEI=true;
									if(taccdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMSI==tacstat[temp_hash][im].A_IMEI_IMSI_TD[temp_hash_imei][m].IMSI){
										isExistIMEIandIMSI=true;
										break;
									}
								}
							}

							if(isExistIMEIandIMSI==false){
								//如果IMEI和IMSI组成的对不重复，那么新增一个
								IMEI_IMSI tempim;
								tempim.IMEI=taccdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMEI;
								tempim.IMSI=taccdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMSI;
								tacstat[temp_hash][im].A_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
							}

							if(isExistIMEI==false){
								//如果IMEI不重复
								tacstat[temp_hash][im].A_IMEI_TD++;
							}
						}
					}
					for(int j=0;j<taccdrfile[fn][hn][cr].B_IMEI_IMSI_GSM.size();j++){
						for(int k=0;k<taccdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j].size();k++){
							//对每一个IMEI和IMSI组合，查询是否已有记录
							bool isExistIMEI=false;
							bool isExistIMEIandIMSI=false;
							int temp_hash_imei=atoi(taccdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
							for(int m=0;m<tacstat[temp_hash][im].B_IMEI_IMSI_GSM[temp_hash_imei].size();m++){
								if(taccdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI==tacstat[temp_hash][im].B_IMEI_IMSI_GSM[temp_hash_imei][m].IMEI){
									isExistIMEI=true;
									if(taccdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMSI==tacstat[temp_hash][im].B_IMEI_IMSI_GSM[temp_hash_imei][m].IMSI){
										isExistIMEIandIMSI=true;
										break;
									}
								}
							}

							if(isExistIMEIandIMSI==false){
								//如果IMEI和IMSI组成的对不重复，那么新增一个
								IMEI_IMSI tempim;
								tempim.IMEI=taccdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI;
								tempim.IMSI=taccdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMSI;
								tacstat[temp_hash][im].B_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
							}

							if(isExistIMEI==false){
								//如果IMEI不重复
								tacstat[temp_hash][im].B_IMEI_GSM++;
							}
						}
					}
					for(int j=0;j<taccdrfile[fn][hn][cr].B_IMEI_IMSI_TD.size();j++){
						for(int k=0;k<taccdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j].size();k++){
							//对每一个IMEI和IMSI组合，查询是否已有记录
							bool isExistIMEI=false;
							bool isExistIMEIandIMSI=false;
							int temp_hash_imei=atoi(taccdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
							for(int m=0;m<tacstat[temp_hash][im].B_IMEI_IMSI_TD[temp_hash_imei].size();m++){
								if(taccdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMEI==tacstat[temp_hash][im].B_IMEI_IMSI_TD[temp_hash_imei][m].IMEI){
									isExistIMEI=true;
									if(taccdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMSI==tacstat[temp_hash][im].B_IMEI_IMSI_TD[temp_hash_imei][m].IMSI){
										isExistIMEIandIMSI=true;
										break;
									}
								}
							}

							if(isExistIMEIandIMSI==false){
								//如果IMEI和IMSI组成的对不重复，那么新增一个
								IMEI_IMSI tempim;
								tempim.IMEI=taccdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMEI;
								tempim.IMSI=taccdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMSI;
								tacstat[temp_hash][im].B_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
							}

							if(isExistIMEI==false){
								//如果IMEI不重复
								tacstat[temp_hash][im].B_IMEI_TD++;
							}
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
//						tacstat[temp_hash][im].A_call_not_connected+=taccdrfile[fn][hn][cr].A_call_not_connected;
//						tacstat[temp_hash][im].B_call_not_connected+=taccdrfile[fn][hn][cr].B_call_not_connected;
					tacstat[temp_hash][im].B_call_attempt_GSM+=taccdrfile[fn][hn][cr].B_call_attempt_GSM;
					tacstat[temp_hash][im].A_call_attempt_GSM+=taccdrfile[fn][hn][cr].A_call_attempt_GSM;
					tacstat[temp_hash][im].A_call_attempt_TD+=taccdrfile[fn][hn][cr].A_call_attempt_TD;
					tacstat[temp_hash][im].B_call_attempt_TD+=taccdrfile[fn][hn][cr].B_call_attempt_TD;
						/*tacstat[temp_hash][im].A_causeTD+=taccdrfile[fn][hn][cr].A_causeTD;
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
						tacstat[temp_hash][im].B_causeTDTransport+=taccdrfile[fn][hn][cr].B_causeTDTransport;*/
					
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
					/*tempimei.A_cause0=taccdrfile[fn][hn][cr].A_cause0;
					tempimei.A_cause1=taccdrfile[fn][hn][cr].A_cause1;
					tempimei.A_cause20=taccdrfile[fn][hn][cr].A_cause20;
					tempimei.A_cause60=taccdrfile[fn][hn][cr].A_cause60;
					tempimei.B_cause0=taccdrfile[fn][hn][cr].B_cause0;
					tempimei.B_cause1=taccdrfile[fn][hn][cr].B_cause1;
					tempimei.B_cause20=taccdrfile[fn][hn][cr].B_cause20;
					tempimei.B_cause60=taccdrfile[fn][hn][cr].B_cause60;
					tempimei.A_causeGSM=taccdrfile[fn][hn][cr].A_causeGSM;
					tempimei.B_causeGSM=taccdrfile[fn][hn][cr].B_causeGSM;*/
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
					/*tempimei.A_causeTD=taccdrfile[fn][hn][cr].A_causeTD;
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
					tempimei.B_causeTDTransport=taccdrfile[fn][hn][cr].B_causeTDTransport;*/
					
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
				
				
					for(int j=0;j<taccdrfile[fn][hn][cr].A_IMEI_IMSI_GSM.size();j++){
						if(j==0){
							//只初始化一次
							tempimei.A_IMEI_IMSI_GSM.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
						}
						for(int k=0;k<taccdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j].size();k++){
							int temp_hash_imei=atoi(taccdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					
							IMEI_IMSI tempim;
							tempim.IMEI=taccdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI;
							tempim.IMSI=taccdrfile[fn][hn][cr].A_IMEI_IMSI_GSM[j][k].IMSI;
							tempimei.A_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
							tempimei.A_IMEI_GSM++;
						}
					}
					for(int j=0;j<taccdrfile[fn][hn][cr].A_IMEI_IMSI_TD.size();j++){
						if(j==0){
							//只初始化一次
							tempimei.A_IMEI_IMSI_TD.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
						}
						for(int k=0;k<taccdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j].size();k++){
							int temp_hash_imei=atoi(taccdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					
							IMEI_IMSI tempim;
							tempim.IMEI=taccdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMEI;
							tempim.IMSI=taccdrfile[fn][hn][cr].A_IMEI_IMSI_TD[j][k].IMSI;
							tempimei.A_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
							tempimei.A_IMEI_TD++;
						}
					}
					for(int j=0;j<taccdrfile[fn][hn][cr].B_IMEI_IMSI_GSM.size();j++){
						if(j==0){
							//只初始化一次
							tempimei.B_IMEI_IMSI_GSM.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
						}
						for(int k=0;k<taccdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j].size();k++){
							int temp_hash_imei=atoi(taccdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					
							IMEI_IMSI tempim;
							tempim.IMEI=taccdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI;
							tempim.IMSI=taccdrfile[fn][hn][cr].B_IMEI_IMSI_GSM[j][k].IMSI;
							tempimei.B_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
							tempimei.B_IMEI_GSM++;
						}
					}
					for(int j=0;j<taccdrfile[fn][hn][cr].B_IMEI_IMSI_TD.size();j++){
						if(j==0){
							//只初始化一次
							tempimei.B_IMEI_IMSI_TD.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
						}
						for(int k=0;k<taccdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j].size();k++){
							int temp_hash_imei=atoi(taccdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					
							IMEI_IMSI tempim;
							tempim.IMEI=taccdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMEI;
							tempim.IMSI=taccdrfile[fn][hn][cr].B_IMEI_IMSI_TD[j][k].IMSI;
							tempimei.B_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
							tempimei.B_IMEI_TD++;
						}
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
	
	cout<<"Start Combining "<<tacstatfilelist.size()<<"TAC STAT FILE"<<endl;
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
					
					for(int j=0;j<temptacstat[hn][cr].A_IMEI_IMSI_GSM.size();j++){
						for(int k=0;k<temptacstat[hn][cr].A_IMEI_IMSI_GSM[j].size();k++){
							//对每一个IMEI和IMSI组合，查询是否已有记录
							bool isExistIMEI=false;
							bool isExistIMEIandIMSI=false;
							int temp_hash_imei=atoi(temptacstat[hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
							for(int m=0;m<tacstat[temp_hash][im].A_IMEI_IMSI_GSM[temp_hash_imei].size();m++){
								if(temptacstat[hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI==tacstat[temp_hash][im].A_IMEI_IMSI_GSM[temp_hash_imei][m].IMEI){
									isExistIMEI=true;
									if(temptacstat[hn][cr].A_IMEI_IMSI_GSM[j][k].IMSI==tacstat[temp_hash][im].A_IMEI_IMSI_GSM[temp_hash_imei][m].IMSI){
										isExistIMEIandIMSI=true;
										break;
									}
								}
							}

							if(isExistIMEIandIMSI==false){
								//如果IMEI和IMSI组成的对不重复，那么新增一个
								IMEI_IMSI tempim;
								tempim.IMEI=temptacstat[hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI;
								tempim.IMSI=temptacstat[hn][cr].A_IMEI_IMSI_GSM[j][k].IMSI;
								tacstat[temp_hash][im].A_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
							}

							if(isExistIMEI==false){
								//如果IMEI不重复
								tacstat[temp_hash][im].A_IMEI_GSM++;
							}
						}
					}
					for(int j=0;j<temptacstat[hn][cr].A_IMEI_IMSI_TD.size();j++){
						for(int k=0;k<temptacstat[hn][cr].A_IMEI_IMSI_TD[j].size();k++){
							//对每一个IMEI和IMSI组合，查询是否已有记录
							bool isExistIMEI=false;
							bool isExistIMEIandIMSI=false;
							int temp_hash_imei=atoi(temptacstat[hn][cr].A_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
							for(int m=0;m<tacstat[temp_hash][im].A_IMEI_IMSI_TD[temp_hash_imei].size();m++){
								if(temptacstat[hn][cr].A_IMEI_IMSI_TD[j][k].IMEI==tacstat[temp_hash][im].A_IMEI_IMSI_TD[temp_hash_imei][m].IMEI){
									isExistIMEI=true;
									if(temptacstat[hn][cr].A_IMEI_IMSI_TD[j][k].IMSI==tacstat[temp_hash][im].A_IMEI_IMSI_TD[temp_hash_imei][m].IMSI){
										isExistIMEIandIMSI=true;
										break;
									}
								}
							}

							if(isExistIMEIandIMSI==false){
								//如果IMEI和IMSI组成的对不重复，那么新增一个
								IMEI_IMSI tempim;
								tempim.IMEI=temptacstat[hn][cr].A_IMEI_IMSI_TD[j][k].IMEI;
								tempim.IMSI=temptacstat[hn][cr].A_IMEI_IMSI_TD[j][k].IMSI;
								tacstat[temp_hash][im].A_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
							}

							if(isExistIMEI==false){
								//如果IMEI不重复
								tacstat[temp_hash][im].A_IMEI_TD++;
							}
						}
					}
					for(int j=0;j<temptacstat[hn][cr].B_IMEI_IMSI_GSM.size();j++){
						for(int k=0;k<temptacstat[hn][cr].B_IMEI_IMSI_GSM[j].size();k++){
							//对每一个IMEI和IMSI组合，查询是否已有记录
							bool isExistIMEI=false;
							bool isExistIMEIandIMSI=false;
							int temp_hash_imei=atoi(temptacstat[hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
							for(int m=0;m<tacstat[temp_hash][im].B_IMEI_IMSI_GSM[temp_hash_imei].size();m++){
								if(temptacstat[hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI==tacstat[temp_hash][im].B_IMEI_IMSI_GSM[temp_hash_imei][m].IMEI){
									isExistIMEI=true;
									if(temptacstat[hn][cr].B_IMEI_IMSI_GSM[j][k].IMSI==tacstat[temp_hash][im].B_IMEI_IMSI_GSM[temp_hash_imei][m].IMSI){
										isExistIMEIandIMSI=true;
										break;
									}
								}
							}

							if(isExistIMEIandIMSI==false){
								//如果IMEI和IMSI组成的对不重复，那么新增一个
								IMEI_IMSI tempim;
								tempim.IMEI=temptacstat[hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI;
								tempim.IMSI=temptacstat[hn][cr].B_IMEI_IMSI_GSM[j][k].IMSI;
								tacstat[temp_hash][im].B_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
							}

							if(isExistIMEI==false){
								//如果IMEI不重复
								tacstat[temp_hash][im].B_IMEI_GSM++;
							}
						}
					}
					for(int j=0;j<temptacstat[hn][cr].B_IMEI_IMSI_TD.size();j++){
						for(int k=0;k<temptacstat[hn][cr].B_IMEI_IMSI_TD[j].size();k++){
							//对每一个IMEI和IMSI组合，查询是否已有记录
							bool isExistIMEI=false;
							bool isExistIMEIandIMSI=false;
							int temp_hash_imei=atoi(temptacstat[hn][cr].B_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
							for(int m=0;m<tacstat[temp_hash][im].B_IMEI_IMSI_TD[temp_hash_imei].size();m++){
								if(temptacstat[hn][cr].B_IMEI_IMSI_TD[j][k].IMEI==tacstat[temp_hash][im].B_IMEI_IMSI_TD[temp_hash_imei][m].IMEI){
									isExistIMEI=true;
									if(temptacstat[hn][cr].B_IMEI_IMSI_TD[j][k].IMSI==tacstat[temp_hash][im].B_IMEI_IMSI_TD[temp_hash_imei][m].IMSI){
										isExistIMEIandIMSI=true;
										break;
									}
								}
							}

							if(isExistIMEIandIMSI==false){
								//如果IMEI和IMSI组成的对不重复，那么新增一个
								IMEI_IMSI tempim;
								tempim.IMEI=temptacstat[hn][cr].B_IMEI_IMSI_TD[j][k].IMEI;
								tempim.IMSI=temptacstat[hn][cr].B_IMEI_IMSI_TD[j][k].IMSI;
								tacstat[temp_hash][im].B_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
							}

							if(isExistIMEI==false){
								//如果IMEI不重复
								tacstat[temp_hash][im].B_IMEI_TD++;
							}
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
						//tacstat_cell[temp_hash][im].A_causeTD+=tacstat[hn][cr].A_causeTD;
						//tacstat_cell[temp_hash][im].A_causeTD46+=tacstat[hn][cr].A_causeTD46;
						//tacstat_cell[temp_hash][im].A_causeTD176+=tacstat[hn][cr].A_causeTD176;
						//tacstat_cell[temp_hash][im].A_causeTD192+=tacstat[hn][cr].A_causeTD192;
						//tacstat_cell[temp_hash][im].A_causeTD209+=tacstat[hn][cr].A_causeTD209;
						//tacstat_cell[temp_hash][im].A_causeTD239+=tacstat[hn][cr].A_causeTD239;
						//tacstat_cell[temp_hash][im].A_causeTDMisc+=tacstat[hn][cr].A_causeTDMisc;
						//tacstat_cell[temp_hash][im].A_causeTDNAS+=tacstat[hn][cr].A_causeTDNAS;
						//tacstat_cell[temp_hash][im].A_causeTDNonStandard+=tacstat[hn][cr].A_causeTDNonStandard;
						//tacstat_cell[temp_hash][im].A_causeTDProtocol+=tacstat[hn][cr].A_causeTDProtocol;
						//tacstat_cell[temp_hash][im].A_causeTDRadioNetwork+=tacstat[hn][cr].A_causeTDRadioNetwork;
						//tacstat_cell[temp_hash][im].A_causeTDTransport+=tacstat[hn][cr].A_causeTDTransport;
						//tacstat_cell[temp_hash][im].B_causeTD+=tacstat[hn][cr].B_causeTD;
						//tacstat_cell[temp_hash][im].B_causeTD46+=tacstat[hn][cr].B_causeTD46;
						//tacstat_cell[temp_hash][im].B_causeTD176+=tacstat[hn][cr].B_causeTD176;
						//tacstat_cell[temp_hash][im].B_causeTD192+=tacstat[hn][cr].B_causeTD192;
						//tacstat_cell[temp_hash][im].B_causeTD209+=tacstat[hn][cr].B_causeTD209;
						//tacstat_cell[temp_hash][im].B_causeTD239+=tacstat[hn][cr].B_causeTD239;
						//tacstat_cell[temp_hash][im].B_causeTDMisc+=tacstat[hn][cr].B_causeTDMisc;
						//tacstat_cell[temp_hash][im].B_causeTDNAS+=tacstat[hn][cr].B_causeTDNAS;
						//tacstat_cell[temp_hash][im].B_causeTDNonStandard+=tacstat[hn][cr].B_causeTDNonStandard;
						//tacstat_cell[temp_hash][im].B_causeTDProtocol+=tacstat[hn][cr].B_causeTDProtocol;
						//tacstat_cell[temp_hash][im].B_causeTDRadioNetwork+=tacstat[hn][cr].B_causeTDRadioNetwork;
						//tacstat_cell[temp_hash][im].B_causeTDTransport+=tacstat[hn][cr].B_causeTDTransport;
						////tacstat_cell[temp_hash][im].A_call_not_connected+=tacstat[hn][cr].A_call_not_connected;
						////tacstat_cell[temp_hash][im].B_call_not_connected+=tacstat[hn][cr].B_call_not_connected;
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
					/*tempimei.A_cause0=tacstat[hn][cr].A_cause0;
					tempimei.A_cause1=tacstat[hn][cr].A_cause1;
					tempimei.A_cause20=tacstat[hn][cr].A_cause20;
					tempimei.A_cause60=tacstat[hn][cr].A_cause60;
					tempimei.B_cause0=tacstat[hn][cr].B_cause0;
					tempimei.B_cause1=tacstat[hn][cr].B_cause1;
					tempimei.B_cause20=tacstat[hn][cr].B_cause20;
					tempimei.B_cause60=tacstat[hn][cr].B_cause60;
					tempimei.A_causeGSM=tacstat[hn][cr].A_causeGSM;
					tempimei.B_causeGSM=tacstat[hn][cr].B_causeGSM;*/
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
					/*tempimei.A_causeTD=tacstat[hn][cr].A_causeTD;
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
					tempimei.B_causeTDTransport=tacstat[hn][cr].B_causeTDTransport;*/
					//tempimei.A_call_not_connected=tacstat[hn][cr].A_call_not_connected;
					//tempimei.B_call_not_connected=tacstat[hn][cr].B_call_not_connected;
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
				
				
					for(int j=0;j<temptacstat[hn][cr].A_IMEI_IMSI_GSM.size();j++){
						if(j==0){
							//只初始化一次
							tempimei.A_IMEI_IMSI_GSM.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
						}
						for(int k=0;k<temptacstat[hn][cr].A_IMEI_IMSI_GSM[j].size();k++){
							int temp_hash_imei=atoi(temptacstat[hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					
							IMEI_IMSI tempim;
							tempim.IMEI=temptacstat[hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI;
							tempim.IMSI=temptacstat[hn][cr].A_IMEI_IMSI_GSM[j][k].IMSI;
							tempimei.A_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
							tempimei.A_IMEI_GSM++;
						}
					}
					for(int j=0;j<temptacstat[hn][cr].A_IMEI_IMSI_TD.size();j++){
						if(j==0){
							//只初始化一次
							tempimei.A_IMEI_IMSI_TD.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
						}
						for(int k=0;k<temptacstat[hn][cr].A_IMEI_IMSI_TD[j].size();k++){
							int temp_hash_imei=atoi(temptacstat[hn][cr].A_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					
							IMEI_IMSI tempim;
							tempim.IMEI=temptacstat[hn][cr].A_IMEI_IMSI_TD[j][k].IMEI;
							tempim.IMSI=temptacstat[hn][cr].A_IMEI_IMSI_TD[j][k].IMSI;
							tempimei.A_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
							tempimei.A_IMEI_TD++;
						}
					}
					for(int j=0;j<temptacstat[hn][cr].B_IMEI_IMSI_GSM.size();j++){
						if(j==0){
							//只初始化一次
							tempimei.B_IMEI_IMSI_GSM.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
						}
						for(int k=0;k<temptacstat[hn][cr].B_IMEI_IMSI_GSM[j].size();k++){
							int temp_hash_imei=atoi(temptacstat[hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					
							IMEI_IMSI tempim;
							tempim.IMEI=temptacstat[hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI;
							tempim.IMSI=temptacstat[hn][cr].B_IMEI_IMSI_GSM[j][k].IMSI;
							tempimei.B_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
							tempimei.B_IMEI_GSM++;
						}
					}
					for(int j=0;j<temptacstat[hn][cr].B_IMEI_IMSI_TD.size();j++){
						if(j==0){
							//只初始化一次
							tempimei.B_IMEI_IMSI_TD.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
						}
						for(int k=0;k<temptacstat[hn][cr].B_IMEI_IMSI_TD[j].size();k++){
							int temp_hash_imei=atoi(temptacstat[hn][cr].B_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					
							IMEI_IMSI tempim;
							tempim.IMEI=temptacstat[hn][cr].B_IMEI_IMSI_TD[j][k].IMEI;
							tempim.IMSI=temptacstat[hn][cr].B_IMEI_IMSI_TD[j][k].IMSI;
							tempimei.B_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
							tempimei.B_IMEI_TD++;
						}
					}
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
//读取tacstatfile
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
			tempcdrstat.cellid=0;
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
			tempcdrstat.A_IMEI_IMSI_GSM.clear();
			tempcdrstat.A_IMEI_IMSI_TD.clear();
			tempcdrstat.B_IMEI_IMSI_GSM.clear();
			tempcdrstat.B_IMEI_IMSI_TD.clear();
			tempcdrstat.A_IMEI_GSM=0;
			tempcdrstat.A_IMEI_TD=0;
			tempcdrstat.B_IMEI_GSM=0;
			tempcdrstat.B_IMEI_TD=0;

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
						/*else if(item=="品牌"&&readitem[pos]!="empty"){
							tempcdrstat.brand=trim(readitem[pos]);
						}
						else if(item=="型号"&&readitem[pos]!="empty"){
							tempcdrstat.name=trim(readitem[pos]);
						}
						else if(item=="类别"&&readitem[pos]!="empty"){
							tempcdrstat.type=trim(readitem[pos]);
						}*/
						else if(item=="CellID"&&readitem[pos]!="empty"){
							tempcdrstat.cellid=atoi(trim(readitem[pos]).c_str());
						}
						/*else if(item=="小区类别"&&readitem[pos]!="empty"){
							tempcdrstat.celltype=trim(readitem[pos]);
						}*/
						else if(item=="网络类别"&&readitem[pos]!="empty"){
							tempcdrstat.network=trim(readitem[pos]).c_str();
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
						else if(item=="A_IMEI_GSM"&&readitem[pos]!="empty"){
							tempcdrstat.A_IMEI_GSM=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="A_IMEI_TD"&&readitem[pos]!="empty"){
							tempcdrstat.A_IMEI_TD=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="B_IMEI_GSM"&&readitem[pos]!="empty"){
							tempcdrstat.B_IMEI_GSM=atoi(trim(readitem[pos]).c_str());
						}
						else if(item=="B_IMEI_TD"&&readitem[pos]!="empty"){
							tempcdrstat.B_IMEI_TD=atoi(trim(readitem[pos]).c_str());
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
						else if(item=="A_IMEI_IMSI_GSM"&&readitem[pos]!="empty"){
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

							tempcdrstat.A_IMEI_IMSI_GSM.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
							for(int k=0;k<colonlist.size();k=k+2){
								IMEI_IMSI tempimei;
								tempimei.IMEI=trim(colonlist[k]);
								tempimei.IMSI=trim(colonlist[k+1]);
								int temp_hash_imei=atoi(tempimei.IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
								tempcdrstat.A_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempimei);
							}
						}
						else if(item=="A_IMEI_IMSI_TD"&&readitem[pos]!="empty"){
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
							tempcdrstat.A_IMEI_IMSI_TD.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
							for(int k=0;k<colonlist.size();k=k+2){
								IMEI_IMSI tempimei;
								tempimei.IMEI=trim(colonlist[k]);
								tempimei.IMSI=trim(colonlist[k+1]);
								int temp_hash_imei=atoi(tempimei.IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
								tempcdrstat.A_IMEI_IMSI_TD[temp_hash_imei].push_back(tempimei);
							}
						}
						else if(item=="B_IMEI_IMSI_GSM"&&readitem[pos]!="empty"){
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
							tempcdrstat.B_IMEI_IMSI_GSM.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
							for(int k=0;k<colonlist.size();k=k+2){
								IMEI_IMSI tempimei;
								tempimei.IMEI=trim(colonlist[k]);
								tempimei.IMSI=trim(colonlist[k+1]);
								int temp_hash_imei=atoi(tempimei.IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
								tempcdrstat.B_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempimei);
							}
						}
						else if(item=="B_IMEI_IMSI_TD"&&readitem[pos]!="empty"){
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
							tempcdrstat.B_IMEI_IMSI_TD.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
							for(int k=0;k<colonlist.size();k=k+2){
								IMEI_IMSI tempimei;
								tempimei.IMEI=trim(colonlist[k]);
								tempimei.IMSI=trim(colonlist[k+1]);
								int temp_hash_imei=atoi(tempimei.IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
								tempcdrstat.B_IMEI_IMSI_TD[temp_hash_imei].push_back(tempimei);
							}
						}
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
//输出tacstat
bool WriteTACFile(std::string temp_result_path_name){
	ofstream fo(temp_result_path_name.c_str(),'w');
	if(fo.is_open()==true){
		fo<<"TAC"<<","<<"CellID"<<","<<"网络类别"<<","\
			<<"timeSection"<<","\
			/*<<"A_count0"<<","<<"A_count1"<<","\
			<<"A_count20"<<","<<"A_count60"<<","\
			<<"A_countGSM"<<","<<"A_countTD"<<","\
			<<"A_causeTD46"<<","<<"A_causeTD176"<<","<<"A_causeTD192"<<","<<"A_causeTD209"<<","<<"A_causeTD239"<<","\
			<<"A_causeTDMisc"<<","<<"A_causeTDNAS"<<","\
			<<"A_causeTDNonStandard"<<","<<"A_causeTDProtocol"<<","\
			<<"A_causeTDRadioNetwork"<<","<<"A_causeTDTransport"<<","\
			*/<<"A_shortcall_1"<<","<<"A_shortcall_2"<<","<<"A_shortcall_3"<<","\
			<<"A_call_attempt"<<","<<"A_call_attempt_GSM"<<","<<"A_call_attempt_TD"<<","\
			/*<<"B_count0"<<","<<"B_count1"<<","\
			<<"B_count20"<<","<<"B_count60"<<","\
			<<"B_countGSM"<<","<<"B_countTD"<<","\
			<<"B_causeTD46"<<","<<"B_causeTD176"<<","<<"B_causeTD192"<<","<<"B_causeTD209"<<","<<"B_causeTD239"<<","\
			<<"B_causeTDMisc"<<","<<"B_causeTDNAS"<<","\
			<<"B_causeTDNonStandard"<<","<<"B_causeTDProtocol"<<","\
			<<"B_causeTDRadioNetwork"<<","<<"B_causeTDTransport"<<","\
			*/<<"B_shortcall_1"<<","<<"B_shortcall_2"<<","<<"B_shortcall_3"<<","\
			<<"B_call_attempt"<<","<<"B_call_attempt_GSM"<<","<<"B_call_attempt_TD"<<","\
			<<"A_IMEI_GSM"<<","<<"A_IMEI_TD"<<","<<"B_IMEI_GSM"<<","<<"B_IMEI_TD"<<","\
			<<"A_BSSMAP_Cause"<<","<<"A_RANAP_Cause"<<","<<"B_BSSMAP_Cause"<<","<<"B_RANAP_Cause"<<","\
			<<"A_DX_Cause_GSM"<<","<<"A_DX_Cause_TD"<<","<<"B_DX_Cause_GSM"<<","<<"B_DX_Cause_TD"<<","\
			<<"A_IMEI_IMSI_GSM"<<","<<"A_IMEI_IMSI_TD"<<","<<"B_IMEI_IMSI_GSM"<<","<<"B_IMEI_IMSI_TD"<<","\
			<<endl;
		for(int hn=0;hn<tacstat.size();hn++){
			for(int i=0;i<tacstat[hn].size();i++){
				
				fo<<tacstat[hn][i].TAC<<","<<tacstat[hn][i].cellid<<","<<tacstat[hn][i].network<<","\
					<<tacstat[hn][i].timeSection<<","\
					<<tacstat[hn][i].A_shortcall_1<<","<<tacstat[hn][i].A_shortcall_2<<","<<tacstat[hn][i].A_shortcall_3<<","\
					<<tacstat[hn][i].A_call_attempt<<","<<tacstat[hn][i].A_call_attempt_GSM<<","<<tacstat[hn][i].A_call_attempt_TD<<","\
					<<tacstat[hn][i].B_shortcall_1<<","<<tacstat[hn][i].B_shortcall_2<<","<<tacstat[hn][i].B_shortcall_3<<","\
					<<tacstat[hn][i].B_call_attempt<<","<<tacstat[hn][i].B_call_attempt_GSM<<","<<tacstat[hn][i].B_call_attempt_TD<<","\
					<<tacstat[hn][i].A_IMEI_GSM<<","<<tacstat[hn][i].A_IMEI_TD<<","<<tacstat[hn][i].B_IMEI_GSM<<","<<tacstat[hn][i].B_IMEI_TD<<",";

				for(int k=0;k<tacstat[hn][i].A_BSSMAP_Cause.size();k++){
					fo<<tacstat[hn][i].A_BSSMAP_Cause[k].cause_id<<";"<<tacstat[hn][i].A_BSSMAP_Cause[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat[hn][i].A_RANAP_Cause.size();k++){
					fo<<tacstat[hn][i].A_RANAP_Cause[k].cause_id<<";"<<tacstat[hn][i].A_RANAP_Cause[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat[hn][i].B_BSSMAP_Cause.size();k++){
					fo<<tacstat[hn][i].B_BSSMAP_Cause[k].cause_id<<";"<<tacstat[hn][i].B_BSSMAP_Cause[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat[hn][i].B_RANAP_Cause.size();k++){
					fo<<tacstat[hn][i].B_RANAP_Cause[k].cause_id<<";"<<tacstat[hn][i].B_RANAP_Cause[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat[hn][i].A_DX_Cause_GSM.size();k++){
					fo<<tacstat[hn][i].A_DX_Cause_GSM[k].cause_id<<";"<<tacstat[hn][i].A_DX_Cause_GSM[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat[hn][i].A_DX_Cause_TD.size();k++){
					fo<<tacstat[hn][i].A_DX_Cause_TD[k].cause_id<<";"<<tacstat[hn][i].A_DX_Cause_TD[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat[hn][i].B_DX_Cause_GSM.size();k++){
					fo<<tacstat[hn][i].B_DX_Cause_GSM[k].cause_id<<";"<<tacstat[hn][i].B_DX_Cause_GSM[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat[hn][i].B_DX_Cause_TD.size();k++){
					fo<<tacstat[hn][i].B_DX_Cause_TD[k].cause_id<<";"<<tacstat[hn][i].B_DX_Cause_TD[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat[hn][i].A_IMEI_IMSI_GSM.size();k++){
					for(int l=0;l<tacstat[hn][i].A_IMEI_IMSI_GSM[k].size();l++){
						fo<<tacstat[hn][i].A_IMEI_IMSI_GSM[k][l].IMEI<<";"<<tacstat[hn][i].A_IMEI_IMSI_GSM[k][l].IMSI<<";";
					}
				}
				fo<<",";
				for(int k=0;k<tacstat[hn][i].A_IMEI_IMSI_TD.size();k++){
					for(int l=0;l<tacstat[hn][i].A_IMEI_IMSI_TD[k].size();l++){
						fo<<tacstat[hn][i].A_IMEI_IMSI_TD[k][l].IMEI<<";"<<tacstat[hn][i].A_IMEI_IMSI_TD[k][l].IMSI<<";";
					}
				}
				fo<<",";
				for(int k=0;k<tacstat[hn][i].B_IMEI_IMSI_GSM.size();k++){
					for(int l=0;l<tacstat[hn][i].B_IMEI_IMSI_GSM[k].size();l++){
						fo<<tacstat[hn][i].B_IMEI_IMSI_GSM[k][l].IMEI<<";"<<tacstat[hn][i].B_IMEI_IMSI_GSM[k][l].IMSI<<";";
					}
				}
				fo<<",";
				for(int k=0;k<tacstat[hn][i].B_IMEI_IMSI_TD.size();k++){
					for(int l=0;l<tacstat[hn][i].B_IMEI_IMSI_TD[k].size();l++){
						fo<<tacstat[hn][i].B_IMEI_IMSI_TD[k][l].IMEI<<";"<<tacstat[hn][i].B_IMEI_IMSI_TD[k][l].IMSI<<";";
					}
				}
				fo<<endl;
			}
		}
	}
	fo.close();
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
					tacstat[i][j].brand=taclist[k].brand.c_str();
					tacstat[i][j].name=taclist[k].name.c_str();
					tacstat[i][j].type=taclist[k].type.c_str();
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
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].A_BSSMAP_Cause[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].A_BSSMAP_Cause[j].cause_num;
						tacstat_timesection[temp_hash][im].A_BSSMAP_Cause.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat[hn][cr].B_BSSMAP_Cause.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesection[temp_hash][im].B_BSSMAP_Cause.size();k++){
						if(tacstat_timesection[temp_hash][im].B_BSSMAP_Cause[k].cause_id==tacstat[hn][cr].B_BSSMAP_Cause[j].cause_id){
							isExistCause=true;
							tacstat_timesection[temp_hash][im].B_BSSMAP_Cause[k].cause_num+=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_num;
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_num;
						tacstat_timesection[temp_hash][im].B_BSSMAP_Cause.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat[hn][cr].A_RANAP_Cause.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesection[temp_hash][im].A_RANAP_Cause.size();k++){
						if(tacstat_timesection[temp_hash][im].A_RANAP_Cause[k].cause_id==tacstat[hn][cr].A_RANAP_Cause[j].cause_id){
							isExistCause=true;
							tacstat_timesection[temp_hash][im].A_RANAP_Cause[k].cause_num+=tacstat[hn][cr].A_RANAP_Cause[j].cause_num;
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].A_RANAP_Cause[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].A_RANAP_Cause[j].cause_num;
						tacstat_timesection[temp_hash][im].A_RANAP_Cause.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat[hn][cr].B_RANAP_Cause.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesection[temp_hash][im].B_RANAP_Cause.size();k++){
						if(tacstat_timesection[temp_hash][im].B_RANAP_Cause[k].cause_id==tacstat[hn][cr].B_RANAP_Cause[j].cause_id){
							isExistCause=true;
							tacstat_timesection[temp_hash][im].B_RANAP_Cause[k].cause_num+=tacstat[hn][cr].B_RANAP_Cause[j].cause_num;
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].B_RANAP_Cause[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].B_RANAP_Cause[j].cause_num;
						tacstat_timesection[temp_hash][im].B_RANAP_Cause.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat[hn][cr].A_DX_Cause_GSM.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesection[temp_hash][im].A_DX_Cause_GSM.size();k++){
						if(tacstat_timesection[temp_hash][im].A_DX_Cause_GSM[k].cause_id==tacstat[hn][cr].A_DX_Cause_GSM[j].cause_id){
							isExistCause=true;
							tacstat_timesection[temp_hash][im].A_DX_Cause_GSM[k].cause_num+=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_num;
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_num;
						tacstat_timesection[temp_hash][im].A_DX_Cause_GSM.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat[hn][cr].A_DX_Cause_TD.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesection[temp_hash][im].A_DX_Cause_TD.size();k++){
						if(tacstat_timesection[temp_hash][im].A_DX_Cause_TD[k].cause_id==tacstat[hn][cr].A_DX_Cause_TD[j].cause_id){
							isExistCause=true;
							tacstat_timesection[temp_hash][im].A_DX_Cause_TD[k].cause_num+=tacstat[hn][cr].A_DX_Cause_TD[j].cause_num;
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].A_DX_Cause_TD[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].A_DX_Cause_TD[j].cause_num;
						tacstat_timesection[temp_hash][im].A_DX_Cause_TD.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat[hn][cr].B_DX_Cause_GSM.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesection[temp_hash][im].B_DX_Cause_GSM.size();k++){
						if(tacstat_timesection[temp_hash][im].B_DX_Cause_GSM[k].cause_id==tacstat[hn][cr].B_DX_Cause_GSM[j].cause_id){
							isExistCause=true;
							tacstat_timesection[temp_hash][im].B_DX_Cause_GSM[k].cause_num+=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_num;
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_num;
						tacstat_timesection[temp_hash][im].B_DX_Cause_GSM.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat[hn][cr].B_DX_Cause_TD.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesection[temp_hash][im].B_DX_Cause_TD.size();k++){
						if(tacstat_timesection[temp_hash][im].B_DX_Cause_TD[k].cause_id==tacstat[hn][cr].B_DX_Cause_TD[j].cause_id){
							isExistCause=true;
							tacstat_timesection[temp_hash][im].B_DX_Cause_TD[k].cause_num+=tacstat[hn][cr].B_DX_Cause_TD[j].cause_num;
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat[hn][cr].B_DX_Cause_TD[j].cause_id;
						tempcause.cause_num=tacstat[hn][cr].B_DX_Cause_TD[j].cause_num;
						tacstat_timesection[temp_hash][im].B_DX_Cause_TD.push_back(tempcause);
					}
				}
					
				for(int j=0;j<tacstat[hn][cr].A_IMEI_IMSI_GSM.size();j++){
					for(int k=0;k<tacstat[hn][cr].A_IMEI_IMSI_GSM[j].size();k++){
						//对每一个IMEI和IMSI组合，查询是否已有记录
						bool isExistIMEI=false;
						bool isExistIMEIandIMSI=false;
						int temp_hash_imei=atoi(tacstat[hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
						for(int m=0;m<tacstat_timesection[temp_hash][im].A_IMEI_IMSI_GSM[temp_hash_imei].size();m++){
							if(tacstat[hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI==tacstat_timesection[temp_hash][im].A_IMEI_IMSI_GSM[temp_hash_imei][m].IMEI){
								isExistIMEI=true;
								if(tacstat[hn][cr].A_IMEI_IMSI_GSM[j][k].IMSI==tacstat_timesection[temp_hash][im].A_IMEI_IMSI_GSM[temp_hash_imei][m].IMSI){
									isExistIMEIandIMSI=true;
									break;
								}
							}
						}

						if(isExistIMEIandIMSI==false){
							//如果IMEI和IMSI组成的对不重复，那么新增一个
							IMEI_IMSI tempim;
							tempim.IMEI=tacstat[hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI;
							tempim.IMSI=tacstat[hn][cr].A_IMEI_IMSI_GSM[j][k].IMSI;
							tacstat_timesection[temp_hash][im].A_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
						}

						if(isExistIMEI==false){
							//如果IMEI不重复
							tacstat_timesection[temp_hash][im].A_IMEI_GSM++;
						}
					}
				}
				for(int j=0;j<tacstat[hn][cr].A_IMEI_IMSI_TD.size();j++){
					for(int k=0;k<tacstat[hn][cr].A_IMEI_IMSI_TD[j].size();k++){
						//对每一个IMEI和IMSI组合，查询是否已有记录
						bool isExistIMEI=false;
						bool isExistIMEIandIMSI=false;
						int temp_hash_imei=atoi(tacstat[hn][cr].A_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
						for(int m=0;m<tacstat_timesection[temp_hash][im].A_IMEI_IMSI_TD[temp_hash_imei].size();m++){
							if(tacstat[hn][cr].A_IMEI_IMSI_TD[j][k].IMEI==tacstat_timesection[temp_hash][im].A_IMEI_IMSI_TD[temp_hash_imei][m].IMEI){
								isExistIMEI=true;
								if(tacstat[hn][cr].A_IMEI_IMSI_TD[j][k].IMSI==tacstat_timesection[temp_hash][im].A_IMEI_IMSI_TD[temp_hash_imei][m].IMSI){
									isExistIMEIandIMSI=true;
									break;
								}
							}
						}

						if(isExistIMEIandIMSI==false){
							//如果IMEI和IMSI组成的对不重复，那么新增一个
							IMEI_IMSI tempim;
							tempim.IMEI=tacstat[hn][cr].A_IMEI_IMSI_TD[j][k].IMEI;
							tempim.IMSI=tacstat[hn][cr].A_IMEI_IMSI_TD[j][k].IMSI;
							tacstat_timesection[temp_hash][im].A_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
						}

						if(isExistIMEI==false){
							//如果IMEI不重复
							tacstat_timesection[temp_hash][im].A_IMEI_TD++;
						}
					}
				}
				for(int j=0;j<tacstat[hn][cr].B_IMEI_IMSI_GSM.size();j++){
					for(int k=0;k<tacstat[hn][cr].B_IMEI_IMSI_GSM[j].size();k++){
						//对每一个IMEI和IMSI组合，查询是否已有记录
						bool isExistIMEI=false;
						bool isExistIMEIandIMSI=false;
						int temp_hash_imei=atoi(tacstat[hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
						for(int m=0;m<tacstat_timesection[temp_hash][im].B_IMEI_IMSI_GSM[temp_hash_imei].size();m++){
							if(tacstat[hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI==tacstat_timesection[temp_hash][im].B_IMEI_IMSI_GSM[temp_hash_imei][m].IMEI){
								isExistIMEI=true;
								if(tacstat[hn][cr].B_IMEI_IMSI_GSM[j][k].IMSI==tacstat_timesection[temp_hash][im].B_IMEI_IMSI_GSM[temp_hash_imei][m].IMSI){
									isExistIMEIandIMSI=true;
									break;
								}
							}
						}

						if(isExistIMEIandIMSI==false){
							//如果IMEI和IMSI组成的对不重复，那么新增一个
							IMEI_IMSI tempim;
							tempim.IMEI=tacstat[hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI;
							tempim.IMSI=tacstat[hn][cr].B_IMEI_IMSI_GSM[j][k].IMSI;
							tacstat_timesection[temp_hash][im].B_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
						}

						if(isExistIMEI==false){
							//如果IMEI不重复
							tacstat_timesection[temp_hash][im].B_IMEI_GSM++;
						}
					}
				}
				for(int j=0;j<tacstat[hn][cr].B_IMEI_IMSI_TD.size();j++){
					for(int k=0;k<tacstat[hn][cr].B_IMEI_IMSI_TD[j].size();k++){
						//对每一个IMEI和IMSI组合，查询是否已有记录
						bool isExistIMEI=false;
						bool isExistIMEIandIMSI=false;
						int temp_hash_imei=atoi(tacstat[hn][cr].B_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
						for(int m=0;m<tacstat_timesection[temp_hash][im].B_IMEI_IMSI_TD[temp_hash_imei].size();m++){
							if(tacstat[hn][cr].B_IMEI_IMSI_TD[j][k].IMEI==tacstat_timesection[temp_hash][im].B_IMEI_IMSI_TD[temp_hash_imei][m].IMEI){
								isExistIMEI=true;
								if(tacstat[hn][cr].B_IMEI_IMSI_TD[j][k].IMSI==tacstat_timesection[temp_hash][im].B_IMEI_IMSI_TD[temp_hash_imei][m].IMSI){
									isExistIMEIandIMSI=true;
									break;
								}
							}
						}

						if(isExistIMEIandIMSI==false){
							//如果IMEI和IMSI组成的对不重复，那么新增一个
							IMEI_IMSI tempim;
							tempim.IMEI=tacstat[hn][cr].B_IMEI_IMSI_TD[j][k].IMEI;
							tempim.IMSI=tacstat[hn][cr].B_IMEI_IMSI_TD[j][k].IMSI;
							tacstat_timesection[temp_hash][im].B_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
						}

						if(isExistIMEI==false){
							//如果IMEI不重复
							tacstat_timesection[temp_hash][im].B_IMEI_TD++;
						}
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
					//tacstat_cell[temp_hash][im].A_causeTD+=tacstat[hn][cr].A_causeTD;
					//tacstat_cell[temp_hash][im].A_causeTD46+=tacstat[hn][cr].A_causeTD46;
					//tacstat_cell[temp_hash][im].A_causeTD176+=tacstat[hn][cr].A_causeTD176;
					//tacstat_cell[temp_hash][im].A_causeTD192+=tacstat[hn][cr].A_causeTD192;
					//tacstat_cell[temp_hash][im].A_causeTD209+=tacstat[hn][cr].A_causeTD209;
					//tacstat_cell[temp_hash][im].A_causeTD239+=tacstat[hn][cr].A_causeTD239;
					//tacstat_cell[temp_hash][im].A_causeTDMisc+=tacstat[hn][cr].A_causeTDMisc;
					//tacstat_cell[temp_hash][im].A_causeTDNAS+=tacstat[hn][cr].A_causeTDNAS;
					//tacstat_cell[temp_hash][im].A_causeTDNonStandard+=tacstat[hn][cr].A_causeTDNonStandard;
					//tacstat_cell[temp_hash][im].A_causeTDProtocol+=tacstat[hn][cr].A_causeTDProtocol;
					//tacstat_cell[temp_hash][im].A_causeTDRadioNetwork+=tacstat[hn][cr].A_causeTDRadioNetwork;
					//tacstat_cell[temp_hash][im].A_causeTDTransport+=tacstat[hn][cr].A_causeTDTransport;
					//tacstat_cell[temp_hash][im].B_causeTD+=tacstat[hn][cr].B_causeTD;
					//tacstat_cell[temp_hash][im].B_causeTD46+=tacstat[hn][cr].B_causeTD46;
					//tacstat_cell[temp_hash][im].B_causeTD176+=tacstat[hn][cr].B_causeTD176;
					//tacstat_cell[temp_hash][im].B_causeTD192+=tacstat[hn][cr].B_causeTD192;
					//tacstat_cell[temp_hash][im].B_causeTD209+=tacstat[hn][cr].B_causeTD209;
					//tacstat_cell[temp_hash][im].B_causeTD239+=tacstat[hn][cr].B_causeTD239;
					//tacstat_cell[temp_hash][im].B_causeTDMisc+=tacstat[hn][cr].B_causeTDMisc;
					//tacstat_cell[temp_hash][im].B_causeTDNAS+=tacstat[hn][cr].B_causeTDNAS;
					//tacstat_cell[temp_hash][im].B_causeTDNonStandard+=tacstat[hn][cr].B_causeTDNonStandard;
					//tacstat_cell[temp_hash][im].B_causeTDProtocol+=tacstat[hn][cr].B_causeTDProtocol;
					//tacstat_cell[temp_hash][im].B_causeTDRadioNetwork+=tacstat[hn][cr].B_causeTDRadioNetwork;
					//tacstat_cell[temp_hash][im].B_causeTDTransport+=tacstat[hn][cr].B_causeTDTransport;
					////tacstat_cell[temp_hash][im].A_call_not_connected+=tacstat[hn][cr].A_call_not_connected;
					////tacstat_cell[temp_hash][im].B_call_not_connected+=tacstat[hn][cr].B_call_not_connected;
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
				/*tempimei.A_cause0=tacstat[hn][cr].A_cause0;
				tempimei.A_cause1=tacstat[hn][cr].A_cause1;
				tempimei.A_cause20=tacstat[hn][cr].A_cause20;
				tempimei.A_cause60=tacstat[hn][cr].A_cause60;
				tempimei.B_cause0=tacstat[hn][cr].B_cause0;
				tempimei.B_cause1=tacstat[hn][cr].B_cause1;
				tempimei.B_cause20=tacstat[hn][cr].B_cause20;
				tempimei.B_cause60=tacstat[hn][cr].B_cause60;
				tempimei.A_causeGSM=tacstat[hn][cr].A_causeGSM;
				tempimei.B_causeGSM=tacstat[hn][cr].B_causeGSM;*/
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
				/*tempimei.A_causeTD=tacstat[hn][cr].A_causeTD;
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
				tempimei.B_causeTDTransport=tacstat[hn][cr].B_causeTDTransport;*/
				//tempimei.A_call_not_connected=tacstat[hn][cr].A_call_not_connected;
				//tempimei.B_call_not_connected=tacstat[hn][cr].B_call_not_connected;
				for(int j=0;j<tacstat[hn][cr].A_BSSMAP_Cause.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].A_BSSMAP_Cause[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].A_BSSMAP_Cause[j].cause_num;
					tempimei.A_BSSMAP_Cause.push_back(tempcause);
				}
				for(int j=0;j<tacstat[hn][cr].B_BSSMAP_Cause.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].B_BSSMAP_Cause[j].cause_num;
					tempimei.B_BSSMAP_Cause.push_back(tempcause);
					
				}
				for(int j=0;j<tacstat[hn][cr].A_RANAP_Cause.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].A_RANAP_Cause[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].A_RANAP_Cause[j].cause_num;
					tempimei.A_RANAP_Cause.push_back(tempcause);
				}
				for(int j=0;j<tacstat[hn][cr].B_RANAP_Cause.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].B_RANAP_Cause[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].B_RANAP_Cause[j].cause_num;
					tempimei.B_RANAP_Cause.push_back(tempcause);
				}
				for(int j=0;j<tacstat[hn][cr].A_DX_Cause_GSM.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].A_DX_Cause_GSM[j].cause_num;
					tempimei.A_DX_Cause_GSM.push_back(tempcause);
				}
				for(int j=0;j<tacstat[hn][cr].A_DX_Cause_TD.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].A_DX_Cause_TD[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].A_DX_Cause_TD[j].cause_num;
					tempimei.A_DX_Cause_TD.push_back(tempcause);
				}
				for(int j=0;j<tacstat[hn][cr].B_DX_Cause_GSM.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].B_DX_Cause_GSM[j].cause_num;
					tempimei.B_DX_Cause_GSM.push_back(tempcause);
				}
				for(int j=0;j<tacstat[hn][cr].B_DX_Cause_TD.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat[hn][cr].B_DX_Cause_TD[j].cause_id;
					tempcause.cause_num=tacstat[hn][cr].B_DX_Cause_TD[j].cause_num;
					tempimei.B_DX_Cause_TD.push_back(tempcause);
				}
				
				
				for(int j=0;j<tacstat[hn][cr].A_IMEI_IMSI_GSM.size();j++){
					if(j==0){
						//只初始化一次
						tempimei.A_IMEI_IMSI_GSM.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
					}
					for(int k=0;k<tacstat[hn][cr].A_IMEI_IMSI_GSM[j].size();k++){
						int temp_hash_imei=atoi(tacstat[hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					
						IMEI_IMSI tempim;
						tempim.IMEI=tacstat[hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI;
						tempim.IMSI=tacstat[hn][cr].A_IMEI_IMSI_GSM[j][k].IMSI;
						tempimei.A_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
						tempimei.A_IMEI_GSM++;
					}
				}
				for(int j=0;j<tacstat[hn][cr].A_IMEI_IMSI_TD.size();j++){
					if(j==0){
						//只初始化一次
						tempimei.A_IMEI_IMSI_TD.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
					}
					for(int k=0;k<tacstat[hn][cr].A_IMEI_IMSI_TD[j].size();k++){
						int temp_hash_imei=atoi(tacstat[hn][cr].A_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					
						IMEI_IMSI tempim;
						tempim.IMEI=tacstat[hn][cr].A_IMEI_IMSI_TD[j][k].IMEI;
						tempim.IMSI=tacstat[hn][cr].A_IMEI_IMSI_TD[j][k].IMSI;
						tempimei.A_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
						tempimei.A_IMEI_TD++;
					}
				}
				for(int j=0;j<tacstat[hn][cr].B_IMEI_IMSI_GSM.size();j++){
					if(j==0){
						//只初始化一次
						tempimei.B_IMEI_IMSI_GSM.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
					}
					for(int k=0;k<tacstat[hn][cr].B_IMEI_IMSI_GSM[j].size();k++){
						int temp_hash_imei=atoi(tacstat[hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					
						IMEI_IMSI tempim;
						tempim.IMEI=tacstat[hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI;
						tempim.IMSI=tacstat[hn][cr].B_IMEI_IMSI_GSM[j][k].IMSI;
						tempimei.B_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
						tempimei.B_IMEI_GSM++;
					}
				}
				for(int j=0;j<tacstat[hn][cr].B_IMEI_IMSI_TD.size();j++){
					if(j==0){
						//只初始化一次
						tempimei.B_IMEI_IMSI_TD.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
					}
					for(int k=0;k<tacstat[hn][cr].B_IMEI_IMSI_TD[j].size();k++){
						int temp_hash_imei=atoi(tacstat[hn][cr].B_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					
						IMEI_IMSI tempim;
						tempim.IMEI=tacstat[hn][cr].B_IMEI_IMSI_TD[j][k].IMEI;
						tempim.IMSI=tacstat[hn][cr].B_IMEI_IMSI_TD[j][k].IMSI;
						tempimei.B_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
						tempimei.B_IMEI_TD++;
					}
				}
				//csize++;
				tacstat_timesection[temp_hash].push_back(tempimei);
			}
		}
		
		//hn/cfg.THREADNUM

		if(hn%100==0){
			end=clock();
			//cout<<"Combine TAC statistic with TimeSection with "<<hsize<<" Records to "<<csize<<" Records in "<<difftime(end,start)<<"ms"<<endl;
			cout<<"Combine TAC statistic with Cell with HASHKEY "<<hn<<" in "<<difftime(end,start)<<"ms"<<endl;
			start=clock();
		}
	}
		
	return true;
}
//将tacstat_timesection中不同的cell合并生成tacstat_timesectioncell
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
	for(int hn=0;hn<tacstat_timesection.size();hn++){
		
		//hsize+=(int)tacstat_timesection[hn].size();
		for(int cr=0;cr<tacstat_timesection[hn].size();cr++){
			//查询是否已经有相应的TAC记录。
			bool isExistTAC=false;
			int temp_hash=atoi(tacstat_timesection[hn][cr].TAC.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
			for(int im=0;im<tacstat_timesectioncell[temp_hash].size();im++){
				if(tacstat_timesectioncell[temp_hash][im].TAC==tacstat_timesection[hn][cr].TAC){
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
				for(int j=0;j<tacstat_timesection[hn][cr].A_BSSMAP_Cause.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesectioncell[temp_hash][im].A_BSSMAP_Cause.size();k++){
						if(tacstat_timesectioncell[temp_hash][im].A_BSSMAP_Cause[k].cause_id==tacstat_timesection[hn][cr].A_BSSMAP_Cause[j].cause_id){
							isExistCause=true;
							tacstat_timesectioncell[temp_hash][im].A_BSSMAP_Cause[k].cause_num+=tacstat_timesection[hn][cr].A_BSSMAP_Cause[j].cause_num;
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat_timesection[hn][cr].A_BSSMAP_Cause[j].cause_id;
						tempcause.cause_num=tacstat_timesection[hn][cr].A_BSSMAP_Cause[j].cause_num;
						tacstat_timesectioncell[temp_hash][im].A_BSSMAP_Cause.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat_timesection[hn][cr].B_BSSMAP_Cause.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesectioncell[temp_hash][im].B_BSSMAP_Cause.size();k++){
						if(tacstat_timesectioncell[temp_hash][im].B_BSSMAP_Cause[k].cause_id==tacstat_timesection[hn][cr].B_BSSMAP_Cause[j].cause_id){
							isExistCause=true;
							tacstat_timesectioncell[temp_hash][im].B_BSSMAP_Cause[k].cause_num+=tacstat_timesection[hn][cr].B_BSSMAP_Cause[j].cause_num;
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat_timesection[hn][cr].B_BSSMAP_Cause[j].cause_id;
						tempcause.cause_num=tacstat_timesection[hn][cr].B_BSSMAP_Cause[j].cause_num;
						tacstat_timesectioncell[temp_hash][im].B_BSSMAP_Cause.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat_timesection[hn][cr].A_RANAP_Cause.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesectioncell[temp_hash][im].A_RANAP_Cause.size();k++){
						if(tacstat_timesectioncell[temp_hash][im].A_RANAP_Cause[k].cause_id==tacstat_timesection[hn][cr].A_RANAP_Cause[j].cause_id){
							isExistCause=true;
							tacstat_timesectioncell[temp_hash][im].A_RANAP_Cause[k].cause_num+=tacstat_timesection[hn][cr].A_RANAP_Cause[j].cause_num;
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat_timesection[hn][cr].A_RANAP_Cause[j].cause_id;
						tempcause.cause_num=tacstat_timesection[hn][cr].A_RANAP_Cause[j].cause_num;
						tacstat_timesectioncell[temp_hash][im].A_RANAP_Cause.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat_timesection[hn][cr].B_RANAP_Cause.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesectioncell[temp_hash][im].B_RANAP_Cause.size();k++){
						if(tacstat_timesectioncell[temp_hash][im].B_RANAP_Cause[k].cause_id==tacstat_timesection[hn][cr].B_RANAP_Cause[j].cause_id){
							isExistCause=true;
							tacstat_timesectioncell[temp_hash][im].B_RANAP_Cause[k].cause_num+=tacstat_timesection[hn][cr].B_RANAP_Cause[j].cause_num;
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat_timesection[hn][cr].B_RANAP_Cause[j].cause_id;
						tempcause.cause_num=tacstat_timesection[hn][cr].B_RANAP_Cause[j].cause_num;
						tacstat_timesectioncell[temp_hash][im].B_RANAP_Cause.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat_timesection[hn][cr].A_DX_Cause_GSM.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesectioncell[temp_hash][im].A_DX_Cause_GSM.size();k++){
						if(tacstat_timesectioncell[temp_hash][im].A_DX_Cause_GSM[k].cause_id==tacstat_timesection[hn][cr].A_DX_Cause_GSM[j].cause_id){
							isExistCause=true;
							tacstat_timesectioncell[temp_hash][im].A_DX_Cause_GSM[k].cause_num+=tacstat_timesection[hn][cr].A_DX_Cause_GSM[j].cause_num;
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat_timesection[hn][cr].A_DX_Cause_GSM[j].cause_id;
						tempcause.cause_num=tacstat_timesection[hn][cr].A_DX_Cause_GSM[j].cause_num;
						tacstat_timesectioncell[temp_hash][im].A_DX_Cause_GSM.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat_timesection[hn][cr].A_DX_Cause_TD.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesectioncell[temp_hash][im].A_DX_Cause_TD.size();k++){
						if(tacstat_timesectioncell[temp_hash][im].A_DX_Cause_TD[k].cause_id==tacstat_timesection[hn][cr].A_DX_Cause_TD[j].cause_id){
							isExistCause=true;
							tacstat_timesectioncell[temp_hash][im].A_DX_Cause_TD[k].cause_num+=tacstat_timesection[hn][cr].A_DX_Cause_TD[j].cause_num;
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat_timesection[hn][cr].A_DX_Cause_TD[j].cause_id;
						tempcause.cause_num=tacstat_timesection[hn][cr].A_DX_Cause_TD[j].cause_num;
						tacstat_timesectioncell[temp_hash][im].A_DX_Cause_TD.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat_timesection[hn][cr].B_DX_Cause_GSM.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesectioncell[temp_hash][im].B_DX_Cause_GSM.size();k++){
						if(tacstat_timesectioncell[temp_hash][im].B_DX_Cause_GSM[k].cause_id==tacstat_timesection[hn][cr].B_DX_Cause_GSM[j].cause_id){
							isExistCause=true;
							tacstat_timesectioncell[temp_hash][im].B_DX_Cause_GSM[k].cause_num+=tacstat_timesection[hn][cr].B_DX_Cause_GSM[j].cause_num;
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat_timesection[hn][cr].B_DX_Cause_GSM[j].cause_id;
						tempcause.cause_num=tacstat_timesection[hn][cr].B_DX_Cause_GSM[j].cause_num;
						tacstat_timesectioncell[temp_hash][im].B_DX_Cause_GSM.push_back(tempcause);
					}
				}
				for(int j=0;j<tacstat_timesection[hn][cr].B_DX_Cause_TD.size();j++){
					bool isExistCause=false;
					for(int k=0;k<tacstat_timesectioncell[temp_hash][im].B_DX_Cause_TD.size();k++){
						if(tacstat_timesectioncell[temp_hash][im].B_DX_Cause_TD[k].cause_id==tacstat_timesection[hn][cr].B_DX_Cause_TD[j].cause_id){
							isExistCause=true;
							tacstat_timesectioncell[temp_hash][im].B_DX_Cause_TD[k].cause_num+=tacstat_timesection[hn][cr].B_DX_Cause_TD[j].cause_num;
							break;
						}
					}
						
					if(isExistCause==false){
						CAUSE_TYPE tempcause;
						tempcause.cause_id=tacstat_timesection[hn][cr].B_DX_Cause_TD[j].cause_id;
						tempcause.cause_num=tacstat_timesection[hn][cr].B_DX_Cause_TD[j].cause_num;
						tacstat_timesectioncell[temp_hash][im].B_DX_Cause_TD.push_back(tempcause);
					}
				}
					
				for(int j=0;j<tacstat_timesection[hn][cr].A_IMEI_IMSI_GSM.size();j++){
					for(int k=0;k<tacstat_timesection[hn][cr].A_IMEI_IMSI_GSM[j].size();k++){
						//对每一个IMEI和IMSI组合，查询是否已有记录
						bool isExistIMEI=false;
						bool isExistIMEIandIMSI=false;
						int temp_hash_imei=atoi(tacstat_timesection[hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
						for(int m=0;m<tacstat_timesectioncell[temp_hash][im].A_IMEI_IMSI_GSM[temp_hash_imei].size();m++){
							if(tacstat_timesection[hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI==tacstat_timesectioncell[temp_hash][im].A_IMEI_IMSI_GSM[temp_hash_imei][m].IMEI){
								isExistIMEI=true;
								if(tacstat_timesection[hn][cr].A_IMEI_IMSI_GSM[j][k].IMSI==tacstat_timesectioncell[temp_hash][im].A_IMEI_IMSI_GSM[temp_hash_imei][m].IMSI){
									isExistIMEIandIMSI=true;
									break;
								}
							}
						}

						if(isExistIMEIandIMSI==false){
							//如果IMEI和IMSI组成的对不重复，那么新增一个
							IMEI_IMSI tempim;
							tempim.IMEI=tacstat_timesection[hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI;
							tempim.IMSI=tacstat_timesection[hn][cr].A_IMEI_IMSI_GSM[j][k].IMSI;
							tacstat_timesectioncell[temp_hash][im].A_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
						}

						if(isExistIMEI==false){
							//如果IMEI不重复
							tacstat_timesectioncell[temp_hash][im].A_IMEI_GSM++;
						}
					}
				}
				for(int j=0;j<tacstat_timesection[hn][cr].A_IMEI_IMSI_TD.size();j++){
					for(int k=0;k<tacstat_timesection[hn][cr].A_IMEI_IMSI_TD[j].size();k++){
						//对每一个IMEI和IMSI组合，查询是否已有记录
						bool isExistIMEI=false;
						bool isExistIMEIandIMSI=false;
						int temp_hash_imei=atoi(tacstat_timesection[hn][cr].A_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
						for(int m=0;m<tacstat_timesectioncell[temp_hash][im].A_IMEI_IMSI_TD[temp_hash_imei].size();m++){
							if(tacstat_timesection[hn][cr].A_IMEI_IMSI_TD[j][k].IMEI==tacstat_timesectioncell[temp_hash][im].A_IMEI_IMSI_TD[temp_hash_imei][m].IMEI){
								isExistIMEI=true;
								if(tacstat_timesection[hn][cr].A_IMEI_IMSI_TD[j][k].IMSI==tacstat_timesectioncell[temp_hash][im].A_IMEI_IMSI_TD[temp_hash_imei][m].IMSI){
									isExistIMEIandIMSI=true;
									break;
								}
							}
						}

						if(isExistIMEIandIMSI==false){
							//如果IMEI和IMSI组成的对不重复，那么新增一个
							IMEI_IMSI tempim;
							tempim.IMEI=tacstat_timesection[hn][cr].A_IMEI_IMSI_TD[j][k].IMEI;
							tempim.IMSI=tacstat_timesection[hn][cr].A_IMEI_IMSI_TD[j][k].IMSI;
							tacstat_timesectioncell[temp_hash][im].A_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
						}

						if(isExistIMEI==false){
							//如果IMEI不重复
							tacstat_timesectioncell[temp_hash][im].A_IMEI_TD++;
						}
					}
				}
				for(int j=0;j<tacstat_timesection[hn][cr].B_IMEI_IMSI_GSM.size();j++){
					for(int k=0;k<tacstat_timesection[hn][cr].B_IMEI_IMSI_GSM[j].size();k++){
						//对每一个IMEI和IMSI组合，查询是否已有记录
						bool isExistIMEI=false;
						bool isExistIMEIandIMSI=false;
						int temp_hash_imei=atoi(tacstat_timesection[hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
						for(int m=0;m<tacstat_timesectioncell[temp_hash][im].B_IMEI_IMSI_GSM[temp_hash_imei].size();m++){
							if(tacstat_timesection[hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI==tacstat_timesectioncell[temp_hash][im].B_IMEI_IMSI_GSM[temp_hash_imei][m].IMEI){
								isExistIMEI=true;
								if(tacstat_timesection[hn][cr].B_IMEI_IMSI_GSM[j][k].IMSI==tacstat_timesectioncell[temp_hash][im].B_IMEI_IMSI_GSM[temp_hash_imei][m].IMSI){
									isExistIMEIandIMSI=true;
									break;
								}
							}
						}

						if(isExistIMEIandIMSI==false){
							//如果IMEI和IMSI组成的对不重复，那么新增一个
							IMEI_IMSI tempim;
							tempim.IMEI=tacstat_timesection[hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI;
							tempim.IMSI=tacstat_timesection[hn][cr].B_IMEI_IMSI_GSM[j][k].IMSI;
							tacstat_timesectioncell[temp_hash][im].B_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
						}

						if(isExistIMEI==false){
							//如果IMEI不重复
							tacstat_timesectioncell[temp_hash][im].B_IMEI_GSM++;
						}
					}
				}
				for(int j=0;j<tacstat_timesection[hn][cr].B_IMEI_IMSI_TD.size();j++){
					for(int k=0;k<tacstat_timesection[hn][cr].B_IMEI_IMSI_TD[j].size();k++){
						//对每一个IMEI和IMSI组合，查询是否已有记录
						bool isExistIMEI=false;
						bool isExistIMEIandIMSI=false;
						int temp_hash_imei=atoi(tacstat_timesection[hn][cr].B_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
						for(int m=0;m<tacstat_timesectioncell[temp_hash][im].B_IMEI_IMSI_TD[temp_hash_imei].size();m++){
							if(tacstat_timesection[hn][cr].B_IMEI_IMSI_TD[j][k].IMEI==tacstat_timesectioncell[temp_hash][im].B_IMEI_IMSI_TD[temp_hash_imei][m].IMEI){
								isExistIMEI=true;
								if(tacstat_timesection[hn][cr].B_IMEI_IMSI_TD[j][k].IMSI==tacstat_timesectioncell[temp_hash][im].B_IMEI_IMSI_TD[temp_hash_imei][m].IMSI){
									isExistIMEIandIMSI=true;
									break;
								}
							}
						}

						if(isExistIMEIandIMSI==false){
							//如果IMEI和IMSI组成的对不重复，那么新增一个
							IMEI_IMSI tempim;
							tempim.IMEI=tacstat_timesection[hn][cr].B_IMEI_IMSI_TD[j][k].IMEI;
							tempim.IMSI=tacstat_timesection[hn][cr].B_IMEI_IMSI_TD[j][k].IMSI;
							tacstat_timesectioncell[temp_hash][im].B_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
						}

						if(isExistIMEI==false){
							//如果IMEI不重复
							tacstat_timesectioncell[temp_hash][im].B_IMEI_TD++;
						}
					}
				}
					tacstat_timesectioncell[temp_hash][im].B_shortcall_1+=tacstat_timesection[hn][cr].B_shortcall_1;
					tacstat_timesectioncell[temp_hash][im].A_shortcall_1+=tacstat_timesection[hn][cr].A_shortcall_1;
					tacstat_timesectioncell[temp_hash][im].B_shortcall_2+=tacstat_timesection[hn][cr].B_shortcall_2;
					tacstat_timesectioncell[temp_hash][im].A_shortcall_2+=tacstat_timesection[hn][cr].A_shortcall_2;
					tacstat_timesectioncell[temp_hash][im].B_shortcall_3+=tacstat_timesection[hn][cr].B_shortcall_3;
					tacstat_timesectioncell[temp_hash][im].A_shortcall_3+=tacstat_timesection[hn][cr].A_shortcall_3;
					tacstat_timesectioncell[temp_hash][im].B_call_attempt+=tacstat_timesection[hn][cr].B_call_attempt;
					tacstat_timesectioncell[temp_hash][im].A_call_attempt+=tacstat_timesection[hn][cr].A_call_attempt;
					tacstat_timesectioncell[temp_hash][im].B_call_attempt_GSM+=tacstat_timesection[hn][cr].B_call_attempt_GSM;
					tacstat_timesectioncell[temp_hash][im].A_call_attempt_GSM+=tacstat_timesection[hn][cr].A_call_attempt_GSM;
					tacstat_timesectioncell[temp_hash][im].A_call_attempt_TD+=tacstat_timesection[hn][cr].A_call_attempt_TD;
					tacstat_timesectioncell[temp_hash][im].B_call_attempt_TD+=tacstat_timesection[hn][cr].B_call_attempt_TD;
					//tacstat_cell[temp_hash][im].A_causeTD+=tacstat[hn][cr].A_causeTD;
					//tacstat_cell[temp_hash][im].A_causeTD46+=tacstat[hn][cr].A_causeTD46;
					//tacstat_cell[temp_hash][im].A_causeTD176+=tacstat[hn][cr].A_causeTD176;
					//tacstat_cell[temp_hash][im].A_causeTD192+=tacstat[hn][cr].A_causeTD192;
					//tacstat_cell[temp_hash][im].A_causeTD209+=tacstat[hn][cr].A_causeTD209;
					//tacstat_cell[temp_hash][im].A_causeTD239+=tacstat[hn][cr].A_causeTD239;
					//tacstat_cell[temp_hash][im].A_causeTDMisc+=tacstat[hn][cr].A_causeTDMisc;
					//tacstat_cell[temp_hash][im].A_causeTDNAS+=tacstat[hn][cr].A_causeTDNAS;
					//tacstat_cell[temp_hash][im].A_causeTDNonStandard+=tacstat[hn][cr].A_causeTDNonStandard;
					//tacstat_cell[temp_hash][im].A_causeTDProtocol+=tacstat[hn][cr].A_causeTDProtocol;
					//tacstat_cell[temp_hash][im].A_causeTDRadioNetwork+=tacstat[hn][cr].A_causeTDRadioNetwork;
					//tacstat_cell[temp_hash][im].A_causeTDTransport+=tacstat[hn][cr].A_causeTDTransport;
					//tacstat_cell[temp_hash][im].B_causeTD+=tacstat[hn][cr].B_causeTD;
					//tacstat_cell[temp_hash][im].B_causeTD46+=tacstat[hn][cr].B_causeTD46;
					//tacstat_cell[temp_hash][im].B_causeTD176+=tacstat[hn][cr].B_causeTD176;
					//tacstat_cell[temp_hash][im].B_causeTD192+=tacstat[hn][cr].B_causeTD192;
					//tacstat_cell[temp_hash][im].B_causeTD209+=tacstat[hn][cr].B_causeTD209;
					//tacstat_cell[temp_hash][im].B_causeTD239+=tacstat[hn][cr].B_causeTD239;
					//tacstat_cell[temp_hash][im].B_causeTDMisc+=tacstat[hn][cr].B_causeTDMisc;
					//tacstat_cell[temp_hash][im].B_causeTDNAS+=tacstat[hn][cr].B_causeTDNAS;
					//tacstat_cell[temp_hash][im].B_causeTDNonStandard+=tacstat[hn][cr].B_causeTDNonStandard;
					//tacstat_cell[temp_hash][im].B_causeTDProtocol+=tacstat[hn][cr].B_causeTDProtocol;
					//tacstat_cell[temp_hash][im].B_causeTDRadioNetwork+=tacstat[hn][cr].B_causeTDRadioNetwork;
					//tacstat_cell[temp_hash][im].B_causeTDTransport+=tacstat[hn][cr].B_causeTDTransport;
					////tacstat_cell[temp_hash][im].A_call_not_connected+=tacstat[hn][cr].A_call_not_connected;
					////tacstat_cell[temp_hash][im].B_call_not_connected+=tacstat[hn][cr].B_call_not_connected;
					break;
				}
			}
			if(isExistTAC==false){
				//如果没有的话，增加
				IMEI_CDR_Statistic tempimei;
				tempimei.IMEI="";
				tempimei.TAC=tacstat_timesection[hn][cr].TAC;
				tempimei.brand=tacstat_timesection[hn][cr].brand;
				tempimei.type=tacstat_timesection[hn][cr].type;
				tempimei.name=tacstat_timesection[hn][cr].name;
				tempimei.cellid=tacstat_timesection[hn][cr].cellid;
				tempimei.network=tacstat_timesection[hn][cr].network;
				tempimei.celltype=tacstat_timesection[hn][cr].celltype;
				/*tempimei.A_cause0=tacstat[hn][cr].A_cause0;
				tempimei.A_cause1=tacstat[hn][cr].A_cause1;
				tempimei.A_cause20=tacstat[hn][cr].A_cause20;
				tempimei.A_cause60=tacstat[hn][cr].A_cause60;
				tempimei.B_cause0=tacstat[hn][cr].B_cause0;
				tempimei.B_cause1=tacstat[hn][cr].B_cause1;
				tempimei.B_cause20=tacstat[hn][cr].B_cause20;
				tempimei.B_cause60=tacstat[hn][cr].B_cause60;
				tempimei.A_causeGSM=tacstat[hn][cr].A_causeGSM;
				tempimei.B_causeGSM=tacstat[hn][cr].B_causeGSM;*/
				tempimei.A_shortcall_1=tacstat_timesection[hn][cr].A_shortcall_1;
				tempimei.B_shortcall_1=tacstat_timesection[hn][cr].B_shortcall_1;
				tempimei.A_shortcall_2=tacstat_timesection[hn][cr].A_shortcall_2;
				tempimei.B_shortcall_2=tacstat_timesection[hn][cr].B_shortcall_2;
				tempimei.A_shortcall_3=tacstat_timesection[hn][cr].A_shortcall_3;
				tempimei.B_shortcall_3=tacstat_timesection[hn][cr].B_shortcall_3;
				tempimei.A_call_attempt=tacstat_timesection[hn][cr].A_call_attempt;
				tempimei.B_call_attempt=tacstat_timesection[hn][cr].B_call_attempt;
				tempimei.B_call_attempt_GSM=tacstat_timesection[hn][cr].B_call_attempt_GSM;
				tempimei.A_call_attempt_GSM=tacstat_timesection[hn][cr].A_call_attempt_GSM;
				tempimei.A_call_attempt_TD=tacstat_timesection[hn][cr].A_call_attempt_TD;
				tempimei.B_call_attempt_TD=tacstat_timesection[hn][cr].B_call_attempt_TD;
				/*tempimei.A_causeTD=tacstat[hn][cr].A_causeTD;
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
				tempimei.B_causeTDTransport=tacstat[hn][cr].B_causeTDTransport;*/
				//tempimei.A_call_not_connected=tacstat[hn][cr].A_call_not_connected;
				//tempimei.B_call_not_connected=tacstat[hn][cr].B_call_not_connected;
				for(int j=0;j<tacstat_timesection[hn][cr].A_BSSMAP_Cause.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat_timesection[hn][cr].A_BSSMAP_Cause[j].cause_id;
					tempcause.cause_num=tacstat_timesection[hn][cr].A_BSSMAP_Cause[j].cause_num;
					tempimei.A_BSSMAP_Cause.push_back(tempcause);
				}
				for(int j=0;j<tacstat_timesection[hn][cr].B_BSSMAP_Cause.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat_timesection[hn][cr].B_BSSMAP_Cause[j].cause_id;
					tempcause.cause_num=tacstat_timesection[hn][cr].B_BSSMAP_Cause[j].cause_num;
					tempimei.B_BSSMAP_Cause.push_back(tempcause);
					
				}
				for(int j=0;j<tacstat_timesection[hn][cr].A_RANAP_Cause.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat_timesection[hn][cr].A_RANAP_Cause[j].cause_id;
					tempcause.cause_num=tacstat_timesection[hn][cr].A_RANAP_Cause[j].cause_num;
					tempimei.A_RANAP_Cause.push_back(tempcause);
				}
				for(int j=0;j<tacstat_timesection[hn][cr].B_RANAP_Cause.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat_timesection[hn][cr].B_RANAP_Cause[j].cause_id;
					tempcause.cause_num=tacstat_timesection[hn][cr].B_RANAP_Cause[j].cause_num;
					tempimei.B_RANAP_Cause.push_back(tempcause);
				}
				for(int j=0;j<tacstat_timesection[hn][cr].A_DX_Cause_GSM.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat_timesection[hn][cr].A_DX_Cause_GSM[j].cause_id;
					tempcause.cause_num=tacstat_timesection[hn][cr].A_DX_Cause_GSM[j].cause_num;
					tempimei.A_DX_Cause_GSM.push_back(tempcause);
				}
				for(int j=0;j<tacstat_timesection[hn][cr].A_DX_Cause_TD.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat_timesection[hn][cr].A_DX_Cause_TD[j].cause_id;
					tempcause.cause_num=tacstat_timesection[hn][cr].A_DX_Cause_TD[j].cause_num;
					tempimei.A_DX_Cause_TD.push_back(tempcause);
				}
				for(int j=0;j<tacstat_timesection[hn][cr].B_DX_Cause_GSM.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat_timesection[hn][cr].B_DX_Cause_GSM[j].cause_id;
					tempcause.cause_num=tacstat_timesection[hn][cr].B_DX_Cause_GSM[j].cause_num;
					tempimei.B_DX_Cause_GSM.push_back(tempcause);
				}
				for(int j=0;j<tacstat_timesection[hn][cr].B_DX_Cause_TD.size();j++){
					CAUSE_TYPE tempcause;
					tempcause.cause_id=tacstat_timesection[hn][cr].B_DX_Cause_TD[j].cause_id;
					tempcause.cause_num=tacstat_timesection[hn][cr].B_DX_Cause_TD[j].cause_num;
					tempimei.B_DX_Cause_TD.push_back(tempcause);
				}
				
				
				for(int j=0;j<tacstat_timesection[hn][cr].A_IMEI_IMSI_GSM.size();j++){
					if(j==0){
						//只初始化一次
						tempimei.A_IMEI_IMSI_GSM.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
					}
					for(int k=0;k<tacstat_timesection[hn][cr].A_IMEI_IMSI_GSM[j].size();k++){
						int temp_hash_imei=atoi(tacstat_timesection[hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					
						IMEI_IMSI tempim;
						tempim.IMEI=tacstat_timesection[hn][cr].A_IMEI_IMSI_GSM[j][k].IMEI;
						tempim.IMSI=tacstat_timesection[hn][cr].A_IMEI_IMSI_GSM[j][k].IMSI;
						tempimei.A_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
						tempimei.A_IMEI_GSM++;
					}
				}
				for(int j=0;j<tacstat_timesection[hn][cr].A_IMEI_IMSI_TD.size();j++){
					if(j==0){
						//只初始化一次
						tempimei.A_IMEI_IMSI_TD.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
					}
					for(int k=0;k<tacstat_timesection[hn][cr].A_IMEI_IMSI_TD[j].size();k++){
						int temp_hash_imei=atoi(tacstat_timesection[hn][cr].A_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					
						IMEI_IMSI tempim;
						tempim.IMEI=tacstat_timesection[hn][cr].A_IMEI_IMSI_TD[j][k].IMEI;
						tempim.IMSI=tacstat_timesection[hn][cr].A_IMEI_IMSI_TD[j][k].IMSI;
						tempimei.A_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
						tempimei.A_IMEI_TD++;
					}
				}
				for(int j=0;j<tacstat_timesection[hn][cr].B_IMEI_IMSI_GSM.size();j++){
					if(j==0){
						//只初始化一次
						tempimei.B_IMEI_IMSI_GSM.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
					}
					for(int k=0;k<tacstat_timesection[hn][cr].B_IMEI_IMSI_GSM[j].size();k++){
						int temp_hash_imei=atoi(tacstat_timesection[hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					
						IMEI_IMSI tempim;
						tempim.IMEI=tacstat_timesection[hn][cr].B_IMEI_IMSI_GSM[j][k].IMEI;
						tempim.IMSI=tacstat_timesection[hn][cr].B_IMEI_IMSI_GSM[j][k].IMSI;
						tempimei.B_IMEI_IMSI_GSM[temp_hash_imei].push_back(tempim);
						tempimei.B_IMEI_GSM++;
					}
				}
				for(int j=0;j<tacstat_timesection[hn][cr].B_IMEI_IMSI_TD.size();j++){
					if(j==0){
						//只初始化一次
						tempimei.B_IMEI_IMSI_TD.resize((int)pow((double)10,cfg.HASH_NUM_IMEI));
					}
					for(int k=0;k<tacstat_timesection[hn][cr].B_IMEI_IMSI_TD[j].size();k++){
						int temp_hash_imei=atoi(tacstat_timesection[hn][cr].B_IMEI_IMSI_TD[j][k].IMEI.substr(cfg.START_HASH_INDEX_IMEI,cfg.HASH_NUM_IMEI).c_str());
					
						IMEI_IMSI tempim;
						tempim.IMEI=tacstat_timesection[hn][cr].B_IMEI_IMSI_TD[j][k].IMEI;
						tempim.IMSI=tacstat_timesection[hn][cr].B_IMEI_IMSI_TD[j][k].IMSI;
						tempimei.B_IMEI_IMSI_TD[temp_hash_imei].push_back(tempim);
						tempimei.B_IMEI_TD++;
					}
				}
				//csize++;
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
//------------------输出合并结果-------------
//输出tacstat_timesection
bool WriteTACFile_TimeSection(std::string temp_result_path_name){
	ofstream fo(temp_result_path_name.c_str(),'w');
	if(fo.is_open()==true){
		fo<<"TAC"<<","<<"品牌"<<","<<"型号"<<","<<"类别"<<","\
			<<"CellID"<<","<<"小区分类"<<","<<"网络类型"<<","\
			/*<<"A_count0"<<","<<"A_count1"<<","\
			<<"A_count20"<<","<<"A_count60"<<","\
			<<"A_countGSM"<<","<<"A_countTD"<<","\
			<<"A_causeTD46"<<","<<"A_causeTD176"<<","<<"A_causeTD192"<<","<<"A_causeTD209"<<","<<"A_causeTD239"<<","\
			<<"A_causeTDMisc"<<","<<"A_causeTDNAS"<<","\
			<<"A_causeTDNonStandard"<<","<<"A_causeTDProtocol"<<","\
			<<"A_causeTDRadioNetwork"<<","<<"A_causeTDTransport"<<","\*/
			<<"A_shortcall_1"<<","<<"A_shortcall_2"<<","<<"A_shortcall_3"<<","\
			<<"A_call_attempt"<<","<<"A_call_attemp_GSM"<<","<<"A_call_attemp_TD"<<","\
			/*<<"B_count0"<<","<<"B_count1"<<","\
			<<"B_count20"<<","<<"B_count60"<<","\
			<<"B_countGSM"<<","<<"B_countTD"<<","\
			<<"B_causeTD46"<<","<<"B_causeTD176"<<","<<"B_causeTD192"<<","<<"B_causeTD209"<<","<<"B_causeTD239"<<","\
			<<"B_causeTDMisc"<<","<<"B_causeTDNAS"<<","\
			<<"B_causeTDNonStandard"<<","<<"B_causeTDProtocol"<<","\
			<<"B_causeTDRadioNetwork"<<","<<"B_causeTDTransport"<<","\*/
			<<"B_shortcall_1"<<","<<"B_shortcall_2"<<","<<"B_shortcall_3"<<","\
			<<"B_call_attempt"<<","<<"B_call_attemp_GSM"<<","<<"B_call_attemp_TD"<<","\
			<<"A_IMEI_GSM"<<","<<"A_IMEI_TD"<<","<<"B_IMEI_GSM"<<","<<"B_IMEI_TD"<<","\
			<<"A_BSSMAP_Cause"<<","<<"A_RANAP_Cause"<<","<<"B_BSSMAP_Cause"<<","<<"B_RANAP_Cause"<<","\
			<<"A_DX_Cause_GSM"<<","<<"A_DX_Cause_TD"<<","<<"B_DX_Cause_GSM"<<","<<"B_DX_Cause_TD"<<","\
			<<"A_IMEI_IMSI_GSM"<<","<<"A_IMEI_IMSI_TD"<<","<<"B_IMEI_IMSI_GSM"<<","<<"B_IMEI_IMSI_TD"<<","\
			<<endl;
		for(int hn=0;hn<tacstat_timesection.size();hn++){
			for(int i=0;i<tacstat_timesection[hn].size();i++){

				fo<<tacstat_timesection[hn][i].TAC<<","<<tacstat_timesection[hn][i].brand<<","<<tacstat_timesection[hn][i].name<<","<<tacstat_timesection[hn][i].type<<","\
					<<tacstat_timesection[hn][i].cellid<<","<<tacstat_timesection[hn][i].celltype<<","<<tacstat_timesection[hn][i].network<<","\
					<<tacstat_timesection[hn][i].A_shortcall_1<<","<<tacstat_timesection[hn][i].A_shortcall_2<<","<<tacstat_timesection[hn][i].A_shortcall_3<<","\
					<<tacstat_timesection[hn][i].A_call_attempt<<","<<tacstat_timesection[hn][i].A_call_attempt_GSM<<","<<tacstat_timesection[hn][i].A_call_attempt_TD<<","\
					<<tacstat_timesection[hn][i].B_shortcall_1<<","<<tacstat_timesection[hn][i].B_shortcall_2<<","<<tacstat_timesection[hn][i].B_shortcall_3<<","\
					<<tacstat_timesection[hn][i].B_call_attempt<<","<<tacstat_timesection[hn][i].B_call_attempt_GSM<<","<<tacstat_timesection[hn][i].B_call_attempt_TD<<","\
					<<tacstat_timesection[hn][i].A_IMEI_GSM<<","<<tacstat_timesection[hn][i].A_IMEI_TD<<","<<tacstat_timesection[hn][i].B_IMEI_GSM<<","<<tacstat_timesection[hn][i].B_IMEI_TD<<",";
				
				for(int k=0;k<tacstat_timesection[hn][i].A_BSSMAP_Cause.size();k++){
					fo<<tacstat_timesection[hn][i].A_BSSMAP_Cause[k].cause_id<<";"<<tacstat_timesection[hn][i].A_BSSMAP_Cause[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat_timesection[hn][i].A_RANAP_Cause.size();k++){
					fo<<tacstat_timesection[hn][i].A_RANAP_Cause[k].cause_id<<";"<<tacstat_timesection[hn][i].A_RANAP_Cause[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat_timesection[hn][i].B_BSSMAP_Cause.size();k++){
					fo<<tacstat_timesection[hn][i].B_BSSMAP_Cause[k].cause_id<<";"<<tacstat_timesection[hn][i].B_BSSMAP_Cause[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat_timesection[hn][i].B_RANAP_Cause.size();k++){
					fo<<tacstat_timesection[hn][i].B_RANAP_Cause[k].cause_id<<";"<<tacstat_timesection[hn][i].B_RANAP_Cause[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat_timesection[hn][i].A_DX_Cause_GSM.size();k++){
					fo<<tacstat_timesection[hn][i].A_DX_Cause_GSM[k].cause_id<<";"<<tacstat_timesection[hn][i].A_DX_Cause_GSM[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat_timesection[hn][i].A_DX_Cause_TD.size();k++){
					fo<<tacstat_timesection[hn][i].A_DX_Cause_TD[k].cause_id<<";"<<tacstat_timesection[hn][i].A_DX_Cause_TD[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat_timesection[hn][i].B_DX_Cause_GSM.size();k++){
					fo<<tacstat_timesection[hn][i].B_DX_Cause_GSM[k].cause_id<<";"<<tacstat_timesection[hn][i].B_DX_Cause_GSM[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat_timesection[hn][i].B_DX_Cause_TD.size();k++){
					fo<<tacstat_timesection[hn][i].B_DX_Cause_TD[k].cause_id<<";"<<tacstat_timesection[hn][i].B_DX_Cause_TD[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat_timesection[hn][i].A_IMEI_IMSI_GSM.size();k++){
					for(int l=0;l<tacstat_timesection[hn][i].A_IMEI_IMSI_GSM[k].size();l++){
						fo<<tacstat_timesection[hn][i].A_IMEI_IMSI_GSM[k][l].IMEI<<";"<<tacstat_timesection[hn][i].A_IMEI_IMSI_GSM[k][l].IMSI<<";";
					}
				}
				fo<<",";
				for(int k=0;k<tacstat_timesection[hn][i].A_IMEI_IMSI_TD.size();k++){
					for(int l=0;l<tacstat_timesection[hn][i].A_IMEI_IMSI_TD[k].size();l++){
						fo<<tacstat_timesection[hn][i].A_IMEI_IMSI_TD[k][l].IMEI<<";"<<tacstat_timesection[hn][i].A_IMEI_IMSI_TD[k][l].IMSI<<";";
					}
				}
				fo<<",";
				for(int k=0;k<tacstat_timesection[hn][i].B_IMEI_IMSI_GSM.size();k++){
					for(int l=0;l<tacstat_timesection[hn][i].B_IMEI_IMSI_GSM[k].size();l++){
						fo<<tacstat_timesection[hn][i].B_IMEI_IMSI_GSM[k][l].IMEI<<";"<<tacstat_timesection[hn][i].B_IMEI_IMSI_GSM[k][l].IMSI<<";";
					}
				}
				fo<<",";
				for(int k=0;k<tacstat_timesection[hn][i].B_IMEI_IMSI_TD.size();k++){
					for(int l=0;l<tacstat_timesection[hn][i].B_IMEI_IMSI_TD[k].size();l++){
						fo<<tacstat_timesection[hn][i].B_IMEI_IMSI_TD[k][l].IMEI<<";"<<tacstat_timesection[hn][i].B_IMEI_IMSI_TD[k][l].IMSI<<";";
					}
				}
				fo<<endl;
			}
		}
	}
	fo.close();
	return true;
}
//输出tacstat_timesectioncell
bool WriteTACFile_TimeSectionCell(std::string temp_result_path_name){
	ofstream fo(temp_result_path_name.c_str(),'w');
	if(fo.is_open()==true){
		fo<<"TAC"<<","<<"品牌"<<","<<"型号"<<","<<"类别"<<","\
			/*<<"A_count0"<<","<<"A_count1"<<","\
			<<"A_count20"<<","<<"A_count60"<<","\
			<<"A_countGSM"<<","<<"A_countTD"<<","\
			<<"A_causeTD46"<<","<<"A_causeTD176"<<","<<"A_causeTD192"<<","<<"A_causeTD209"<<","<<"A_causeTD239"<<","\
			<<"A_causeTDMisc"<<","<<"A_causeTDNAS"<<","\
			<<"A_causeTDNonStandard"<<","<<"A_causeTDProtocol"<<","\
			<<"A_causeTDRadioNetwork"<<","<<"A_causeTDTransport"<<","\*/
			<<"A_shortcall_1"<<","<<"A_shortcall_2"<<","<<"A_shortcall_3"<<","\
			<<"A_call_attempt"<<","<<"A_call_attemp_GSM"<<","<<"A_call_attemp_TD"<<","\
			/*<<"B_count0"<<","<<"B_count1"<<","\
			<<"B_count20"<<","<<"B_count60"<<","\
			<<"B_countGSM"<<","<<"B_countTD"<<","\
			<<"B_causeTD46"<<","<<"B_causeTD176"<<","<<"B_causeTD192"<<","<<"B_causeTD209"<<","<<"B_causeTD239"<<","\
			<<"B_causeTDMisc"<<","<<"B_causeTDNAS"<<","\
			<<"B_causeTDNonStandard"<<","<<"B_causeTDProtocol"<<","\
			<<"B_causeTDRadioNetwork"<<","<<"B_causeTDTransport"<<","\*/
			<<"B_shortcall_1"<<","<<"B_shortcall_2"<<","<<"B_shortcall_3"<<","\
			<<"B_call_attempt"<<","<<"B_call_attemp_GSM"<<","<<"B_call_attemp_TD"<<","\
			<<"A_IMEI_GSM"<<","<<"A_IMEI_TD"<<","<<"B_IMEI_GSM"<<","<<"B_IMEI_TD"<<","\
			<<"A_BSSMAP_Cause"<<","<<"A_RANAP_Cause"<<","<<"B_BSSMAP_Cause"<<","<<"B_RANAP_Cause"<<","\
			<<"A_DX_Cause_GSM"<<","<<"A_DX_Cause_TD"<<","<<"B_DX_Cause_GSM"<<","<<"B_DX_Cause_TD"<<","\
			<<"A_IMEI_IMSI_GSM"<<","<<"A_IMEI_IMSI_TD"<<","<<"B_IMEI_IMSI_GSM"<<","<<"B_IMEI_IMSI_TD"<<","\
			<<endl;
		for(int hn=0;hn<tacstat_timesectioncell.size();hn++){
			for(int i=0;i<tacstat_timesectioncell[hn].size();i++){
				fo<<tacstat_timesectioncell[hn][i].TAC<<","<<tacstat_timesectioncell[hn][i].brand<<","<<tacstat_timesectioncell[hn][i].name<<","<<tacstat_timesectioncell[hn][i].type<<","\
					/*<<tacstat_timesectioncell[hn][i].A_cause0<<","<<tacstat_timesectioncell[hn][i].A_cause1<<","\
					<<tacstat_timesectioncell[hn][i].A_cause20<<","<<tacstat_timesectioncell[hn][i].A_cause60<<","\
					<<tacstat_timesectioncell[hn][i].A_causeGSM<<","<<tacstat_timesectioncell[hn][i].A_causeTD<<","\
					<<tacstat_timesectioncell[hn][i].A_causeTD46<<","<<tacstat_timesectioncell[hn][i].A_causeTD176<<","<<tacstat_timesectioncell[hn][i].A_causeTD192<<","<<tacstat_timesectioncell[hn][i].A_causeTD209<<","<<tacstat_timesectioncell[hn][i].A_causeTD239<<","\
					<<tacstat_timesectioncell[hn][i].A_causeTDMisc<<","<<tacstat_timesectioncell[hn][i].A_causeTDNAS<<","\
					<<tacstat_timesectioncell[hn][i].A_causeTDNonStandard<<","<<tacstat_timesectioncell[hn][i].A_causeTDProtocol<<","\
					<<tacstat_timesectioncell[hn][i].A_causeTDRadioNetwork<<","<<tacstat_timesectioncell[hn][i].A_causeTDTransport<<","\*/
					<<tacstat_timesectioncell[hn][i].A_shortcall_1<<","<<tacstat_timesectioncell[hn][i].A_shortcall_2<<","<<tacstat_timesectioncell[hn][i].A_shortcall_3<<","\
					<<tacstat_timesectioncell[hn][i].A_call_attempt<<","<<tacstat_timesectioncell[hn][i].A_call_attempt_GSM<<","<<tacstat_timesectioncell[hn][i].A_call_attempt_TD<<","\
					/*<<tacstat_timesectioncell[hn][i].B_cause0<<","<<tacstat_timesectioncell[hn][i].B_cause1<<","\
					<<tacstat_timesectioncell[hn][i].B_cause20<<","<<tacstat_timesectioncell[hn][i].B_cause60<<","\
					<<tacstat_timesectioncell[hn][i].B_causeGSM<<","<<tacstat_timesectioncell[hn][i].B_causeTD<<","\
					<<tacstat_timesectioncell[hn][i].B_causeTD46<<","<<tacstat_timesectioncell[hn][i].B_causeTD176<<","<<tacstat_timesectioncell[hn][i].B_causeTD192<<","<<tacstat_timesectioncell[hn][i].B_causeTD209<<","<<tacstat_timesectioncell[hn][i].B_causeTD239<<","\
					<<tacstat_timesectioncell[hn][i].B_causeTDMisc<<","<<tacstat_timesectioncell[hn][i].B_causeTDNAS<<","\
					<<tacstat_timesectioncell[hn][i].B_causeTDNonStandard<<","<<tacstat_timesectioncell[hn][i].B_causeTDProtocol<<","\
					<<tacstat_timesectioncell[hn][i].B_causeTDRadioNetwork<<","<<tacstat_timesectioncell[hn][i].B_causeTDTransport<<","\*/
					<<tacstat_timesectioncell[hn][i].B_shortcall_1<<","<<tacstat_timesectioncell[hn][i].B_shortcall_2<<","<<tacstat_timesectioncell[hn][i].B_shortcall_3<<","\
					<<tacstat_timesectioncell[hn][i].B_call_attempt<<","<<tacstat_timesectioncell[hn][i].B_call_attempt_GSM<<","<<tacstat_timesectioncell[hn][i].B_call_attempt_TD<<","\
					<<tacstat_timesectioncell[hn][i].A_IMEI_GSM<<","<<tacstat_timesectioncell[hn][i].A_IMEI_TD<<","<<tacstat_timesectioncell[hn][i].B_IMEI_GSM<<","<<tacstat_timesectioncell[hn][i].B_IMEI_TD<<",";
				for(int k=0;k<tacstat_timesectioncell[hn][i].A_BSSMAP_Cause.size();k++){
					fo<<tacstat_timesectioncell[hn][i].A_BSSMAP_Cause[k].cause_id<<";"<<tacstat_timesectioncell[hn][i].A_BSSMAP_Cause[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat_timesectioncell[hn][i].A_RANAP_Cause.size();k++){
					fo<<tacstat_timesectioncell[hn][i].A_RANAP_Cause[k].cause_id<<";"<<tacstat_timesectioncell[hn][i].A_RANAP_Cause[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat_timesectioncell[hn][i].B_BSSMAP_Cause.size();k++){
					fo<<tacstat_timesectioncell[hn][i].B_BSSMAP_Cause[k].cause_id<<";"<<tacstat_timesectioncell[hn][i].B_BSSMAP_Cause[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat_timesectioncell[hn][i].B_RANAP_Cause.size();k++){
					fo<<tacstat_timesectioncell[hn][i].B_RANAP_Cause[k].cause_id<<";"<<tacstat_timesectioncell[hn][i].B_RANAP_Cause[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat_timesectioncell[hn][i].A_DX_Cause_GSM.size();k++){
					fo<<tacstat_timesectioncell[hn][i].A_DX_Cause_GSM[k].cause_id<<";"<<tacstat_timesectioncell[hn][i].A_DX_Cause_GSM[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat_timesectioncell[hn][i].A_DX_Cause_TD.size();k++){
					fo<<tacstat_timesectioncell[hn][i].A_DX_Cause_TD[k].cause_id<<";"<<tacstat_timesectioncell[hn][i].A_DX_Cause_TD[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat_timesectioncell[hn][i].B_DX_Cause_GSM.size();k++){
					fo<<tacstat_timesectioncell[hn][i].B_DX_Cause_GSM[k].cause_id<<";"<<tacstat_timesectioncell[hn][i].B_DX_Cause_GSM[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat_timesectioncell[hn][i].B_DX_Cause_TD.size();k++){
					fo<<tacstat_timesectioncell[hn][i].B_DX_Cause_TD[k].cause_id<<";"<<tacstat_timesectioncell[hn][i].B_DX_Cause_TD[k].cause_num<<";";
				}
				fo<<",";
				for(int k=0;k<tacstat_timesectioncell[hn][i].A_IMEI_IMSI_GSM.size();k++){
					for(int l=0;l<tacstat_timesectioncell[hn][i].A_IMEI_IMSI_GSM[k].size();l++){
						fo<<tacstat_timesectioncell[hn][i].A_IMEI_IMSI_GSM[k][l].IMEI<<";"<<tacstat_timesectioncell[hn][i].A_IMEI_IMSI_GSM[k][l].IMSI<<";";
					}
				}
				fo<<",";
				for(int k=0;k<tacstat_timesectioncell[hn][i].A_IMEI_IMSI_TD.size();k++){
					for(int l=0;l<tacstat_timesectioncell[hn][i].A_IMEI_IMSI_TD[k].size();l++){
						fo<<tacstat_timesectioncell[hn][i].A_IMEI_IMSI_TD[k][l].IMEI<<";"<<tacstat_timesectioncell[hn][i].A_IMEI_IMSI_TD[k][l].IMSI<<";";
					}
				}
				fo<<",";
				for(int k=0;k<tacstat_timesectioncell[hn][i].B_IMEI_IMSI_GSM.size();k++){
					for(int l=0;l<tacstat_timesectioncell[hn][i].B_IMEI_IMSI_GSM[k].size();l++){
						fo<<tacstat_timesectioncell[hn][i].B_IMEI_IMSI_GSM[k][l].IMEI<<";"<<tacstat_timesectioncell[hn][i].B_IMEI_IMSI_GSM[k][l].IMSI<<";";
					}
				}
				fo<<",";
				for(int k=0;k<tacstat_timesectioncell[hn][i].B_IMEI_IMSI_TD.size();k++){
					for(int l=0;l<tacstat_timesectioncell[hn][i].B_IMEI_IMSI_TD[k].size();l++){
						fo<<tacstat_timesectioncell[hn][i].B_IMEI_IMSI_TD[k][l].IMEI<<";"<<tacstat_timesectioncell[hn][i].B_IMEI_IMSI_TD[k][l].IMSI<<";";
					}
				}
				fo<<endl;
			}
		}
	}
	fo.close();
	return true;
}