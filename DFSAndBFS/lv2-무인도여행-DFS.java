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
    
    static int dfs(Node now, int days) {

        for (int i = 0; i < 4; i++) {
            Node nxt = new Node(now.y + dy[i], now.x + dx[i]);

            if (isOut(nxt)) continue;
            if (used[nxt.y][nxt.x]) continue;
            if (maps[nxt.y][nxt.x] == 'X') continue;

            used[nxt.y][nxt.x] = true;
            days = dfs(nxt, days + (maps[nxt.y][nxt.x] - '0'));
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
                
                Node start = new Node(i, j);
                used[start.y][start.x] = true;
                list.add(dfs(start, maps[start.y][start.x] - '0'));
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