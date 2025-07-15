#pragma once
#include <assert.h>

template<typename T>
struct tStackNode
{
	T				tValue;
	tStackNode<T>*	pDownValue;
};

template<typename T>
class CStack
{
private:
	tStackNode<T>*	m_tTop;
	size_t			m_iSize;

public:
	void Push(T& _value);
	void Pop();
	T& Top();
	size_t Size() { return m_iSize; }
	bool Empty() { return m_iSize == 0; }

public:
	CStack();
	~CStack();
};

template<typename T>
inline CStack<T>::CStack()
	: m_tTop(nullptr)
	, m_iSize(0)
{
}

template<typename T>
inline CStack<T>::~CStack()
{
	while (!Empty())
	{
		Pop();
	}
}

template<typename T>
inline void CStack<T>::Push(T& _value)
{
	tStackNode<T>* newNode = new tStackNode<T>;

	newNode->tValue = _value;

	if (Empty())
		newNode->pDownValue = nullptr;
	else
		newNode->pDownValue = this->m_tTop;

	this->m_tTop = newNode;

	++m_iSize;
}

template<typename T>
inline void CStack<T>::Pop()
{
	if (Empty())
		return;

	tStackNode<T>* deleteNode = m_tTop;
	m_tTop = deleteNode->pDownValue;

	delete deleteNode;
	--m_iSize;
}

template<typename T>
inline T& CStack<T>::Top()
{
	if (Empty())
		assert(nullptr);

	return m_tTop->tValue;
}
