#pragma once
#define MaxSize 300

template <class T>
class TStack
{
	int size, top;
	T *array;
public:
	TStack(int s=MaxSize): size(s), top(-1)
	{
		if (size<0) throw "negative size";
		if (size>MaxSize) throw "very big size";
		array = new T[size];
	}
	TStack(const TStack &st): size(st.size), top(st.top)
	{
		array = new T[size];
		for (int i=0;i<size;i++)
			array[i]=st.array[i];
	}
	virtual ~TStack()
	{
		delete[] array;
	}
	bool empty() const
	{
		return top==-1;
	}
	bool full() const
	{
		return top==size-1;
	}
	virtual void push(const T val)
	{
		if (full()) throw "stack is full";
		array[++top]=val;
	}
	virtual T pop()
	{
		if (empty()) throw "stack is empty";
		return array[top--];
	}
	virtual T Top()
	{
		if (empty()) throw "stack is empty";
		return array[top];
	}
	void print()
	{
        for (int i=0;i<=top;i++)
		{
			cout<<array[i]<<" | ";
		}
		cout << endl;
	}
	void Clear()
	{
		top = -1;
	}
	int GetSize() const
	{
		return size;
	}
	int GetTop() const
	{
		return top;
	}
};