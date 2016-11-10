/*
	Name: Adrian Paparelli
	
	Class: CSCI 6410
	
	Assignment 5

	Class Name: MinHeap.java
		
	Class Definition:  This class defines the minHeap and all related functions.  
	
*/

public class MinHeap {
	private HeapNode heap[];
	private int position[];
	private int size;
	
	//Returns parent of provided heap position
	private int parent(int pos)
	{
		return (pos-1)/2;
	}
	
	//Returns left child of provided position
	private int leftChild(int pos)
	{
		return (pos * 2) + 1;
	}	

	//Returns right child of provided position
	private int rightChild(int pos)
	{
		return (pos * 2) + 2;
	}	
	
	//Swaps the heap node at pos1 with the heap node at pos2
	private void swap(int pos1, int pos2)
	{
		HeapNode tempNode = heap[pos1];
		heap[pos1] = heap[pos2];
		heap[pos2] = tempNode;
		
		int tmpPos = position[pos1];
		position[pos1] = position[pos2];
		position[pos2] = tmpPos;
	}
	
	
	//This function will arrange the minhep in proper heap order.
	private void heapify(int pos)
	{
		if (size == 0)
			return;
		
	    int left = leftChild(pos);
	    int right = rightChild(pos);
	    int mindex = pos;
	    
	    if(left >= size)
	        return; //Leaf node
	    
	    if(heap[mindex].getDistance() > heap[left].getDistance())
	        mindex = left;
	    
	    if((right < size) && (heap[mindex].getDistance() > heap[right].getDistance()))
	        mindex = right;
	        
	    if(mindex != pos)
	    {
	        swap(mindex,pos);
	        heapify(mindex);
	    }
	}
	
	//Constructor to initialize a MinHeap with 100 entries.
	public MinHeap()
	{
		size = 100;
		heap = new HeapNode[size];
		position  = new int[size];
	}
	
	//Constructor to create a minHeap with n entries.
	public MinHeap(int n)
	{
		size = n;
		heap = new HeapNode[size];
		position = new int[size];
	}
	
	//Constructor to create a minHeap with heap nodes defined by input array
	public void buildMinHeap(HeapNode input[])
	{
		for(int i = 0; i < size; i++)
		{
			heap[i] = input[i];
			position[i] = i;
		}
		
		for(int i = size-1; i >= 0; i--)
		{
			heapify(i);
		}
	}
	
	//Function to extract the min value of the heap and then rearrange the remainder of the heap into
	// minHeap order.
	public HeapNode heapExtractMin()
	{
		if(size == 0)
			throw new IndexOutOfBoundsException();
		
		HeapNode min = heap[0];
		heap[0] = heap[size-1];
		size--;
		heapify(0);
		return min;
	}
	// Function to set the position value of the heap node that contains vertex V.
	public void heapDecreaseKey(int V, double distance)
	{
		int pos = position[V];
		
		heap[pos].setDistance(distance);
		heap[pos].setVertex(V);
		
		while((pos != 0) && (heap[pos].getDistance() < heap[parent(pos)].getDistance()))
		{
			swap(pos,parent(pos));
			pos = parent(pos);
		}
	}

	// Returns the size of the heap
	public int getSize()
	{
		return size;
	}

	// Returns the heap position of Vertex V
	public int getPosition(int V)
	{
		return position[V];
	}
	
}
