#include <windows.h>
#include <string.h>


HANDLE Com_Init(
	char *portname,
	int speed,
	int numbit,
	int stopbit,
	int  parity,		// parity on(1) / off(0)
	int flow,
	int timeoutinterval,
	int timeoutconst,
	int timeoutmult,
	BOOL fOutxCtsFlow
);

void Com_Close(HANDLE hCom);
void Com_SendStr(HANDLE hCom, char *str, int len);
void Com_RecvStr(HANDLE hCom, char *str, int *len);



