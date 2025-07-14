#pragma once

// 정적 메모리
template <typename T, size_t N>
class CArray
{
private:
	T*	m_pData[N];

public:
	size_t size() { return N; }

	T& operator [] (size_t _i) { return m_pData[_i]; }
	const T& operator[] (size_t _i) const { return m_pData[_i]; }
	
public:
	CArray();
	~CArray();
};

template<typename T, size_t N>
inline CArray<T, N>::CArray()
{
}

template<typename T, size_t N>
inline CArray<T, N>::~CArray()
{
}
