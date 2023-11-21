// https://school.programmers.co.kr/learn/courses/30/lessons/154540

import java.util.*;
/**
 * 맵의 모든 노드를 루프로 돌면서 시작점으로 잡는다.
 * 이때, 바다가 아닌 곳과 탐색하지 않은 노드 들을 시작으로 bfs를 돌린다.
 * bfs는 연결 된 식량의 개수를 리턴한다.
 */
class Solution {
    static char[][] maps;
    static boolean[][] used;
    
    // 방향배열
    static int[] dx = { -1, 0, 1, 0 };
    static int[] dy = { 0, -1, 0, 1 };
    
    // 1x1 한칸을 노드로 정의
    static class Node {
        int y;
        int x;
        
        Node(int y, int x) {
            this.y = y;
            this.x = x;
        }
    }
    
    // 지도 밖으로 나갔다.
    static boolean isOut(Node n) {
        int y = maps.length;
        int x = maps[0].length;
        return (n.y < 0 || n.y >= y || n.x < 0 || n.x >= x);
    }
    
    static int bfs(Node start) {
        Queue<Node> q = new LinkedList<>();
        q.add(start);
        used[start.y][start.x] = true;
        int days = maps[start.y][start.x] - '0';
        
        while(!q.isEmpty()) {
            Node now = q.poll();            
            
            for (int i = 0; i < 4; i++) {
                Node nxt = new Node(now.y + dy[i], now.x + dx[i]);
                
                if (isOut(nxt)) continue;
                if (used[nxt.y][nxt.x]) continue;
                if (maps[nxt.y][nxt.x] == 'X') continue;
                
                used[nxt.y][nxt.x] = true;
                days += maps[nxt.y][nxt.x] - '0';
                q.add(nxt);
            }
        }
        
        return days;
    }
    
    public int[] solution(String[] maps_) {
        // init
        int y = maps_.length;
        int x = maps_[0].length();
        used = new boolean[y][x];        
        maps = new char[y][];
        for (int i = 0; i < y; i++) maps[i] = maps_[i].toCharArray();
        
        // 바다가 아닌 곳과 탐색하지 않은 노드 들을 시작으로 bfs를 돌린다.
        List<Integer> list = new ArrayList<>();
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                if (maps[i][j] == 'X') continue;
                if (used[i][j]) continue;
                list.add(bfs(new Node(i, j)));
            }
        }
        
        // 예외 상황, 무인도 여행 불가
        if (list.isEmpty()) return new int[] { -1 };
        // 오름 차순 정렬
        return list.stream().sorted((a, b) -> a - b)
            .mapToInt(ele -> ele)
            .toArray();
    }
}