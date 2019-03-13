#include <iostream>
#include <list>
#include <stack>
using namespace std;

/*
* The solution is to find the strongly connected components.
* The answer is the number of vertices in the scc where all
* edges have direction from outside the component. In kosaraju
* algorithm this is the last component in DFS.
*/

/*
* Link for finding the scc using kosaraju algorithm.
* https://www.geeksforgeeks.org/strongly-connected-components/.
*/

/* Holds each time number of edges in a scc */
int count;

class Graph {
	int V; /* Number of vertices */
	list<int> *adj; /* An array of adjacency lists */

	/* Fills Stack with vertices (in increasing order of finishing
	* times). The top element of stack has the maximum finishing
	* time
	*/
	void fillOrder(int v, bool visited[], stack<int> &Stack);

	/* A recursive function to print DFS starting from v */
	void DFSUtil(int v, bool visited[]);
public:
	Graph(int V);
	void addEdge(int v, int w);

	/* The main function that finds strongly connected
	* components
	*/
	void printSCCs();

	/* Function that returns reverse (or transpose) of this graph */
	Graph getTranspose();
};

Graph::Graph(int V) {
	this->V = V;
	adj = new list<int>[V];
}

/* A recursive function to run DFS starting from v */
void Graph::DFSUtil(int v, bool visited[]) {
	/* Mark the current node as visited and print it */
	visited[v] = true;
  count = count + 1;
	/* Recur for all the vertices adjacent to this vertex */
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFSUtil(*i, visited);
}

Graph Graph::getTranspose() {
	Graph g(V);
	for (int v = 0; v < V; v++) {
		/* Recur for all the vertices adjacent to this vertex */
		list<int>::iterator i;
		for(i = adj[v].begin(); i != adj[v].end(); ++i) {
			g.adj[*i].push_back(v);
		}
	}
	return g;
}

void Graph::addEdge(int v, int w) {
	adj[v].push_back(w); /* Add w to v’s list. */
}

void Graph::fillOrder(int v, bool visited[], stack<int> &Stack) {
	/* Mark the current node as visited and print it */
	visited[v] = true;

	/* Recur for all the vertices adjacent to this vertex */
	list<int>::iterator i;
	for(i = adj[v].begin(); i != adj[v].end(); ++i)
		if(!visited[*i])
			fillOrder(*i, visited, Stack);

	/* All vertices reachable from v are processed by now, push v */
	Stack.push(v);
}

/* The main function that finds and prints all strongly connected
* components
*/
void Graph::printSCCs() {
	stack<int> Stack;

	/* Mark all the vertices as not visited (For first DFS) */
	bool *visited = new bool[V];
	for(int i = 0; i < V; i++)
		visited[i] = false;

	/* Fill vertices in stack according to their finishing times */
	for(int i = 0; i < V; i++)
		if(visited[i] == false)
			fillOrder(i, visited, Stack);

	/* Create a reversed graph */
	Graph gr = getTranspose();

	/* Mark all the vertices as not visited (For second DFS) */
	for(int i = 0; i < V; i++)
		visited[i] = false;

	/* Now process all vertices in order defined by Stack */
	while (Stack.empty() == false) {
		/* Pop a vertex from stack */
		int v = Stack.top();
		Stack.pop();

		/* Print Strongly connected component of the popped vertex */
		if (visited[v] == false) {
      count = 0;
			gr.DFSUtil(v, visited);
    }
	}
}

int main() {
  int N;
	/* Read number of teams-vertices */
  cin >> N;
  int i, j;
  int m;
  int edge;
  Graph g(N);

  /* Read input graph */
  for(i = 0; i < N; i++){
    cin >> m;
    for (j = 0; j < m; j++){
      cin >> edge;
      g.addEdge(i, edge-1);
    }
  }
  count = 0;
	g.printSCCs();
  cout << count << endl;
	return 0;
}
