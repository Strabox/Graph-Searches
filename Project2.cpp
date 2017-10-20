/*@@@@@@@@@@@@@@@@@@@@@@@ 2º PROJECTO ASA @@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
#include <cstdio>
#include <vector>
#include <list>
#include <stdlib.h>
#define UNDEFINED -1
#define NOVO_V 0
#define GRAY 1
#define BLACK 2
#define oo 1000000000
int *cor;
int *caminho;
int cabeca, cu;
int *Q;

typedef int Vertex;

class Edge{
	public: Vertex destino;
	public: bool fluxo;
	
	public: Vertex getDestino(){ return destino;}
	//public: void setDestino( int v){ destino= (Vertex) v;}
	public: void setDestino( Vertex v){ destino=v;}
	public: bool getFluxo(){ return fluxo;};
	public: void setFluxo(bool f){ fluxo=f;};
};

class Graph{
	
	public: std::vector< std::list<Edge> > _lists;
	public: int _numVertex;
	public: int _numConnections;
	
	public: Graph(int numVertex,int numConnections){
		int i;
		_numVertex = numVertex;
		_numConnections = numConnections;
		for(i = 0; i < _numVertex;i++){
			_lists.push_back( std::list<Edge>() );
		}
	}
	
	public: std::list<Edge>::iterator getIterator(Vertex vertex){
		return _lists[vertex-1].begin();
	}
	
	public: std::list<Edge>::iterator getIteratorEnd(Vertex vertex){
		return _lists[vertex-1].end();
	}
	
	public: void addConnection(Vertex v1,Vertex v2){
		Edge* manq=(Edge*) malloc(sizeof(Edge));
		Edge* inho=(Edge*) malloc(sizeof(Edge));
		manq->setDestino(v2);
		manq->setFluxo(false);
		inho->setDestino(v1);
		inho->setFluxo(false);
		_lists[v1].push_back(*manq);
		_lists[v2].push_back(*inho);
	}
	
	public: int getVertexes(){
		return _numVertex;
	}
};


void push(int shit) {
    Q[cu] = shit;
    cu++;
    cor[shit] = GRAY;
}

int pop() {
    int x = Q[cabeca];
    cabeca++;
    cor[x] = BLACK;
    return x;
}


int bfs(int start, int end, int n, Graph *garfo) {
    int u, v;
    printf("a");
    for (u=0; u<n; u++) {
		cor[u] = NOVO_V;
    }   
    cabeca = cu = 0;
    push(start);
    printf("passou o ciclo de u");
    caminho[start] = -1;
    while (cabeca != cu) {
		u = pop();
			// Search all adjacent white nodes v. If the capacity
			// from u to v in the residual network is positive,
			// enqueue v.
			
		v=0;
		Vertex fim = garfo->getIteratorEnd(u)->getDestino();
		for(std::list<Edge>::iterator passador = garfo->getIterator(u); passador->getDestino() != fim; passador++) {
			printf("%d %d\n",v, cor[v]);
			if (cor[v]==NOVO_V && passador->getFluxo()==false) {
			push(v);
			caminho[v] = u;
			v++;
			}
		}
    }
    // If the color of the target node is black now,
    // it means that we reached it.
    return cor[end]==BLACK;
}

int main(){
	int numVertexes, numConnections,i,k,numProblems,numCriticPoints, criticPoint;
	char c;
	int v1,v2;
	
	scanf("%d %d",&numVertexes,&numConnections);
	Graph* garfo= new Graph(numVertexes,numConnections);
	Q= (int*)malloc(sizeof(Vertex)*numVertexes);
	cor= (int*)malloc(sizeof(Vertex)*numVertexes);
	caminho= (int*)malloc(sizeof(Vertex)*numVertexes);
	
	
	for(i = 0; i < numConnections;i++){
		scanf("%d %d",&v1,&v2);
		garfo->addConnection(v1, v2);
	}
	printf("haha");
	printf("%d",(int) garfo);
	bfs(0,3,4, garfo);
	scanf("%d",&numProblems);
	
	for(i = 0; i < numProblems;i++){
		scanf("%d ",&numCriticPoints);
		while((c = getchar()) != -1){
			//if(c == " "){
				
			//}
		}
	}
	
	return 0;
}
