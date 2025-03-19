/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 *
 * @param graph - the graph to search
 * @return the minimum edge weight
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 */
int GraphTools::findMinWeight(Graph& graph) {
    vector<Edge> edges = graph.getEdges();
    for(size_t i = 0 ; i < edges.size(); i++){
        graph.setEdgeLabel(edges[i].source, edges[i].dest, "UNEXPLORED");
    }
    vector<Vertex> verticies = graph.getVertices();
    for (size_t i = 0 ; i < verticies.size() ; i++){
        graph.setVertexLabel(verticies[i], "UNEXPLORED");
    }
    
    Edge minWeightEdge = BFS(graph, verticies[0]);
    graph.setEdgeLabel(minWeightEdge.source, minWeightEdge.dest, "MIN");
    return minWeightEdge.weight;
}




/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    unordered_map<Vertex, Vertex> parent;

    // TODO
    // 1. Set all vertices as unexplored

    // 2. Do a modified BFS. See the BFS function below as a guideline, but
    //    your BFS here only needs to populate the "parent" map and stop once the short-
    //    est path has been found.

    // 3. Use the unordered map to trace from a path from the end to the start,
    //    counting edges. You should set edges to "minpath" here too.

    if (graph.getEdges().size()==0) {
        return 0;
    } 
	vector<Vertex> vertices = graph.getVertices();
	vector<Edge> edges = graph.getEdges();
	for (int i = 0 ; i < vertices.size() ; i++) {
	    graph.setVertexLabel(vertices[i],"UNEXPLORED");
    }
	for (int j = 0 ; j < edges.size() ; j++) {
		graph.setEdgeLabel(edges[j].source,edges[j].dest,"UNEXPLORED");
    }
    Vertex temp = start;	
	graph.setVertexLabel(temp,"VISITED");		
	queue<Vertex> q_graph;		
	q_graph.push(temp);
	unordered_map<Vertex,Vertex> tempgraph;
    vector<Vertex> neighbors;
	bool flag = false;
	while (!q_graph.empty()&&!flag) {
		temp = q_graph.front();
		q_graph.pop();
		neighbors=graph.getAdjacent(temp);
		for(int i = 0 ; i < neighbors.size() && !flag ; i++) {
			if (neighbors[i] == end) {
			    flag = true;
            } else if(graph.getVertexLabel(neighbors[i]) == "UNEXPLORED") {
				graph.setEdgeLabel(temp,neighbors[i],"DISCOVERY");				
				graph.setVertexLabel(neighbors[i],"VISITED");
				q_graph.push(neighbors[i]);
				tempgraph[neighbors[i]] = temp;
			} else if(graph.getEdgeLabel(temp,neighbors[i]) == "UNEXPLORED") {
				graph.setEdgeLabel(temp,neighbors[i],"CROSS");
			}
		}
	}
    graph.setEdgeLabel(temp,end,"CROSS");
	graph.setEdgeLabel(temp,end,"MINPATH");
	int count = 1;
	while (temp!=start) {
		Vertex hold = tempgraph[temp];
		graph.setEdgeLabel(temp,hold,"MINPATH");
		temp = hold;
		count ++;
	}
	return count;
}

/**
 * Finds a minimal spanning tree on a graph.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class given in dsets.cpp to help you with
 *  Kruskal's algorithm.
 *
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    int a;
    int b;
    int graphSize;
	DisjointSets set;
	graphSize = graph.getVertices().size();
	set.addelements(graphSize);
	vector<Edge> edges = graph.getEdges();
	sort(edges.begin(), edges.end());
    for (int i = 0 ; i < edges.size() ; i++) {
        a= set.find(edges[i].dest);
		b= set.find(edges[i].source);
        if (a != b) {
            graph.setEdgeLabel(edges[i].source, edges[i].dest, "MST");
            set.setunion(a,b);
        }
	}
       
}

/**
 * Does a BFS of a graph, keeping track of the minimum
 *  weight edge seen so far.
 * @param g - the graph
 * @param start - the vertex to start the BFS from
 * @return the minimum weight edge
 */
Edge GraphTools::BFS(Graph& graph, Vertex start)
{
    queue<Vertex> q;
    graph.setVertexLabel(start, "VISITED");
    q.push(start);
    Edge min;
    min.weight = INT_MAX;

    while (!q.empty()) {
        Vertex v = q.front();
        q.pop();
        vector<Vertex> adj = graph.getAdjacent(v);
        for (size_t i = 0; i < adj.size(); ++i) {
            if (graph.getVertexLabel(adj[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(v, adj[i], "DISCOVERY");
                graph.setVertexLabel(adj[i], "VISITED");
                q.push(adj[i]);
                int weight = graph.getEdgeWeight(v, adj[i]);
                if (weight < min.weight) {
                    min.source = v;
                    min.dest = adj[i];
                    min.weight = weight;
                }
            } else if (graph.getEdgeLabel(v, adj[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(v, adj[i], "CROSS");
                int weight = graph.getEdgeWeight(v, adj[i]);
                if (weight < min.weight) {
                    min.source = v;
                    min.dest = adj[i];
                    min.weight = weight;
                }
            }
        }
    }
    return min;
}
