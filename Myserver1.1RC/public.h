/******************************************************************\
* ��Ȩ���� (C)2011, by Tristone
* �ļ����ƣ� public.h
*
* ����ժҪ�� ���õ�һ��ͷ�ļ��������˴󲿷ֵ��õ�Linux API�����
*	     ͷ�ļ����Լ��󲿷ֽṹ��Ķ������
*
* ��ʷ��
*�������ڣ�2011-8-13
*�����ˣ�	����
\******************************************************************/
#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include <stdio.h>
#include <pthread.h>
#include <ncurses.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sqlite3.h>
#include <errno.h>
#include <time.h>
//#include <semaphore.h>


#include "protocol.h"

#define LISTEN_QUEUE 10		//�������г���
#define THREAD_NUM 7		//��ʼ�߳���
#define SERVER_PORT 607		//�÷�����ʹ�õĶ˿�
#define CLIENT_TIMEOUT 30	//�ͻ��˳�ʱ����
#define THREAD_IDLE 0		//�߳̿���
#define THREAD_BUSY 1		//�߳�æ
#define BUF_SIZE 2048		//�����С

//�߳���������ָ��
typedef void*(*start_routine) (void*);


//����ҵ�����Ľṹ��
typedef struct service_context_t
{
	int index;
	char* recv_pack;
}ser_cont;

//ʵ�ʹ�������
typedef void (*actual_func) (ser_cont);

//������нڵ�ṹ
typedef struct que_list_node_t
{
	actual_func actual_task;	//ʵ��Ҫ�����������ָ��
	ser_cont context;		//�������������Ĳ���
	struct que_list_node_t *next;	//ָ����һ�����нڵ�
	struct que_list_node_t *pre;	//ָ����һ�����нڵ�
}que_node;

//�߳���Ϣ
typedef struct thread_info_t
{
	pthread_t thread_id;		//�߳�ID
	int index;			//�������
	pthread_mutex_t mutex_id;	//������
	pthread_cond_t cond_id;		//��������
}thread_info;

//�̳߳�
typedef struct thread_pool_t
{	
	//pthread_mutex_t mutex_id;				//������
	int idle_threads;					//���ڿ����߳���
	thread_info* pool_threads;				//ָ������̵߳�ָ��
	que_node* que_head;					//�������ͷ
	que_node* que_tail;					//�������β
}thread_pool;


#endif








