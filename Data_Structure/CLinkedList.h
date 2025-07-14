#pragma once

struct tNode
{
	int		iData;
	tNode*	pNextNode;

};

class CLinkedList
{
private:
	tNode*			m_pHeadNode;	// ���� �ּ�
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

