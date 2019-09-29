#pragma once
#ifndef _XXB_H
#define _XXB_H
#include <assert.h>

//���Ա�ͨ��ģ��
template<typename X> class xxb {
private:
	void operator =(const xxb&){}
	xxb(const xxb&) {}
public:
	xxb() {}
	virtual ~xxb(){}
	//���麯��
	virtual void clear() = 0;
	virtual void insert(const X& item) = 0;
	virtual void append(const X& item) = 0;
	virtual X remove() = 0;
	virtual void moveToStart() = 0;
	virtual void moveToEnd() = 0;
	virtual void prev() = 0;  //ǰ��
	virtual void next() = 0;  //����
	virtual int length() = 0;
	virtual int currPos() const = 0;  //const�����þ��Ǵ˺��������޸ĳ�Ա������ֵ
	virtual void moveToPos(int pos) = 0;
	virtual const X& getValue() const = 0;
};

//˳����̳������Ա�
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
#endif
