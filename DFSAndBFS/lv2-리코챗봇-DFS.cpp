// https://school.programmers.co.kr/learn/courses/30/lessons/169199?language=cpp

/*
* 시간 초과 남.
* 
* dfs 완전 탐색시 사용하며, bfs는 최단경로 및 임의의 경로를 찾을 때 사용합니다.
* 최단거리 문제는 dfs로 구현시, promising을 적용해도 TLE가 나올 가능성이 굉장히 높습니다.
* https://school.programmers.co.kr/questions/46830
*/

#include <string>
#include <vector>

#define MAXN 100

using namespace std;

vector<string> board;
bool visited[MAXN][MAXN];
int cnt, min_cnt = 21e8, flag;

int dx[] = { 0, 1, 0, -1 };
int dy[] = { 1, 0, -1, 0 };

struct Node {
    int y, x;
};

Node start;

void init() {
    int y = board.size();
    int x = board[0].size();
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (board[i][j] == 'R') {
                start = { i, j };
                return;
            }
        }
    }
}

bool isOut(Node n) {
    int y = board.size();
    int x = board[0].size();

    return (n.y < 0 || n.y >= y || n.x < 0 || n.x >= x);
}

void dfs(Node now) {
    if (board[now.y][now.x] == 'G') {
        flag = true;
        if (min_cnt > cnt) min_cnt = cnt;
        return;
    }

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

        if (visited[nxt.y][nxt.x]) continue;
        if (cnt + 1 > min_cnt) continue;

        visited[nxt.y][nxt.x] = true;
        cnt += 1;
        dfs(nxt);
        cnt -= 1;
        visited[nxt.y][nxt.x] = false;
    }
}

int solution(vector<string> board_) {
    board = board_;
    init();

    visited[start.y][start.x] = true;
    dfs(start);

    if (!flag) return -1;
    return min_cnt;
}