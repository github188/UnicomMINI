/**********************************************************************

*�ļ�����
		Dialogu.cpp
*�ļ�������
		CDialogu��ķ�װ
*�����ߣ�
		�Ʊ�

*����ʱ�䣺
2011-8-9

******************************************************************/


#include "Dialogue.h"

CDialogue::CDialogue(const char *caption,int height,int width,int scry,int scrx):CLable(caption,height,width,scry,scrx)
{
	this->pWin =NULL;
	this->nIndex = 0;
}

CDialogue::~CDialogue()
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
void CDialogue::draw()
{
	this->pWin = newwin(this->m_iHeight,this->m_iWidth,this->m_iStarty,this->m_iStartx);
	wbkgd(this->pWin,COLOR_PAIR(3));
	mvwprintw(this->pWin,this->m_iHeight/2,(this->m_iWidth-strlen(acCaption))/2,"%s",this->acCaption);
	wrefresh(this->pWin);
}

/*****************************
*��������getControlType
*���ܣ���������
*��������
*����ֵ:����ֵ
******************************/
int CDialogue::getControlType()
{
	return DIALOGUE;
}

/*****************************
*��������show
*���ܣ��������ڲ�����
*��������
*����ֵ:����ֵ
******************************/
void CDialogue::show()
{
	this->draw();

	this->driver(1);
}




/*****************************
*��������driver
*���ܣ�����
*��������
*����ֵ:��
******************************/
int CDialogue::driver(int KeyNum)
{
    curs_set(0);
	sleep(1);
}

