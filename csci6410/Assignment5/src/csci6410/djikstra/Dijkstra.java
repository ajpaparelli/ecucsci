package csci6410.djikstra;

public class Dijkstra {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Graph g = new Graph(9,10);
		
		g.addEdge(0, 1, 13.50);
		g.addEdge(0, 2, 12.10);
		g.addEdge(2, 3, 12.30);
		
		g.addEdge(1, 3, 1.40);
		g.addEdge(3, 4, 14.00);
		g.addEdge(3, 5, 12.10);
		
		g.addEdge(4, 6, 9.90);
		g.addEdge(5, 7, 4.30);
		g.addEdge(6, 8, 2.30);
		g.addEdge(7, 8, 5.60);
		g.shortestPath(0);
	}

}
