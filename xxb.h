#pragma once
#ifndef _XXB_H
#define _XXB_H
#include <assert.h>

//线性表通用模板
template<typename X> class xxb {
private:
	void operator =(const xxb&){}
	xxb(const xxb&) {}
public:
	xxb() {}
	virtual ~xxb(){}
	//纯虚函数
	virtual void clear() = 0;
	virtual void insert(const X& item) = 0;
	virtual void append(const X& item) = 0;
	virtual X remove() = 0;
	virtual void moveToStart() = 0;
	virtual void moveToEnd() = 0;
	virtual void prev() = 0;  //前移
	virtual void next() = 0;  //后移
	virtual int length() = 0;
	virtual int currPos() const = 0;  //const的作用就是此函数不能修改成员变量的值
	virtual void moveToPos(int pos) = 0;
	virtual const X& getValue() const = 0;
};

//顺序表，继承于线性表
template<typename E>
class sxb :public xxb<E> {
private:
	int maxSize;
	int listSize;
	int curr;
	E* listArray;
public:
	sxb(int size = 50)
	{
		maxSize = size;
		listSize = curr = 0;
		listArray = new E[maxSize];
	}
	~sxb() { delete[]listArray; }
	void clear()
	{
		delete[] listArray;
		curr = listSize = 0;
		listArray = new E[maxSize];
	}
	void insert(const E& item)
	{
		assert(listSize < maxSize, "list capacity exceeded");
		for (int i = listSize; i > curr; i--)
			listArray[i] = listArray[i - 1];
		listArray[curr] = item;
		listSize++;
	}
	void append(const E& item)
	{
		assert(listSize < maxSize, "list capacity exceeded");
		listArray[listSize++] = item;
	}
	E remove()
	{
		assert((curr >= 0) && (listSize < maxSize), "no element");
		E it = listArray[curr];
		for (int i = curr; i < listSize - 1; i++)
			listArray[i] = listArray[i + 1];
		listSize--;
		return it;
	}
	void moveToStart() { curr = 0; }
	void moveToEnd() { curr = listSize; }
	void prev() { if (curr != 0) curr--; }
	void next() { if (curr < listSize)curr++; }
	int length() { return listSize; }
	int currPos()const { return curr; }
	void moveTopos(int pos)
	{ 
		assert((pos >= 0) && (pos <= listSize), "pos out of range");
		curr = pos; 
	}
	const E& getValue() const
	{
		assert((curr >= 0) && (curr <= listSize), "no current element");
		return listArray[curr];
	}
};

//链表，继承于线性表
template<typename T> class Link
{
public:
	T element;
	Link* next;
	Link(const T& elemval,Link*nextval=NULL)
	{
		element = elemval; next = nextval;
	}
	Link(Link* nextval = NULL) { next = nextval; }
};
template<typename L>
class lb :public xxb<L>
{
private:
	Link<L>* head;	//头指针
	Link<L>* tail;	//尾指针
	Link<L>* curr;	//当前指针
	int cnt;		//元素数
	void init()
	{
		curr = head = tail = new Link<L>;
		cnt = 0;
	}
	void removeAll() 
	{
		while (head != NULL)
		{
			curr = head;
			head = head->next;
			delete curr;
		}
	}
public:
	lb() { init(); }
	~lb() { removeAll(); }
	void print()const;
	void clear() { removeAll(); init(); }
	void insert(const L& item)
	{
		curr->next = new Link<L>(item, curr->next);
		if (tail = curr) tail = curr->next;
		cnt++;
	}
	void append(const L& item)
	{
		tail = tail->next = new Link(item, NULL);
		cnt++;
	}
	L remove()
	{
		assert(curr > next != NULL, "no element");
		L it = curr->next->element;
		Link<L>* itemp = curr->next;
		if (tail = curr->next)tail = curr;
		curr->next = curr->next->next;
		delete itemp;
		cnt--;
		return it;
	}
	void moveToStart() { curr = head; }
	void moveToEnd() { curr = tail; }
	void prev()
	{
		if (curr == head)return;
		Link<L>* temp = head;
		while (temp->next != curr)temp = temp->next;
		curr = temp;
	}
	void next()
	{
		if (curr != tail) curr = curr->next;
	}
	int length() const { return cnt; }
	int currPos() const 
	{
		Link<L>* temp = head;
		int i;
		for (i = 0; curr != temp; i++)
			temp = temp->next;
		return i;
	}
	void moveToPos(int pos)
	{
		assert((pos >= 0) && (pos <= cnt), "position is wrong!");
		curr = head;
		for (int i = 0; i < pos; i++)
			curr = curr->next;
	}
	const L& getValue() const
	{
		assert(curr->next != NULL, "No value");
		return curr->next->element;
	}
};
#endif
