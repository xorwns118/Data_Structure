#pragma once
#include <assert.h>

const int g_iChunkSize = 20;

template<typename T>
struct tDequeList
{
	T				tValue[g_iChunkSize];
	tDequeList<T>*	pPrevList;
	tDequeList<T>*	pNextList;
	int				iFrontIdx;
	int				iBackIdx;
	bool			bIsFull;
	bool			bIsEmpty;
	// ���ο� ������ ���� �� �� �ڿ� ���ο� ����Ʈ ���� ����
};

template<typename T>
class CDeque
{
private:
	T*				m_pHeadValue;
	T*				m_pTailValue;
	tDequeList<T>*	m_pFrontList;	// ���� ���ʿ� �Ҵ�� ���
	tDequeList<T>*	m_pBackList;	// ���� ���ʿ� �Ҵ�� ���
	size_t			m_iSize;		// ���� ����
	size_t			m_iListCount;	// ������� ����Ʈ ����

public:
	void Assign(int _count, const T _value); // _value ������ _count���� ���� �Ҵ�
	const T& At(const int idx); // idx��° ���� ����, ��ȿ������ �����ϹǷ� CDeque[idx] ���� ��������� ����
	const T& Front() { return m_pHeadValue; } // ù��° ���� ����
	const T& Back() { return m_pTailValue; } // ������ ���� ����
	void Clear(); // ��� ���� ����
	void PushFront(const T& _value); // ù��° ���� �տ� _value �߰�
	void PopFront(); // ù��° ���� ����
	void PushBack(const T& _value); // ������ ���� �ڿ� _value �߰�
	void PopBack(); // ������ ���� ����
	void Resize(const size_t _i); // ũ�⸦ _i �� ����, �� Ŀ���� ������ ����ִ� ���Ҹ� 0���� ����
	void Resize(const size_t _i, const T _value); // ũ�⸦ _i �� ����, �� Ŀ���� �� ����ִ� ���Ҹ� _value �� ����
	const size_t Size() { return m_iSize; } // ������ ���� ��ȯ
	void Insert(const int _idx, const T _value); // _idx ��ġ�� _value ���� 
	void Insert(const int _idx, const int _count, const T _value); // _idx ��ġ�� _count ���� _value ����
	bool Empty() { return m_iSize == 0; } // ���Ұ� ��������� true
	
	class iterator;
	iterator Begin() { return iterator(this, m_pFrontList, m_pHeadValue); } // ù��° ���Ҹ� ����Ŵ
	iterator End() { return iterator(this, m_pBackList, ++m_pTailValue); } // �������� ���� ���Ҹ� ����Ŵ
	iterator RBegin() { return iterator(this, m_pBackList, m_pTailValue); } // reverse begin()
	iterator REnd() { return iterator(this, m_pFrontList, --m_pHeadValue); } // reverse end()
	iterator Erase(iterator _iter); // _iter �� ����Ű�� ���� ����, �� �� ���� ���� �Ǵ� �� ���� �� ���ҵ��� ��� ä��, �����Ѱ� iterator ��ȯ

public:
	const T& operator [] (int _idx) {} // ��ȿ���� �������� �ʰ� idx��° ���� ����
	
private:
	void init_list();
	void make_new_list_back();
	void make_new_list_front();

public:
	CDeque();						// ����ִ� deque ����
	CDeque(const size_t _i);				// default ������ �ʱ�ȭ�� _i ���� ���Ҹ� ���� deque ����
	CDeque(const size_t _i, const T _value);	// _value ������ �ʱ�ȭ �� _i ���� ���Ҹ� ���� deque ����
	CDeque(const CDeque<T>* _copy);		// �ٸ� deque �� ����
	~CDeque();

	class iterator
	{
	private:
		CDeque<T>*		m_pDeque;
		tDequeList<T>*	m_pCurList; // ���� ����Ű�� �ִ� ����Ʈ
		T*				m_pValue;	// ���� ����Ű�� �ִ� ����

	public:
		iterator& operator ++ ()
		{
			// ���� ����Ű�� ���Ұ� �迭 �������� ������ �� ���� �迭�� �Ѿ
		}
		T& operator * ()
		{
			return *m_pValue;
		}

	public:
		iterator()
			: m_pDeque(nullptr)
			, m_pCurList(nullptr)
			, m_pValue(nullptr)
		{

		}

		iterator(CDeque<T>* _deque, tDequeList<T>* _list, T* _value)
			: m_pDeque(_deque)
			, m_pCurList(_list)
			, m_pValue(_value)
		{

		}

		~iterator()
		{

		}

		friend class CDeque;
	};
};

template<typename T>
inline void CDeque<T>::init_list()
{
	tDequeList<T>* newList = new tDequeList<T>;

	newList->pNextList = nullptr;
	newList->pPrevList = nullptr;
	newList->iFrontIdx = 0;
	newList->iBackIdx = -1;
	newList->bIsFull = false;
	newList->bIsEmpty = true;

	this->m_pFrontList = newList;
	this->m_pBackList = newList;
}

template<typename T>
inline void CDeque<T>::make_new_list_back()
{
	tDequeList<T>* newList = new tDequeList<T>;

	newList->pPrevList = m_pBackList;
	newList->pNextList = nullptr;
	newList->iFrontIdx = 0;
	newList->iBackIdx = -1;
	newList->bIsFull = false;
	newList->bIsEmpty = true;

	m_pBackList->pNextList = newList;
	m_pBackList = newList;

	++m_iListCount;
}

template<typename T>
inline void CDeque<T>::make_new_list_front()
{
	tDequeList<T>* newList = new tDequeList<T>;
	newList->pPrevList = nullptr;
	newList->pNextList = m_pFrontList;
	newList->iFrontIdx = g_iChunkSize;
	newList->iBackIdx = g_iChunkSize - 1;
	newList->bIsFull = false;
	newList->bIsEmpty = true;

	m_pFrontList->pPrevList = newList;
	m_pFrontList = newList;

	++m_iListCount;
}

template<typename T>
inline CDeque<T>::CDeque()
	: m_pFrontList(nullptr)
	, m_pBackList(nullptr)
	, m_pHeadValue(nullptr)
	, m_pTailValue(nullptr)
	, m_iSize(0)
	, m_iListCount(0)
{
	init_list();
}

template<typename T>
inline CDeque<T>::CDeque(const size_t _i)
	: m_pFrontList(nullptr)
	, m_pBackList(nullptr)
	, m_pHeadValue(nullptr)
	, m_pTailValue(nullptr)
	, m_iSize(0)
	, m_iListCount(0)
{
	init_list();
	
	for (size_t i = 0; i < _i; ++i)
	{
		T t = {};

		PushBack(t);
	}
}

template<typename T>
inline CDeque<T>::CDeque(const size_t _i, const T _value)
	: m_pFrontList(nullptr)
	, m_pBackList(nullptr)
	, m_pHeadValue(nullptr)
	, m_pTailValue(nullptr)
	, m_iSize(0)
	, m_iListCount(0)
{
	init_list();

	for (size_t i = 0; i < _i; ++i)
	{
		PushBack(_value);
	}
}

template<typename T>
inline CDeque<T>::CDeque(const CDeque<T>* _copy)
	: m_pFrontList(_copy->m_pFrontList)
	, m_pBackList(_copy->m_pBackList)
	, m_pHeadValue(_copy->m_pHeadValue)
	, m_pTailValue(_copy->m_pTailValue)
	, m_iSize(_copy->m_iSize)
	, m_iListCount(_copy->m_iListCount)
{
	// ���� ���� �����, ���� �ּҸ� �����ϰ� ����.
	// ���� ����� ���� �ʱ�ȭ ���� ���ο� deque ��ü�� ������ �Ȱ��� ������ �� �ִ� ���� ���簡 �ʿ���

	//init_list();

	//for (int i = 0; i < m_iSize; ++i)
	//{
	//	// �� �κп� ���� ���� ������ �� �ֵ��� ����
	//}
}

template<typename T>
inline CDeque<T>::~CDeque()
{
}

template<typename T>
inline void CDeque<T>::Assign(const int _count, const T _value)
{
}

template<typename T>
inline const T& CDeque<T>::At(const int idx)
{
	// TODO: ���⿡ return ���� �����մϴ�.
}

template<typename T>
inline void CDeque<T>::Clear()
{
	size_t size = m_iSize;

	// ��� ���Ҹ� ����
	for (size_t i = 0; i < size; ++i)
	{
		PopBack();
	}
	
	// �Ҵ�Ǿ��ִ� ���� ó�� ������� �Ѿ
	while (m_pFrontList->pPrevList != nullptr)
	{
		m_pFrontList = m_pFrontList->pPrevList;
	}

	// FrontList �� �Ҵ�Ǿ��ִ� ��ϵ��� �߰��������� ������
	for (size_t i = 0; i < m_iListCount / 2; ++i)
	{
		m_pFrontList = m_pFrontList->pNextList;
	}

	m_pBackList = m_pFrontList;
}

template<typename T>
inline void CDeque<T>::PushFront(const T& _value)
{
	// ���� ���� ����Ʈ�� �� �� ���
	if (m_pFrontList->bIsFull)
	{
		if (m_pFrontList->pPrevList == nullptr) // ����Ʈ�� �պκп� �Ҵ��س��� ����Ʈ�� ���°��
			make_new_list_front();
		else // �Ҵ��س��� ����Ʈ�� �̹� �ִ� ���
			m_pFrontList = m_pFrontList->pPrevList;
	}

	if (m_pFrontList->bIsEmpty)
	{
		m_pFrontList->bIsEmpty = false;

		// �պ��� ä������ ����Ʈ�� ������� ���
		m_pFrontList->iFrontIdx = g_iChunkSize;
		m_pFrontList->iBackIdx = g_iChunkSize - 1;
	}

	--m_pFrontList->iFrontIdx;

	m_pFrontList->tValue[m_pFrontList->iFrontIdx] = _value;

	if (m_pFrontList->iFrontIdx == 0)
		m_pFrontList->bIsFull = true;

	m_pHeadValue = &m_pFrontList->tValue[m_pFrontList->iFrontIdx];

	if (m_pTailValue == nullptr)
		m_pTailValue = &m_pFrontList->tValue[m_pFrontList->iFrontIdx];

	++m_iSize;
}

template<typename T>
inline void CDeque<T>::PopFront()
{
	if (m_iSize == 0)
		assert(nullptr);

	++m_pFrontList->iFrontIdx;

	// HeadValue ����
	if (m_pFrontList->iFrontIdx == g_iChunkSize)
	{
		m_pFrontList->bIsEmpty = true;
		m_pFrontList = m_pFrontList->pNextList;

		m_pHeadValue = &m_pFrontList->pNextList->tValue[0];
	}
	else
	{
		m_pHeadValue = &m_pFrontList->tValue[m_pFrontList->iFrontIdx];
	}

	--m_iSize;

	if (m_iSize == 0)
	{
		m_pHeadValue = nullptr;
		m_pTailValue = nullptr;
	}
}

template<typename T>
inline void CDeque<T>::PushBack(const T& _value)
{
	// ���� ���� ����Ʈ�� �� �� ��� 
	if (m_pBackList->bIsFull)
	{
		if (m_pBackList->pNextList == nullptr) // ����Ʈ�� �޺κп� �Ҵ��س��� ����Ʈ�� ���°��
			make_new_list_back();
		else // �Ҵ��س��� ����Ʈ�� �̹� �ִ� ���
			m_pBackList = m_pBackList->pNextList;
	}

	if (m_pBackList->bIsEmpty)
	{
		m_pBackList->bIsEmpty = false;

		// �ں��� ä�������� ����Ʈ�� ������� ���, ex) �ں��� ä���� ����Ʈ�� �ʱ�ȭ �Ǿ��� ��
		m_pBackList->iFrontIdx = 0;
		m_pBackList->iBackIdx = -1;
	}

	++m_pBackList->iBackIdx;

	m_pBackList->tValue[m_pBackList->iBackIdx] = _value;
	
	if (m_pBackList->iBackIdx == g_iChunkSize - 1)
		m_pBackList->bIsFull = true;

	if (m_pHeadValue == nullptr)
		m_pHeadValue = &m_pBackList->tValue[m_pBackList->iBackIdx];

	m_pTailValue = &m_pBackList->tValue[m_pBackList->iBackIdx];

	++m_iSize;
}

template<typename T>
inline void CDeque<T>::PopBack()
{
	if (m_iSize == 0)
		assert(nullptr);

	if (m_pBackList->bIsFull)
	{
		m_pBackList->bIsFull = false;
	}

	--m_pBackList->iBackIdx;

	// TailValue ����
	if (m_pBackList->iBackIdx == -1)
	{
		m_pBackList->bIsEmpty = true;
		m_pBackList = m_pBackList->pPrevList;

		m_pTailValue = &m_pBackList->pPrevList->tValue[g_iChunkSize - 1];
	}
	else
	{
		m_pTailValue = &m_pBackList->tValue[m_pBackList->iBackIdx];
	}

	--m_iSize;

	if (m_iSize == 0)
	{
		m_pHeadValue = nullptr;
		m_pTailValue = nullptr;
	}
}

template<typename T>
inline void CDeque<T>::Resize(const size_t _i)
{
	if (_i > m_iSize)
	{
		size_t iDiff = _i - m_iSize;

		for (size_t i = 0; i < iDiff; ++i)
		{
			T t = {};
			PushBack(t);
		}
	}
	else if (_i < m_iSize)
	{
		size_t iDiff = m_iSize - _i;

		for (size_t i = 0; i < iDiff; ++i)
		{
			PopBack();
		}
	}

	m_iSize = _i;
}

template<typename T>
inline void CDeque<T>::Resize(const size_t _i, const T _value)
{
	if (_i > m_iSize)
	{
		size_t iDiff = _i - m_iSize;

		for (size_t i = 0; i < iDiff; ++i)
		{
			PushBack(_value);
		}
	}
	else if (_i < m_iSize)
	{
		size_t iDiff = m_iSize - _i;

		for (size_t i = 0; i < iDiff; ++i)
		{
			PopBack();
		}
	}

	m_iSize = _i;
}

template<typename T>
inline void CDeque<T>::Insert(const int _idx, const T _value)
{
}

template<typename T>
inline void CDeque<T>::Insert(const int _idx, int _count, const T _value)
{
}

template<typename T>
inline typename CDeque<T>::iterator CDeque<T>::Erase(iterator _iter)
{
	return iterator();
}
