#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <string.h>

int N, M;
int a, b, w;
int **am;
int *dis;
int **ceny;
int *visited; //all 0

int cdn[10000], index = 0;

int dij(int x) {
	visited[x] = 1;

	//update
	for (int i = 1; i <= M; i++) {
		if ((visited[i] == 0) && (am[x][i] != -1)) {
			if ((dis[x] + am[x][i] < dis[i]) || (dis[i] == -1)) {
				dis[i] = dis[x] + am[x][i];
				cdn[index] = dis[i];
				index++;
			}
		}
	}


	for (int i = 0; i < index; i++) {
		printf("%d ", cdn[i]);
	}
	printf("\n");


	//select new node
	int smaller = -1, sw = -1;
	for (int i = 0; i <= M; i++) {
		if ((visited[i] == 0) && (dis[i] >= 0) && ((sw > dis[i]) || (sw == -1))) {
			sw = dis[i];
			smaller = i;
		}
	}

	if (smaller != -1) {
		dij(smaller);
		return 1;
	}

	return 0;
}

void print() {
	printf("     ");
	for (int i = 0; i < M; i++) {
		printf("%3d ", i + 1);
	}

	printf("\n\n");

	for (int i = 0; i < M; i++) {
		printf("%3d  ", i + 1);
		for (int j = 0; j < M; j++) {
			(am[i][j] == -1) ? printf("    ") : printf("%3d ", am[i][j]);
//			printf("%3d ", am[i][j]);
		}
		printf("\n");
	}
}

void neigh_table_init(char **mapa, int n, int m) {

	// creating neigh table
	
	// creating array of prices od every node
	ceny = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		ceny[i] = (int*)malloc(m * sizeof(int));
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			ceny[i][j] = 0;
			if (mapa[i][j] == 'C') {
				ceny[i][j] = 1;
			}
			if (mapa[i][j] == 'H') {
				ceny[i][j] = 2;
			}
			if (mapa[i][j] == 'N') {
				ceny[i][j] = 100000;
			}

			printf("%d ", ceny[i][j]);
		}
		printf("\n");
	}




	//initializing am
	M = n * m;
	am = (int**)malloc((M + 1) * sizeof(int*));
	for (int i = 0; i <= M; i++) {
		am[i] = (int*)malloc((M + 1) * sizeof(int));
	}

	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			am[i][j] = -1;
		}
	}

	dis = (int*)malloc((M + 1) * sizeof(int));
	//initializing dis
	for (int i = 0; i <= M; i++) {
		dis[i] = -1;
	}

	visited = (int*)malloc((M + 1) * sizeof(int));
	//initializing visited
	for (int i = 0; i <= M; i++) {
		visited[i] = 0;
	}

	//initializing root
	dis[1] = -1;


	//-------------------------------------------------------------------------------------------- Connecting edges nodes

	//-------------------- top left edge

			//node to right
	a = 0;
	b = 1;

//	if (mapa[0][0] == 'C' && mapa[0][1] == 'C') {
		am[a][b] = ceny[0][0] + ceny[0][1];
		am[b][a] = ceny[0][0] + ceny[0][1];
//	}

	//node to bottom
	a = 0;
	b = m;

//	if (mapa[0][0] == 'C' && mapa[1][0] == 'C') {
		am[a][b] = ceny[0][0] + ceny[1][0];
		am[b][a] = ceny[0][0] + ceny[1][0];
//	}


	//-------------------- top right edge

			// node to left
	a = m - 1;
	b = m - 2;

//	if (mapa[0][m - 1] == 'C' && mapa[0][m - 2] == 'C') {
		am[a][b] = ceny[0][m - 1] + ceny[0][m - 2];
		am[b][a] = ceny[0][m - 1] + ceny[0][m - 2];
//	}

	// node to bottom
	a = m - 1;
	b = m * 2 - 1;

//	if (mapa[0][m - 1] == 'C' && mapa[1][m - 1] == 'C') {
		am[a][b] = ceny[0][m - 1] + ceny[1][m - 1];
		am[b][a] = ceny[0][m - 1] + ceny[1][m - 1];
//	}


	//-------------------- bottom left edge

			// node to top
	a = n * (m - 1);
	b = n * (m - 2);

//	if (mapa[n - 1][0] == 'C' && mapa[n - 2][0] == 'C') {
		am[a][b] = ceny[n - 1][0] + ceny[n - 2][0];
		am[b][a] = ceny[n - 1][0] + ceny[n - 2][0];
//	}

	// node to right
	a = n * (m - 1);
	b = n * (m - 1) + 1;

//	if (mapa[n - 1][0] == 'C' && mapa[n - 1][1] == 'C') {
		am[a][b] = ceny[n - 1][0] + ceny[n - 1][1];
		am[b][a] = ceny[n - 1][0] + ceny[n - 1][1];
//	}


	//-------------------- bottom right edge

			// node to top
	a = n * m - 1;
	b = n * (m - 1) - 1;

//	if (mapa[n - 1][m - 1] == 'C' && mapa[n - 2][m - 1] == 'C') {
		am[a][b] = ceny[n - 1][m - 1] + ceny[n - 2][m - 1];
		am[b][a] = ceny[n - 1][m - 1] + ceny[n - 2][m - 1];
//	}

	// node to left
	a = n * m - 1;
	b = n * m - 2;

//	if (mapa[n - 1][m - 1] == 'C' && mapa[n - 1][m - 2] == 'C') {
		am[a][b] = ceny[n - 1][m - 1] + ceny[n - 1][m - 2];
		am[b][a] = ceny[n - 1][m - 1] + ceny[n - 1][m - 2];
//	}


	//-------------------------------------------------------------------- Connecting top, bottom, left and right lines of nodes

	//------------ top line
	for (int i = 1; i < m - 1; i++) {

		// node to left
		a = i;
		b = i - 1;

//		if (mapa[0][i] == 'C' && mapa[0][i - 1] == 'C') {
			am[a][b] = ceny[0][i] + ceny[0][i - 1];
			am[b][a] = ceny[0][i] + ceny[0][i - 1];
//		}

		// node to right
		a = i;
		b = i + 1;

//		if (mapa[0][i] == 'C' && mapa[0][i + 1] == 'C') {
			am[a][b] = ceny[0][i] + ceny[0][i + 1];
			am[b][a] = ceny[0][i] + ceny[0][i + 1];
//		}

		// node to bottom
		a = i;
		b = i + m;

//		if (mapa[0][i] == 'C' && mapa[1][i] == 'C') {
			am[a][b] = ceny[0][i] + ceny[1][i];
			am[b][a] = ceny[0][i] + ceny[1][i];
//		}
	}

	//------------ left line
	for (int i = 1; i < n - 1; i++) {

		// node to top
		a = i * m;
		b = (i - 1) * m;

//		if (mapa[i][0] == 'C' && mapa[i - 1][0] == 'C') {
			am[a][b] = ceny[i][0] + ceny[i - 1][0];
			am[b][a] = ceny[i][0] + ceny[i - 1][0];
//		}

		// node to right
		a = i * m;
		b = i * m + 1;

//		if (mapa[i][0] == 'C' && mapa[i][1] == 'C') {
			am[a][b] = ceny[i][0] + ceny[i][1];
			am[b][a] = ceny[i][0] + ceny[i][1];
//		}

		// node to bottom
		a = i * m;
		b = (i + 1) * m;

//		if (mapa[i][0] == 'C' && mapa[i + 1][0] == 'C') {
			am[a][b] = ceny[i][0] + ceny[i + 1][0];
			am[b][a] = ceny[i][0] + ceny[i + 1][0];
//		}
	}

	//------------ bottom line
	for (int i = 1; i < m - 1; i++) {

		// node to left
		a = (n - 1) * m + i;
		b = (n - 1) * m + i - 1;

//		if (mapa[n - 1][i] == 'C' && mapa[n - 1][i - 1] == 'C') {
			am[a][b] = ceny[n - 1][i] + ceny[n - 1][i - 1];
			am[b][a] = ceny[n - 1][i] + ceny[n - 1][i - 1];
//		}

		// node to right
		b = (n - 1) * m + i + 1;

//		if (mapa[n - 1][i] == 'C' && mapa[n - 1][i + 1] == 'C') {
			am[a][b] = ceny[n - 1][i] + ceny[n - 1][i + 1];
			am[b][a] = ceny[n - 1][i] + ceny[n - 1][i + 1];
//		}

		// node to top
		b = (n - 2) * m + i;

//		if (mapa[n - 1][i] == 'C' && mapa[n - 2][i] == 'C') {
			am[a][b] = ceny[n - 1][i] + ceny[n - 2][i];
			am[b][a] = ceny[n - 1][i] + ceny[n - 2][i];
//		}
	}

	//------------ right line
	for (int i = 1; i < n - 1; i++) {

		// node to top
		a = (i + 1) * m - 1;
		b = i * m - 1;

//		if (mapa[i][m - 1] == 'C' && mapa[i - 1][m - 1] == 'C') {
			am[a][b] = ceny[i][m - 1] + ceny[i - 1][m - 1];
			am[b][a] = ceny[i][m - 1] + ceny[i - 1][m - 1];
//		}

		// node to left
		a = (i + 1) * m - 1;
		b = (i + 1) * m - 2;

//		if (mapa[i][m - 1] == 'C' && mapa[i][m - 2] == 'C') {
			am[a][b] = ceny[i][m - 1] + ceny[i][m - 2];
			am[b][a] = ceny[i][m - 1] + ceny[i][m - 2];
//		}

		// node to bottom
		a = (i + 1) * m - 1;
		b = (i + 2) * m - 1;

//		if (mapa[i][m - 1] == 'C' && mapa[i + 1][m - 1] == 'C') {
			am[a][b] = ceny[i][m - 1] + ceny[i + 1][m - 1];
			am[b][a] = ceny[i][m - 1] + ceny[i + 1][m - 1];
//		}
	}


	//------------------------------------------------------------------- Connecting all the other nodes, which are not edges or edge lines

	for (int i = 1; i < n - 1; i++) {
		for (int j = 1; j < m - 1; j++) {

			a = i * m + j;

			// node to top
			b = (i - 1) * m + j;

//			if (mapa[i][j] == 'C' && mapa[i - 1][j] == 'C') {
				am[a][b] = ceny[i][j] + ceny[i - 1][j];
				am[b][a] = ceny[i][j] + ceny[i - 1][j];
//			}

			// node to left
			b = i * m + j - 1;

//			if (mapa[i][j] == 'C' && mapa[i][j - 1] == 'C') {
				am[a][b] = ceny[i][j] + ceny[i][j - 1];
				am[b][a] = ceny[i][j] + ceny[i][j - 1];
//			}

			// node to bottom
			b = (i + 1) * m + j;

//			if (mapa[i][j] == 'C' && mapa[i + 1][j] == 'C') {
				am[a][b] = ceny[i][j] + ceny[i + 1][j];
				am[b][a] = ceny[i][j] + ceny[i + 1][j];
//			}

			// node to right
			b = i * m + j + 1;

//			if (mapa[i][j] == 'C' && mapa[i][j + 1] == 'C') {
				am[a][b] = ceny[i][j] + ceny[i][j + 1];
				am[b][a] = ceny[i][j] + ceny[i][j + 1];
//			}

		}
	}

}

int *zachran_princezne(char **mapa, int n, int m, int t, int *dlzka_cesty) {

	for (int i = 0; i < n; i++)
		printf("%s\n", mapa[i]);

	neigh_table_init(mapa, n, m);

	print();

	dij(0);

	printf("N = %d, M = %d\n", N, M);

	//update
	for (int i = 1; i < M; i++) {
		dis[i] += 1;
	}

	//output
	for (int i = 0; i < M; i++) {
		printf ("%d - %d\n", i + 1,  dis[i]);
	}
	

	return 0;
}

int main() {
	char **map = (char**) malloc (100 * sizeof(char*));
	FILE *file = fopen("map - 0.txt", "r");
	int n = 0, m;

	// initializing map
	for (int i = 0; i < 100; i++)
		map[i] = (char*)malloc(100 * sizeof(char));
	while (fscanf(file, "%s", map[n]) > 0) 
		n++;
	m = strlen(map[0]);

	//start function
	zachran_princezne(map, n, m, 0, 0);

	system("pause");
}