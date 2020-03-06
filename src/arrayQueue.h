/* \large 
\underline{ArrayQueue class}*/
#pragma once
#include "array.h"

template <typename T>
class ArrayQueue
{
private: 
	/*
	Attributes: 
	j is the starting index of the queue
	n is the number of element in the queue
	a is the backing array
	*/
	int j;
	int n; 
	array<T> a;
	
	/* 
	resize: allocate more memory or free unused memory
	\begin{Verbatim}
Pseudocode:
	resize()
		b = new array(max(1,2n))
		for k in 0,1,2...,n - 1 do
			b[k] = a[(j + k) mod length(a)]
		a = b
		j = 0
\end{Verbatim}
	*/
	void resize()
	{
		/* creates another array that has a size of 2n and copies the elements to the new array. */
		array<T> temp(2*n);
		for(int i = 0; i < n; i++)
		{
			temp[i] = a[(j+i) % a.getLength()];
		}
		a = temp;
		j = 0; 
	}
	
public: 
	/*
	Default constructor:
	Note: a is already initialized by the default constructor. 
\begin{Verbatim}
Pseudocode:
	initialize()
		a = new array(1)
		j = 0
		n = 0
\end{Verbatim}
	*/
	ArrayQueue()
	{
		j = n = 0; 
	}
	/*
	Parameterized constructor for testing
	*/
	ArrayQueue(int c, int N, int J, T arr[])
	{
		array<T> b(c); 
		for(int i = 0; i < c; i++)
			b[i] = arr[i]; 
		a = b; 
		n = N; 
		j = J;
	}
	
	/*
	add: 
	\begin{Verbatim}
Pseudocode:
	add(x)
		if n == length(a) then resize()
		a[(j + n) mod length(a)] = x
		n = n + 1
		return true
\end{Verbatim}
	*/
	bool add(T x)
	{
		/*
		If the list is full, then resize it.
		*/
		if(n == a.getLength())
			resize();
		/*
		add the element to the end and increment n
		*/
		a[(j+n) % a.getLength()] = x; 
		n++;
		
		return true;
	}
	/*
	remove:
	\begin{Verbatim}
Pseudocode:
	remove()
		x = a[j]
		j = (j + 1) mod length(a)
		n = n - 1
		if length(a) >= 3n then resize()
		return x
\end{Verbatim}
	*/
	T remove()
	{
		/*
		save the value of the first element
		increment j(the starting index) and decrement n
		*/
		T temp = a[j]; 
		j = (j+1) % a.getLength(); 
		n--;
		/*
		If two thirds of the list is empty, then resize/shrink it.
		Note: n need to be greater than 0 to call resize so that resize does not create a new array with length of 0. 
		*/
		if(3*n <= a.getLength() && n > 0)
			resize();
		
		return temp;
	}
	
	/*
	size:
	*/
	int size(){ return n; }
	
	/*
	capacity: return length of a
	*/
	int capacity(){ return a.getLength(); }
};
