/*
	Name: Adrian Paparelli
	
	Class: CSCI 6410
	
	Assignment 5

Class Name: EdgeNode.java
		
	Class Definition:  Defines the container class for the edges in the Graphs adjacency list.
	
*/

public class EdgeNode {
	private Edge edge;
	private EdgeNode next;
	
	//Initalize the edge node to "edge"
	public EdgeNode(Edge edge)
	{
		this.edge = edge;
		this.next = null;
	}
	
	//Set the value of the next pointer
	public void setNext(EdgeNode node)
	{
		this.next = node;
	}
	
	//Get the value of the next pointer
	public EdgeNode getNext()
	{
		return this.next;
	}
	
	//Get the edge object contained in the edgenode
	public Edge getEdge()
	{
		return this.edge;
	}
}
