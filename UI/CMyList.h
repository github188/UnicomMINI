#ifndef CMYLIST_H
#define CMYLIST_H

#define LEN_NODE sizeof(NODE)

typedef struct ListNode
{
	struct ListNode *next;
	void *pData;
}NODE;

typedef NODE * PNode;

class CMyList
{
public:
	CMyList();
	virtual ~CMyList();
	void addNode(void *pData);  //��ӽڵ�
	void delNode(int nIndex);   //ɾ���ڵ�
	void begin();			//�õ�ǰָ��ָ������ͷ
	bool hasNext();			//�ӵ�ǰָ�뿪ʼ�Ƿ�����һ���ڵ�
	void * Next();		//�õ�ǰָ��ָ����һ���ڵ�
	void * operator[] (int nIndex); //���ָ���±�Ľڵ������
	void * ReturnNow (); //��õ�ǰ�ڵ������
	int count();    //����ܸ���
	void delAll();      //ɾ��ͷ���������
protected:

	PNode get(const int index); //��ȡָ��λ�õ�����
private:
	PNode pHead;
	PNode pCurNode;

};
#endif // CMYLIST_H
