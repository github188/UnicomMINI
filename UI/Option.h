#ifndef _OPTION_H_
#define _OPTION_H_

#include "BaseControl.h"

class COption : public CBaseControl
{
    public:
        COption(const char *caption,int height,int width,int scry,int scrx);
        virtual ~COption();
        void draw();				//��������
        int getControlType();       //�ؼ�����
		bool getOption();			//����ѡ��
		int driver(int KeyNum);      //����
		void press();           //��ťЧ��
		void focus();               //��ý���
        void unfocus();             //ȡ������
    protected:
        char *acCaption;    //��������
		bool choice;		//ѡ��
    private:
};

#endif //_OPTION_H_




