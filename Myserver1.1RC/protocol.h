/******************************************************************\
* ��Ȩ���� (C)2011, by Tristone
* �ļ����ƣ� protocol.h
*
* ����ժҪ��������ͨ��Э�飬��ͨ��ʱ���õİ�ͷ�����а���
*
* ��ʷ��
*�������ڣ�2011-8-14
*�����ˣ�	����
\******************************************************************/

#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_


//Э���ͷ
typedef struct pack_head_t
{
	char acDev_id[18];		//�豸ID
	int iBody_Size;			//�����С
	int iPack_Seq;			//����ţ�Ӧ����
	int iPack_Sum;			//��������Ӧ����
	char acTrans_id[19];	//���װ���ˮ�Ÿ�ʽ��YYYYMMDDHHMISS+4λ�����
	char acFunc_ID[5];		//���ܺ�
	char acErr_Code[4];		//�������,ȫΪ'0'��ʾЭ�鲻����
	char acErr_Msg[30];		//������Ϣ
}pack_head;


//��¼�����----0001
typedef struct Packet_Login_Request_T
{
	char acSoft_Ver[7];		//����汾��
	char acHard_Ver[7];		//Ӳ���汾��
}log_req;

//��¼Ӧ���----0001
typedef struct Packet_Login_Respond_T
{
	char cDev_Stat;		//�豸״̬,'1'��ʾ�Ϸ��豸
}log_res;

//һ��ͨ��ֵ�����----1001
typedef struct Packet_Prepaid_Request_T
{	
	char acPhone_Num[13];	//�ֻ�����
	char cCard_ID;			//��ֵ�Ŀ�ID 0��20Ԫ;1��30Ԫ;2��50Ԫ;3��100Ԫ
	int	iCard_Num;			//������
}use_card_req;

//һ��ͨ��ֵӦ�����----1001
typedef struct Packet_Prepaid_Respond_T
{
	char acTrans_Flowid[23];//������ˮ��ƽ̨���ɣ���ʽ��YYYYMMDDHHMISS+func_id+5λ�����
}use_card_res;

//����ѯ�����----2001
typedef struct Packet_Balance_Query_Request_T
{
	char acPhone_Num[13];	//�ֻ�����
	char cFee_Type;			//��������0��������1����ʷ�˵���2����ʷ�굥
}que_money_req;

//����ѯӦ���----2001
typedef struct Packet_Balance_Query_Respond_T
{
	char acTrans_Flowid[23];//������ˮ��ƽ̨���ɣ���ʽ��YYYYMMDDHHMISS+func_id+5
	char acBalance[10];		//����λ��
}que_money_res;

//��ʷ�˵���ѯ�����----2002
typedef struct Packet_HisBill_Qry_Request_T
{
	char acPhone_Num[13];	//�ֻ�����
	char cFee_Type;			//��������0��������1����ʷ�˵���2����ʷ�굥
	char acMonth[7];		//�·� ��ʽYYYYMM
}bill_req;

//��ʷ�˵���ѯӦ���----2002
typedef struct Packet_HisBill_Qry_Respond_T
{
	char acTrans_Flowid[23];	//������ˮ��ƽ̨���ɣ���ʽ��YYYYMMDDHHMISS+func_id+5
	char acBill_Content[1024];	//�˵�����
}bill_res;

//��ʷ�굥��ѯ�����----2003
typedef struct Packet_DetBill_Qry_Request_T
{
	char acPhone_Num[13];	//�ֻ�����
	char cFee_Type;			//��������0��������1����ʷ�˵���2����ʷ�굥
	char acMonth_Begin[7];	//��ʼ�·�
	char acMonth_End[7];	//��ֹ�·�
}det_bill_req; 

//��ʷ�굥��ѯӦ���----2003
typedef struct Packet_DetBill_Qry_Respond_T
{
	char acTrans_Flowid[23];	//������ˮ��ƽ̨���ɣ���ʽ��YYYYMMDDHHMISS+func_id+5	
	char acBill_Content[1024];	//�굥����
}det_bill_res;

//������ӿ������----3001
typedef struct Packet_Buy_Card_Request_T
{
	char acCard_Sum[13];	//����ֵ
	int iCard_Count;		//������
}buy_card_req;

//������ӿ�Ӧ���----3001
typedef struct Packet_Buy_Card_Respond_T
{
	char acTrans_Flowid[23];//������ˮ��ƽ̨���ɣ���ʽ��YYYYMMDDHHMISS+func_id+5
	int iCard_Count;		//������
	char acCard_NO[30];		//�����к�
}buy_card_res;


#endif

