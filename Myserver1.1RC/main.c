/******************************************************************\
* ��Ȩ���� (C)2011, by Tristone
* �ļ����ƣ� main.c
*
* ����ժҪ�� main function
*
* ��ʷ��
*�������ڣ�2011-8-18
*�����ˣ�	���� (Tristone)
\******************************************************************/
#include "init.h"
#include "DB.h"


int main(int argc, char* argv[])
{
	char* dbname = "mini_server.db";
	printf("use local port��%d\nuse database : /%s\n", SERVER_PORT, dbname);
	thread_init();
	DB_open(dbname);	//������argv,����չ
	socket_server_startup();




	return 0;
}










