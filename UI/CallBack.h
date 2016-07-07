#ifndef _CALLBACK_H_
#define _CALLBACK_H_


#define SHM_SIZE 4096

typedef struct
{
    char send_connect[10];		//��������
    char have_connect[10];		//�ɹ���¼
	char send_bag[10];			//���ͽ���
	char rec_bag[10];			//�յ�����
	char business_OK[10];		//���׳ɹ�
	char business_FAIL[10];		//����ʧ��
	char debug_time[10];			//����ʱ��
	char debug_sum[10];			//��������
	char debug_interval[10];		//���Լ��
	bool isAnswer;				//�Ƿ�Ӧ��
	bool use_card;				//�Ƿ��ֵ
	bool buy_card;				//�Ƿ���
	bool phone_last;			//�Ƿ����
	bool phone_blur;			//�Ƿ��˵�
	bool phone_particular;		//�Ƿ��굥
    bool isBreak;				//�Ƿ��ж�
	bool isOK;					//�Ƿ�OK
}SHM_MESSAGE;


void CALLBACK_forward_init();			//��ʼ������

void CALLBACK_shm_create();				//�����ڴ�Ĵ���

void CALLBACK_shm_memset();				//�����ڴ������

void* CALLBACK_time_refresh(void *argv);		//ʱ��ˢ��

void* CALLBACK_form_init(void *form_control);		//��������

int CALLBACK_start_debug(void *form_control);		//��ʼ���Իص�

int CALLBACK_parameter(void* control,int eventID);	//��ʼ���԰�ť���¼�

int CALLBACK_stop_debug(void *form_control);		//��ͣ����

int CALLBACK_write_debug(void *form_control);		//д���ļ�

int CALLBACK_end_debug(void *form_control);			//�˳�

int CALLBACK_debug(void* control,int eventID);		//�ص�



#endif

