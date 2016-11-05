package csci6410.djikstra;

import java.text.DecimalFormat;
import java.util.ArrayList;

public class Graph {
	
	private static DecimalFormat df2 = new DecimalFormat("#.##");
	private EdgeNode AdjList[];
	private int V;
	private int E;
	
	public Graph(int V, int E)
	{
		this.V = V;
		this.E = E;
		AdjList = new EdgeNode[V];
		for(int i = 0; i < V; i++)
			AdjList[i] = null;
	}
	
	public void addEdge(int source, int destination, double distance)
	{
		EdgeNode tmpNode = new EdgeNode(new Edge(source, destination, distance));
		
		tmpNode.setNext(AdjList[source]);
		AdjList[source] = tmpNode;
	}
	
	public void shortestPath(int source)
	{
		HeapNode nodes[] = new HeapNode[V];
		MinHeap heap = new MinHeap(V);
		double distance[] = new double[V];
		ArrayList<Edge> edges = new ArrayList<Edge>();
		
		for(int i = 0; i < this.V; i++)
		{
			nodes[i] = new HeapNode(i, Double.MAX_VALUE);
			distance[i] = Double.MAX_VALUE;
		}

		heap.buildMinHeap(nodes);
		
		distance[source] = 0;
		
		edges.add(new Edge(0,0,0.0));
		heap.heapDecreaseKey(source, distance[source],edges);
	

		while(heap.getSize() != 0)
		{
			HeapNode minHeapNode = heap.heapExtractMin();
			int u = minHeapNode.getVertex();
			EdgeNode curEdgeNode = AdjList[u];
			while(curEdgeNode != null)
			{
				Edge curEdge = curEdgeNode.getEdge();
				int v = curEdge.getDestination();
				double weight = curEdge.getDistance();
				
				if(((distance[u] != Double.MAX_VALUE) && (distance[v] > distance[u] + weight) ))
				{
					distance[v] = distance[u] + weight;
					edges = minHeapNode.getEdges();
					edges.add(curEdge);
					
					heap.heapDecreaseKey(v, distance[v], edges);
				}
				
				curEdgeNode = curEdgeNode.getNext();			
			}
		}
		
		
		
		for(int i = 0; i < this.V; i++)
		{
			System.out.println("Vertex: " + Integer.toString(i));
			if(distance[i] == Double.MAX_VALUE)
				System.out.println("No Path Defined");
			else
				System.out.println("Distance: " + df2.format(distance[i]));
		}
		

	}
	
	public void printGraph()
	{
		for(int i = 0; i < V; i++)
		{
			EdgeNode curptr = AdjList[i];
			while(curptr != null)
			{
				Edge edge = curptr.getEdge();
				System.out.print(Integer.toString(i) + ": ");
				System.out.print(Integer.toString(edge.getDestination()));
				System.out.print(" --> ");
				curptr = curptr.getNext();
			}
			System.out.println("");
		}
	}
}
