#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <semaphore.h>
#include "Service.h"

// #ifdef _GLOBAL_
// #define EXTERN_FU
// #else
// #define EXTERN_FU extern
// #endif
// 

//�����
static int for_send_num = 0;

//�ļ�����ģ����������
static pthread_mutex_t mutex_send;
static pthread_cond_t cond_send;

//�ж���������
static pthread_mutex_t mutex_break;
static pthread_cond_t cond_break;;

//�ļ�����ģ����������
static pthread_mutex_t mutex_rec;
static pthread_cond_t cond_rec;

//�����ڴ�
static SHM_MESSAGE *stu_info=NULL;

//�ж��Ƿ�����Ӧ��
static bool server_answer = false;


//������
static pthread_mutex_t  mutex_shm;		//������
static sem_t empty_shm;



#endif

