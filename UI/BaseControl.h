#ifndef _BASECONTROL_H_
#define _BASECONTROL_H_

#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

#define FORM	 0
#define LABLE	 1
#define BUTTON	 2
#define EDIT	 3
#define PASSWD	 4
#define OPTION	 5
#define REFRESH  6
#define DIALOGUE 7

#define MYKEY_TAB			9
#define MYKEY_ENTER			10
#define MYKEY_BACK			263
#define MYKEY_UP	    	259
#define MYKEY_DOWN			258
#define MYKEY_LEFT			260
#define MYKEY_RIGHT			261
#define MYKEY_F2			266
#define MYKEY_F3			267
#define MYKEY_F4			268
#define MYKEY_F5			269
#define MYKEY_ESC               27
#define MYKEY_SPACE			32
#define MYKEY_PAGEUP    339
#define MYKEY_PAGEDOWN    338



class CBaseControl  
{
    public:
        CBaseControl(int height,int width,int scry,int scrx);
        virtual ~CBaseControl();
        virtual void draw()=0;              //��������
        virtual void focus();               //��ý���
        virtual void unfocus();             //ȡ������
        virtual int getControlType()=0;     //�ؼ�����
        virtual int driver(int KeyNum);      //����
        void setName(char *Name);           //���ÿؼ���
        char * getFormName() const;         //��ȡ�ؼ���
        WINDOW *getWindow() const;          //��ô���ָ��
        void SetParent(CBaseControl &parent);       //���ø��ؼ�
        void SetIndex(int index);		//����index
        int getIndex()const;            //���index
        int getScry() const;        //��ȡy����
        int getScrx() const;        //��ȡx����
    protected:
        WINDOW *pWin;		// WINDOW *pWin��ǰ�ؼ���ӦNCurse Window��ָ��
        int nIndex;			//�ؼ���ת����
        char m_acName[30];      //�ؼ�����
        int m_iStartx;          //��ʼx����
        int m_iStarty;          //��ʼY����
        int m_iHeight;          //�߶�
        int m_iWidth;           //���
        CBaseControl *pParentControl;	//��Ÿ��ؼ�ָ��
    private:
};

#endif

