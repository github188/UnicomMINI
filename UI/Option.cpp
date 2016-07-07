/**********************************************************************

*�ļ�����
		Option.cpp
*�ļ�������
		COption��ķ�װ
*�����ߣ�
		�Ʊ�

*����ʱ�䣺
2011-8-4

******************************************************************/


#include "Option.h"

COption::COption(const char *caption,int height,int width,int scry,int scrx):CBaseControl(height,width,scry,scrx)
{
	acCaption = new char [strlen(caption) +1];
	strcpy(acCaption,caption);
	choice = false ;
}

COption::~COption()
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
void COption::draw()
{
	this->pWin = derwin(this->pParentControl->getWindow(),this->m_iHeight,this->m_iWidth,this->m_iStarty,this->m_iStartx);
	//wbkgd(this->shadow ,COLOR_PAIR(1));
	//box(this->shadow ,0,0);
	//touchwin(this->pWin);
	mvwprintw(this->pWin,this->m_iHeight/2,0,"�� ��");
	mvwprintw(this->pWin,this->m_iHeight/2,6,"%s",this->acCaption);
	touchwin(this->pParentControl->getWindow());
	wrefresh(this->pParentControl->getWindow());
}

/*****************************
*��������getControlType
*���ܣ���������
*��������
*����ֵ:����ֵ
******************************/
int COption::getControlType()
{
	return OPTION;
}


/*****************************
*��������driver
*���ܣ�����
*��������
*����ֵ:��ֵ
******************************/
int COption::driver(int KeyNum)
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
		case MYKEY_SPACE:
			

            this->press();

			break;
			
        case MYKEY_UP:
        case MYKEY_DOWN:
        case MYKEY_LEFT:
        case MYKEY_RIGHT:
        case MYKEY_TAB:
        case MYKEY_ESC:
        case MYKEY_PAGEUP:
        case MYKEY_PAGEDOWN:
			
			this->unfocus();
            return nGet;
			
            break;
			
			
        default:
            break;
        }
		
    }while(1);
	
	
}


/*****************************
*��������press
*���ܣ���ťЧ��--����
*��������
*����ֵ:����ֵ
******************************/
void COption::press()
{
	if (choice == false)
	{
		choice = true;

		
		mvwprintw(this->pWin,this->m_iHeight/2,2,"*");
	}
	else
	{
		choice = false;

		mvwprintw(this->pWin,this->m_iHeight/2,3,"\b \b");
	}

	wrefresh(this->pWin);
}



/*****************************
*��������getOption
*���ܣ�����ѡ����
*��������
*����ֵ:ѡ����
******************************/
bool COption::getOption()
{
	return choice;
}


/*****************************
*��������focus
*���ܣ���ý���
*��������
*����ֵ:��
******************************/
void COption::focus()
{

	wbkgd(this->pWin ,COLOR_PAIR(1));
	wrefresh(this->pWin);
}

/*****************************
*��������unfocus
*���ܣ�ȡ������
*��������
*����ֵ:��
******************************/
void COption::unfocus()
{
	wbkgd(this->pWin ,COLOR_PAIR(2));
	wrefresh(this->pWin);
}

