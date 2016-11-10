
public class EdgeNode {
	private Edge edge;
	private EdgeNode next;
	
	public EdgeNode(Edge edge)
	{
		this.edge = edge;
		this.next = null;
	}
	
	public void setNext(EdgeNode node)
	{
		this.next = node;
	}
	
	public EdgeNode getNext()
	{
		return this.next;
	}
	
	public Edge getEdge()
	{
		return this.edge;
	}
}
