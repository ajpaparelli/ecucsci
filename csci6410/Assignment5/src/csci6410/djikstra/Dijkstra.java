import java.util.*;
import java.io.File;
import java.io.FileReader;

public class Dijkstra {

	public static void main(String[] args)
	{
			Scanner sc;
			try
			{
			if(args.length == 0)
				sc = new Scanner(System.in);
			else
			{
				FileReader reader = new FileReader(new File(args[0]));
				sc = new Scanner(reader);
			}
	
			int s, d;
			double w;
			int V = sc.nextInt();
			int E = sc.nextInt();
			Graph g = new Graph(V,E);
			for(int i = 0; i < E; i++)
			{
				s = sc.nextInt();
				d = sc.nextInt();
				w = sc.nextDouble();
				g.addEdge(s,d,w);
			}
			g.shortestPath(1);
		}
		catch(Exception x)
		{}
	}

}

	//	Scanner sc;
	//	try
	//	{
	//		if(args.length == 0)
	//			sc = new Scanner(System.in);
	//		else
	//		{
			//	FileReader reader = new FileReader(new File(args[0]));
			//	sc = new Scanner(reader);
	//		}
	
	//		int s, d;
	//		double w;
			//int V = sc.nextInt();
			//int E = sc.nextInt();
			/*for(int i = 0; i < E; i++)
			{
				s = sc.nextInt();
				d = sc.nextInt();
				w = sc.nextDouble();
				String str = String.valueOf(s) + " " + String.valueOf(d) + " " + Double.toString(w);
				System.out.println(str);
				//g.addEdge(s,d,w);
			}*/	
//	}
	//	catch(Exception x)
	//	{}
