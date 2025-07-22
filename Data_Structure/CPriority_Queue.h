#pragma once

template<typename T>
class CPriority_Queue
{
private:


public:
	void Push();
	void Pop();
	T Top();
	size_t Size();
	bool Empty();

public:
	CPriority_Queue();
	~CPriority_Queue();
};

