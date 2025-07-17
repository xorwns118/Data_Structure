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
// Deque
void Deque();
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
	//Vector();
	//Stack();
	//Queue();
	Deque();
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

	cout << "=========================" << endl;

	for (cIter = cVecInt.begin(); cIter != cVecInt.end(); ++cIter)
	{
		cout << *cIter << endl;
	}

	cout << "=========================" << endl;

	cIter = cVecInt.find(5);
	cVecInt.insert(cIter, 4);

	for (cIter = cVecInt.begin(); cIter != cVecInt.end(); ++cIter)
	{
		cout << *cIter << endl;
	}
}

#include <stack>
#include "CStack.h"

void Stack()
{
	// LIFO
	stack<int> sInt;
	stack<int> swapInt;

	int result = 0;

	// push
	// 이미 존재하는 객체를 복사하거나 이동하여 추가
	// 복사/이동으로 인해 단순 자료형이나 이미 생성된 객체를 추가할 때 효율적
	sInt.push(1); // 데이터 추가 
	result = sInt.top(); // 현재 존재하는 요소 중 최상단 요소(제일 마지막에 들어온 요소), empty 이면 -1
	sInt.pop(); // stack의 top 데이터 삭제
	bool isEmpty = sInt.empty(); // 아무것도 없는지
	// sInt.size(); // 현재 stack size
	// sInt.swap(stack); // 다른 stack 과 swap

	for (int i = 10; i >= 0; --i)
	{
		sInt.push(i);
	}

	cout << "stack size : " << sInt.size() << endl;
	cout << "stack top : " << sInt.top() << endl;
	
	// emplace
	// 인자를 받아 새 객체를 직접 생성해 추가
	// 직접 생성으로 인해 복잡하거나 큰 객체를 직접 생성할 때 효율적
	// sInt.emplace();

	CStack<int>* iStack = new CStack<int>;

	for (int i = 10; i > 0; --i)
	{
		iStack->Push(i);
	}

	cout << "stack size : " << iStack->Size() << endl;
	cout << "stack top : " << iStack->Top() << endl;

	size_t sSize = iStack->Size();

	for (size_t i = 0; i < sSize; ++i)
	{
		iStack->Pop();
	}

	cout << "empty : " << boolalpha << iStack->Empty() << endl;
}

#include <queue>
#include "CQueue.h"

void Queue()
{
	queue<int> qInt;

	// queue.emplace();
	qInt.push(1);
	// qInt.front(); // 제일 앞의 요소
	// qInt.back(); // 제일 뒤의 요소
	qInt.pop(); // 맨 앞 요소 제거
	// qInt.size(); // 큐 사이즈
	bool b = qInt.empty(); // 비어있는가

	CQueue<int>* iQueue = new CQueue<int>;

	iQueue->Push(1);
	cout << "front : " << iQueue->Front() << endl;
	cout << "back : " << iQueue->Back() << endl;
	cout << "size : " << iQueue->Size() << endl;

	iQueue->Pop();
	cout << "pop -> size : " << iQueue->Size() << endl;

	for (int i = 0; i < 10; ++i)
	{
		iQueue->Push(i);
	}

	cout << "push 0 ~ 9, size : " << iQueue->Size() << endl;
	cout << "front : " << iQueue->Front() << endl;
	cout << "back : " << iQueue->Back() << endl;
	
	size_t size = iQueue->Size();

	for (size_t i = 0; i < size; ++i)
	{
		cout << "remove front : " << iQueue->Front() << endl;
		iQueue->Pop();
	}

	cout << "size : " << iQueue->Size() << endl;
}

#include <deque>
#include "CDeque.h"

void Deque()
{
	deque<int> dInt;

	dInt.push_front(1); // 1
	dInt.push_back(2);  // 1 2
	
	deque<int>::iterator dIter = dInt.begin();

	dInt.insert(++dIter, 3); // 1 3 2
	// dInt.insert(dIter + 1, 4); // 1 3 4 2

	cout << "size : " << dInt.size() << endl;

	for (dIter = dInt.begin(); dIter != dInt.end(); ++dIter)
	{
		cout << dInt[1] << endl;
	}

	dInt.pop_back();
	dInt.pop_front();

	cout << "front : " << dInt.front() << endl; // 3
	cout << "back : " << dInt.back() << endl; // 3

	dIter = dInt.begin();
	dInt.erase(dIter);

	cout << "erase, size : " << dInt.size() << endl;

	/*CDeque<int> iDeque;
	iDeque.PushBack(3);
	iDeque.PushFront(2);
	iDeque.PushFront(1);
	iDeque.PushBack(4);

	iDeque.PopBack();
	iDeque.PopFront();
	iDeque.PopFront();

	iDeque.Resize(10);
	iDeque.Resize(15, 5);*/

	/*CDeque<int> iDeque2(40);

	iDeque2.PushBack(3);
	iDeque2.PushFront(5);*/

	CDeque<int> iDeque3(30, 1);
	iDeque3.PushBack(3);
	iDeque3.PushFront(5);
	iDeque3.Clear();
	iDeque3.PushBack(55);

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
