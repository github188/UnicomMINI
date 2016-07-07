/******************************************************************\
* ��Ȩ���� (C)2011, by Tristone
* �ļ����ƣ� thread_pool.c
*
* ����ժҪ�� implementation for the ThreadPool module
*				
* ��ʷ��
*�������ڣ�2011-8-19
*�����ˣ�	����
*�޶���ʷ: 2011-8-23
*�޶���:	����
*�޶�����:�Ľ�����ʵ��
\******************************************************************/

#include "thread_pool.h"
#include "init.h"

//�̳߳ص�ַ
thread_pool* pool = NULL;
//�߳�״̬λͼ�ṹ
char thread_stat[THREAD_NUM];
//����߳�ID
pthread_t breathe_id = 0;
//�����������źŵ�
//sem_t sem_task;

void thread_init()
{
	int i;
	int shm_id;
	void* shm_addr = NULL;

	//�������������߳�
	pthread_create(&breathe_id, NULL, monitor, NULL);

	//pthread_create(&breathe_id, NULL, fix, NULL);

	//����ؿռ�
	pool = (thread_pool*)malloc(sizeof(thread_pool));

	//sem_init(&sem_task, 0, 0);
	
	memset(pool, 0, sizeof(thread_pool));
	//��������߳̿ռ�
	pool->pool_threads = (thread_info*)malloc(sizeof(thread_info) * THREAD_NUM);

	//�����߳�
	for (i = 0; i < THREAD_NUM; i++)
	{
		pool->pool_threads[i].index = i;
		pthread_create(&(pool->pool_threads[i].thread_id), NULL, routine_func, (void*)(&pool->pool_threads[i].index));
	}
	//���ó��������߳�״̬,0-idle,1-busy
	memset(thread_stat, 0, sizeof(thread_stat));
}

void* routine_func(void* context)
{
	
	int index = *((int*)context);
	pthread_mutex_init(&pool->pool_threads[index].mutex_id, NULL);		
	pthread_cond_init(&pool->pool_threads[index].cond_id, NULL);
	pthread_mutex_lock(&pool->pool_threads[index].mutex_id);
	ser_cont task_context;
	actual_func actual_task = NULL;
	while(1)
	{
		//�߳̿�ʼ��˯�ߵȴ�����
		pthread_cond_wait(&pool->pool_threads[index].cond_id, &pool->pool_threads[index].mutex_id);
		//sem_wait(&sem_task);
		//printf("thread %d is running..\n", pool->pool_threads[index].index);
		if (pool->que_head)
		{
			//ȡ���������Ͳ���
			actual_task = pool->que_head->actual_task;
			task_context = pool->que_head->context;
			//����������������ɾ��
			queue_del(&pool->que_head);
			//ִ������
			actual_task(task_context);
		}
		thread_stat[index] = THREAD_IDLE;
	}



}







