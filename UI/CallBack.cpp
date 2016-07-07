/**********************************************************************

*�ļ�����
		CallBack.cpp
*�ļ�������
		ҵ����
*�����ߣ�
		�Ʊ�

*����ʱ�䣺
    2011-8-5


******************************************************************/

#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "CallBack.h"
#include "Button.h"
#include "Lable.h"
#include "Refresh.h"
#include "Dialogue.h"
#include "Form.h"
#include "global.h"

/*****************************
*��������CALLBACK_forward_init
*���ܣ������ڴ洴��
*��������
*����ֵ:��
******************************/
void CALLBACK_forward_init()
{
	//���������ڴ�
	CALLBACK_shm_create();

	//����ģ���ʼ��
	pthread_t thread_time;
	pthread_create(&thread_time,NULL,CALLBACK_time_refresh,NULL);
}


/*****************************
*��������CALLBACK_shm_create
*���ܣ������ڴ洴��
*��������
*����ֵ:��
******************************/
void CALLBACK_shm_create()
{
	int shm_id;
    void *shm_addr = NULL;
    shm_id = shmget((key_t)1111,SHM_SIZE,0666|IPC_CREAT);
    if(shm_id < 0)
    {
        perror("shm_id");
        exit(0);
    }
    shm_addr = shmat(shm_id,NULL,0);
    stu_info = (SHM_MESSAGE *)shm_addr;

	CALLBACK_shm_memset();
}

/*****************************
*��������CALLBACK_shm_memset
*���ܣ�Ϊ�����ڴ��ʼ��
*��������
*����ֵ:��
******************************/
void CALLBACK_shm_memset()
{
	memset(stu_info,0,sizeof(SHM_MESSAGE));


	strcpy(stu_info->send_connect,"0\0");
	strcpy(stu_info->have_connect,"0\0");
	strcpy(stu_info->business_OK,"0\0");
	strcpy(stu_info->business_FAIL,"0\0");
	strcpy(stu_info->send_bag,"0\0");
	strcpy(stu_info->rec_bag,"0\0");
}


/*****************************
*��������CALLBACK_time_refresh
*���ܣ�ʱ��ˢ��
*��������
*����ֵ:��
******************************/
void* CALLBACK_time_refresh(void *argv)
{

	int t;

	while(1)
	{		
		if (stu_info->isOK && stu_info->isBreak == false)
		{
			sscanf(time_used,"%d",&t);
			sprintf(time_used,"%d",t+1);
			
			sscanf(time_left,"%d",&t);
			sprintf(time_left,"%d",t-1);
			
			//printf("%s %s",time_used,time_left);
			
			if (t == 1)
			{
				stu_info->isOK = false;
			}
		}
		
		sleep(1);
	}
	
	
}



/*****************************
*��������CALLBACK_form_init
*���ܣ����ڴ���
*��������
*����ֵ:��
******************************/
void* CALLBACK_form_init(void *form_control)
{
	CForm *form;
	CBaseControl *control;

	
	//���Խ���
    form = new CForm(24,80,0,0,CALLBACK_debug);
	
    control = new CLable("����ʱ��:",1,10,2,4);
    form->addControl(*control);
	control = new CLable(stu_info->debug_time,1,4,2,16);
    form->addControl(*control);
	
    control = new CLable("ģ���豸��:",1,12,2,26);
    form->addControl(*control);
	control = new CLable(stu_info->debug_sum,1,4,2,40);
    form->addControl(*control);
	
    control = new CLable("���ͼ��(����):",1,16,2,50);
    form->addControl(*control);
	control = new CLable(stu_info->debug_interval,1,10,2,68);
    form->addControl(*control);
	
	control = new CLable("����������:",1,14,5,2);
    form->addControl(*control);
	control = new CLable("�ɹ���¼  :",1,14,5,42);
    form->addControl(*control);
	control = new CLable("�Ѳ���ʱ��:",1,14,8,2);
    form->addControl(*control);
	control = new CLable("ʣ��ʱ��  :",1,14,8,42);
    form->addControl(*control);
	control = new CLable("���ͽ��װ�:",1,14,11,2);
    form->addControl(*control);
	control = new CLable("�յ�Ӧ���:",1,14,11,42);
    form->addControl(*control);
	control = new CLable("���׳ɹ�  :",1,14,14,2);
    form->addControl(*control);
	control = new CLable("����ʧ��  :",1,14,14,42);
    form->addControl(*control);
	
	
    control = new CButton("ֹͣ����",3,12,18,15,1);
    form->addControl(*control);
    control = new CButton("��ӡ���",3,12,18,34,2);
    form->addControl(*control);
	control = new CButton("��    ��",3,12,18,53,3);
    form->addControl(*control);

	control = new CRefresh(1,10,5,18,stu_info->send_connect);
	form->addControl(*control);
	control = new CRefresh(1,10,5,58,stu_info->have_connect);
	form->addControl(*control);
	control = new CRefresh(1,10,8,18,time_used);
	form->addControl(*control);
	control = new CRefresh(1,10,8,58,time_left);
	form->addControl(*control);
	control = new CRefresh(1,10,11,18,stu_info->send_bag);
	form->addControl(*control);
	control = new CRefresh(1,10,11,58,stu_info->rec_bag);
	form->addControl(*control);
	control = new CRefresh(1,10,14,18,stu_info->business_OK);
	form->addControl(*control);
	control = new CRefresh(1,10,14,58,stu_info->business_FAIL);
	form->addControl(*control);


	return (void *)form;
}

/*****************************
*��������CALLBACK_start_debug
*���ܣ���ʼ���Իص�
*��������
*����ֵ:��
******************************/

int CALLBACK_start_debug(void *form_control)
{
	CForm *form = (CForm *)form_control;
	CForm *form_debug;
	int nReturn ;
	int t;
	int interval;

	//��ȡ����
	strcpy(stu_info->debug_time,form->getEditCaption(1));
    strcpy(stu_info->debug_sum,form->getEditCaption(2));
	strcpy(stu_info->debug_interval,form->getEditCaption(3));

	sscanf(stu_info->debug_interval,"%d",&interval);

	if (interval == 0)
	{
		CDialogue dialogue(" ʱ �� �� �� �� �� Ϊ �� ",8,32,8,24);;
		dialogue.show();
		
		return 1;
	}

	if (strlen(stu_info->debug_time) != 0 && strlen(stu_info->debug_sum) != 0 && strlen(stu_info->debug_interval) != 0 )
	{
		//��ȡѡ���ѡ��
		stu_info->isAnswer = form->getOption(1);
		stu_info->use_card= form->getOption(2);
		stu_info->buy_card= form->getOption(3);
		stu_info->phone_last= form->getOption(4);
		stu_info->phone_blur= form->getOption(5);
		stu_info->phone_particular= form->getOption(6);

		if (stu_info->use_card == false && stu_info->buy_card == false && stu_info->phone_last == false && stu_info->phone_blur == false && stu_info->phone_particular == false)
		{
			CDialogue dialogue(" �� �� �� ѡ �� һ �� �� �� ",8,32,8,24);;
			dialogue.show();
			
			return 1;
		}


		form_debug  = (CForm *)CALLBACK_form_init(form_control);

		strcpy(time_used,"0");
		strcpy(time_left,stu_info->debug_time);

		//�������
		isDebug = 1;
		stu_info->isOK = true;
		
		nReturn = form_debug->show();

		form_debug->unshow();

		return nReturn;

	}
	else
	{
		CDialogue dialogue(" �� �� �� ȫ ",8,20,8,30);;
		dialogue.show();
		
		return 1;
	}

	
}



/*****************************
*������:CALLBACK_parameter
*���ܣ���ʼ���ԵĻص�����
*��������
*����ֵ:��
******************************/
int CALLBACK_parameter(void* control,int eventID)
{

    switch(eventID)
    {
    case 1:
        return CALLBACK_start_debug(control);
        break;
    case -1:
        return -1;
        break;


    default:
        break;
    }
}



/*****************************
*������:CALLBACK_stop_debug
*���ܣ���ͣ�Ļص�����
*��������
*����ֵ:��
******************************/
int CALLBACK_stop_debug(void *form_control)
{
	CForm *form = (CForm *)form_control;
	//�ı䰴������
	//����ˢ�¿��״̬
	if (stu_info->isOK == true)
	{
		
		if (isDebug == 1)
		{
			isDebug = 2;
			stu_info->isBreak = true;
			form->changeButtonCaption("��ʼ����",1);
			form->changeRefresh();
		}
		else if (isDebug == 2)
		{
			isDebug = 1;
			stu_info->isBreak = false;
			form->changeButtonCaption("ֹͣ����",1);
			form->changeRefresh();
		}

	}

	return 999;	
}

/*****************************
*������:CALLBACK_write_debug
*���ܣ����Ա���Ļص�����
*��������
*����ֵ:��
******************************/
int CALLBACK_write_debug(void *form_control)
{
	int fw;
	char buffer[50];
	//д�����ڼ���ָ������ݵ��ļ�
	fw = open("test.txt",O_CREAT|O_WRONLY|O_TRUNC,0711);
	if(fw < 0)
	{
		perror("open failed");
    }

	//д��
	strcpy(buffer,"����������:");
	write(fw,buffer,strlen(buffer));
	write(fw,stu_info->send_connect,strlen(stu_info->send_connect));
	strcpy(buffer,"\t�ɹ���¼:");
	write(fw,buffer,strlen(buffer));
	write(fw,stu_info->have_connect,strlen(stu_info->have_connect));
	strcpy(buffer,"\t�Ѳ���ʱ��:");
	write(fw,buffer,strlen(buffer));
	write(fw,time_used,strlen(time_used));
	strcpy(buffer,"\tʣ��ʱ��:");
	write(fw,buffer,strlen(buffer));
	write(fw,time_left,strlen(time_left));
	strcpy(buffer,"\t���ͽ��װ�:");
	write(fw,buffer,strlen(buffer));
	write(fw,stu_info->send_bag,strlen(stu_info->send_bag));
	strcpy(buffer,"\t�յ�Ӧ���:");
	write(fw,buffer,strlen(buffer));
	write(fw,stu_info->rec_bag,strlen(stu_info->rec_bag));
	strcpy(buffer,"\t���׳ɹ�:");
	write(fw,buffer,strlen(buffer));
	write(fw,stu_info->business_OK,strlen(stu_info->business_OK));
	strcpy(buffer,"\t����ʧ��:");
	write(fw,buffer,strlen(buffer));
	write(fw,stu_info->business_FAIL,strlen(stu_info->business_FAIL));

	return 999;
}

/*****************************
*������:CALLBACK_end_debug
*���ܣ��˳���ť�Ļص�����
*��������
*����ֵ:��
******************************/
int CALLBACK_end_debug(void *form_control)
{
	CForm *form = (CForm *)form_control;

	//����ˢ�¿��Ƿ�ˢ��
	if (isDebug == 1)
	{
		form->changeRefresh();
	}
	isDebug = 0;
	
	//����ˢ�¿��߳̿���
	form->closeRefresh();
	
	CALLBACK_shm_memset();

	return 0;
}


/*****************************
*������:CALLBACK_debug
*���ܣ����Բ�������Ļص�����
*��������
*����ֵ:��
******************************/
int CALLBACK_debug(void* control,int eventID)
{

    switch(eventID)
    {
    case 1:
        return CALLBACK_stop_debug(control);
        break;
    case 2:
        return CALLBACK_write_debug(control);
        break;
	case 3:
        return CALLBACK_end_debug(control);
		break;
    default:
        break;
    }
}
