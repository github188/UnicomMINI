/******************************************************************\
* ��Ȩ���� (C)2011, by Tristone
* �ļ����ƣ� DB.h
*
* ����ժҪ��interface for the DB module
*
* ��ʷ��
*�������ڣ�2011-8-14
*�����ˣ�	����
\******************************************************************/

#ifndef _DB_H_
#define _DB_H_

#include "public.h"



//exec����ĺ���ָ��
typedef int (*ClBck)(void*, int, char**, char**);
//��ʼ������һ�����ݿ�
int DB_open(const char *filename);	
//�ر����ݿ�
int DB_close();							

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
int DB_exec(const char *statement, ClBck cbFunc, void* context, char *errmsg);














#endif
