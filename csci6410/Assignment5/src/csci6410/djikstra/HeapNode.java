/*
	Name: Adrian Paparelli
	
	Class: CSCI 6410
	
	Assignment 5

	Class Name: HeapNode.java
		
	Class Definition:  This class defines the heapNode which will contain information about the verticies
	contained in the heap.
	
*/

import java.util.ArrayList;

public class HeapNode {
	
	private double distance = Double.MAX_VALUE;
	private int V;
	private boolean visited = false;
	private ArrayList<Edge> edges = new ArrayList<Edge>();
	
	//Generate a new heap node for Vertex V and a distance = distance.
	public HeapNode(int V, double distance)
	{
		this.V = V;
		this.distance = distance;
	}
	
	//Return the heap nodes distance value
	public double getDistance()
	{
		return distance;
	}
	
	//Set the heap nodes distance value
	public void setDistance(double val)
	{
		this.distance = val;
	}
	
	//Return the heap nodes visited value
	public boolean getVisited()
	{
		return visited;
	}
	
	//Set the heap nodes visited value
	public void setVisited(boolean val)
	{
		this.visited = val;
	}
	
	//Set the arrayList containing the path to Vertex V
	public ArrayList<Edge> getEdges()
	{
		return edges;
	}
	
	//Get the path list to Vertex V
	public void setEdges(ArrayList<Edge> edges)
	{
		this.edges = edges;
	}
	
	//Set the value of the vertex contained in the heap node
	public void setVertex(int V)
	{
		this.V = V;
	}
	
	//Get the value of the vertex contained in the heap node
	public int getVertex()
	{
		return this.V;
	}
	
}
