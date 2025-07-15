#pragma once
#include <assert.h>

template<typename T>
struct tQueueNode
{
	T				tValue;
	tQueueNode<T>*	pNextNode;
	tQueueNode<T>*	pPrevNode;
};

template<typename T>
class CQueue
{
private:
	tQueueNode<T>*	m_tHeadNode;
	tQueueNode<T>*	m_tTailNode;
	size_t			m_iSize;

public:
	void Push(const T& _value);
	void Pop();
	T& Front();
	T& Back();
	bool Empty() { return m_iSize == 0; }
	size_t Size() { return m_iSize; }

public:
	CQueue();
	~CQueue();
};

template<typename T>
inline CQueue<T>::CQueue()
	: m_tHeadNode(nullptr)
	, m_tTailNode(nullptr)
	, m_iSize(0)
{

}

template<typename T>
inline CQueue<T>::~CQueue()
{
	while (!Empty())
	{
		Pop();
	}
}

template<typename T>
inline void CQueue<T>::Push(const T& _value)
{
	tQueueNode<T>* newNode = new tQueueNode<T>;

	newNode->tValue = _value;

	if (Empty())
	{
		newNode->pNextNode = nullptr;
		newNode->pPrevNode = nullptr;
		this->m_tHeadNode = newNode;
	}
	else
	{
		newNode->pNextNode = nullptr;
		newNode->pPrevNode = this->m_tTailNode;

		m_tTailNode->pNextNode = newNode;
		m_tTailNode = newNode;
	}

	m_tTailNode = newNode;

	++m_iSize;
}

template<typename T>
inline void CQueue<T>::Pop()
{
	// FIFO

	if (Empty())
		return;

	tQueueNode<T>* delNode = m_tHeadNode;
	m_tHeadNode = delNode->pNextNode;

	// 삭제하려는 노드가 이미 HeadNode 일 때
	if(m_tHeadNode != nullptr)
		m_tHeadNode->pPrevNode = nullptr;
	delete delNode;

	--m_iSize;
}

template<typename T>
inline T& CQueue<T>::Front()
{
	if (Empty())
		assert(nullptr);

	return m_tHeadNode->tValue;
}

template<typename T>
inline T& CQueue<T>::Back()
{
	if (Empty())
		assert(nullptr);

	return m_tTailNode->tValue;
}