/**********************************************************************

*�ļ�����
		Refresh.cpp
*�ļ�������
		CRefresh��ķ�װ
*�����ߣ�
		�Ʊ�

*����ʱ�䣺
2011-8-8

******************************************************************/

#include "Refresh.h"

CRefresh::CRefresh(int height,int width,int scry,int scrx,char *arg):CBaseControl(height,width,scry,scrx)
{
	argv = arg;
	isON = true ;
	isREFRESH = true;
	pthread_mutex_init(&mutex_id,NULL);
	pthread_cond_init(&cond_id,NULL);
}

CRefresh::~CRefresh()
{
	if (this->pWin != NULL)
	{
		delwin(this->pWin);
	}
}

/*****************************
*��������draw
*���ܣ���������
*��������
*����ֵ:��
******************************/
void CRefresh::draw()
{
	this->pWin = derwin(this->pParentControl->getWindow(),this->m_iHeight,this->m_iWidth,this->m_iStarty,this->m_iStartx);
    wrefresh(this->pWin);
	pthread_create(&pthread_id,NULL,refresh,this);

	this->sendSINGAL();
}

/*****************************
*��������getControlType
*���ܣ���������
*��������
*����ֵ:����ֵ
******************************/
int CRefresh::getControlType()
{
	return REFRESH;
}


/*****************************
*��������refresh
*���ܣ�ˢ�´���
*��������
*����ֵ:��
******************************/
void* CRefresh::refresh(void *point)
{
 	CRefresh *refresh_manager = (CRefresh *)point;
	while(refresh_manager->isON == true)
	{
		pthread_cond_wait(&refresh_manager->cond_id,&refresh_manager->mutex_id);
		while (refresh_manager->isREFRESH == true)
		{

			mvwprintw(refresh_manager->pWin,refresh_manager->m_iHeight/2,0,"%-5s",(char *)refresh_manager->argv);
			curs_set(0);
			wrefresh(refresh_manager->pWin);
			usleep(1000);
		}

	}

}



/*****************************
*��������changeREFRESH
*���ܣ�����ˢ�¿���
*��������
*����ֵ:���ڵ�״̬
******************************/
bool CRefresh::changeREFRESH()
{
	if (isREFRESH == true)
	{
		isREFRESH = false;
	}
	else
	{
		isREFRESH = true;
	}
}

/*****************************
*��������changeON
*���ܣ������߳̿���
*��������
*����ֵ:���ڵ�״̬
******************************/
bool CRefresh::changeON()
{
	isON = false;
}



/*****************************
*��������sendSINGAL
*���ܣ���������
*��������
*����ֵ:��
******************************/
void CRefresh::sendSINGAL()
{
	pthread_mutex_lock(&mutex_id);
	pthread_cond_signal(&cond_id);
	pthread_mutex_unlock(&mutex_id);
}






