#include"stdafx.h"
#include"FileWriteModule.h"
#include<omp.h>

//输出tacstat
bool WriteTACFile(std::string temp_result_path_name){
	ofstream fo(temp_result_path_name.c_str(),'w');
	if(fo.is_open()==true){
		fo<<"TAC"<<","<<"品牌"<<","<<"型号"<<","<<"类别"<<","\
			<<"CellID"<<","<<"小区分类"<<","<<"网络类型"<<","\
			<<"timeSection"<<","\
			<<"A_shortcall_1"<<","<<"A_shortcall_2"<<","<<"A_shortcall_3"<<","\
			<<"A_call_attempt"<<","<<"A_call_attempt_GSM"<<","<<"A_call_attempt_TD"<<","\
			<<"B_shortcall_1"<<","<<"B_shortcall_2"<<","<<"B_shortcall_3"<<","\
			<<"B_call_attempt"<<","<<"B_call_attempt_GSM"<<","<<"B_call_attempt_TD"<<","\
			<<"A_call_first_cell_connected"<<","<<"A_call_first_cell_connected_TD"<<","<<"A_call_first_cell_connected_GSM"<<","\
			<<"A_call_last_cell_connected"<<","<<"A_call_last_cell_connected_TD"<<","<<"A_call_last_cell_connected_GSM"<<","\
			<<"B_call_first_cell_connected"<<","<<"B_call_first_cell_connected_TD"<<","<<"B_call_first_cell_connected_GSM"<<","\
			<<"B_call_last_cell_connected"<<","<<"B_call_last_cell_connected_TD"<<","<<"B_call_last_cell_connected_GSM"<<","\
			<<"A_BSSMAP_Cause"<<","<<"A_RANAP_Cause"<<","<<"B_BSSMAP_Cause"<<","<<"B_RANAP_Cause"<<","\
			<<"A_DX_Cause_GSM"<<","<<"A_DX_Cause_TD"<<","<<"B_DX_Cause_GSM"<<","<<"B_DX_Cause_TD"<<","\
			<<endl;
		for(int hn=0;hn<tacstat.size();hn++){
			for(int i=0;i<tacstat[hn].size();i++){
				
				fo<<tacstat[hn][i].TAC<<","<<tacstat[hn][i].brand<<","<<tacstat[hn][i].name<<","<<tacstat[hn][i].type<<","\
					<<tacstat[hn][i].cellid<<","<<tacstat[hn][i].celltype<<","<<tacstat[hn][i].network<<","\
					<<tacstat[hn][i].timeSection<<","\
					<<tacstat[hn][i].A_shortcall_1<<","<<tacstat[hn][i].A_shortcall_2<<","<<tacstat[hn][i].A_shortcall_3<<","\
					<<tacstat[hn][i].A_call_attempt<<","<<tacstat[hn][i].A_call_attempt_GSM<<","<<tacstat[hn][i].A_call_attempt_TD<<","\
					<<tacstat[hn][i].B_shortcall_1<<","<<tacstat[hn][i].B_shortcall_2<<","<<tacstat[hn][i].B_shortcall_3<<","\
					<<tacstat[hn][i].B_call_attempt<<","<<tacstat[hn][i].B_call_attempt_GSM<<","<<tacstat[hn][i].B_call_attempt_TD<<","\
					<<tacstat[hn][i].A_call_first_cell_connected<<","<<tacstat[hn][i].A_call_first_cell_connected_TD<<","<<tacstat[hn][i].A_call_first_cell_connected_GSM<<","\
					<<tacstat[hn][i].A_call_last_cell_connected<<","<<tacstat[hn][i].A_call_last_cell_connected_TD<<","<<tacstat[hn][i].A_call_last_cell_connected_GSM<<","\
					<<tacstat[hn][i].B_call_first_cell_connected<<","<<tacstat[hn][i].B_call_first_cell_connected_TD<<","<<tacstat[hn][i].B_call_first_cell_connected_GSM<<","\
					<<tacstat[hn][i].B_call_last_cell_connected<<","<<tacstat[hn][i].B_call_last_cell_connected_TD<<","<<tacstat[hn][i].B_call_last_cell_connected_GSM<<","\
					;
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
				fo<<endl;
			}
		}
	}
	fo.close();
	return true;
}
//------------------输出合并结果-------------
//输出tacstat_timesection
bool WriteTACFile_TimeSection(std::string temp_result_path_name){
	ofstream fo(temp_result_path_name.c_str(),'w');
	if(fo.is_open()==true){
		fo<<"TAC"<<","<<"品牌"<<","<<"型号"<<","<<"类别"<<","\
			<<"CellID"<<","<<"小区分类"<<","<<"网络类型"<<","\
			<<"A_shortcall_1"<<","<<"A_shortcall_2"<<","<<"A_shortcall_3"<<","\
			<<"A_call_attempt"<<","<<"A_call_attemp_GSM"<<","<<"A_call_attemp_TD"<<","\
			<<"B_shortcall_1"<<","<<"B_shortcall_2"<<","<<"B_shortcall_3"<<","\
			<<"B_call_attempt"<<","<<"B_call_attemp_GSM"<<","<<"B_call_attemp_TD"<<","\
			<<"A_BSSMAP_drop"<<","<<"A_RANAP_drop"<<","<<"B_BSSMAP_drop"<<","<<"B_RANAP_drop"<<","\
			<<"A_DX_GSM_block"<<","<<"A_DX_TD_block"<<","<<"B_DX_GSM_block"<<","<<"B_DX_TD_block"<<","\
			<<"A_call_first_cell_connected"<<","<<"A_call_first_cell_connected_TD"<<","<<"A_call_first_cell_connected_GSM"<<","\
			<<"A_call_last_cell_connected"<<","<<"A_call_last_cell_connected_TD"<<","<<"A_call_last_cell_connected_GSM"<<","\
			<<"B_call_first_cell_connected"<<","<<"B_call_first_cell_connected_TD"<<","<<"B_call_first_cell_connected_GSM"<<","\
			<<"B_call_last_cell_connected"<<","<<"B_call_last_cell_connected_TD"<<","<<"B_call_last_cell_connected_GSM"<<","\
			<<endl;
		for(int hn=0;hn<tacstat_timesection.size();hn++){
			for(int i=0;i<tacstat_timesection[hn].size();i++){

				fo<<tacstat_timesection[hn][i].TAC<<","<<tacstat_timesection[hn][i].brand<<","<<tacstat_timesection[hn][i].name<<","<<tacstat_timesection[hn][i].type<<","\
					<<tacstat_timesection[hn][i].cellid<<","<<tacstat_timesection[hn][i].celltype<<","<<tacstat_timesection[hn][i].network<<","\
					<<tacstat_timesection[hn][i].A_shortcall_1<<","<<tacstat_timesection[hn][i].A_shortcall_2<<","<<tacstat_timesection[hn][i].A_shortcall_3<<","\
					<<tacstat_timesection[hn][i].A_call_attempt<<","<<tacstat_timesection[hn][i].A_call_attempt_GSM<<","<<tacstat_timesection[hn][i].A_call_attempt_TD<<","\
					<<tacstat_timesection[hn][i].B_shortcall_1<<","<<tacstat_timesection[hn][i].B_shortcall_2<<","<<tacstat_timesection[hn][i].B_shortcall_3<<","\
					<<tacstat_timesection[hn][i].B_call_attempt<<","<<tacstat_timesection[hn][i].B_call_attempt_GSM<<","<<tacstat_timesection[hn][i].B_call_attempt_TD<<","\
					<<tacstat_timesection[hn][i].A_BSSMAP_drop<<","<<tacstat_timesection[hn][i].A_RANAP_drop<<","<<tacstat_timesection[hn][i].B_BSSMAP_drop<<","<<tacstat_timesection[hn][i].B_RANAP_drop<<","\
					<<tacstat_timesection[hn][i].A_DX_GSM_block<<","<<tacstat_timesection[hn][i].A_DX_TD_block<<","<<tacstat_timesection[hn][i].B_DX_GSM_block<<","<<tacstat_timesection[hn][i].B_DX_TD_block<<","\
					<<tacstat_timesection[hn][i].A_call_first_cell_connected<<","<<tacstat_timesection[hn][i].A_call_first_cell_connected_TD<<","<<tacstat_timesection[hn][i].A_call_first_cell_connected_GSM<<","\
					<<tacstat_timesection[hn][i].A_call_last_cell_connected<<","<<tacstat_timesection[hn][i].A_call_last_cell_connected_TD<<","<<tacstat_timesection[hn][i].A_call_last_cell_connected_GSM<<","\
					<<tacstat_timesection[hn][i].B_call_first_cell_connected<<","<<tacstat_timesection[hn][i].B_call_first_cell_connected_TD<<","<<tacstat_timesection[hn][i].B_call_first_cell_connected_GSM<<","\
					<<tacstat_timesection[hn][i].B_call_last_cell_connected<<","<<tacstat_timesection[hn][i].B_call_last_cell_connected_TD<<","<<tacstat_timesection[hn][i].B_call_last_cell_connected_GSM<<","\
					;
					
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
			<<"A_shortcall_1"<<","<<"A_shortcall_2"<<","<<"A_shortcall_3"<<","\
			<<"A_call_attempt"<<","<<"A_call_attemp_GSM"<<","<<"A_call_attemp_TD"<<","\
			<<"B_shortcall_1"<<","<<"B_shortcall_2"<<","<<"B_shortcall_3"<<","\
			<<"B_call_attempt"<<","<<"B_call_attemp_GSM"<<","<<"B_call_attemp_TD"<<","\
			<<"A_BSSMAP_drop"<<","<<"A_RANAP_drop"<<","<<"B_BSSMAP_drop"<<","<<"B_RANAP_drop"<<","\
			<<"A_DX_GSM_block"<<","<<"A_DX_TD_block"<<","<<"B_DX_GSM_block"<<","<<"B_DX_TD_block"<<","\
			<<"A_call_first_cell_connected"<<","<<"A_call_first_cell_connected_TD"<<","<<"A_call_first_cell_connected_GSM"<<","\
			<<"A_call_last_cell_connected"<<","<<"A_call_last_cell_connected_TD"<<","<<"A_call_last_cell_connected_GSM"<<","\
			<<"B_call_first_cell_connected"<<","<<"B_call_first_cell_connected_TD"<<","<<"B_call_first_cell_connected_GSM"<<","\
			<<"B_call_last_cell_connected"<<","<<"B_call_last_cell_connected_TD"<<","<<"B_call_last_cell_connected_GSM"<<","\
			<<endl;
		for(int hn=0;hn<tacstat_timesectioncell.size();hn++){
			for(int i=0;i<tacstat_timesectioncell[hn].size();i++){
				fo<<tacstat_timesectioncell[hn][i].TAC<<","<<tacstat_timesectioncell[hn][i].brand<<","<<tacstat_timesectioncell[hn][i].name<<","<<tacstat_timesectioncell[hn][i].type<<","\
					<<tacstat_timesectioncell[hn][i].A_shortcall_1<<","<<tacstat_timesectioncell[hn][i].A_shortcall_2<<","<<tacstat_timesectioncell[hn][i].A_shortcall_3<<","\
					<<tacstat_timesectioncell[hn][i].A_call_attempt<<","<<tacstat_timesectioncell[hn][i].A_call_attempt_GSM<<","<<tacstat_timesectioncell[hn][i].A_call_attempt_TD<<","\
					<<tacstat_timesectioncell[hn][i].B_shortcall_1<<","<<tacstat_timesectioncell[hn][i].B_shortcall_2<<","<<tacstat_timesectioncell[hn][i].B_shortcall_3<<","\
					<<tacstat_timesectioncell[hn][i].B_call_attempt<<","<<tacstat_timesectioncell[hn][i].B_call_attempt_GSM<<","<<tacstat_timesectioncell[hn][i].B_call_attempt_TD<<","\
					<<tacstat_timesectioncell[hn][i].A_BSSMAP_drop<<","<<tacstat_timesectioncell[hn][i].A_RANAP_drop<<","<<tacstat_timesectioncell[hn][i].B_BSSMAP_drop<<","<<tacstat_timesectioncell[hn][i].B_RANAP_drop<<","\
					<<tacstat_timesectioncell[hn][i].A_DX_GSM_block<<","<<tacstat_timesectioncell[hn][i].A_DX_TD_block<<","<<tacstat_timesectioncell[hn][i].B_DX_GSM_block<<","<<tacstat_timesectioncell[hn][i].B_DX_TD_block<<","\
					<<tacstat_timesectioncell[hn][i].A_call_first_cell_connected<<","<<tacstat_timesectioncell[hn][i].A_call_first_cell_connected_TD<<","<<tacstat_timesectioncell[hn][i].A_call_first_cell_connected_GSM<<","\
					<<tacstat_timesectioncell[hn][i].A_call_last_cell_connected<<","<<tacstat_timesectioncell[hn][i].A_call_last_cell_connected_TD<<","<<tacstat_timesectioncell[hn][i].A_call_last_cell_connected_GSM<<","\
					<<tacstat_timesectioncell[hn][i].B_call_first_cell_connected<<","<<tacstat_timesectioncell[hn][i].B_call_first_cell_connected_TD<<","<<tacstat_timesectioncell[hn][i].B_call_first_cell_connected_GSM<<","\
					<<tacstat_timesectioncell[hn][i].B_call_last_cell_connected<<","<<tacstat_timesectioncell[hn][i].B_call_last_cell_connected_TD<<","<<tacstat_timesectioncell[hn][i].B_call_last_cell_connected_GSM<<","\
					;
				fo<<endl;
			}
		}
	}
	fo.close();
	return true;
}