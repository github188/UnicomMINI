/******************************************************************\
* ��Ȩ���� (C)2011, by Tristone
* �ļ����ƣ� init.c
*
* ����ժҪ�� implementation for the init module
*
* ��ʷ��
*�������ڣ�2011-8-20
*�����ˣ�	����
*�޶���ʷ: 2011-8-23
*�޶���:	����
*�޶�����:�޸�����bug,�Ľ�����ʵ��,���������
*�޶���ʷ: 2011-8-24
*�޶���:	����
*�޶�����:������select���Ŀ��
*�޶���ʷ: 2011-8-25
*�޶���:	����
*�޶�����:������һ�����������µĶ���bug
\******************************************************************/

#include "init.h"
#include "task_queue.h"
#include "service.h"

//���ߺϷ��ͻ�����
int client_num = 0;
//��������
int conned_num = 0;
//���߿ͻ�����Ϣ
online_client clients[FD_SETSIZE];
//�̳߳ص�ַ
extern thread_pool* pool;
//�߳�״̬�ṹ
extern char thread_stat[THREAD_NUM];
//������ˮ����
long iRand = 0;
//���߿ͻ����������ֵ
int max_index = 0;
//����ˮλͼ����,��ֹ�ذ�����
char pack_id[600000];
//����
//pthread_mutex_t main_mutex =  PTHREAD_MUTEX_INITIALIZER;
fd_set allset;

int  socket_server_startup()
{
	int i, m;
	int flag = 0;
	int opt_val = 1;
	fd_set rset;
	int maxfd;
	int socket_ret;
	int select_ret;
	int accept_ret;
	int addr_len = sizeof(struct sockaddr_in);
	struct sockaddr_in ser_addr;
	struct sockaddr_in clt_addr;

	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(SERVER_PORT);
	ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	socket_ret = socket(AF_INET, SOCK_STREAM, 0);	//��ʽ�׽���
	ser_cont recv_context = {0, NULL};

	//���õ�ַ������
	setsockopt(socket_ret, SOL_SOCKET,
		SO_REUSEADDR, &opt_val, sizeof(opt_val));

	//��,����
	bind(socket_ret, (struct  sockaddr*)&ser_addr, addr_len);
	listen(socket_ret, LISTEN_QUEUE);

	//selectǰ�ĳ�ʼ��׼������
	maxfd = socket_ret;
	//���߿ͻ�����ϢĬ��ȫ��Ϊ-1
	memset(clients, -1, sizeof(clients));
	FD_ZERO(&allset);
	FD_SET(socket_ret, &allset);

	//IO���ú���
	while (1)
	{
		rset = allset;
		select_ret = select(maxfd + 1, &rset, NULL, NULL, NULL);
		if (FD_ISSET(socket_ret, &rset))
		{
			accept_ret = accept(socket_ret, (struct sockaddr *)&clt_addr, &addr_len);
			conned_num++;
			printf("New client connect..\n");
			if (accept_ret > maxfd)
			{
				maxfd = accept_ret;
			}
			for (i = 0; i < FD_SETSIZE; i++)
			{
				if (clients[i].client_fd < 0)
				{
					clients[i].client_fd = accept_ret;
					break;
				}
			}
			if (i >= FD_SETSIZE)
			{
				printf("Clients upper limit..\n");
			}
			FD_SET(accept_ret, &allset);
			if (max_index < i)
			{
				max_index = i;
			}
			//����select����ֵ�ж��Ƿ����¿ͻ�������,��û��,�������һ��ѭ��
			//printf("%d\n", select_ret);
			if (select_ret <= 0)
			{
				continue;
			}
		}
		for (i = 0; i <= max_index; i++)
		{
			if ((accept_ret = clients[i].client_fd) > 0)
			{
				if (FD_ISSET(accept_ret, &rset))
				{
					recv_context.index = i;
					//��Ӷ������������
					recv_func(recv_context);
					//pool->que_tail = queue_add(&pool->que_head, NULL, recv_func, recv_context);
					
					for(m = 0; m < THREAD_NUM; m++)
					{
						if (THREAD_IDLE == thread_stat[m])
						{
							thread_stat[m] = THREAD_BUSY;
							pthread_cond_signal(&pool->pool_threads[m].cond_id);		
							break;
						}	
						if ((THREAD_NUM-1) == m)
						{
							m = -1;
						}
					}
				}
			}
			//if (select_ret <= 0)
			//{
			//	break;
			//}
		}
	}

	return 1;
}

void recv_func(ser_cont context)
{
	ser_cont ser_context;
	int i;
	int recv_fd = clients[context.index].client_fd;
	int recv_ret;
	int func_id;
	pack_head recv_head;
	char *buf = (char*)malloc(BUF_SIZE);
	ser_context.index = context.index;
	ser_context.recv_pack = buf;
	recv_ret = recv(recv_fd, buf, BUF_SIZE, MSG_DONTWAIT);
	//pthread_mutex_unlock(&main_mutex);
	//printf("recv = %d\n", recv_ret);
	if (recv_ret <= 0)
	{
		switch(recv_ret)
		{
		case EAGAIN://��ǰ�����ݿɶ�
			free(buf);
			return;
		case 0://���ӶϿ�
			//���ð���ˮ����
			memset(pack_id, 0, sizeof(pack_id));
			close(recv_fd);
			client_num--;
			printf("�豸IDΪ %s �Ŀͻ����������\n", clients[context.index].dev_id);			
			FD_CLR(clients[context.index].client_fd, &allset);
			memset(&clients[context.index], -1, sizeof(online_client));
			free(buf);
			return;
		default:
			free(buf);
			return;
		}
	}
	
	if ('~' == buf[0])
	{
		memcpy(&recv_head, &buf[1], sizeof(pack_head));
		func_id = atoi(recv_head.acFunc_ID);
		//�ذ�������,����λͼ���ݽṹ
		
		if (0 != func_id)
		{
			char temp[7] = {0};
			memcpy(temp, &recv_head.acTrans_id[12], 6);
			//printf("%s\n", temp);
			int count = atoi(temp);
			if (0 == pack_id[count])
			{
				pack_id[count] = 1;
			}
			else
			{
				printf("�յ��ذ�������\n");
				free(buf);
				return;
			}
		}
		//��������
		switch (func_id)
		{
		case 0://������	
			if ('<' == buf[sizeof(pack_head)+1])
			{
				printf("�յ��豸IDΪ %s �Ŀͻ��� ������\n", recv_head.acDev_id);
				clients[context.index].timeout = CLIENT_TIMEOUT;
				free(buf);
				return;
			}			
		case 1://��¼��
			if ('<' == buf[sizeof(pack_head)+sizeof(log_req)+1])
			{
				printf("�յ��豸IDΪ %s �Ŀͻ��� ��¼��\n", recv_head.acDev_id);
				pool->que_tail = queue_add(&pool->que_head, NULL, login_service, ser_context);
			}
			break;
		case 1001:
			if ('<' == buf[sizeof(pack_head)+sizeof(use_card_req)+1])
			{
				use_card_req pack_body;
				memcpy(&pack_body, &buf[sizeof(pack_head)+1], sizeof(use_card_req));
				//printf("%c\n", pack_body.cCard_ID);
				printf("�յ��豸IDΪ %s �Ŀͻ��� ��ֵ��\n", recv_head.acDev_id);
				pool->que_tail = queue_add(&pool->que_head, NULL, use_card_service, ser_context);
			}
			break;
			case 2001:
				if ('<' == buf[sizeof(pack_head)+sizeof(que_money_req)+1])
				{
					que_money_req pack_body;
					memcpy(&pack_body, &buf[sizeof(pack_head)+1], sizeof(que_money_req));
					printf("�յ��豸IDΪ %s �Ŀͻ��� ����ѯ��\n", recv_head.acDev_id);
					pool->que_tail = queue_add(&pool->que_head, NULL, que_money_service, ser_context);
				}
				break;
			case 2002:
				if ('<' == buf[sizeof(pack_head)+sizeof(bill_req)+1])
				{
					bill_req pack_body;
					memcpy(&pack_body, &buf[sizeof(pack_head)+1], sizeof(bill_req));
					printf("�յ��豸IDΪ %s �Ŀͻ��� �˵���ѯ��\n", recv_head.acDev_id);
					pool->que_tail = queue_add(&pool->que_head, NULL, que_bill_service, ser_context);
				}
				break;
			case 2003:
				if ('<' == buf[sizeof(pack_head)+sizeof(det_bill_req)+1])
				{
					det_bill_req pack_body;
					memcpy(&pack_body, &buf[sizeof(pack_head)+1], sizeof(det_bill_req));
					printf("�յ��豸IDΪ %s �Ŀͻ��� �굥��ѯ��\n", recv_head.acDev_id);
					pool->que_tail = queue_add(&pool->que_head, NULL, que_detail_service, ser_context);
				}
				break;
			case 3001:
				if ('<' == buf[sizeof(pack_head)+sizeof(buy_card_req)+1])
				{
					buy_card_req pack_body;
					memcpy(&pack_body, &buf[sizeof(pack_head)+1], sizeof(buy_card_req));
					printf("�յ��豸IDΪ %s �Ŀͻ��� ������\n", recv_head.acDev_id);
					pool->que_tail = queue_add(&pool->que_head, NULL, buy_card_service, ser_context);
				}
				break;
			case 1111://���߰�
				if ('<' == buf[sizeof(pack_head)+1])
				{
					printf("�յ��豸IDΪ %s �Ŀͻ������߰�,�����Ͽ�\n", clients[context.index].dev_id);
					FD_CLR(clients[context.index].client_fd, &allset);
					memset(&clients[context.index], -1, sizeof(online_client));
					//���ð���ˮ����
					memset(pack_id, 0, sizeof(pack_id));
					close(recv_fd);
					client_num--;
					free(buf);
					return;
				}	
		}
	}

}


void* monitor(void* context)
{
	int i;
	int count =0;
	memset(pack_id, 0, sizeof(pack_id));
	while(1)
	{
		i= 0;
		count++;
		if (count == 30)
		{//Լÿ30s���ð���ˮ����
			count = 0;
			memset(pack_id, 0, sizeof(pack_id));
		}
		sleep(1);
		for ( ; i <= max_index; i++)
		{
			if (clients[i].client_fd > 0)
			{
				clients[i].timeout--;
				//printf("timeout = %d\n", clients[i].timeout);
				//������ʱ,����
				if (0 == clients[i].timeout)
				{
					printf("�豸IDΪ %s �Ŀͻ��˳�ʱ����\n", clients[i].dev_id);
					close(clients[i].client_fd);
					FD_CLR(clients[i].client_fd, &allset);
					memset(&clients[i], -1, sizeof(online_client));
					client_num--;
				}
			}
		}
	}

}












