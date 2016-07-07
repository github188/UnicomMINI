#ifndef CFORM_H
#define CFORM_H

#include "BaseControl.h"
#include "CMyList.h"

//#define FIRST   500

typedef int (*PFUN)(void*,int);

class CForm :public CBaseControl
{
    public:
        CForm(int height,int width,int scry,int scrx,PFUN pfun);
        virtual ~CForm();
        virtual void draw();              //��������
        //virtual void focus();               //��ý���
        //virtual void unfocus();             //ȡ������
        virtual int getControlType();     //�ؼ�����
        virtual void addControl(CBaseControl &control);     //��ӿؼ�
        virtual int show();     //�������ڲ�����
        virtual void unshow();      //ɾ������
        char * getEditCaption(int index);       //��ȡָ��λ�õı༭����ı�
		bool getOption(int index);			//��ȡָ��λ�õ�ѡ����ѡ��
        CBaseControl * getListNow(); //��ȡ��ǰ����ָ��ָ��Ĵ���ָ��
		bool changeButtonCaption(char *caption,int index);
        void delAll();   //ɾ�������Ӵ���
		void changeRefresh();
		void closeRefresh();
    protected:
        virtual int driver(int KeyNum);      //����
        CBaseControl* find(int index);      //��ȡ����λ�õĴ���
        CMyList pListControl;               //����
        int snIndex;            //�Ӵ��ڵĸ���
        PFUN pFunction;         //����ָ��
    private:
};

#endif // CFORM_H


