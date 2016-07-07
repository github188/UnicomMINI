/**********************************************************************

*�ļ�����
		MainControl.cpp
*�ļ�������
		CMainControl��ķ�װ
*�����ߣ�
		�Ʊ�

*����ʱ�䣺
2011-8-4

******************************************************************/

#include "MainControl.h"
#include "Edit.h"
#include "Button.h"
#include "Lable.h"
#include "Option.h"
#include "CallBack.h"

CMainControl::CMainControl()
{

}

CMainControl::~CMainControl()
{

}

/*****************************
*��������init
*���ܣ����ڳ�ʼ��
*��������
*����ֵ:��
******************************/
void CMainControl::init()
{
	this->addfunction();
}


/*****************************
*��������show
*���ܣ��������ڲ�����
*��������
*����ֵ:��
******************************/
void CMainControl::show()
{
    this->init();

    this->driver();

}


/*****************************
*��������driver
*����:����
*��������
*����ֵ:��
******************************/
void CMainControl::driver()
{
    CForm *curform;
    int formReturn=0,now=1;


    curform = this->find(now);

    while(curform != NULL)
    {
        wbkgd(stdscr,COLOR_PAIR(7));

		refresh();

		curs_set(0);

        formReturn = curform->show();

        curform->unshow();

        switch(formReturn)
        {
        case 0:
			now = 1;

			break;

        case 1:

            now = formReturn;

            break;

        case -1:
            return;
            break;

        default:
            break;
        }

        curform = this->find(now);
    }

}


/*****************************
*��������find
*���ܣ���ȡָ��λ�õĴ���
*��������
*����ֵ:��
******************************/
CForm * CMainControl::find(int index)
{
	return ((CForm *)(pListControl[index]));
}


/*****************************
*��������addfunction
*���ܣ���ӹ��ܽ���
*��������
*����ֵ:��
******************************/
void CMainControl::addfunction()
{
	CForm *form;

	
	
   //����ѡ��
    form = new CForm(24,80,0,0,CALLBACK_parameter);
	
    control = new CLable("����ʱ��( �� ):",3,16,1,2);
    form->addControl(*control);
    control = new CLable("ģ���豸��:",3,16,1,42);
    form->addControl(*control);
    control = new CLable("���ͼ��(����):",3,16,5,2);
    form->addControl(*control);
	control = new CLable("ҵ������",1,10,9,35);
    form->addControl(*control);
	control = new CLable("֧�֡�����ѡ��,tab�л�,ѡ���ո�,enter֧��,���������ÿ�ͨ��config.ini�޸�",1,76,21,3);
    form->addControl(*control);
	control = new CLable("Ϊ�˲����ȶ�,��30�����������������������",1,50,22,1);
    form->addControl(*control);

	
    control = new CEdit(3,16,1,20,4,1);
    form->addControl(*control);
    control = new CEdit(3,16,1,60,3,1);
    form->addControl(*control);
	control = new CEdit(3,16,5,20,8,1);
    form->addControl(*control);

	control = new COption("�Ƿ���Ӧ��",1,24,6,50);
	form->addControl(*control);
	control = new COption("һ��ͨ��ֵ",1,24,11,10);
	form->addControl(*control);
	control = new COption("������ӿ�",1,24,11,50);
	form->addControl(*control);
	control = new COption("�ֻ�����ѯ",1,24,13,10);
	form->addControl(*control);
	control = new COption("�ֻ���ʷ�˵�",1,24,13,50);
	form->addControl(*control);
	control = new COption("�ֻ���ʷ�굥",1,24,15,10);
	form->addControl(*control);
	
	
    control = new CButton("��ʼ����",3,12,17,23,1);
    form->addControl(*control);
    control = new CButton("��    ��",3,12,17,45,-1);
    form->addControl(*control);
	
    this->pListControl.addNode(form);

	
   
}


