/**********************************************************************

*�ļ�����
		CMyList.cpp
*�ļ�������
		CMyList��ķ�װ
*�����ߣ�
		�Ʊ�

*����ʱ�䣺
2011-6-8

******************************************************************/


#include <stdlib.h>
#include <string.h>
#include "CMyList.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyList::CMyList()
{
	pHead=(PNode)malloc(LEN_NODE);
	if (pHead==NULL)
	{
		//cout<<"����ʧ��"<<endl;
	}
	else
	{
		pHead->pData=NULL;
		pHead->next=NULL;
		pCurNode = pHead;
		//cout<<"�����ɹ�"<<endl;
	}


}

CMyList::~CMyList()
{
	PNode p1;
	int free_count=0;

	if (pHead==NULL)
	{
		//cout<<"�ͷ�ʧ��"<<endl;
	}
	else
	{
		p1=pHead->next;
		while(p1!=NULL)
		{
			pHead->next=p1->next;
			free(p1);
			p1=pHead->next;
			free_count++;
		}
		free(pHead);
		//cout<<"�ͷųɹ�"<<free_count<<"���ڵ�"<<endl;
	}

}

/*
���ܣ�
�����ݱ��浽�����β��
������
Data ��Ҫ����Ļ�����
����ֵ��

*/
void CMyList::addNode(void *pData)
{
	PNode p1,p2;

	if (pHead==NULL)
	{
		return;
	}

	p2= (PNode) malloc(LEN_NODE);
	memset(p2,0,LEN_NODE);
	if (p2==NULL)
	{
		return;
	}

	p2->pData=pData;
	p2->next=NULL;
	if (pHead->next==NULL)
	{
		pHead->next=p2;
		pCurNode = p2;
		return;
	}
	p1=pHead->next;
	while(p1->next!=NULL)
	{
		p1=p1->next;
	}
	p1->next=p2;
	pCurNode = p2;

}


void CMyList::delNode(int nIndex)
{
	PNode p1,p2;
	int i=1;

	if (pHead==NULL)
	{
		return;
	}
	p1=pHead;
	for(i=0;i<nIndex;i++)
	{
		if (p1->next==NULL)
		{
			if (i<nIndex)
			{
				return;
			}
			else if (i==nIndex)
			{
				break;
			}

		}

		p2=p1;
		p1=p1->next;
	}
	p2->next=p1->next;
	free(p1);
}


/*
���ܣ�
�õ�ǰָ��ָ������ͷ
������
����ֵ��
*/
void CMyList::begin()
{
	pCurNode =pHead;
}

/*
���ܣ�
�ӵ�ǰָ�뿪ʼ�Ƿ�����һ���ڵ�
������
����ֵ��true ���� flase ������
*/
bool CMyList::hasNext()
{
	if (pCurNode->next !=NULL)
	{
		return true;
	}
	else return false;
}

/*
���ܣ�
�õ�ǰָ��ָ����һ���ڵ�
������
����ֵ��ָ����һ���ڵ�
*/

void * CMyList::Next()
{
	if (pCurNode->next !=NULL)
	{
		pCurNode =pCurNode->next;
		return pCurNode->pData;
	}
	else return NULL;
}



/*
���ܣ�
��������Ľڵ�ĸ���
������
����ֵ��
 �ڵ����
*/

int CMyList::count()
{
	PNode p1;
	int count=0;

	if (pHead==NULL)
	{
		return 0;
	}

	p1=pHead->next;
	while(p1!=NULL)
	{
		p1=p1->next;
		count++;
	}
	return count;
}



/*
���ܣ�
����ָ��λ�õĽڵ�
������
Index �ڵ��������е��±�

����ֵ��
 �±��Ӧ�Ľڵ�
*/

PNode CMyList::get(const int index)
{
	PNode p1;
	int i=0;

	if (pHead==NULL)
	{
		return NULL;
	}

	if (index <= 0)
	{
		return NULL;
	}

	p1=pHead->next;
	for(i=1;i<index;i++)
	{
		if (p1->next==NULL)
		{
			return NULL;
		}
		p1=p1->next;
	}
	return p1;

}


/*
���ܣ�
����ָ���±�ڵ������
������
Index �ڵ��������е��±�

����ֵ��
 �±��Ӧ�Ľڵ�
*/
void * CMyList::operator[] (int nIndex)
{

	pCurNode=get(nIndex);

	if (pCurNode != NULL)
	{
		return pCurNode->pData;
	}
	return NULL;
}


/*
���ܣ�
���ص�ǰ�ڵ������
������
����ֵ��
*/

void * CMyList::ReturnNow ()
{
	if (pCurNode != NULL)
	{
		return pCurNode->pData;
	}
	return NULL;
}


void CMyList::delAll()
{
    PNode p1;
	//int free_count=0;

	if (pHead==NULL)
	{
		//cout<<"�ͷ�ʧ��"<<endl;
	}
	else
	{
		p1=pHead->next;
		while(p1!=NULL)
		{
			pHead->next=p1->next;
			free(p1);
			p1=pHead->next;
			//free_count++;
		}
		//cout<<"�ͷųɹ�"<<free_count<<"���ڵ�"<<endl;
	}
}

