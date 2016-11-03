package csci6410.djikstra;

public class Edge {

	private int source;
	private int destination;
	private double distance;
	
	public Edge(int source, int destination, double distance)
	{
		this.source = source;
		this.destination = destination;
		this.distance = distance;
	}
	
	public int getSource()
	{
		return source;
	}
	
	public int getDestination()
	{
		return destination;
	}
	
	public double getDistance()
	{
		return distance;
	}
	
	public int getAdjacent(int n)
	{
		if(n == this.source)
			return this.source;
		else
			return this.destination;
	}
}
