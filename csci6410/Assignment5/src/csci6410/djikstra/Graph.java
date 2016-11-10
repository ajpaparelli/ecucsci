/*
	Name: Adrian Paparelli
	
	Class: CSCI 6410
	
	Assignment 5
	
	Class Name: Graph.java
		
	Class Definition:  Defines the container class for the edges in the Graphs adjacency list.
	
*/
import java.text.DecimalFormat;
import java.util.ArrayList;

public class Graph {
	
	private static DecimalFormat df2 = new DecimalFormat("#.##");
	private EdgeNode AdjList[];
	private int V;
	private int E;
	
	//Initialize the graph to contain V verticies and E edges, and initalize the adjacency list
	// for each Vertex in the graph
	public Graph(int V, int E)
	{
		this.V = V;
		this.E = E;
		AdjList = new EdgeNode[V];
		for(int i = 0; i < V; i++)
			AdjList[i] = null;
	}
	
	//Function to add an edge to the Graphs adjacency list for the source vertex
	public void addEdge(int source, int destination, double distance)
	{
		EdgeNode tmpNode = new EdgeNode(new Edge(source-1, destination-1, distance));
		
		tmpNode.setNext(AdjList[source-1]);
		AdjList[source-1] = tmpNode;
	}
	
	//Function to calculate the shortest path to each vertex reachable from 
	// the vertex defined by source.  Once the calculation is complete the vertex
	// list will be displayed with distance and path values.  If there is no path
	// the distance will be reported as infinite and no path value will be displayed
	public void shortestPath(int source)
	{
		HeapNode nodes[] = new HeapNode[V];
		MinHeap heap = new MinHeap(V);
		double distance[] = new double[V];
		
		for(int i = 0; i < this.V; i++)
		{
			nodes[i] = new HeapNode(i, Double.MAX_VALUE);
			distance[i] = Double.MAX_VALUE;
		}

		heap.buildMinHeap(nodes);
		
		distance[source-1] = 0;
			
		heap.heapDecreaseKey(source-1, distance[source-1]);
	

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
					ArrayList<Edge> edgeLst = new ArrayList<Edge>(nodes[u].getEdges());
					edgeLst.add(curEdge);
					nodes[v].setEdges(edgeLst);
					heap.heapDecreaseKey(v, distance[v]);
				}
				
				curEdgeNode = curEdgeNode.getNext();			
			}
		}
		
		
		
		for(int i = 0; i < this.V; i++)
		{
			System.out.println("Vertex: " + Integer.toString(i+1));
			if(distance[i] == Double.MAX_VALUE)
			{
				System.out.println("No Path Defined");
			}
			else
			{
				System.out.println("Distance: " + df2.format(distance[i]));
				ArrayList<Edge> edges = nodes[i].getEdges();
				System.out.print("Path: ");
				if(i == (source-1))
					System.out.print("Source Vertex");
				else
				{
					for(int j = 0; j < edges.size(); j++)
					{
						int vertex = edges.get(j).getSource() +1;
						System.out.print(Integer.toString(vertex) + " ");
					}
				}
				System.out.print("\n\n");
			}
		}
		

	}
}
