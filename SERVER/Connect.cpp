/**********************************************************************

*�ļ�����
		connect.cpp
*�ļ�������
		CConnect ��װ��
*�����ߣ�
		�Ʊ�

*����ʱ�䣺
2011-8-11

******************************************************************/

#include <stdio.h>
#include "Connect.h"
#include "global.h"



CConnect ::CConnect (tp_socket_addr address,socket_notify_event read_event,CPthread *pthread)
{
	on = 1;
	index = 0;
	socket_addr = address;
	//connect_sum = max_connect;

	nChoice = true;

	memset(&stSocket_info,0,sizeof(tp_socket_info));
	//��ʼ��
	for(i=0;i<FD_SETSIZE;i++)
	{
		memset(&socket_array[i],0,sizeof(ClientSockets_T));
	}

	rec_event = read_event;

	thread_manager = pthread;

	server_active();
}

CConnect ::~CConnect ()
{
	for (i=0;i<FD_SETSIZE;i++)
	{
		if(socket_array[i].cliSocket != 0)
		{
			close(socket_array[i].cliSocket);
			socket_array[i].cliSocket = 0;
		}
	}
	//�������� ����ӷ����
	FD_ZERO(&allset);	

	delete socket_addr.ip_addr;
}

/*****************************
*��������start
*���ܣ��ṩ�û���ʼsocket
*��������
*����ֵ:��
******************************/
int CConnect ::start()
{

	service_core();
}


/*****************************
*��������stop
*���ܣ��ṩ�û�����socket
*��������
*����ֵ:��
******************************/
int CConnect ::stop()
{
	nChoice = false;
}


/*****************************
*��������server_active
*���ܣ�������������
*��������
*����ֵ:��
******************************/
int CConnect ::server_active()
{
	int nSend_connect;

	//����address
	addr_len = sizeof(server_addr);
	server_addr.sin_family =PF_INET;
	server_addr.sin_port = htons(socket_addr.port);
	server_addr.sin_addr.s_addr =inet_addr(socket_addr.ip_addr);

	//�������� ����ӷ����
	FD_ZERO(&allset);	

	
}


/*****************************
*��������add_connect
*���ܣ��������
*��������
*����ֵ:��
******************************/
void CConnect ::add_connect()
{
	//��������
	for(i=0;i<FD_SETSIZE;i++)
	{
		if (socket_array[i].cliSocket == 0)
		{

			//����socket
			socket_array[i].cliSocket = socket(PF_INET,SOCK_STREAM,0);
			setsockopt(socket_array[i].cliSocket,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
			//����
			connect(socket_array[i].cliSocket,(struct sockaddr *)&server_addr,addr_len);
			//�������
			FD_SET(socket_array[i].cliSocket,&allset);
			//��������׽���
			if (maxfd < socket_array[i].cliSocket)
			{
				maxfd = socket_array[i].cliSocket;
			}
			
			//��������
			if (index < i )
			{
				index = i;
			}

			break;

		}
		
		
	}
}


/*****************************
*��������service_core
*���ܣ����������� IO����
*��������
*����ֵ:��
******************************/
int CConnect ::service_core()
{

	while(nChoice)
	{
		rset=allset;

		select_return=select(maxfd+1,&rset,NULL,NULL,0);			//��ʱ5��Ͽ�

		//printf("---select %d---\n",select_return);

		if (select_return == 0)
		{	
			break;
		}

		//���пͻ��˼��� �Ƿ�������Ϣ����
		for (i=0;i<=index ;i++ )
		{
			if ( (ac_socket=socket_array[i].cliSocket)>0)
			{
				if (FD_ISSET(ac_socket,&rset))
				{

					memset(dialogue,0,sizeof(dialogue));
					n_read=recv(ac_socket,dialogue,sizeof(dialogue),MSG_PEEK);

					if (n_read==0)
					{
						close(ac_socket);
						FD_CLR(ac_socket,&allset);
						socket_array[i].cliSocket = 0;
						printf("disconnect!!!\n");
					}
					else if (n_read > 0 )
					{

						if (socket_array[i].HaveUseThread == 0)
						{
							socket_array[i].HaveUseThread == 1;
							stSocket_info = (tp_socket_info *)malloc(sizeof(tp_socket_info));
							memset(stSocket_info,0,sizeof(tp_socket_info));
							stSocket_info->client_socket_fd= ac_socket;
							stSocket_info->buffer = NULL;

							if (thread_manager != NULL)
							{
								thread_work = (tp_thread_work *)malloc(sizeof(tp_thread_work));
								thread_work->callback = ChangeState;
								thread_work->argv = (void *)stSocket_info;
// 								thread_work->callback = rec_event;
// 								thread_work->argv = (void *)stSocket_info;

								thread_manager->add_thread(thread_work);
							}
							else
							{
								rec_event(&stSocket_info);
							}


						}


					}

					//�ж��¼��Ƿ�����ȫ
					if(--select_return<=0)
					{
						break;
					}
				}
			}
		}

		usleep(100);		//��΢��ʱ �ɱ���̩��
	}
}


/*****************************
*��������getSocket
*���ܣ���ȡ�׽���
*��������
*����ֵ:��
******************************/
int CConnect ::getSocket(int array_index)
{
	return socket_array[array_index].cliSocket;
}


void* ChangeState(void *argv)
{
	int j= 0;
	tp_socket_info  *socket_info = (tp_socket_info  *)argv;

	rec_event((void *)socket_info);

	for (j=0;j<FD_SETSIZE;j++)
	{
		if (socket_array[j].cliSocket == socket_info->client_socket_fd)
		{
			socket_array[j].HaveUseThread  = 0;
			break;
		}
	}

	if (socket_info->buffer != NULL)
	{
		free(socket_info->buffer);
	}
	free(socket_info);

}
