/**********************************************************************

*�ļ�����
		Main.cpp
*�ļ�������
		main����
*�����ߣ�
		�Ʊ�

*����ʱ�䣺
2011-8-4

******************************************************************/

#include "MainControl.h"
#include "CallBack.h"

void startGUI();
void endGUI();
void GUI_color();

int main()
{

	//���������ڴ�
	CALLBACK_forward_init();

	//NCurses������ʼ��
	//.........................
	startGUI();
	GUI_color();

	refresh();

	CMainControl Main_control;

	Main_control.show();

	endGUI();
	//.........................
	//NCurses�����ر�


	return 0;
}


/*****************************
*��������startGUI
*���ܣ�ncurses��ʼ��
*��������
*����ֵ:��
******************************/
void startGUI()
{
	initscr();
	start_color();
	noecho();
	cbreak();
    refresh();
	curs_set(0);
}

/*****************************
*��������endGUI
*���ܣ��˳�ncurses
*��������
*����ֵ:��
******************************/
void endGUI()
{
	endwin();
}


/*****************************
*��������GUI_color
*���ܣ���ɫ����
*��������
*����ֵ:��
******************************/
void GUI_color()
{
    init_pair(1,COLOR_BLACK,COLOR_WHITE);
	init_pair(2,COLOR_BLACK,COLOR_CYAN);
	init_pair(3,COLOR_BLACK,COLOR_MAGENTA);
	init_pair(4,COLOR_CYAN,COLOR_BLACK);
	init_pair(5,COLOR_WHITE,COLOR_BLUE);
	init_pair(6,COLOR_WHITE,COLOR_BLACK);
	init_pair(7,COLOR_BLUE,COLOR_BLUE);
	init_pair(8,COLOR_WHITE,COLOR_BLUE);
	init_pair(9,COLOR_BLACK,COLOR_RED);
	init_pair(10,COLOR_BLACK,COLOR_BLACK);
	init_pair(11,COLOR_CYAN,COLOR_CYAN);
}
