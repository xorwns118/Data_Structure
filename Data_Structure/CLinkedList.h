#pragma once

struct tListNode
{
	int		iData;
	tListNode*	pNextNode;

};

class CLinkedList
{
private:
	tListNode*		m_pHeadNode;	// ���� �ּ�
	unsigned int	m_iSize;		// ����Ʈ ũ��

public:
	void PushBack(int _i);
	void PushFront(int _i);
	unsigned int size() { return m_iSize; }
	void PrintList();
	void ReleaseList();

public:
	CLinkedList();
	~CLinkedList();
};

