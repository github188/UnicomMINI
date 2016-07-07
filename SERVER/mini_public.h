#ifndef _MINI_PUBLIC_H_
#define _MINI_PUBLIC_H_

//��ͷ
struct package_head{
	char dev_id[18];//�豸ID
	int packet_size;//������
	int packet_seq;//�����
	int packet_sum;//������
	char trans_id[19];//������ˮ��
	char func_id[5];//���ܺţ��������ӿ�
	char error_code[4] ;//�������
	char error_msg[30];//������Ϣ
};
//��¼����
//�����
struct request_login{
	char soft_ver[7];//����汾��
	char hard_ver[7];//Ӳ���汾��
};

//Ӧ���
struct response_login{
	char dev_status;//�豸״̬  1������� 0 �����ʧ
};

//һ��ͨ��ֵ
//�����
struct request_recharge{
	char phone_num[13];//�ֻ�����
	char card_id;//��ֵ�� ID 0-20Ԫ  1��30Ԫ 2:50Ԫ 3��ʾ 100Ԫ
	int card_num;//������
};
//Ӧ���
struct response_recharge{
	char trans_flowid[23];//������ˮ��

};

//                       ���Ѳ�ѯ

//����ѯ
//�����
struct request_callsearch{
	char phone_num[13];//�ֻ�����
	char fee_type;//�������� 0������� 1 ��ʷ�˵� 2��ʷ�˵�
};
//Ӧ���
struct response_callsearch{
	char trans_flowid[23];//ƽ̨��ˮ��
	char balance[10];//��λ��
};

//��ʷ�˵�
//�����
struct request_historybill{
	char phone_num[13];//�ֻ�����
	char fee_type;//�������� 0������� 1��ʷ�˵� 2��ʷ�굥
	char month[7];//�·ݸ�ʽ YYYYMM

};
//Ӧ���
struct response_historybill{
	char trans_flowid[23];//��ˮ�� YYYYMMDDHHMISS+func_id+4δ�������
	char bill_content[1024];//�˵�����
};
//�˵�����
//�����
struct request_billdetail{
	char phone_num[13];//�ֻ�����
	char fee_type;//��������
	char month_begin[7];//��ʼ�·� ��ʽYYYYMM
	char month_end[7];//��ֹ�·�

};

//Ӧ���
struct response_billdetail{
	char trans_flowid[23];//������ˮ��
	char bill_content[1024];//�굥����
};

//������ӿ�
//�����
struct request_buycard{
	char card_sum[13];//����ֵ
	int char_count;//������
};
//Ӧ���
struct response_buycard{
	char trans_flowid[23];//������ˮ��
	int card_count;//������
	char card_no[30];//�����к�
};


#endif

