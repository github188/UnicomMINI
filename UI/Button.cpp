/**********************************************************************

*�ļ�����
		Button.cpp
*�ļ�������
		CButton��ķ�װ
*�����ߣ�
		�Ʊ�

*����ʱ�䣺
2011-8-4

******************************************************************/


#include <unistd.h>
#include "Button.h"

CButton::CButton(const char *caption,int height,int width,int scry,int scrx,int buttonID):CBaseControl(height,width,scry,scrx)
{
	this->acCaption = new char [strlen(caption) +1];
	strcpy(this->acCaption,caption);
	this->pWin = NULL;
	this->shadow = NULL;
	this->nIndex = 0;
	nButtonID = buttonID;
}

CButton::~CButton()
{
	delete acCaption;
	if (this->pWin != NULL)
	{
		delwin(this->pWin);
	}
	if (this->shadow != NULL)
	{
		delwin(this->shadow);
	}
}

/*****************************
*��������draw
*���ܣ���������
*��������
*����ֵ:��
******************************/
void CButton::draw()
{
    //������ӰЧ��
	this->shadow = derwin(this->pParentControl->getWindow(),this->m_iHeight,this->m_iWidth,this->m_iStarty+1,this->m_iStartx+2);
	wbkgd(this->shadow,COLOR_PAIR(10));
	touchwin(this->pParentControl->getWindow());
	wrefresh(this->pParentControl->getWindow());

    //������ť
	this->pWin = derwin(this->pParentControl->getWindow(),this->m_iHeight,this->m_iWidth,this->m_iStarty,this->m_iStartx);
	wbkgd(this->pWin,COLOR_PAIR(9));
	box(this->pWin,0,0);
	mvwprintw(this->pWin,this->m_iHeight/2,(this->m_iWidth-strlen(acCaption))/2,"%s",this->acCaption);
	touchwin(this->pParentControl->getWindow());
	wrefresh(this->pParentControl->getWindow());
}


/*****************************
*��������focus
*���ܣ���ý���
*��������
*����ֵ:��
******************************/
void CButton::focus()
{

    wbkgd(this->pWin,COLOR_PAIR(3));
	curs_set(0);
    wrefresh(this->pWin);

}

/*****************************
*��������unfocus
*���ܣ�ʧȥ����
*��������
*����ֵ:��
******************************/
void CButton::unfocus()
{
    wbkgd(this->pWin,COLOR_PAIR(9));
	curs_set(0);
    wrefresh(this->pWin);
}

/*****************************
*��������getControlType
*���ܣ���������
*��������
*����ֵ:����ֵ
******************************/
int CButton::getControlType()
{
	return BUTTON;
}

/*****************************
*��������press
*���ܣ���ťЧ��--����
*��������
*����ֵ:����ֵ
******************************/
void CButton::press()
{
	mvwin(this->pWin,this->pParentControl->getScry()+this->m_iStarty+1,this->pParentControl->getScrx()+this->m_iStartx+2);
	touchwin(this->pParentControl->getWindow());
	wrefresh(this->pParentControl->getWindow());
	sleep(1);
	mvwin(this->pWin,this->pParentControl->getScry()+this->m_iStarty,this->pParentControl->getScrx()+this->m_iStartx);
	wbkgd(this->shadow,COLOR_PAIR(10));
	wrefresh(this->shadow);
	wbkgd(this->pWin,COLOR_PAIR(3));
	wrefresh(this->pWin);
	
}

/*****************************
*��������getButtonID
*���ܣ����ذ�ťID
*��������
*����ֵ:����ֵ
******************************/
int CButton::getButtonID()
{
	return this->nButtonID;
}


/*****************************
*��������driver
*���ܣ�����
*��������
*����ֵ:��
******************************/
int CButton::driver(int KeyNum)
{
    int nGet;

    //�����������Ч
    keypad(this->pWin,TRUE);

    this->focus();

    do
    {
        nGet=wgetch(this->pWin);

        switch(nGet)
        {

        case MYKEY_ENTER:

            this->press();

        case MYKEY_UP:
        case MYKEY_DOWN:
        case MYKEY_LEFT:
        case MYKEY_RIGHT:
        case MYKEY_TAB:
        case MYKEY_ESC:
        case MYKEY_PAGEUP:
        case MYKEY_PAGEDOWN:

            return nGet;

            break;


        default:
            break;
        }

    }while(1);


}


/*****************************
*��������changeCaption
*���ܣ��ı䰴ť����
*��������
*����ֵ:��
******************************/
void CButton::changeCaption(char *caption)
{
	delete this->acCaption;
	this->acCaption = new char [strlen(caption) +1];
	strcpy(this->acCaption,caption);
	mvwprintw(this->pWin,this->m_iHeight/2,(this->m_iWidth-strlen(acCaption))/2,"%s",this->acCaption);
	wrefresh(this->pWin);
	
}


