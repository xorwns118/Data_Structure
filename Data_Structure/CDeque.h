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
	int				iListNum;
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
	int				m_iListCount;	// 만들어진 리스트 개수

public:
	void Assign(int _count, const T _value);	// _value 값으로 _count개의 원소 할당
	const T& At(const int idx);					// idx번째 원소 참조, 유효범위를 점검하므로 CDeque[idx] 보다 상대적으로 느림
	const T& Front() { return m_pHeadValue; }	// 첫번째 원소 참조
	const T& Back() { return m_pTailValue; }	// 마지막 원소 참조
	void Clear();								// 모든 원소 제거
	void PushFront(const T& _value);			// 첫번째 원소 앞에 _value 추가
	void PopFront();							// 첫번째 원소 제거
	void PushBack(const T& _value);				// 마지막 원소 뒤에 _value 추가
	void PopBack();								// 마지막 원소 제거
	void Resize(const size_t _i);				// 크기를 _i 로 변경, 더 커졌을 때에는 비어있는 원소를 0으로 변경
	void Resize(const size_t _i, const T _value); // 크기를 _i 로 변경, 더 커졌을 때 비어있는 원소를 _value 로 변경
	const size_t Size() { return m_iSize; }		// 원소의 개수 반환
	bool Empty() { return m_iSize == 0; }		// 원소가 비어있으면 true
	
	class iterator;
	iterator Begin() { return iterator(this, m_pFrontList, 0); }				// 첫번째 원소를 가리킴
	iterator End() { return iterator(this, m_pFrontList, m_iSize); }			// 마지막의 다음 원소를 가리킴
	iterator RBegin() { return iterator(this, m_pFrontList, m_iSize - 1); }		// reverse begin()
	iterator REnd() { return iterator(this, m_pFrontList , -1); }				// reverse end()
	iterator Erase(iterator _iter); // _iter 가 가리키는 원소 제거, 앞 뒤 원소 개수 판단 후 적은 쪽 원소들을 당겨 채움, 제거한곳 iterator 반환
	iterator Insert(const iterator _iter, const T _value);						// _idx 위치에 _value 삽입, 삽입 위치 반환
	iterator Insert(const iterator _iter, const int _count, const T _value);	// _idx 위치에 _count 개의 _value 삽입

public:
	T& operator [] (int _idx)
	{
		tDequeList<T>* pSearch = m_pFrontList;

		int index = pSearch->iFrontIdx + _idx;

		for (int i = 0; i < index / g_iChunkSize; ++i)
		{
			pSearch = pSearch->pNextList;
		}

		return pSearch->tValue[index % g_iChunkSize];
	}// 유효범위 점검하지 않고 idx번째 원소 참조
	
private:
	void init_list();
	void make_new_list_back();
	void make_new_list_front();

public:
	CDeque();									// 비어있는 deque 생성
	CDeque(const size_t _i);					// default 값으로 초기화된 _i 개의 원소를 가진 deque 생성
	CDeque(const size_t _i, const T _value);	// _value 값으로 초기화 된 _i 개의 원소를 가진 deque 생성
	CDeque(const CDeque<T>* _copy);				// 다른 deque 를 복사
	~CDeque();

	class iterator
	{
	private:
		CDeque<T>*		m_pDeque;
		tDequeList<T>*	m_pCurList;	// 현재 가리키고 있는 리스트
		T*				m_pValue;	// 현재 가리키고 있는 원소
		int				m_iIdx;		// 현재 인덱스

	public:
		iterator& operator ++ ()
		{
			if (m_iIdx > m_pDeque->Size())
				assert(nullptr);

			++m_iIdx;

			// 지금 가리키는 원소가 배열 마지막에 존재할 때 다음 배열로 넘어감
			if (m_iIdx != 0 && m_iIdx % g_iChunkSize == 0)
				m_pCurList = m_pCurList->pNextList;
			
			if (m_iIdx == (int)m_pDeque->Size())
				m_pValue = nullptr;
			else
				m_pValue = &m_pCurList->tValue[m_iIdx % g_iChunkSize];

			return *this;
		}

		T& operator * ()
		{
			return *m_pValue;
		}

		bool operator == (const iterator& _other)
		{
			return m_pValue == _other.m_pValue && m_iIdx == _other.m_iIdx;
		}

		bool operator != (const iterator& _other)
		{
			return !(*this == _other);
		}

	public:
		iterator()
			: m_pDeque(nullptr)
			, m_pCurList(nullptr)
			, m_pValue(nullptr)
			, m_iIdx(0)
		{

		}

		iterator(CDeque<T>* _pDeq, tDequeList<T>* _list, int _idx)
			: m_pDeque(_pDeq)
			, m_pCurList(_list)
			, m_pValue(nullptr)
			, m_iIdx(_idx)
		{
			m_iIdx = _idx;

			if (_idx == _pDeq->Size() || _idx == -1)
			{
				m_pValue = nullptr;
				return;
			}

			tDequeList<T>* pSearch = m_pDeque->m_pFrontList;

			int index = pSearch->iFrontIdx + _idx;

			for (int i = 0; i < index / g_iChunkSize; ++i)
			{
				pSearch = pSearch->pNextList;
			}

			m_pValue = &m_pCurList->tValue[index % g_iChunkSize];
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
	newList->iListNum = 0;

	this->m_pFrontList = newList;
	this->m_pBackList = newList;
}

template<typename T>
inline void CDeque<T>::make_new_list_back()
{
	tDequeList<T>* newList = new tDequeList<T>;

	++m_iListCount;

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
	// 현재 얕은 복사로, 같은 주소를 공유하고 있음.
	// 깊은 복사로 직접 초기화 이후 새로운 deque 객체와 값까지 똑같이 복사할 수 있는 깊은 복사가 필요함

	//init_list();

	//for (int i = 0; i < m_iSize; ++i)
	//{
	//	// 이 부분에 같은 값을 복사할 수 있도록 구현
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
inline const T& CDeque<T>::At(const int _idx)
{
	if (m_iSize <= _idx || _idx < 0)
		assert(nullptr);

	tDequeList<T>* pSearch = m_pFrontList;

	int index = pSearch->iFrontIdx + _idx;

	for (int i = 0; i < index / g_iChunkSize; ++i)
	{
		pSearch = pSearch->pNextList;
	}

	return pSearch->tValue[index % g_iChunkSize];
}

template<typename T>
inline void CDeque<T>::Clear()
{
	size_t size = m_iSize;

	// 모든 원소를 제거
	for (size_t i = 0; i < size; ++i)
	{
		PopBack();
	}
	
	// 할당되어있는 제일 처음 블록으로 넘어감
	while (m_pFrontList->pPrevList != nullptr)
	{
		m_pFrontList = m_pFrontList->pPrevList;
	}

	// FrontList 를 할당되어있는 블록들의 중간지점으로 변경함
	for (size_t i = 0; i < m_iListCount / 2; ++i)
	{
		m_pFrontList = m_pFrontList->pNextList;
	}

	m_pBackList = m_pFrontList;
}

template<typename T>
inline void CDeque<T>::PushFront(const T& _value)
{
	// 제일 앞의 리스트가 꽉 찬 경우
	if (m_pFrontList->bIsFull)
	{
		if (m_pFrontList->pPrevList == nullptr) // 리스트의 앞부분에 할당해놓은 리스트가 없는경우
			make_new_list_front();
		else // 할당해놓은 리스트가 이미 있는 경우
			m_pFrontList = m_pFrontList->pPrevList;
	}

	if (m_pFrontList->bIsEmpty)
	{
		m_pFrontList->bIsEmpty = false;

		// 앞부터 채워졌던 리스트가 비어있을 경우
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

	// HeadValue 갱신
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
	// 제일 뒤의 리스트가 꽉 찬 경우 
	if (m_pBackList->bIsFull)
	{
		if (m_pBackList->pNextList == nullptr) // 리스트의 뒷부분에 할당해놓은 리스트가 없는경우
			make_new_list_back();
		else // 할당해놓은 리스트가 이미 있는 경우
			m_pBackList = m_pBackList->pNextList;
	}

	if (m_pBackList->bIsEmpty)
	{
		m_pBackList->bIsEmpty = false;

		// 뒤부터 채워진졌던 리스트가 비어있을 경우, ex) 뒤부터 채워진 리스트가 초기화 되었을 때
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

	// TailValue 갱신
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
inline typename CDeque<T>::iterator CDeque<T>::Insert(const iterator _iter, const T _value)
{
	tDequeList<T>* pList = m_pBackList;

	if (m_iSize <= 1)
	{
		PushBack(_value);
		return iterator(this, pList, _iter.m_iIdx);
	}

	// 뒷 요소가 더 적으면 뒤로 밀어냄
	if (_iter.m_iIdx > m_iSize / 2)
	{
		PushBack(*m_pTailValue);

		for (int i = (int)m_iSize - 1; i >= _iter.m_iIdx; --i)
		{
			(*this)[i] = (*this)[i - 1];
		}

		(*this)[_iter.m_iIdx] = _value;
	}
	else // 앞 요소가 더 적으면 앞으로 당김
	{
		PushFront(*m_pHeadValue);

		for (int i = 1; i < _iter.m_iIdx; i++)
		{
			(*this)[i] = (*this)[i + 1];
		}

		(*this)[_iter.m_iIdx] = _value;
	}

	pList = m_pFrontList;

	int iListIndex = (pList->iFrontIdx + _iter.m_iIdx) / g_iChunkSize - 1;

	for (int i = 0; i < iListIndex; ++i)
	{
		pList = pList->pNextList;
	}

	return iterator(this, pList, _iter.m_iIdx);
}

template<typename T>
inline typename CDeque<T>::iterator CDeque<T>::Insert(const iterator _iter, int _count, const T _value)
{
	tDequeList<T>* pList = m_pBackList;

	if (m_iSize <= 1)
	{
		for (int i = 0; i < _count; ++i)
		{
			PushBack(_value);
		}

		return iterator(this, pList, _iter.m_iIdx);
	}

	// (왼쪽보다 적을 때)
	// 뒷 요소가 더 적으면 뒤로 밀어냄
	if (_iter.m_iIdx > m_iSize / 2)
	{
		for (int i = 0; i < _count; ++i)
		{
			PushBack(*m_pTailValue);
		}

		for (int i = (int)m_iSize - 1; i >= _iter.m_iIdx; --i)
		{
			(*this)[i] = (*this)[i - _count];
		}

		for (int i = 0; i < _count; ++i)
		{
			(*this)[_iter.m_iIdx + i] = _value;
		}
	}
	else // 앞 요소가 더 적으면 앞으로 당김
	{
		for (int i = 0; i < _count; ++i)
		{
			PushFront(*m_pHeadValue);
		}

		for (int i = 1; i < _iter.m_iIdx; i++)
		{
			(*this)[i] = (*this)[i + _count];
		}

		for (int i = _iter.m_iIdx; i > _iter.m_iIdx - _count; --i)
		{
			(*this)[i] = _value;
		}
	}

	pList = m_pFrontList;

	int iListIndex = (pList->iFrontIdx + _iter.m_iIdx) / g_iChunkSize - 1;

	for (int i = 0; i < iListIndex; ++i)
	{
		pList = pList->pNextList;
	}

	return iterator(this, pList, _iter.m_iIdx);
}

template<typename T>
inline typename CDeque<T>::iterator CDeque<T>::Erase(iterator _iter)
{
	return iterator();
}
