#ifndef _CONNECT_H_
#define _CONNECT_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "Pthread.h"

#define BUFFER_SIZE 4096


//��������Ϣ
typedef struct 
{
	int port;
	char *ip_addr;
}tp_socket_addr;

//����������Ϊ�ͻ��˲����׼����Լ�������Ϣ������
typedef struct
{
	int client_socket_fd;	
	int len;
	void *buffer;
}tp_socket_info;


//socket����ڲ�ʱ��֪ͨ�ĺ���ָ�����ڸ��û�ʹ�õĻص�ָ��
typedef void *(*socket_notify_event)(void *socket_info);

//���ķ���������ĺ���ָ��
typedef   int (*server_active)(int port);

//socketģ�͵ĺ���ָ������ָ��io���ú��ĺ���
typedef   void (*service_core)(void);


typedef  struct
{
    int  cliSocket;
    int  HaveUseThread;
}ClientSockets_T;


void* ChangeState(void *argv);


static ClientSockets_T socket_array[FD_SETSIZE];
static socket_notify_event rec_event;					//�ͻ��˷��������¼�����

class CConnect
{
public:
	CConnect (tp_socket_addr address,socket_notify_event read_event,CPthread *pthread);
	virtual ~CConnect ();
	int start();
	int stop();
	int getSocket(int array_index);
	void add_connect();
protected:
	int server_active();
	int service_core();
private:	
	//�̳߳�
	CPthread *thread_manager;
	tp_thread_work *thread_work;

	//�ͻ���
	int on;
	int ac_socket;		//accept����ֵ
	int addr_len;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	tp_socket_addr socket_addr;
	tp_socket_info	*stSocket_info;
	
	//select
	fd_set rset;
	fd_set allset;
	
	//���ñ���
	int i,j;	//���ñ���
	int maxfd;		//����fd
	int index;		//����
	int select_return;	//select����ֵ
	int n_read,n_write;	//��д����ֵ
	int iID;		//ID ��
	bool nChoice;		//socket����
	int connect_sum;  //�׽��ָ���
	
	//�ַ���
	char dialogue[BUFFER_SIZE];
};

#endif

