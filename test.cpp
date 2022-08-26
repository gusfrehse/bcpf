#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;

#define N 1001

vector<vector<ll>> board1(N, vector<ll>(N));
vector<vector<ll>> board2(N, vector<ll>(N));

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  set<pair<ll, ll>> fires;
  set<pair<ll, ll>> candidates;

  ll n, m, t;
  cin >> n >> m >> t;

  for (int y = 0; y < n; y++) {
    for (int x = 0; x < m; x++) {
      ll a;
      cin >> a;
      board1[y][x] = a;
      if (a == 0) {
        fires.insert({y, x});
      }
    }
  }

  ll dx[] = { 0, -1, 1,  0, -1,  1, -1, 1 };
  ll dy[] = { 1,  0, 0, -1, -1, -1,  1, 1 };

  while (t--) {
    for (auto &[y, x] : candidates) {
      board2[y][x] = 0;
    }
    for (auto [y, x] : fires) {
      for (int i = 0; i < 8; i++) {
        ll xi = x + dx[i];
        ll yi = y + dy[i];

        if (xi < 0 || xi >= m || yi < 0 || yi >= n)
          continue;
        
        if (board1[yi][xi] == 1 || (board1[yi][xi] > 1 && i < 4)) {
          // 4 vizinhaca
          candidates.insert({yi, xi});
          board2[yi][xi]++;
        }
      }
    }

    for (auto &[y, x] : candidates) {
      if ((board2[y][x] + 1 >= board1[y][x]) || (board1[y][x] == 1 && board2[y][x])) {
        fires.insert({y, x});
        //candidates.erase({y, x});
        board1[y][x] = 0;
      }
    }
  }

  cout << fires.size();
}

