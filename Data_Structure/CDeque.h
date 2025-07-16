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
	// 새로운 공간을 만들 때 앞 뒤에 새로운 리스트 구조 연결
};

template<typename T>
class CDeque
{
private:
	T*				m_pHeadValue;
	T*				m_pTailValue;
	tDequeList<T>*	m_pFrontList;	// 제일 앞쪽에 할당된 블록
	tDequeList<T>*	m_pBackList;	// 제일 뒤쪽에 할당된 블록
	size_t			m_iSize;		// 원소 개수

public:
	void Assign(int _count, const T _value); // _value 값으로 _count개의 원소 할당
	const T& At(const int idx); // idx번째 원소 참조, 유효범위를 점검하므로 CDeque[idx] 보다 상대적으로 느림
	const T& Front() { return m_pHeadValue; } // 첫번째 원소 참조
	const T& Back() { return m_pTailValue; } // 마지막 원소 참조
	void Clear(); // 모든 원소 제거
	void PushFront(const T& _value); // 첫번째 원소 앞에 _value 추가
	void PopFront(); // 첫번째 원소 제거
	void PushBack(const T& _value); // 마지막 원소 뒤에 _value 추가
	void PopBack(); // 마지막 원소 제거
	void Resize(const size_t _i); // 크기를 _i 로 변경, 더 커졌을 때에는 비어있는 원소를 0으로 변경
	void Resize(const size_t _i, const T _value); // 크기를 _i 로 변경, 더 커졌을 때 비어있는 원소를 _value 로 변경
	const size_t Size() { return m_iSize; } // 원소의 개수 반환
	void Insert(const int _idx, const T _value); // _idx 위치에 _value 삽입 
	void Insert(const int _idx, const int _count, const T _value); // _idx 위치에 _count 개의 _value 삽입
	bool Empty() { return m_iSize == 0; } // 원소가 비어있으면 true
	
	class iterator;
	iterator Begin() { return iterator(this, m_pFrontList, m_pHeadValue); } // 첫번째 원소를 가리킴
	iterator End() { return iterator(this, m_pBackList, ++m_pTailValue); } // 마지막의 다음 원소를 가리킴
	iterator RBegin() { return iterator(this, m_pBackList, m_pTailValue); } // reverse begin()
	iterator REnd() { return iterator(this, m_pFrontList, --m_pHeadValue); } // reverse end()
	iterator Erase(iterator _iter); // _iter 가 가리키는 원소 제거, 앞 뒤 원소 개수 판단 후 적은 쪽 원소들을 당겨 채움, 제거한곳 iterator 반환

public:
	const T& operator [] (int _idx) {} // 유효범위 점검하지 않고 idx번째 원소 참조
	
private:
	void init_list();
	void make_new_list_back();
	void make_new_list_front();

public:
	CDeque();						// 비어있는 deque 생성
	CDeque(const size_t _i);				// default 값으로 초기화된 _i 개의 원소를 가진 deque 생성
	CDeque(const size_t _i, const T _value);	// _value 값으로 초기화 된 _i 개의 원소를 가진 deque 생성
	CDeque(const CDeque<T>* _copy);		// 다른 deque 를 복사
	~CDeque();

	class iterator
	{
	private:
		CDeque<T>*		m_pDeque;
		tDequeList<T>*	m_pCurList; // 현재 가리키고 있는 리스트
		T*				m_pValue;	// 현재 가리키고 있는 원소

	public:
		iterator& operator ++ ()
		{
			// 지금 가리키는 원소가 배열 마지막에 존재할 때 다음 배열로 넘어감
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
}

template<typename T>
inline CDeque<T>::CDeque()
	: m_pFrontList(nullptr)
	, m_pBackList(nullptr)
	, m_iSize(0)
{
	init_list();;
}

template<typename T>
inline CDeque<T>::CDeque(const size_t _i)
	: m_pFrontList(nullptr)
	, m_pBackList(nullptr)
	, m_iSize(_i)
{
	init_list();;

	while (_i > g_iChunkSize)
	{
		for (size_t i = 0; i < _i; ++i)
		{
			PushBack(0);
		}

		_i -= 32;

		make_new_list_back();
	}
}

template<typename T>
inline CDeque<T>::CDeque(const size_t _i, const T _value)
	: m_pFrontList(nullptr)
	, m_pBackList(nullptr)
	, m_iSize(_i)
{
	init_list();

	while (_i > g_iChunkSize)
	{
		for (size_t i = 0; i < _i; ++i)
		{
			PushBack(_value);
		}

		_i -= g_iChunkSize;

		make_new_list_back();
	}
}

template<typename T>
inline CDeque<T>::CDeque(const CDeque<T>* _copy)
	: m_pFrontList(_copy->m_pFrontList)
	, m_pBackList(_copy->m_pBackList)
	, m_iSize(_copy->m_iSize)
{
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
	// TODO: 여기에 return 문을 삽입합니다.
}

template<typename T>
inline void CDeque<T>::Clear()
{
}

template<typename T>
inline void CDeque<T>::PushFront(const T& _value)
{
	if (m_pFrontList->bIsFull)
	{
		make_new_list_front();
	}

	tDequeList<T>& target = *m_pFrontList;

	if (target.bIsEmpty)
		target.bIsEmpty = false;

	--target.iFrontIdx;

	target.tValue[target.iFrontIdx] = _value;

	if (target.iFrontIdx == 0)
		target.bIsFull = true;

	m_pHeadValue = &target.tValue[target.iFrontIdx];

	++m_iSize;

	if (m_iSize == 1)
		m_pTailValue = &target.tValue[target.iFrontIdx];
}

template<typename T>
inline void CDeque<T>::PopFront()
{
	if (m_iSize == 0)
		assert(nullptr);

	tDequeList<T>& target = *m_pFrontList;

	++target.iFrontIdx;

	--m_iSize;

	if (m_iSize == 0)
	{
		target.bIsEmpty = true;

		m_pHeadValue = nullptr;
		m_pTailValue = nullptr;

		return;
	}

	// HeadValue 갱신
	if (target.iFrontIdx == g_iChunkSize)
	{
		m_pFrontList = target.pNextList;
		m_pHeadValue = &target.pNextList->tValue[0];
	}
	else
	{
		m_pHeadValue = &target.tValue[target.iFrontIdx];
	}
}

template<typename T>
inline void CDeque<T>::PushBack(const T& _value)
{
	if (m_pBackList->bIsFull)
	{
		make_new_list_back();
	}

	tDequeList<T>& target = *m_pBackList;

	if (target.bIsEmpty)
		target.bIsEmpty = false;

	++target.iBackIdx;

	target.tValue[target.iBackIdx] = _value;
	
	if (target.iBackIdx == 31)
		target.bIsFull = true;

	m_pTailValue = &target.tValue[target.iBackIdx];

	++m_iSize;

	if (m_iSize == 1)
		m_pHeadValue = &target.tValue[target.iBackIdx];
}

template<typename T>
inline void CDeque<T>::PopBack()
{
	if (m_iSize == 0)
		assert(nullptr);

	tDequeList<T>& target = *m_pBackList;

	--target.iBackIdx;

	--m_iSize;

	if (m_iSize == 0)
	{
		target.bIsEmpty = true;

		m_pHeadValue = nullptr;
		m_pTailValue = nullptr;

		return;
	}

	// TailValue 갱신
	if (target.iBackIdx == -1)
	{
		m_pBackList = target.pPrevList;
		m_pTailValue = &target.pPrevList->tValue[g_iChunkSize - 1];
	}
	else
	{
		m_pTailValue = &target.tValue[target.iBackIdx];
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
