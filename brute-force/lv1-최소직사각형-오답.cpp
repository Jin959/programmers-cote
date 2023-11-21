#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> sizes;
int sz = 0;
bool flip[10000];
int min_wallet = 21e8;

int getWalletSize() {
    int max_w = 0, max_h = 0;

    for (int i = 0; i < sz; i++) {
        if (sizes[i][0] > max_w) {
            max_w = sizes[i][0];
        }
        if (sizes[i][1] > max_h) {
            max_h = sizes[i][1];
        }
    }

    return max_h * max_w;
}

void dfs(int n) {
    //base condition
    if (n == sz) return;

    int tmp = getWalletSize();
    if (tmp < min_wallet) {
        min_wallet = tmp;
    }

    // flip[n] = true;
    swap(sizes[n][0], sizes[n][1]);
    dfs(n + 1);

    // flip[n] = false;
    swap(sizes[n][0], sizes[n][1]);
    dfs(n + 1);
}

int solution(vector<vector<int>> sizes_) {
    sizes = sizes_;
    sz = sizes.size();

    dfs(0);
    return min_wallet;
}
