// https://school.programmers.co.kr/learn/courses/30/lessons/86491

#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> sizes;
int sz = 0;

void setCard() {
    for (int i = 0; i < sz; i++) {
        if (sizes[i][0] >= sizes[i][1]) continue;
        swap(sizes[i][0], sizes[i][1]);
    }
}

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

int solution(vector<vector<int>> sizes_) {
    sizes = sizes_;
    sz = sizes.size();

    setCard();
    return getWalletSize();
}