#define _CRT_SECURE_NO_WARNINGS
#include "hCOM_class.h"


hCOM_class::hCOM_class()
{
	char com_port[5] = "COM5";
	fill_n(recv_buf, 32, '\0');
	strcpy(get_data,"GD");
	parsed_data = 0;
	recv_cnt = 0;
	switch_status = 0;
	COM_SPEED = 38400;
	m_hCom = Com_Init(com_port, COM_SPEED, 8, 1, 0, 1, 1, 1, 1, 0);   // Serial Port Init
}


hCOM_class::~hCOM_class()
{
	Com_Close(m_hCom);
}

void hCOM_class::get_packet() {
	fill_n(recv_buf, 32, '\0');

	Com_SendStr(m_hCom, get_data, sizeof(get_data));
	recv_cnt = 7;
	Com_RecvStr(m_hCom, recv_buf, &recv_cnt);
	if (recv_cnt > 0) {
		parse_packet();
	}
}

void hCOM_class::parse_packet() {
	
	string packet = static_cast<string>(recv_buf);
	if (packet != "") {
		header = packet.substr(0, 2);
		parsed_data = stoi(packet.substr(2, 3));

		if (header.at(1) == 'M') {
			parsed_data *= -1;
		}
		switch_status = atoi(packet.substr(5, 6).c_str());
		cout << "packets:" << packet << endl;
	}
	
	
	return;
}
