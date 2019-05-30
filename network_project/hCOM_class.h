#pragma once
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include "Serial_Com_func.h"
#include <string>

using namespace std;

class hCOM_class
{
private:
	char get_data[6];
	HANDLE	m_hCom;		// SerialComPort_Handle
	char recv_buf[32];
	int recv_cnt ;
	string header;
	int parsed_data;
	int switch_status ;
	int COM_SPEED ;
public:
	hCOM_class();
	~hCOM_class();
	void get_packet();
	void parse_packet();
	inline HANDLE get_handle(){ return m_hCom; };
	inline int get_parsed_data(){ return parsed_data; };
	inline int get_switch_status() { return switch_status; };
};

