/*
	Name: Adrian Paparelli
	
	Class: CSCI 6410
	
	Assignment 5
	Class Name: Edge.java
		
	Class Definition:  This class defines the storage containers the edges in the graph
	
*/

public class Edge {

	private int source;
	private int destination;
	private double distance;
	
	//Initialize the edge container to the provided edge values
	public Edge(int source, int destination, double distance)
	{
		this.source = source;
		this.destination = destination;
		this.distance = distance;
	}
	
	//Return the source Vertex of the edge
	public int getSource()
	{
		return source;
	}
	
	//Return the destination Vertex of the edge
	public int getDestination()
	{
		return destination;
	}
	
	//Return the distance from the source to destination of the edge
	public double getDistance()
	{
		return distance;
	}
}
