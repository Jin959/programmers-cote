// https://school.programmers.co.kr/learn/courses/30/lessons/86971

/*
* 간선을 하나씩 지워 보면서 완전 탐색하여 노드의 개수를 하나하나 센다.
* n개의 송전탑은 하나의 트리 형태로 연결되어 있다.
* 즉, 둘로 나눴을 때 한쪽만 탐색하면 남은 하나의 트리의 노드수는 알 수 있다.
* 
* solution()은 다음과 같은 로직으로 구성된다.
* 1. init()으로 Adjacency list와 방문기록을 초기화 한다.
* 2. deleteEdgeGetAdj() 로 간선을 하나 택하여 제거한 뒤, 그에 맞게 Adjacency list 를 구성한다.
* 3. dfs()로 트리를 탐색한다.
* 4. 2개의 트리 중, 탐색한 트리의 노드 수(cnt)와 탐색하지 않은 부분(n - cnt) 의 절대값 차를 구하고 최소값 갱신.
*/

#include <string>
#include <vector>
#include <cmath>
#include <cstring>

#define MAXN 100

using namespace std;

int n;
vector<vector<int>> wires;
vector<int> adj[MAXN];  // adjacency list
bool visited[MAXN];

int cnt;
int min_abs = 21e8;

void init() {
    for (int i = 0; i < n; i++) adj[i].clear();
    memset(visited, false, sizeof(visited));
}

void deleteEdgeGetAdj(int edgeIdx) {
    for (int i = 0; i < n - 1; i++) {
        if (i == edgeIdx) continue;
        // 노드 넘버 1부터
        int v1 = wires[i][0] - 1;
        int v2 = wires[i][1] - 1;
        // 무향 그래프
        adj[v1].push_back(v2);
        adj[v2].push_back(v1);
    }
}

void dfs(int now) {

    visited[now] = true;
    cnt++;

    for (int nxt : adj[now]) {
        if (visited[nxt]) continue;
        dfs(nxt);
    }
}

int solution(int n_, vector<vector<int>> wires_) {
    n = n_;
    wires = wires_;

    for (int i = 0; i < n - 1; i++) {
        init();

        deleteEdgeGetAdj(i);
        cnt = 0;
        dfs(0);

        int tmp = abs(cnt - (n - cnt));
        if (min_abs > tmp) min_abs = tmp;
    }

    return min_abs;
}