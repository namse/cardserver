// CardServer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "WebSocketServer.cpp"
int _tmain(int argc, _TCHAR* argv[])
{
	WebSocketServer	server;
	server.main();
	return 0;
}

