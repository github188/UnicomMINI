#ifndef CEDIT_H
#define CEDIT_H

#include "BaseControl.h"

class CEdit :public CBaseControl
{
    public:
        CEdit(int height,int width,int scry,int scrx,int size,int type);
        virtual ~CEdit();
        virtual void draw();              //��������
        virtual void focus();               //��ý���
        virtual void unfocus();             //ȡ������
        virtual int getControlType();     //�ؼ�����
        virtual int driver(int KeyNum);      //����
        char* getCaption();                 //ȡ���ı�����
    protected:
        char acCaption[30];                //������������
		int CaptionSize;			//�༭�����������
		int nType;					//�༭��������ַ������� 0:��ĸ+���� 1:���� 2:��ĸ
    private:
};

#endif //CEDIT_H


