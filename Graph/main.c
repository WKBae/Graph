#include <stdio.h>

#define MAX_VERTEX 12
double COST[MAX_VERTEX][MAX_VERTEX];
double distance[MAX_VERTEX];
int pred[MAX_VERTEX];
int set_S[MAX_VERTEX];

void read_and_make_graph() {
	FILE* in = fopen("graphdata.txt", "r");
	char ch;
	int vertices, i, v, u;
	double c;
	fscanf(in, "%d", &vertices);
	for(i = 0; i < vertices; i++) {
		fscanf(in, "%d%c", &v, &ch);
		while(ch != '\n') {
			fscanf(in, "%d%lf%c", &u, &c, &ch);
			COST[v][u] = c;
		}
	}
}

void print_path(int last_v) {
	if(last_v >= 0) {
		print_path(pred[last_v]);
		printf("%d ", last_v);
	}
}

int shortest_path(int start, int dest) {
	int i, min_u, w, s_count;
	double min;
	for(i = 0; i < MAX_VERTEX; i++) {
		set_S[i] = 0;
		if(COST[start][i] != 0) {
			distance[i] = COST[start][i];
			pred[i] = start;
		} else {
			distance[i] = ~(1 << 31);
		}
	}
	set_S[start] = 1;
	distance[start] = 0;
	pred[start] = -1;

	s_count = MAX_VERTEX;
	while(s_count > 0) {
		min_u = 0;
		min = ~(1 << 31);
		for(i = 0; i < MAX_VERTEX; i++) {
			if(!set_S[i]) {
				if(distance[i] <= min) {
					min_u = i;
					min = distance[i];
				}
			}
		}
		set_S[min_u] = 1;
		s_count--;

		for(i = 0; i < MAX_VERTEX; i++) {
			if(!set_S[i] && COST[min_u][i] > 0) {
				if(distance[min_u] + COST[min_u][i] < distance[i]) {
					distance[i] = distance[min_u] + COST[min_u][i];
					pred[i] = min_u;
				}
			}
		}

		if(min_u == dest) {
			printf("경로: ");
			print_path(dest);
			printf("\t총 비용: %lf\n", distance[dest]);
			return distance[dest];
		}
	}

}
int main() {
	int u, v;
	read_and_make_graph();
	
	while(1) {
		printf("최소경로를 찾을 두 정점을 입력하시오> ");
		scanf("%d%d", &u, &v);
		if(0 <= u && u < MAX_VERTEX && 0 <= v && v < MAX_VERTEX) {
			shortest_path(u, v);
		} else {
			printf("프로그램을 종료합니다.\n");
			break;
		}
	}
	return 0;
}
