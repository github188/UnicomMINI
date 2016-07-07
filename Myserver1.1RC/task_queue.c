/******************************************************************\
* ��Ȩ���� (C)2011, by Tristone
* �ļ����ƣ� DB.h
*
* ����ժҪ��implementation for the task_queue module
*
* ��ʷ��
*�������ڣ�2011-8-14
*�����ˣ�	����
*�������ڣ�2011-8-24
*�޸����ݣ������������б�����
*�޸��ˣ�	����
\******************************************************************/

#include "task_queue.h"

//���������
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
//�������źŵ�
//extern sem_t sem_task;

que_node* queue_add(que_node** head, que_node* tail, actual_func task_func, ser_cont context)
{
	pthread_mutex_lock(&queue_mutex);
	if (tail)
	{
		que_node* temp = tail;
		tail = malloc(sizeof(que_node));
		tail->next = temp;
		tail->pre = NULL;
		temp->pre = tail;
	}
	//tailΪNULL��Ϊ�ն���,��ӵ�һ���ڵ�
	else
	{
		tail = malloc(sizeof(que_node));
		*head = tail;
		tail->next = NULL;
		tail->pre = NULL;
	}
	tail->actual_task = task_func;
	tail->context = context;
	//sem_post(&sem_task);
	pthread_mutex_unlock(&queue_mutex);
	return tail;
}

int queue_del(que_node** head)
{
	pthread_mutex_lock(&queue_mutex);
	if (*head)
	{
		que_node *temp = *head;
		*head = temp->pre;
		free(*head);
	}
	pthread_mutex_unlock(&queue_mutex);
	return 1;
}











