#ifndef CMAINCONTROL_H
#define CMAINCONTROL_H


#include "Form.h"



class CMainControl
{
public:
	CMainControl();
	virtual ~CMainControl();
	void show();		//չʾ
protected:
	void init();		//����
	void addfunction();	//��ӹ��ܿ�
	void driver();		//����
	CForm * find(int index);	//���Ҵ���
private:
	CMyList pListControl;       //����
	CBaseControl *control;      //����ָ��
	int height;     //���ڸ�
	int width;      //���ڿ�
	int scry;       //����y����
	int scrx;       //����x����
	
};

#endif // CMAINCONTROL_H
