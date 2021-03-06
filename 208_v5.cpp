#include <stdio.h>
#include <stdlib.h>

#include <vector>
using namespace std;

int target;
int dg[22], adj[22][22];
int visited[22], reachable[22];

int path[21], isInPath[22];
int sizePath;
long int countRoutes;

vector< vector<int> > OUT;

int cmp(const void *a, const void *b) {
	int *pa = (int *)a;
	int *pb = (int *)b;
	return *pa - *pb;
}

/*
1---2
\     \
 \--3--4--5

5
1 2
1 3
2 4
3 4
4 5
0 0
6
1 2
1 3
3 4
3 5
4 6
5 6
2 3
2 4
0 0
4
2 3
3 4
5 1
1 6
7 8
8 9
2 5
5 7
3 1
1 8
4 6
6 9
0 0

target = 5

DFS(1, {1})
   DFS(2, {1,2})
      DFS(4, {1,2,4})
        DFS(3, {1,2,4,3})
        DFS(5, {1,2,4,5}) print(1, 2, 4, 5)
   DFS(3)
      DFS(4)
        DFS(2)
        DFS(5) print(1, 3, 4, 5)
*/

void DFSfromTarget(int u) {
	int flag = 0;
	reachable[u] = 1;
	if(u==1) return;

	for(int i=0; i<dg[u]; i++) {
		int v = adj[u][i];
		if(!reachable[v])
			DFSfromTarget(v);
	}
}

void DFS(int u) {
	
	path[sizePath++] = u;
	isInPath[u] = 1;

	if(u==target) {
		printf("%d", path[0]);
		for(int i=1; i<sizePath; i++)
			printf(" %d", path[i]);
		printf("\n");
		countRoutes++;
	}
	else {
		for(int i=0; i<dg[u]; i++) {
			int v = adj[u][i];
			if(!isInPath[v] && reachable[v]) {
				DFS(v);
			}
		}
	}

	isInPath[ path[--sizePath] ] = 0;
}

int main() {
	int casos;
	int i, j;

	for(casos=1; ;casos++) {
		if(scanf("%d", &target)==EOF) return 0;
		
		printf("CASE %d:\n", casos);

		for(i=1; i<=21; i++)
			dg[i] = 0;

		while(1) {
			int u, v;
			scanf("%d %d", &u, &v);
			if(u==0&&v==0) break;
			adj[u][dg[u]++] = v;
			adj[v][dg[v]++] = u;
		}

		//entrada lida!

		sizePath = 0;
		countRoutes = 0;
		for(i=1; i<=21; i++) {
			isInPath[i] = 0;
			reachable[i] = 0;
			visited[i] = 0;
			qsort(adj[i], dg[i], sizeof(int), cmp);
		}

		DFSfromTarget(target);

		/*
		for(i=1; i<=21; i++) {
			printf("REACHABLE[%d] = %d\n", i, reachable[i]);
		}
		*/
		
		OUT.clear();

		if(reachable[1])
			DFS(1);

		if(countRoutes<=1) {
			printf("There is %ld route from the firestation to streetcorner %d.\n", countRoutes, target);
		}
		else
			printf("There are %ld routes from the firestation to streetcorner %d.\n", countRoutes, target);
	}

}