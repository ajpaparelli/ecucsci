
public class MinHeap {
	private HeapNode heap[];
	private int position[];
	private int size;
	
	private int parent(int pos)
	{
		return (pos-1)/2;
	}
	
	private int leftChild(int pos)
	{
		return (pos * 2) + 1;
	}	

	private int rightChild(int pos)
	{
		return (pos * 2) + 2;
	}	
	
	private void swap(int pos1, int pos2)
	{
		
		HeapNode tempNode = heap[pos1];
		heap[pos1] = heap[pos2];
		heap[pos2] = tempNode;
		
		int tmpPos = position[pos1];
		position[pos1] = position[pos2];
		position[pos2] = tmpPos;
	}
	
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
	
	public MinHeap()
	{
		size = 100;
		heap = new HeapNode[size];
		
	}
	
	public MinHeap(int n)
	{
		size = n;
		heap = new HeapNode[size];
		position = new int[size];
	}
	
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

	public int getSize()
	{
		return size;
	}

	public int getPosition(int V)
	{
		return position[V];
	}
	
}
