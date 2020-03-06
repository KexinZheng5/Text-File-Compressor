/* \large 
\underline{array class}*/
#pragma once
#include <stdexcept>

/*
uses template. The datatype of the stored element will be indicated by T
*/
template <typename T>
class array
{
	private: 
		/* 
		Attributes: 
		p is the pointer to the beginning of the array. 
		length stores the capacity of the array.  
		*/
		T* p;
		int length;
		
	public: 
		/* 
		Constructors
		*/
		array()
		{
			p = new T[1];
			length = 1;
		}
		array(int n)
		{
			p = new T[n];
			length = n;
		}
		
		/*
		Destructor
		*/
		~array()
		{
			/* It frees the memory if p is not a null pointer */
			if(p != nullptr)
				delete [] p;
		}

		/* 
		get length
		*/
		int getLength(){ return length; }
		
		/* 
		overloaded operator =
		*/
		array operator=(array& a)
		{
			/* It frees the memory of the current object because it is no longer needed. Then, p and length of the other object, a, will be assigned to the current object. To delete a, a.p is set to null pointer to prevent a from modifying or deleting its original array, and a.length is set to 0.*/
			delete [] p;
			p = a.p;
			length = a.length;
			a.p = nullptr; 
			a.length = 0;
			return a;
		}
		
		/*	
		overloaded operator []
		*/
		T& operator[](int i)
		{
			/* throws an exception if the index is out of range. Else, it returns the element at index i. */
			if(i < 0 || i > length - 1)
			{
				throw std::out_of_range("index out of range");
			}
			return p[i];
		}
		
		/*
		function created to test if p is a null pointer
		*/
		bool isNullPointer(){ return p == nullptr; }
};


