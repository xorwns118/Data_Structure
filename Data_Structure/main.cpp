#include <iostream>

using namespace std;

// Linked List
void LinkedList();
// Array
void Array();
// Vector
void Vector();
// Stack
void Stack();
// Queue
void Queue();
// Priority Queue
void PriorityQueue();
// Heap
void Heap();
// Map
void Map();
// Unordered Map
void UnorderedMap();
// Set
void Set();

int main()
{
	//LinkedList();
	//Array();
	Vector();
	return 0;
}

#include <list>
#include "CLinkedList.h"

void LinkedList()
{
	// 연결 리스트 -> 현재 노드가 다음 노드만 알고 있음.
	// 이중 연결 리스트 -> 현재 노드가 이전 노드, 다음 노드를 알고 있음.

	list<int> iList = { 0, 1, 2 };

	iList.push_back(3);
	iList.push_front(-1);

	list<int>::iterator iter = iList.begin();

	for (; iter != iList.end(); ++iter)
	{
		cout << *iter << endl;
	}

	CLinkedList* list = new CLinkedList;
	cout << "현재 리스트 크기 : " << list->size() << endl;
	list->PushBack(1);
	list->PushBack(2);
	cout << "push_back 1, 2 이후 리스트 크기 : " << list->size() << endl;
	list->PushFront(0);
	cout << "push_front 0 이후 리스트 크기 : " << list->size() << endl;

	cout << "최종 리스트" << endl;
	list->PrintList();
}

#include <array>
#include "CArray.h"

void Array()
{
	int iArr[3] = { 0, 1, 2 };
	int i = iArr[0];
	cout << "첫번째 요소 : " << i << endl;
}

#include <vector>
#include "CVector.h"

void Vector()
{
	vector<int> vecInt;
	vecInt.push_back(0);
	vecInt.push_back(1);

	vector<int>::iterator iter = vecInt.begin();
	++iter;
	vecInt.insert(iter, 3);
	cout << "현재 vector 할당크기 : " << vecInt.capacity() << endl;

	for (iter = vecInt.begin(); iter != vecInt.end(); ++iter)
	{
		cout << *iter << endl;
	}
	iter = vecInt.begin();
	++iter;
	iter = vecInt.erase(iter);
	cout << *iter << endl;

	vecInt.resize(10);

	cout << "현재 vector 할당크기 : " << vecInt.capacity() << endl;

	size_t a = vecInt.size();

	for (size_t i = 0; i < a; ++i)
	{
		vecInt.pop_back();
	}
	
	cout << "현재 vector 메모리 할당량 : " << vecInt.capacity() << endl;
	cout << "현재 vector 사이즈 : " << vecInt.size() << endl;
	CVector<int> cVecInt;
	CVector<int>::iterator cIter;

	cVecInt.push_back(0);
	cVecInt.push_back(1);

	cVecInt[1] = 5;
	cout << "1번째 인덱스 요소 : " << cVecInt[1] << endl;
	
	cIter = cVecInt.begin();
	cout << "cVecInt 0번째 인덱스 요소 : " << *cIter << endl;
	cIter++;
	cout << "cVecInt 1번째 인덱스 요소 : " << *cIter << endl;

	cVecInt.push_back(2);
	cVecInt.push_back(3);
	cVecInt.push_back(4);
	cVecInt.push_back(5);
	cVecInt.push_back(6);
	cVecInt.push_back(7);
	cVecInt.push_back(8);
	cVecInt.push_back(9);

	cIter = cVecInt.begin();
	++(++(++(++cIter)));
	cout << *cIter << endl;
	cIter = cVecInt.erase(cIter);
	cout << *cIter << endl;
}

void Stack()
{
}

void Queue()
{
}

void PriorityQueue()
{
}

void Heap()
{
}

void Map()
{
}

void UnorderedMap()
{
}

void Set()
{
}
