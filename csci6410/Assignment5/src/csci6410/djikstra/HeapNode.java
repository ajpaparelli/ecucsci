package csci6410.djikstra;

import java.util.ArrayList;

public class HeapNode {
	
	private double distance = Double.MAX_VALUE;
	private int V;
	private boolean visited = false;
	private ArrayList<Edge> edges = new ArrayList<Edge>();
	
	public HeapNode(int V, double distance)
	{
		this.V = V;
		this.distance = distance;
	}
	
	public double getDistance()
	{
		return distance;
	}
	
	public void setDistance(double val)
	{
		this.distance = val;
	}
	
	public boolean getVisited()
	{
		return visited;
	}
	
	public void setVisited(boolean val)
	{
		this.visited = val;
	}
	
	public ArrayList<Edge> getEdges()
	{
		return edges;
	}
	
	public void setEdges(ArrayList<Edge> edges)
	{
		this.edges = edges;
	}
	
	public void setVertex(int V)
	{
		this.V = V;
	}
	
	public int getVertex()
	{
		return this.V;
	}
	
}
