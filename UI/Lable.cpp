/**********************************************************************

*�ļ�����
		Lable.cpp
*�ļ�������
		CLable��ķ�װ
*�����ߣ�
		�Ʊ�

*����ʱ�䣺
2011-8-4

******************************************************************/

#include "Lable.h"

CLable::CLable(const char *caption,int height,int width,int scry,int scrx):CBaseControl(height,width,scry,scrx)
{
	acCaption = new char [strlen(caption) +1];
	strcpy(acCaption,caption);
}

CLable::~CLable()
{
	delete acCaption;
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
void CLable::draw()
{
	this->pWin = derwin(this->pParentControl->getWindow(),this->m_iHeight,this->m_iWidth,this->m_iStarty,this->m_iStartx);
	mvwprintw(this->pWin,this->m_iHeight/2,(this->m_iWidth-strlen(acCaption))/2,"%s",this->acCaption);
	touchwin(this->pParentControl->getWindow());
	wrefresh(this->pParentControl->getWindow());
}

/*****************************
*��������getControlType
*���ܣ���������
*��������
*����ֵ:����ֵ
******************************/
int CLable::getControlType()
{
	return LABLE;
}



