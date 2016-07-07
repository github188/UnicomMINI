/**********************************************************************

*�ļ�����
		BaseControl.cpp
*�ļ�������
		CBaseControl��ķ�װ
*�����ߣ�
		�Ʊ�

*����ʱ�䣺
2011-8-4

******************************************************************/


#include "BaseControl.h"



//���캯��
CBaseControl::CBaseControl(int height,int width,int scry,int scrx)
{
	m_iHeight = height;
	m_iWidth = width;
	m_iStarty = scry;
	m_iStartx = scrx;
	memset(m_acName,0,30);
    this->pWin =NULL;
	this->nIndex = 0;
}


//�������� 
CBaseControl::~CBaseControl()
{

}

/*****************************
*��������setparent
*���ܣ����ø�����ָ��
*��������
*����ֵ:��
******************************/
void CBaseControl::SetParent(CBaseControl &parent)
{
	this->pParentControl = &parent;
}

/*****************************
*��������getWindow
*���ܣ���ô���ָ��
*��������
*����ֵ:��
******************************/
WINDOW * CBaseControl::getWindow() const
{
	return this->pWin;
}

/*****************************
*��������setindex
*���ܣ�����������
*��������
*����ֵ:��
******************************/
void CBaseControl::SetIndex(int index)
{
	this->nIndex = index;
}

/*****************************
*��������getindex
*���ܣ����������
*��������
*����ֵ:��
******************************/
int CBaseControl::getIndex() const
{
	return this->nIndex;
}


/*****************************
*��������driver
*���ܣ�����
*��������
*����ֵ:��
******************************/
int CBaseControl::driver(int KeyNum)
{
    return KeyNum;
}

/*****************************
*��������focus
*���ܣ���ý���
*��������
*����ֵ:��
******************************/
void CBaseControl::focus()
{

}

/*****************************
*��������unfocus
*���ܣ�ȡ������
*��������
*����ֵ:��
******************************/
void CBaseControl::unfocus()
{

}


/*****************************
*��������getscry
*���ܣ���ȡy����
*��������
*����ֵ:��
******************************/
int CBaseControl::getScry() const
{
    return m_iStarty;
}


/*****************************
*��������getscrx
*���ܣ���ȡx����
*��������
*����ֵ:��
******************************/
int CBaseControl::getScrx() const
{
    return m_iStartx;
}


