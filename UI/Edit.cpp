/**********************************************************************

*�ļ�����
		Edit.cpp
*�ļ�������
		CEdit��ķ�װ
*�����ߣ�
		�Ʊ�

*����ʱ�䣺
2011-8-4

******************************************************************/

#include "Edit.h"


//���캯��
CEdit::CEdit(int height,int width,int scry,int scrx,int size,int type):CBaseControl(height,width,scry,scrx)
{
	this->pWin = NULL;
	this->nIndex = 0;
	this->CaptionSize = size;
	memset(acCaption,0,30);
	this->nType = type;
}


//��������
CEdit::~CEdit()
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
void CEdit::draw()
{
	this->pWin = derwin(this->pParentControl->getWindow(),this->m_iHeight,this->m_iWidth,this->m_iStarty,this->m_iStartx);
	box(this->pWin,0,0);
	wbkgd(this->pWin,COLOR_PAIR(1));
	touchwin(this->pParentControl->getWindow());
	wrefresh(this->pParentControl->getWindow());

	memset(acCaption,0,30);
}


/*****************************
*��������focus
*���ܣ���ý���
*��������
*����ֵ:��
******************************/
void CEdit::focus()
{
    curs_set(1);
    wrefresh(this->pWin);
}

/*****************************
*��������unfocus
*���ܣ�ʧȥ����
*��������
*����ֵ:��
******************************/

void CEdit::unfocus()
{

    curs_set(0);
    wrefresh(this->pWin);

}

/*****************************
*��������getControlType
*���ܣ���������
*��������
*����ֵ:����ֵ
******************************/
int CEdit::getControlType()
{
	return EDIT;
}

/*****************************
*��������getCaption
*���ܣ������ı�����
*��������
*����ֵ:����ֵ
******************************/
char* CEdit::getCaption()
{
	return acCaption;
}

/*****************************
*��������driver
*���ܣ�����
*��������
*����ֵ:����ֵ
******************************/
int CEdit::driver(int KeyNum)
{
	//static int offset=0;
	int result=1,nGet=0,i=0;

	//�����������Ч
	keypad(this->pWin,TRUE);

	this->focus();

	while(1)
	{

		//������������Ϣ
		if (this->getControlType() == EDIT)
		{
			mvwprintw(this->pWin,1,1,"%s",this->acCaption);
		}
		else if (this->getControlType() == PASSWD)
		{
			for(i=0;i<strlen(this->acCaption);i++)
			{
				mvwprintw(this->pWin,1,1+i,"%c",'*');
			}

			if (strlen(this->acCaption) == 0)
			{
				wmove(this->pWin,1,1);
			}
		}
		wrefresh(this->pWin);

		nGet=wgetch(this->pWin);

		switch(nGet)
		{

		case MYKEY_BACK:

			if(strlen(acCaption) > 0)
			{
				wprintw(this->pWin,"\b \b");
				wrefresh(this->pWin);

				acCaption[strlen(acCaption)-1] = '\0';

			}
			else beep();

			break;


		case MYKEY_LEFT:
			this->unfocus();
			return MYKEY_LEFT;

			break;

		case MYKEY_TAB:
		case MYKEY_ENTER:
		case MYKEY_RIGHT:

			this->unfocus();
			return MYKEY_TAB;

			break;

		case MYKEY_UP:
		case MYKEY_DOWN:
        case MYKEY_ESC:
        case MYKEY_PAGEUP:
        case MYKEY_PAGEDOWN:

            return nGet;

            break;

		default:

			if (nType == 0)
			{
				if ( (nGet >= 'a' && nGet <= 'z') || (nGet >= 'A' && nGet <= 'Z') || (nGet >= '0' && nGet <= '9') )
				{
					//����������� �˴��޸�
					if (strlen(acCaption) < CaptionSize)
					{
						acCaption[strlen(acCaption)] = nGet;
					}
					else beep();
				}
			}
			else if (nType == 1)
			{
				if (nGet >= '0' && nGet <= '9')
				{
					//����������� �˴��޸�
					if (strlen(acCaption) < CaptionSize)
					{
						acCaption[strlen(acCaption)] = nGet;
					}
					else beep();
				}
			}
			else if (nType == 2)
			{
				if ( (nGet >= 'a' && nGet <= 'z') || (nGet >= 'A' && nGet <= 'Z'))
				{
					//����������� �˴��޸�
					if (strlen(acCaption) < CaptionSize)
					{
						acCaption[strlen(acCaption)] = nGet;
					}
					else beep();
				}
			}
			break;
		}
	}
}

