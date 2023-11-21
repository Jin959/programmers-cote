// https://school.programmers.co.kr/learn/courses/30/lessons/169199?language=cpp

/*
* 1. 격자 탐색은 여러 칸으로 이동 할 수도 있다.
* 2. 이동 횟수가 cost 이므로 이동 칸과는 무관하다. 즉, 간선의 가중치가 동일한 탐색이다.
* 
* DFS 처럼 flag와 cnt 변수로 해결할 수 없다.
* BFS 탐색 중 여러 가지에서 누적되기 때문 각 가지별로 cnt 해주어야 하는데
* visted 배열에 기록하거나 dist 배열을 하나 더 만들어 사용한다.
*/

#include <string>
#include <vector>
#include <queue>

#define MAXN 100

using namespace std;

vector<string> board;
int visited[MAXN][MAXN];
int cnt;

int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

struct Node {
    int y, x;
};

Node start, goal;

void init() {
    int y = board.size();
    int x = board[0].size();

    int tmp = 0;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (board[i][j] == 'R') {
                start = { i, j };
                tmp++;
            }
            if (board[i][j] == 'G') {
                goal = { i, j };
                tmp++;
            }
            if (tmp == 2) return;
        }
    }
}

bool isOut(Node n) {
    int y = board.size();
    int x = board[0].size();

    return (n.y < 0 || n.y >= y || n.x < 0 || n.x >= x);
}

void bfs() {
    queue<Node> q;
    q.push(start);
    visited[start.y][start.x] = 1;

    while (!q.empty()) {
        Node now = q.front();
        q.pop();

        if (board[now.y][now.x] == 'G') return;

        for (int i = 0; i < 4; i++) {
            Node nxt = { now.y + dy[i], now.x + dx[i] };
            if (isOut(nxt)) continue;
            if (board[nxt.y][nxt.x] == 'D') continue;

            while (1) {
                nxt.y += dy[i];
                nxt.x += dx[i];
                if (isOut(nxt) || board[nxt.y][nxt.x] == 'D') {
                    nxt.y -= dy[i];
                    nxt.x -= dx[i];
                    break;
                }
            }

            if (visited[nxt.y][nxt.x] != 0) continue;

            visited[nxt.y][nxt.x] = visited[now.y][now.x] + 1;
            q.push(nxt);
        }
    }
}

int solution(vector<string> board_) {
    board = board_;
    init();
    bfs();

    if (visited[goal.y][goal.x] == 0) return -1;

    // 시작점 방문 여부 체크를 위해 bfs() 에서 1을 먼저 더해주고 탐색 시작한 것 제외
    return visited[goal.y][goal.x] - 1;
}