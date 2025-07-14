#include <iostream>

#include "CLinkedList.h"

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
	cout << "Hello, World" << endl;

	LinkedList();
	return 0;
}

#include <list>

void LinkedList()
{
	// ���� ����Ʈ -> ���� ��尡 ���� ��常 �˰� ����.
	// ���� ���� ����Ʈ -> ���� ��尡 ���� ���, ���� ��带 �˰� ����.

	list<int> iList = { 0, 1, 2 };

	iList.push_back(3);
	iList.push_front(-1);

	list<int>::iterator iter = iList.begin();

	for (; iter != iList.end(); ++iter)
	{
		cout << *iter << endl;
	}

	CLinkedList* list = new CLinkedList;
	cout << "���� ����Ʈ ũ�� : " << list->size() << endl;
	list->PushBack(1);
	list->PushBack(2);
	cout << "push_back 1, 2 ���� ����Ʈ ũ�� : " << list->size() << endl;
	list->PushFront(0);
	cout << "push_front 0 ���� ����Ʈ ũ�� : " << list->size() << endl;

	cout << "���� ����Ʈ" << endl;
	list->PrintList();
	
	cout << "�޸� ����" << endl;
	list->ReleaseList();
}

void Array()
{

}

void Vector()
{
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
