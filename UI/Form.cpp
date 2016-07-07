/**********************************************************************

*�ļ�����
		Form.cpp
*�ļ�������
		CForm��ķ�װ
*�����ߣ�
		�Ʊ�

*����ʱ�䣺
2011-8-4

******************************************************************/



#include "Form.h"
#include "Button.h"
#include "Edit.h"
#include "Option.h"
#include "Refresh.h"



CForm::CForm(int height,int width,int scry,int scrx,PFUN pfun):CBaseControl(height,width,scry,scrx)
{
	this->pWin = NULL;
	this->nIndex = 0;
	snIndex = 1;
    pFunction = pfun;
}

CForm::~CForm()
{

	if (this->pWin != NULL)
	{
		delwin(this->pWin);
	}

}

/*****************************
*��������addcontrol
*���ܣ���ӿؼ�
*��������
*����ֵ:��
******************************/

void CForm::addControl(CBaseControl &control)
{


	//Ϊ���ӵĿؼ����ø��ؼ� Ϊ������
	control.SetParent(*this);

	snIndex ++;

	this->pListControl.addNode(&control);

	//
}


/*****************************
*��������draw
*���ܣ���������
*��������
*����ֵ:��
******************************/
void CForm::draw()
{

	//����������
	//�õ���ǰ���ڶ�Ӧ��NCURSES WINDOW *ָ��
	this->pWin = newwin(m_iHeight,m_iWidth,m_iStarty,m_iStartx);
	wbkgd(this->pWin,COLOR_PAIR(2));
	box(this->pWin,0,0);
	wrefresh(this->pWin);

	//�����������е��ӿؼ�
	for (pListControl.begin();pListControl.hasNext();)
	{
		((CBaseControl *)(pListControl.Next()))->draw();
	}
}

/*****************************
*��������show
*���ܣ��������ڲ�����
*��������
*����ֵ:��
******************************/
int CForm::show()
{
	this->draw();

	//���봰����������
	return this->driver(1);

}

/*****************************
*��������unshow
*���ܣ�ɾ������
*��������
*����ֵ:��
******************************/
void CForm::unshow()
{

	//ɾ���������е��ӿؼ�
	for (pListControl.begin();pListControl.hasNext();)
	{
		delwin(((CBaseControl *)(pListControl.Next()))->getWindow());

	}

	//ɾ��������
	delwin(this->getWindow());

	refresh();

}

/*****************************
*��������getControlType
*���ܣ���������
*��������
*����ֵ:����ֵ
******************************/
int CForm::getControlType()
{
	return FORM;
}

/*****************************
*��������driver
*���ܣ���������
*��������
*����ֵ:�ж�ֵ
******************************/
int CForm::driver(int KeyNum)
{
	int nGet=MYKEY_TAB,index=1,i=0,nReturn;
    CBaseControl *pControl;


	///�ж�form�����Ƿ��пؼ�
	pControl =	this->find(index);

	while(pControl!=NULL)
	{

		//�����������Ч
        //keypad(pControl->getWindow(),TRUE);

        //pControl->focus(TURN_ON);

        nGet=pControl->driver(nGet);

		switch (nGet)
		{

		case MYKEY_LEFT:
			pControl->unfocus();

			index --;
			if(index <= 0)
			{
				index = snIndex-1;
			}
			pControl = this->find(index);


			break;

		case MYKEY_ENTER:

            if(pFunction != NULL)
            {
                nReturn = pFunction((void *)this,((CButton *)pControl)->getButtonID());

				if (nReturn == 999)
				{
					pControl = this->find(index);
				}
				else
				{		
					return nReturn;
				}
            }
            else return ((CButton *)pControl)->getButtonID();


			break;

		case MYKEY_TAB:
		case MYKEY_RIGHT:


			pControl->unfocus();

			index ++;
			if(index >= snIndex)
			{
				index = 1;
			}
			pControl = this->find(index);

			break;

// 		case MYKEY_ESC:
// 
// 
// 			return 0;
// 			break;

		default:
			break;
		}
	}

	return 0;

}


/*****************************
*��������find
*���ܣ��ҵ�����λ�õĴ���
*��������
*����ֵ:����ָ��
******************************/
CBaseControl* CForm::find(int index)
{
	return ((CBaseControl *)(pListControl[index]));
}


/*****************************
*��������getOption
*���ܣ���ȡѡ����ѡ����
*��������
*����ֵ:ѡ����
******************************/
bool CForm::getOption(int index)
{
	int now=0;
    int num=0;
    int count= 0;
	
    count = this->pListControl.count();
	
    while(count > now)
    {
        now += 1;
        if ((((CBaseControl *)(pListControl[now]))->getControlType()) == OPTION)
        {
            num += 1;
            if(num == index)
            {
                return (((COption *)(pListControl[now]))->getOption());
            }
        }
    }
	
	
    return false;
}

/*****************************
*��������getEditCaption
*���ܣ���ȡ�����б༭�������
*��������
*����ֵ:�ı�����
******************************/
char * CForm::getEditCaption(int index)
{
    int now=0;
    int num=0;
    int count= 0;

    count = this->pListControl.count();

    while(count > now)
    {
        now += 1;
        if ((((CBaseControl *)(pListControl[now]))->getControlType()) == EDIT || (((CBaseControl *)(pListControl[now]))->getControlType()) == PASSWD)
        {
            num += 1;
            if(num == index)
            {
                return (((CEdit *)(pListControl[now]))->getCaption());
            }
        }
    }


    return NULL;


}

/*****************************
*��������getListNow
*���ܣ���ȡ��ǰ����ָ��ָ��Ĵ���ָ��
*��������
*����ֵ:��
******************************/
CBaseControl * CForm::getListNow()
{
    return ((CBaseControl *)(this->pListControl.ReturnNow ()));
}

/*****************************
*��������changeButtonCaption
*���ܣ��ı�ָ����ť������
*��������
*����ֵ:�Ƿ�ɹ�
******************************/
bool CForm::changeButtonCaption(char *caption,int index)
{
	int now=0;
    int num=0;
    int count= 0;
	
    count = this->pListControl.count();
	
    while(count > now)
    {
        now += 1;
        if ((((CBaseControl *)(pListControl[now]))->getControlType()) == BUTTON)
        {
            num += 1;
            if(num == index)
            {
               (((CButton *)(pListControl[now]))->changeCaption(caption));
			    return true;
            }
        }
    }
	
	
    return false;
}

/*****************************
*��������changeRefresh
*���ܣ��ı�ˢ�¿��״̬
*��������
*����ֵ:��
******************************/
void CForm::changeRefresh()
{
	int now=0;
    int count= 0;
	
    count = this->pListControl.count();
	
    while(count > now)
    {
        now += 1;
        if ((((CBaseControl *)(pListControl[now]))->getControlType()) == REFRESH)
        {
             (((CRefresh *)(pListControl[now]))->changeREFRESH());	 			 
			 (((CRefresh *)(pListControl[now]))->sendSINGAL());
        }
    }	
}


/*****************************
*��������closeRefresh
*���ܣ��ر�ˢ�¿���߳�
*��������
*����ֵ:��
******************************/
void CForm::closeRefresh()
{
	int now=0;
    int count= 0;
	
    count = this->pListControl.count();
	
    while(count > now)
    {
        now += 1;
        if ((((CBaseControl *)(pListControl[now]))->getControlType()) == REFRESH)
        {
             (((CRefresh *)(pListControl[now]))->changeON());
			 (((CRefresh *)(pListControl[now]))->sendSINGAL());
        }
    }	
}


/*****************************
*��������delAll
*���ܣ�ɾ������������
*��������
*����ֵ:��
******************************/
void CForm::delAll()
{
    //ɾ���������е��ӿؼ�
	for (pListControl.begin();pListControl.hasNext();)
	{
		delwin(((CBaseControl *)(pListControl.Next()))->getWindow());
	}

	snIndex = 1;

    refresh();

    this->pListControl.delAll();

}



