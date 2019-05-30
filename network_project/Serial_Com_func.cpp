#include "Serial_Com_func.h"
//----------------------------------------------------------
// 車体との通信パラメータ 後でconrol.prm へ


//=============================================================================================================
//=============================================================================================================

// RS232C 通信を行うための関数群
// 指定された名前のシリアルポートを初期化し、HANDLEを返す。
// 失敗したら(HANDLE)INVALID_HANDLE_VALUEを返す。


//================================
//	Com Port のオープン＆初期化
//--------------------------------
//	引数	ComPort 名  例： "COM8" など
//			Speed	通信速度[bps]
//			numbit	通信Bit数
//			stopbit	ストップビット	// (0:1bit  1:1.5Bit   2:2Bit
//			parity	パリティ		// parity on(TRUE) / off(FALSE)
//			flow	フロー制御の有無
//			timeoutinterval
//			timeoutconst
//			timeoutmult
//			fOutxCtsFlow
//	戻り値	オープンしたCOMポートのHANDLE	失敗時はINVALID_HANDLE_VALUEを返す
//================================
HANDLE Com_Init(
			char *portname,
			int speed,
			int numbit,
			int stopbit,		
			int parity,		// parity on(TRUE) / off(FALSE)
			int flow,
			int timeoutinterval,
			int timeoutconst,
			int timeoutmult,
			BOOL fOutxCtsFlow
		)
{
	DCB		dcb;
	COMMTIMEOUTS sto;
	static const int startbit=1;
	HANDLE hCom;

	hCom = CreateFile( (LPCTSTR)portname,
			    GENERIC_READ | GENERIC_WRITE,
			    0,				// comm devices must be opened w/exclusive-access 
				NULL,			// no security attributes 
			    OPEN_EXISTING,	// comm devices must use OPEN_EXISTING 
				0,			    // not overlapped I/O 
				NULL			// hTemplate must be NULL for comm devices 
			);

	if (hCom == INVALID_HANDLE_VALUE)
	{
	    MessageBox(NULL,"Cannot get a handle",NULL,MB_OK);

	}
	else if( !GetCommState(hCom, &dcb) )
	{
	    MessageBox(NULL,"Cannot get a status",NULL,MB_OK);
		hCom = INVALID_HANDLE_VALUE;
	}
	else
	{
		dcb.BaudRate = speed;
		dcb.ByteSize = numbit;
		dcb.Parity   = parity;
		dcb.StopBits = (stopbit==1)?0:stopbit;		//DCB.StopBits:(0,1,2)=(1,1.5, 2)
		dcb.fOutxCtsFlow = fOutxCtsFlow;

		if ( !SetCommState(hCom, &dcb) )
		{
		    MessageBox(NULL,"Cannot configure ",NULL,MB_OK);
			hCom = INVALID_HANDLE_VALUE;
		}
		else
		{  //succeeds
			sto.ReadIntervalTimeout			= timeoutinterval;
			sto.ReadTotalTimeoutConstant	= timeoutconst;
			sto.ReadTotalTimeoutMultiplier	= timeoutmult;
			sto.WriteTotalTimeoutConstant	= timeoutconst;
			sto.WriteTotalTimeoutMultiplier	= timeoutmult;
			if( !SetCommTimeouts(hCom,&sto) )
			{												//fail
			    MessageBox(NULL,"Cannot set timeout",NULL,MB_OK);
				hCom = INVALID_HANDLE_VALUE;
			}
		}
	}
	return hCom;
}


//================================
//	Com Port のクローズ
//--------------------------------
//	引数	ComPortの Handle
//	戻り値	true (仮固定）
//================================
void Com_Close( HANDLE hCom )
{
	CloseHandle( hCom );

	return;
}


//==========================================
// COMポートにデータ列を出力する
//------------------------------------------
//	引数　　hCom	Comポートのハンドル
//			*str	送信したいデータ列の先頭ポインタ
//			len		送信したいデータ列の長さ[Byte]
//
//	戻り値	true 成功   / false 失敗 （ポートが開けていないなど）
//==========================================

void Com_SendStr( HANDLE hCom, char *str, int len)
{	
	DWORD	written_byte_num;

	if( hCom == INVALID_HANDLE_VALUE ) return;	//異常

	if( WriteFile(hCom, str, len, &written_byte_num ,NULL)!=0 ) //comunication succeeds
		if( written_byte_num == len ) return;			// and wrote data number is Right!
	
	return;
}


//==========================================
// COMポートから受信したデータ列を取得する
//------------------------------------------
//	引数　　hCom	Comポートのハンドル
//			*str	受信したデータ列を格納するバッファの先頭ポインタ
//			len		取得したい受信データ列の長さ[Byte]
//						この関数の実行後は，実際に取得されたデータ数が変数lenの中に格納される．
//						受信したデータ数がこの値より少なかったら，受信したデータ数文だけバッファに格納する
//	戻り値	true 成功   / false 失敗 （ポートが開けていないなど）
//==========================================

void Com_RecvStr( HANDLE hCom, char *str, int *len)
{	
	DWORD	read_byte_num;

	if( hCom == INVALID_HANDLE_VALUE ) return;	//異常

	if( ReadFile(hCom, str, *len, &read_byte_num ,NULL)!=0 )		//comunication succeeds
	{
		*len = read_byte_num;
		return;  // and wrote data number is Right!
	}

	return;
}
