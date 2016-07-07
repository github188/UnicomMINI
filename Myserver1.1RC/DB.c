/******************************************************************\
* ��Ȩ���� (C)2011, by Tristone
* �ļ����ƣ� DB.c
*
* ����ժҪ�� implementation for the DB module
*
* ��ʷ��
*�������ڣ�2011-8-20
*�����ˣ�	����
\******************************************************************/

#include "DB.h"

sqlite3 *pDB = NULL;
//sqlite3���ݿ���
pthread_mutex_t db_mutex =  PTHREAD_MUTEX_INITIALIZER;

int DB_open(const char *filename)
{
	//pFile = filename;
	
	int err;
	err = sqlite3_open(filename, &pDB);
	return err;			//����0�ɹ��������
}

int DB_close()
{
	int err;
	err = sqlite3_close(pDB);
	return err;
}

/***************************************\
*��������DB_exec
*
*���ܣ�ִ��SQL���
*
*������
*	1.statement--Ҫִ�е�SQL���
*	2.cbFunc--ָ��Ҫ�ص��ĺ�����ָ��
*	3.context--���ݸ��ص������ĵ�һ������
*	4.errmsg--������Ϣ����
*
*����ֵ��0--�ɹ� !0--ʧ��
*
*˵�������ûص�ʱ�ڶ�������������ΪNULL
*	����Ҫ������ϢʱerrmsgҲ����ΪNULL
****************************************/
int DB_exec(const char *statement, ClBck cbFunc, void* context, char *errmsg)
{
	int err;
	pthread_mutex_lock(&db_mutex);
	err = sqlite3_exec(pDB, statement, cbFunc, context, &errmsg);
	pthread_mutex_unlock(&db_mutex);
	if (errmsg)
	{
		sqlite3_free(errmsg);
	}
	
	return err;

}


