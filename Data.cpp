#include "all_head.h"

// 这个是要修改的，要能根据场景加入损坏的线路
void DRCdata::Damage_RC_data_assign(vector<int> broken_info ) {

	// 此版本修改：取消了修复时间，损坏线路不会修复
	//vector<vector<int>> all_bline1 = { {1,2},{19,20},{23,24},{11,12},{15,16},{29,30},{6,26},{31,32} };
	vector<vector<int>> all_bline1;
	vector<vector<int>> line_node_pair;
	line_node_pair = { {1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11},{11,12},{12,13},{13,14},{14,15},{15,16},{16,17},{17,18},{2,19},{19,20},{20,21},{21,22},{3,23},{23,24},{24,25},{6,26},{26,27},{27,28},{28,29},{29,30},{30,31},{31,32},{32,33},{8,21},{9,15},{12,22},{18,33},{25,29} };
	for (int i = 0; i < broken_info.size(); i++) {
		if (broken_info[i] == 0)
			all_bline1.push_back(line_node_pair[i]);
	}

	vector<BrokeLine> all_bl_BrokeLine;
	for (size_t i_bl = 0; i_bl < all_bline1.size(); ++i_bl) {
		BrokeLine temp_bl_BrokeLine;
		temp_bl_BrokeLine.b_node = all_bline1[i_bl][0];
		temp_bl_BrokeLine.e_node = all_bline1[i_bl][1];
		all_bl_BrokeLine.push_back(temp_bl_BrokeLine);
	}
	all_bline = all_bl_BrokeLine;
}

void RDNData::dn_default_data_assign(int new_R, double new_CR, bool distributed) {

	R = new_R;					//租借车辆数
	CR = new_CR;					//租金
	// Variable intialize
	double S_base;			// MW
	double V_base;		// kV
	double X_base;
	// DLine
	int line_num;
	vector<vector<int>> line_node_pair;
	vector<double> line_R;		// ohm
	vector<double> line_X;		// ohm
	vector<double> line_S_max;		// kVA
	// DNode
	int node_num;
	vector<double> node_Pl; // Load P, MW
	vector<double> node_Ql; // Load Q, MVar
	vector<double> node_V_min;
	vector<double> node_V_max;
	vector<double> node_factor;
	double V_ref = 1.2; // The reference voltage for power supplying node
	vector<double> node_per_value;

	// Feeder
	int FD_num;
	vector<int> FD_loc;

	// SRC at different time t
	vector<int> AllSrc;

	// Charging Station
	vector<int> AllStation;
	vector<int> Station_capacity;
	vector<int> Station_EB_num;
	vector<double> Station_Pbus_max;
	vector<int> Station_EB_min;

	// EB attr
	/*int EB_num;
	vector<int> EB_depot_id;
	vector<double> EB_batterycap;
	vector<double> EB_P_ch;
	vector<double> EB_P_dch;
	vector<double> EB_soc_max;
	vector<double> EB_soc_min;
	vector<double> EB_ch_eff;
	vector<double> EB_dch_eff;
	vector<double> EB_soc_on_road;*/
	//int EB_depot_id;
	//double EB_soc_on_road; 



	// Time intervals
	intervals = 6;
	int time_min = 5;	//min

	// Cases

	S_base = 100;			// MW
	V_base = 12.66;		// kV
	X_base = V_base * V_base / S_base;

	// Branch data
	line_num = 37;
	line_node_pair = { {1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11},{11,12},{12,13},{13,14},{14,15},{15,16},{16,17},{17,18},{2,19},{19,20},{20,21},{21,22},{3,23},{23,24},{24,25},{6,26},{26,27},{27,28},{28,29},{29,30},{30,31},{31,32},{32,33},{8,21},{9,15},{12,22},{18,33},{25,29} };
	line_R = { 0.0922,0.4930,0.3660,0.3811,0.8190,0.1872,0.7114,1.0300,1.0440,0.1966,0.3744,1.4680,0.5416,0.5910,0.7463,1.2890,0.7320,0.1640,1.5042,0.4095,0.7089,0.4512,0.8980,0.8960,0.2030,0.2842,1.0590,0.8042,0.5075,0.9744,0.3105,0.3410,2.0000,2.0000,2.0000,0.5000,0.5000 };
	line_X = { 0.0470,0.2511,0.1864,0.1941,0.7070,0.6188,0.2351,0.7400,0.7400,0.0650,0.1238,1.1550,0.7129,0.5260,0.5450,1.7210,0.5740,0.1565,1.3554,0.4784,0.9373,0.3083,0.7091,0.7011,0.1034,0.1447,0.9337,0.7006,0.2585,0.9630,0.3619,0.5302,2.0000,2.0000,2.0000,0.5000,0.5000 };
	vector<double> temp_line_S_max(line_num, 1);		// 1p.u.
	line_S_max = temp_line_S_max;
	for (size_t i_l = 0; i_l < line_num; ++i_l) {
		line_R[i_l] = line_R[i_l] / X_base;
		line_X[i_l] = line_X[i_l] / X_base;
	}

	// Bus data
	node_num = 33;
	//          1   2    3   4   5    6	  7    8    9  10  11  12  13   14  15  16  17  18  19  20  21  22  23  24    25  26  27  28   29   30  31   32   33
	node_Pl = { 0, 100, 90, 120, 70, 60, 200, 200, 60, 60, 45, 60, 60, 120, 60, 60, 60, 90, 90, 90, 90, 90, 90, 420, 420, 60, 60, 60, 120, 200, 150, 210, 60 };	// kW
	node_Ql = { 0, 60, 40,  80,  30, 20, 100, 100, 20, 20, 30, 35, 35, 80,  10, 20, 20, 40, 40, 40, 40, 40, 50, 200, 200, 25, 25, 20,  70, 600,  70, 100, 40 };			// Load Q, kVar
	vector<double> t_node_V_min(node_num, 0.9);
	vector<double> t_node_V_max(node_num, 1.1);
	vector<double> t_node_factor(node_num, 0.9);
	node_V_min = t_node_V_min;
	node_V_max = t_node_V_max;
	node_factor = t_node_factor;
	V_ref = 1.2;
	//				   1  2  3  4  5  6  7  8  9  10 11  12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33
	node_per_value = { 9, 2, 2, 8, 7, 5, 3, 2, 2, 1, 12, 3, 5, 6, 9, 9, 1, 8, 3, 4, 7, 8, 2, 5, 5, 2, 8, 4, 6, 6, 6, 9, 7 };		// $/kWh 
	for (size_t i_n = 0; i_n < node_num; ++i_n) {
		node_Pl[i_n] = node_Pl[i_n] / 1000 / S_base;
		node_Ql[i_n] = node_Ql[i_n] / 1000 / S_base;
	}

	// Feeder
	FD_num = 1;
	FD_loc = { 1 };

	if (distributed == 1)
		AllSrc = { 1,9,18,29 };
	else
		AllSrc = { 1 };


	// Charging Station
	AllStation = { 15, 20 };
	Station_capacity = { 15, 25 };
	Station_EB_num = { 40, 60 };
	Station_EB_min = { 10, 20 };

	EB_batterycap = double(160) / 1000 / S_base;		//kWh
	EB_P_ch = double(80) / 1000 / S_base;				//kW
	EB_P_dch = double(80) / 1000 / S_base;
	EB_soc0 = 0.6;
	EB_soc_max = 0.8;
	EB_soc_min = 0.2;
	EB_ch_eff = 0.8;
	EB_dch_eff = 0.8;



	//==================================================================
	// Value assignment for AllNode obj
	for (size_t i_node = 0; i_node < node_num + 1; ++i_node)
	{	// Virtual node has been taken into account
		AllNode temp_all_node;
		if (i_node == 0)
		{	// Virtual node
			temp_all_node.node_id = i_node;
			temp_all_node.node_name = to_string(i_node);
		}
		else
		{
			temp_all_node.node_id = i_node;
			temp_all_node.node_name = to_string(i_node);
			temp_all_node.p_load = node_Pl[i_node - 1];
			temp_all_node.q_load = node_Ql[i_node - 1];
			temp_all_node.V_min = node_V_min[i_node - 1];
			temp_all_node.V_max = node_V_max[i_node - 1];
			temp_all_node.factor = node_factor[i_node - 1];
			temp_all_node.weight = node_per_value[i_node - 1];
		}
		all_node.push_back(temp_all_node);
	}
	// Value assignment for DSLine obj
	for (size_t i_line = 0; i_line < line_num; ++i_line)
	{
		DSLine temp_DS_line;
		temp_DS_line.line_id = i_line;
		temp_DS_line.node_1_id = line_node_pair[i_line][0];
		temp_DS_line.node_1_name = all_node[temp_DS_line.node_1_id].node_name;
		temp_DS_line.node_2_id = line_node_pair[i_line][1];
		temp_DS_line.node_2_name = all_node[temp_DS_line.node_2_id].node_name;

		string temp_line_name = "line_" + temp_DS_line.node_1_name + "_" + temp_DS_line.node_2_name;
		temp_DS_line.line_name = temp_line_name;
		temp_DS_line.R = line_R[i_line];
		temp_DS_line.X = line_X[i_line];
		temp_DS_line.S_max = line_S_max[i_line];
		all_ds_line.push_back(temp_DS_line);
	}

	// Value assignment for Feeder obj
	for (size_t i_fd = 0; i_fd < FD_num; ++i_fd)
	{
		FDnode temp_fd;
		temp_fd.node_id = FD_loc[i_fd];
		temp_fd.node_name = all_node[temp_fd.node_id].node_name;
		all_feeder.push_back(temp_fd);
	}
	// Value assignment for set of source node at different time section
	all_power = AllSrc;

	// Value assignment for Virtual line
	for (size_t i_po = 0; i_po < AllSrc.size(); ++i_po)
	{
		VirtualLine temp_vline;
		temp_vline.vline_id = i_po;
		temp_vline.node_1_id = 0;
		temp_vline.node_2_id = AllSrc[i_po];
		all_v_line.push_back(temp_vline);
	}

	// Value assignment for Charging Station
	for (size_t i_s = 0; i_s < AllStation.size(); ++i_s)
	{
		ChargSNode temp_station;
		temp_station.station_id = i_s;
		temp_station.node_id = AllStation[i_s];
		temp_station.Capacity = Station_capacity[i_s];
		temp_station.node_name = all_node[temp_station.node_id].node_name;
		temp_station.EB_num = Station_EB_num[i_s];
		temp_station.EB_min = Station_EB_min[i_s];
		temp_station.P_bus_max = EB_P_ch * temp_station.Capacity * 0.8;		//可修改
		temp_station.P_bus_min = temp_station.P_bus_max * temp_station.EB_min / temp_station.EB_num;	//可修改

		all_station.push_back(temp_station);
	}
}



