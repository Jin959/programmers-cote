// https://school.programmers.co.kr/learn/courses/30/lessons/154540

import java.util.*;

class Solution {
    static char[][] maps;
    static boolean[][] used;
    
    static int[] dx = { -1, 0, 1, 0 };
    static int[] dy = { 0, -1, 0, 1 };
    
    static class Node {
        int y;
        int x;
        
        Node(int y, int x) {
            this.y = y;
            this.x = x;
        }
    }
    
    static boolean isOut(Node n) {
        int y = maps.length;
        int x = maps[0].length;
        return (n.y < 0 || n.y >= y || n.x < 0 || n.x >= x);
    }
    
    static int bfs(Node start) {
        Queue<Node> q = new LinkedList<>();
        q.add(start);
        int days = 0;
        
        while(!q.isEmpty()) {
            Node now = q.poll();
            
            /**
             * 여기서 기록하면 마지막에 이미 방문한 노드를 한번 더 탐색하게 된다.
             * 어떤 섬에서 마지막 노드가 탐색 될때
             * 마지막 노드로 갈 수 있는 직전 노드가 여러 군데 일 수 있다.
             * 예를 들면 3 x 3 인데 가운데가 뻥 뚤린 섬은 마지막 노드를 두번 탐색한다.
             * 이 때, 이 직전 노드들이 now 가 되었을 때, 마지막 노드인 nxt를 각자 방문하게 된다.
             */
            used[now.y][now.x] = true;
            days += maps[now.y][now.x] - '0';
            
            for (int i = 0; i < 4; i++) {
                Node nxt = new Node(now.y + dy[i], now.x + dx[i]);
                
                if (isOut(nxt)) continue;
                if (used[nxt.y][nxt.x]) continue;
                if (maps[nxt.y][nxt.x] == 'X') continue;
                
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