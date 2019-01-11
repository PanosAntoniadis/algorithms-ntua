#include <iostream>
#include <cstdint>
using namespace std;

/*
* A struct representing a node with the following:
* isEnd: true if the node is the end of a cross.
* isStart: true if the node is the start of a cross.
* myStart: if isEnd is true then myStart contains the start of my cross.
* count: the number of total paths to this node.
*/
struct node {
    bool isEnd = false;
    bool isStart = false;
    int myStart = -1;
    uint64_t count = 0;
};

/* A 3-dimensional array that should be stored in the heap. */
node*** paths;

int main() {
    int i, j, cr;
    int sx, sy;
    /*
    * Read dimensions N, M, number of crosses K and
    * number of max crosses allowed X.
    */
    int N, M, K, X;
    cin >> N >> M >> K >> X;
    /*
    * The problem is solved using dynamic programming.
    * Α cell (i,j,k) in the 'path' array represents the total
    * paths from cell (N-1, M-1) to (i, j) using up to k crosses.
    */
    paths = new node**[N];
    for (i = 0; i < N; ++i) {
      paths[i] = new node*[M];
      for (j = 0; j < M; ++j)
        paths[i][j] = new node[X+1];
    }
    /*
    * Read crossings and fill the fields of the corresponding cells.
    */
    int start, end;
    for(i = 0; i < K; i++){
        cin >> start >> end;
        for(cr = 0; cr <= X; cr++){
            paths[start/M][start%M][cr].isStart = true;
            paths[end/M][end%M][cr].isEnd = true;
            paths[end/M][end%M][cr].myStart = start;
        }
    }

	/* Initialization of path array */
    for(i = 0; i <= X; i++){
        paths[N-1][M-1][i].count = 1;
    }

    /* Calculate count of paths for other cells in bottom-up manner (dynamic programming) */
    for (i = N-1; i >= 0; i--) {
    	for (j = M-1; j >=0; j--) {
            for(cr = 0 ; cr <= X; cr++) {
                if (i == N-1 && j == M-1)   continue;   /* Initial cell */
                if (i < N-1 && !paths[i+1][j][cr].isStart){
                    paths[i][j][cr].count += paths[i+1][j][cr].count%1000000103;
                }
                if (j < M-1 && !paths[i][j+1][cr].isStart){
                    paths[i][j][cr].count += paths[i][j+1][cr].count%1000000103;
                }
                /* If we are in a crossing we should add the paths using the crossing too */
                if (paths[i][j][cr].isEnd){
                    /* If we can use a crossing add the paths of the start cell to the total */
                    if (cr > 0){
                        sx = paths[i][j][cr].myStart/M;
                        sy = paths[i][j][cr].myStart%M;
                        paths[i][j][cr].count += paths[sx][sy][cr-1].count%1000000103;
                    }
                }
            }
    	}
    }
    /* Print total paths from (N-1, M-1) to (0, 0) using up to X crossings */
    cout << paths[0][0][X].count%1000000103 << endl;
	return 0;
}
