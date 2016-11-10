/*
	Name: Adrian Paparelli
	
	Class: CSCI 6410
	
	Assignment 5
	
	Class Definition:  This is the main class for Assignment 5.  The program will read input as defined by the assignment
	document.  It will accept a file name as the first command line parameter, if no file is provided the program will accept
	user input one value as a time.
	
	Compile Instructions:  javac *.java
	
	Execution: java Dijkstra <file_name>
*/

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
