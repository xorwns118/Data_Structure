#pragma once
#include <assert.h>

template<typename T>
class CVector
{
private:
	T*		m_pData;
	size_t	m_iCount;
	size_t	m_iCapacity;

public:
	void push_back(const T& _data);
	size_t size() { return m_iCount; }
	size_t capacity() { return m_iCapacity; }
	void reallocate(size_t _i);
	T& front() { return m_pData[0]; }

	class iterator;
	iterator begin() { return iterator(this, &m_pData[0]); }
	iterator end() { return iterator(this, &m_pData[m_iCount]); }
	iterator find(const T& _data);
	iterator erase(iterator& _iter);
	void insert(iterator& _iter, const T& _data);

public:
	T& operator [] (size_t _index) { return m_pData[_index]; }
	const T& operator [] (size_t _index) const { return m_pData[_index]; }

public:
	CVector();
	~CVector();

	class iterator
	{
	private:
		CVector<T>*	m_pVec;
		T*			m_pData;
		bool		m_bValid;

	public:
		T& operator * ()
		{
			return *m_pData;
		}

		iterator& operator ++ ()
		{
			if (m_pData)
				++m_pData;

			return *this;
		}

		iterator& operator ++ (int)
		{
			iterator copy(*this);

			++m_pData;

			return copy;
		}

		iterator& operator -- ()
		{
			if (m_pData)
				--m_pData;

			return *this;
		}

		iterator& operator -- (int)
		{
			iterator copy(*this);

			--m_pData;

			return copy;
		}

		bool operator == (const iterator& _other)
		{
			return m_pData == _other.m_pData;
		}

		bool operator != (const iterator& _other)
		{
			return !(*this == _other);
		}

	public:
		iterator() 
			: m_pVec(nullptr)
			, m_pData(nullptr)
			, m_bValid(false)
		{

		}
		iterator(CVector<T>* _pVec, T* _pData)
			: m_pVec(_pVec)
			, m_pData(_pData)
			, m_bValid(false)
		{

		}
		~iterator() {}

		friend class CVector;
	};
};

template<typename T>
inline CVector<T>::CVector()
{
	m_pData = new T[2];
	m_iCount = 0;
	m_iCapacity = 2;
}

template<typename T>
inline CVector<T>::~CVector()
{
	delete[] m_pData;
}

template<typename T>
inline void CVector<T>::push_back(const T& _data)
{
	if (m_iCount >= m_iCapacity)
	{
		reallocate(m_iCapacity * 2);
	}

	m_pData[m_iCount] = _data;
	++m_iCount;
}

template<typename T>
inline void CVector<T>::reallocate(size_t _i)
{
	if (_i <= m_iCapacity)
		return;

	T* newData = new T[_i];

	for (size_t i = 0; i < m_iCount; ++i)
	{
		newData[i] = m_pData[i];
	}

	delete[] m_pData;
	m_pData = newData;
	m_iCapacity = _i;
}

template<typename T>
inline typename CVector<T>::iterator CVector<T>::find(const T& _data)
{
	for (size_t i = 0; i < m_iCount; ++i)
	{
		if (this->m_pData[i] == _data)
		{
			return iterator(this, &m_pData[i]);
		}
	}
	return iterator(this, nullptr);
}

template<typename T>
inline typename CVector<T>::iterator CVector<T>::erase(iterator& _iter)
{
	if (_iter == end())
		assert(nullptr);

	// 현재 가리키고 있는 인덱스 주소 - 시작 인덱스 주소
	size_t index = _iter.m_pData - m_pData;

	for (size_t i = index; i < m_iCount; ++i)
	{
		m_pData[i] = m_pData[i + 1];
	}

	--m_iCount;

	return iterator(this, &m_pData[index]);
}

template<typename T>
inline void CVector<T>::insert(iterator& _iter, const T& _data)
{
	if (m_iCount + 1 >= m_iCapacity)
	{
		reallocate(m_iCapacity * 2);
	}

	size_t index = _iter.m_pData - m_pData;

	T temp = m_pData[m_iCount - 1];

	for (size_t i = m_iCount - 1; i > index; --i)
	{
		m_pData[i] = m_pData[i - 1];
	}

	m_pData[index] = _data;
	push_back(temp); // push back 할 때 ++m_iCount
}
