#ifndef CBUTTON_H
#define CBUTTON_H

#include "BaseControl.h"

class CButton :public CBaseControl
{
    public:
        CButton(const char *caption,int height,int width,int scry,int scrx,int buttonID);
        virtual ~CButton();
        virtual void draw();              //��������
        virtual void focus();               //��ý���
        virtual void unfocus();             //ȡ������
        virtual int getControlType();     //�ؼ�����
        virtual int driver(int KeyNum);      //����
        void press();           //��ťЧ��
        int getButtonID();     //��ð�ťID
		void changeCaption(char *caption);
    protected:
        WINDOW *shadow;     //��Ӱ��������
        char *acCaption;     //���洰������
        int nButtonID;      //�¼�ID
    private:
};

#endif // CBUTTON_H


