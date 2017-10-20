#include <cstdio>
#include <vector>
#include <cstdlib>
#include <stack>
#include <list>
#include <queue>
#include <set>
#define UNDEFINED -1
typedef int Vertex;

class Graph{
	
	private: std::vector< std::list<Vertex> > _lists;
	private: int _numVertex;
	private: int _numConnections;
	
	public: Graph(int numVertex,int numConnections){
		int i;
		_numVertex = numVertex;
		_numConnections = numConnections;
		for(i = 0; i < _numVertex;i++){
			_lists.push_back( std::list<Vertex>() );
		}
	}
	
	public: std::list<Vertex>::iterator getIterator(Vertex vertex){
		return _lists[vertex-1].begin();
	}
	
	public: std::list<Vertex>::iterator getIteratorEnd(Vertex vertex){
		return _lists[vertex-1].end();
	}
	
	public: void addConnection(Vertex v1,Vertex v2){
		_lists[v1-1].push_back(v2);
	}
	
	public: int getVertexes(){
		return _numVertex;
	}
};
/*====================================================================*/
/* - Implementation of Tarjans Algorythm */

/* auxiliary variables and structures*/
bool* stackFlag;			    /* Used to see if vertexes are in Stack O(1)*/
std::stack<Vertex> Stack;		/* Used for pushing vertexes */
static int* index;
int* lowLink;
int Index = 0;
int totalVertexes = 0;
int contMaxScc = 0;			/* Size of large Strongly Connected Component*/
int numberScc = 0;			/* Number of Strongly Connected Components's */	
std::vector< std::vector<Vertex> > scc;		/* SCC container separated */

/* min - Returns the minimum between both numbers. */
int min(int a,int b){
	if(a < b)
		return a;
	else if( a > b) 
		return b;
	else 
		return a;
}

/* BFS - Exectures Breadth.First Search starting in startVertex */
int BFS(Graph* graph,Vertex startVertex){
	std::queue<Vertex> auxQueueBFS;
	std::set<Vertex> auxSetBFS;
	Vertex auxVertex,auxVertex2;
	auxQueueBFS.push(startVertex);
	auxSetBFS.insert(startVertex);
	while(auxQueueBFS.empty() == false){
			auxVertex = auxQueueBFS.front();
			auxQueueBFS.pop();
			for(std::list<Vertex>::iterator it = graph->getIterator(auxVertex); it != graph->getIteratorEnd(auxVertex) ;++it){
				auxVertex2 = *(it);
				if(auxSetBFS.find(auxVertex2) == auxSetBFS.end()){
					auxSetBFS.insert(auxVertex2);
					auxQueueBFS.push(auxVertex2);
				}
			}
	}
	return auxSetBFS.size();/* Number of nodes reachable from starVertex*/
}

/* findSccConnections2 - returns SCC's that haven't connections with 
 * other SCC's */
int findSccConnections2(Graph* graph){
	int i,notConnectedSCC = 0;
	int size = scc.size();
	for(i = 0 ; i < size;i++){
		if((int)scc[i].size() == BFS(graph,scc[i][0])){
			notConnectedSCC++;	
		}
	}
	return notConnectedSCC;
}

/* strongConnect - Find SCC*/
void strongConnect(Vertex v,Graph* graph){
	Vertex auxVertex = 0;
	int counter = 0;				/* Counter used to find SCC size */
	index[v-1] = Index;
	lowLink[v-1] = Index;
	Index++;
	Stack.push(v);
	stackFlag[v-1] = true;			/* Vertex v is in stack now */
	std::vector<Vertex> component;
	for(std::list<Vertex>::iterator it=graph->getIterator(v); it != graph->getIteratorEnd(v); ++it){		/* For all adjacent Vertexes */
			auxVertex = (*it);			/* FIX-ME !!!! Colado a implementacao do grafo */
			if(index[auxVertex-1] == UNDEFINED){
				strongConnect(auxVertex,graph);
				lowLink[v-1] = min(lowLink[v-1],lowLink[auxVertex-1]);
			}
			else if(stackFlag[auxVertex-1] == true)
				lowLink[v-1] = min(lowLink[v-1],index[auxVertex-1]);
	}
	if(lowLink[v-1] == index[v-1]){
		while(true){
			auxVertex = Stack.top();
			Stack.pop();
			stackFlag[auxVertex-1] = false;
			component.push_back(auxVertex);
			counter++;
			if(auxVertex == v)
				break;
		}
		scc.push_back(component);		
		if(counter > contMaxScc)
			contMaxScc = counter;/*output strong connected componnet */
		numberScc++;
	}
}

/* tarjan - tarjan's algorythm */
void tarjan(int TotalVertexes,Graph* graph){
	int i;
	Vertex vertex;
	totalVertexes = TotalVertexes;
	index = (int*) malloc(sizeof(int)*totalVertexes);
	lowLink = (int*) malloc(sizeof(int)*totalVertexes);
	stackFlag = (bool*) malloc(sizeof(bool)*totalVertexes);
	
	for(i= 0; i < totalVertexes; i++){
		index[i] = UNDEFINED;
		lowLink[i] = UNDEFINED;
		stackFlag[i] = false;
	}
	Index = 0;
	/* For each Unvisited vertex in graph */
	for(vertex = 1; vertex <= totalVertexes; vertex++){
		if(index[vertex-1] == UNDEFINED)
			strongConnect(vertex,graph);
	}
	
	printf("%d\n",numberScc);
	printf("%d\n",contMaxScc);
	printf("%d\n",findSccConnections2(graph));
	free(index);
	free(lowLink);
	free(stackFlag);
}
/*========================== main ====================================*/
int main(){
	int numVertex,numConnections,k;
	Vertex v1,v2;
	Graph* graph;
	scanf("%d %d",&numVertex,&numConnections);
	graph = new Graph(numVertex,numConnections);
	for(k = 0; k < numConnections;k++){
		scanf("%d %d",&v1,&v2);
		graph->addConnection(v1,v2);
	}
	tarjan(graph->getVertexes(),graph);
	delete graph;	/*Free all memory associated with graph*/
	return 0;
} 
