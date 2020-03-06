#pragma once
/* \large 
\underline{BinaryHeap class}*/
#include "array.h"
#include "hnode.h"

template <typename T>
class BinaryHeap
{
private: 
	/* 
	Attributes: 
	a is the array to store the nodes. 
	n is the number of nodes in the heap.  
	*/
	array<T> a; 
	int n; 
	/*
	\vspace{500px}\clearpage
	\marginnote{
	functions for getting the left child, right child, and parent of a node at index i
	\includegraphics[scale=0.7]{get.png}
	}
	*/
	int left(int i){ return 2*i+1; }
	int right(int i){ return 2*i+2; }
	int parent(int i){ return (i-1)/2; }
	/* 
	\vspace{500px}\clearpage
	\marginnote{
	resize: 
	allocate more memory or free unused memory
}
	*/
	void resize()
	{
		/* 
		create another array that is has a size of $2n$ and copy all the elements to the new array. 
		*/
		array<T> temp(n*2);	
		for(int i = 0; i < n; i++)
		{
			temp[i] = a[i];
		}
		a = temp; 
	}	
	/*
	\vspace{500px}\clearpage
	\marginnote{
	bubbleUp: 
	\includegraphics[scale=0.7]{bubbleUp.png}
}
	*/
	void bubbleUp(int i)
	{
		/*
		p stores the index of the parent of a node at position i
		*/
		int p = parent(i);
		/*
		While the parent has larger value than the child node, exchange their values. Then, set i to the index of the parent and p to the parent of i.
		*/
		while(a[i] < a[p])
		{
			T temp = a[i];
			a[i] = a[parent(i)];
			a[p] = temp; 
			i = p; 
			p = parent(i);
		}
	}
		/*
		\vspace{500px}\clearpage
		\marginnote{
	trickleDown: 
	\includegraphics[scale=0.7]{trickleDown.png}
}
	*/
	void trickleDown(int i)
	{
		/*
		While the current index is not negative
		*/
		while(i >= 0)
		{
			/*
			create the variable j that stores the index of a node that needs to be swapped with the current node at the end. r stores the index of the current node's right child.
			*/
			int j = -1;
			int r = right(i);
			/*
			If r is less than n, meaning within the range, and the right child is smaller than the current node, then the right child can be swapped with the current node. 
			*/
			if(r < n && a[r] < a[i])
			{
				/*
				However, we need to check if the left child, with index l, is even smaller than the right child. If so, we will be swapping the current node with the left child instead. 
				*/
				int l = left(i);
				if(a[l] < a[r])
					j = l; 
				else
					j = r;
			}
			/*
			If the right child cannot be swapped with the current node, we check the left child. If l is less than n and the left child is smaller than the current node, we will swap the left chlid with the current node. 
			*/
			else
			{
				int l = left(i);
				if(l < n && a[l] < a[i])
					j = l;
			}
			/*
						\vspace{500px}\clearpage
			If j is not negative, meaning there is a node to swap with the current node, we will exchange the values of the 2 nodes. 
			*/
			if(j >= 0)
			{
				T temp = a[i]; 
				a[i] = a[j];
				a[j] = temp; 
			}
			/*
			Then, we set i to j. If j is negative, the while loop will end. 
			*/
			i = j;
		}	
	}
	
public: 
	/*
	\vspace{500px}\clearpage
	\marginnote{
	constructor: 
	Note: a is already initialized by its constructor.
	\includegraphics[scale=0.7]{init1.png}
}
	*/
	BinaryHeap()
	{
		n = 0; 
	}
	/*
	\vspace{500px}\clearpage
	\marginnote{
	add: 
	\includegraphics[scale=0.7]{add1.png}
}
	*/
	bool add(T x)
	{
		/*
		First, check if the array needs to be expanded. 
		*/
		if(n == a.getLength())
			resize(); 
		/*
		add the node the end of the array, and increment n. bubbleUp is called to put the new element to the correct position. 
		*/	
		a[n] = x; 
		n++; 
		bubbleUp(n-1); 
	}
	/*
	\vspace{500px}\clearpage
	\marginnote{
	remove: 
	\includegraphics[scale=0.7]{remove1.png}
}
	*/
	T remove()
	{
		/*
		store the smallest value at the root as temp and set the root to the last element in the array. n is decemented, and trickleDown is called to put the new root to the corret position.
		*/
		T temp = a[0]; 
		a[0] = a[n-1]; 
		n--;
		trickleDown(0);
		/*
		%\vspace{500px}\clearpage
		Check if the array needs to be shrunk. 
		*/
		if(3*n <= a.getLength() && n > 0)
			resize(); 
		return temp;
	}
	
	int size(){ return n; }
};
