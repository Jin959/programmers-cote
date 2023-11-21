class Solution {
    static String[] targets;
    static String[] keymap;
    static int[] ans;
    static int[] min_key;
    
    // min_key[] 에 키를 누르는데 걸리는 최소 횟수만 기록한다.
    static void initMinKey() {
        int sz = keymap.length;
        
        for (int i = 0; i < sz; i ++) {
            int sz_key = keymap[i].length();
            for (int j = 0; j < sz_key; j++) {
                char c = keymap[i].charAt(j);
                int tmp = j + 1;
                if (min_key[c] == 0) min_key[c] = tmp;
                else if (tmp < min_key[c]) min_key[c] = tmp;
            }
        }
    }
    
    // 기록한 최소 누름 횟수를 이용하여 더한다.
    static int countPress(String tar) {        
        int cnt = 0;
        int sz = tar.length();
        for (int i = 0; i < sz; i++) {
            if (min_key[tar.charAt(i)] == 0) return -1; // 없는 문자가 있으면 -1
            else cnt += min_key[tar.charAt(i)];
        }
        
        return cnt;
    }
    
    public int[] solution(String[] keymap_, String[] targets_) {
        keymap = keymap_;
        targets = targets_;
        int sz = targets.length;
        ans = new int[sz];
        
        min_key = new int[200]; // ascii 사이즈
        initMinKey();
        
        for (int i =0 ;i < sz; i++) {
            ans[i] = countPress(targets[i]);
        }
        
        return ans;
    }
}