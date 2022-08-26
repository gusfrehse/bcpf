#include <algorithm>
#include <bits/stdc++.h>
#include <vector>

using namespace std;
using ll = long long;
using ull = unsigned long long;

#define N 11234567

int t[2 * N] = {};
int d[N] = {};
int n;
int h;
//int t2[2 * N] = {};

void calc(int p, int k) {
  if (d[p] == 0)
    t[p] = t[p << 1] + t[p << 1 | 1];
  else
    t[p] = d[p] * k;
}

void apply(int p, int val, int k) {
  t[p] = val * k;
  if (p < n) d[p] = val;
}

void apply_inc(int p, int val, int k) {
  t[p] += val;
  if (p < n) d[p] += val;
}

void build(int l, int r) {
  int k = 2;
  for (l += n, r += n -1; l > 1; k <<= 1) {
    l >>= 1, r >>= 1;
    for (int i = r; i >= l; i--)
      calc(i, k);
  }
}

void push(int l, int r) {
  int s = h, k = 1 << (h - 1);
  for (l += n, r += n - 1; s > 0; s--, k >>= 1)
    for (int i = l >> s; i <= r >> s; i++) {
      apply(i << 1, d[i], k);
      apply(i << 1|1, d[i], k);
      d[i] = 0;
    }

}

void modify(int l, int r, int val) {
  if (val == 0)
    return;

  push(l, l + 1);
  push(r - 1, r);

  int l0 = l, r0 = r, k = 1;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
    if (l & 1) apply(l++, val, k);
    if (r & 1) apply(--r, val, k);
  }

  build(l0, l0 + 1);
  build(r0 - 1, r0);
}

void inc(int l, int r, int val) {
  if (val == 0)
    return;

  push(l, l + 1);
  push(r - 1, r);

  int l0 = l, r0 = r, k = 1;

  for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
    if (l & 1)
      apply_inc(l++, val, k);
    if (r & 1)
      apply_inc(--r, val, k);
  }

  build(l0, l0 + 1);
  build(r0 - 1, r0);
}

int query(int l, int r) {
  push(l, l + 1);
  push(r - 1, r);

  int res = 0;

  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      res += t[l++];
    if (r & 1)
      res += t[--r];
  }

  return res;
}

void compress(vector<int> &v, vector<int> &cv) {
  set<int> vals(v.begin(), v.end());
  map<int, int> ida, volta;
  int ix = 0;
  for (int i : vals) {
    ida[i] = ix;
    volta[ix] = i;
    ix++;
  }

  for (int i = 0; i < v.size(); ++i)
    cv[i] = ida[v[i]];
}

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  fill_n(t, 2 * N, 0);

  int q;

  cin >> n >> q;

  h = sizeof(int) * 8 - __builtin_clz(n);

  for (int i = 0; i < n; i++) {
    int a;
    cin >> a; //t[n + i];
    inc(i, i + 1, a);
  }

  //for (int i = 0; i < n; i++) {
  //  build(i);
  //}

  //for (int i = 0; i < n; i++) {
  //  cout << query(i, i + 1) << " ";
  //}
  //cout << " <- \n";

  //cout << query(0, 5) << "\n";
  //cout << query(0, 5) << "\n";

  //inc(0, 3, 2);
  //for (int i = 0; i < n; i++) {
  //  cout << query(i, i + 1) << " ";
  //}
  //cout << " <- \n";

  //inc(1, 5, 10);
  //for (int i = 0; i < n; i++) {
  //  cout << query(i, i + 1) << " ";
  //}
  //cout << " <- \n";

  //inc(1, 4, 10);
  //for (int i = 0; i < n; i++) {
  //  cout << query(i, i + 1) << " ";
  //}
  //cout << " <- #\n";

  //build();

  //compress(uncom, com);

  for (int i = 0; i < q; i++) {
    int op, a, b;
    cin >> op >> a >> b;
    a--;

    if (op == 1) {
      int x;
      cin >> x;
      inc(a, b, x);
    } else if (op == 2) {
      int x;
      cin >> x;
      modify(a, b, x);
    } else {
      cout << query(a, b) << "\n";
    }
  }
}
/*
5 9
1 2 3 4 5
q 1 5 = 1
+ 1 3 2
3 4 5 4 5
q 4 5 = 4
q 4 5 = 4
+ 2 5 10
3 14 15 14 15
q 2 5 = 14
q 1 5 = 14
+ 2 4 10
3 24 25 24 15
q 2 5 = 15
*/
