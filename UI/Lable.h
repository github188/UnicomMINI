#ifndef CLABLE_H
#define CLABLE_H

#include "BaseControl.h"

class CLable : public CBaseControl
{
    public:
        CLable(const char *caption,int height,int width,int scry,int scrx);
        virtual ~CLable();
        void draw();        //��������
        int getControlType();       //�ؼ�����
    protected:
        char *acCaption;    //��������
    private:
};

#endif // CLABLE_H
