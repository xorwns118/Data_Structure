#include "CLinkedList.h"
#include <assert.h>
#include <iostream>

using namespace std;

CLinkedList::CLinkedList()
	: m_pHeadNode(nullptr)
	, m_iSize(0)
{
}

CLinkedList::~CLinkedList()
{
	ReleaseList();
}

void CLinkedList::PushBack(int _i)
{
	if (m_pHeadNode == nullptr)
	{
		tListNode* node = new tListNode;
		node->iData = _i;
		node->pNextNode = nullptr;

		m_pHeadNode = node;
	}
	else
	{
		tListNode* pCurNode = m_pHeadNode;

		while (pCurNode->pNextNode != nullptr)
		{
			pCurNode = pCurNode->pNextNode;
		}

		tListNode* newNode = new tListNode;
		newNode->iData = _i;
		newNode->pNextNode = nullptr;

		pCurNode->pNextNode = newNode;
	}

	++m_iSize;
}

void CLinkedList::PushFront(int _i)
{
	tListNode* originHead = m_pHeadNode;
	tListNode* newNode = new tListNode;

	newNode->iData = _i;
	newNode->pNextNode = originHead;

	m_pHeadNode = newNode;

	++m_iSize;
}

void CLinkedList::PrintList()
{
	tListNode* pCurNode = m_pHeadNode;

	if (pCurNode == nullptr)
		assert(nullptr);

	while (pCurNode != nullptr)
	{
		cout << pCurNode->iData << endl;
		pCurNode = pCurNode->pNextNode;
	}
}

void CLinkedList::ReleaseList()
{
	tListNode* pCurNode = m_pHeadNode;

	while (pCurNode != nullptr)
	{
		tListNode* pDelNode = pCurNode;
		pCurNode = pCurNode->pNextNode;
		delete pDelNode;
	}

	cout << "메모리 해제 완료" << endl;
}