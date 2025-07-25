#pragma once

struct tListNode
{
	int		iData;
	tListNode*	pNextNode;

};

class CLinkedList
{
private:
	tListNode*		m_pHeadNode;	// 시작 주소
	unsigned int	m_iSize;		// 리스트 크기

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

