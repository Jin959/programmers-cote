#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>

#define MAXN 10'000

using namespace std;

vector<vector<string>> tickets;
string start = "ICN";

vector<string> track;   // ans
vector<string> tmp_track;

unordered_map<string, vector<string>> adj;  // HashMap<>()
unordered_map<string, int> rest;
int cnt;

bool comp(vector<string> a, vector<string> b) {
    return a[1] < b[1];
}

void init() {
    sort(tickets.begin(), tickets.end(), comp);
    for (vector<string> ticket : tickets) {
        string from = ticket[0];
        string to = ticket[1];

        adj[from].push_back(to);
        rest[from + to]++;    // 티켓 개수 올리기
    }
}

void dfs(string now) {
    if (cnt == tickets.size()) {
        for (string airport : tmp_track) {
            track.push_back(airport);
        }
        return;
    }

    for (string nxt : adj[now]) {
        if (!rest[now + nxt]) continue;   // 티켓이 남아있으면

        tmp_track.push_back(nxt);
        rest[now + nxt]--;
        cnt++;

        dfs(nxt);
        if (cnt == tickets.size()) return;

        cnt--;
        rest[now + nxt]++;
        tmp_track.pop_back();
    }
}

vector<string> solution(vector<vector<string>> tickets_) {
    tickets = tickets_;
    init();

    tmp_track.push_back(start);
    dfs(start);

    return track;
}