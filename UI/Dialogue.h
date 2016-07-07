#ifndef CDIALOGUE_H
#define CDIALOGUE_H

#include <unistd.h>
#include "Lable.h"

class CDialogue :public CLable
{
public:
	CDialogue(const char *caption,int height,int width,int scry,int scrx);
	virtual ~CDialogue();
	void draw();        //��������
	int getControlType();       //�������
	void show();        //�������ڲ�����
protected:
	int driver(int KeyNum);   //����
};

#endif // CDIALOGUE_H
