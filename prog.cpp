#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;

#define N ll(1e6)

ll t[2 * N];
ll n;

void build() {
  for (int i = n - 1; i > 0; i--) {
    t[i] = t[i << 1] + t[i << 1 | 1];
  }
}

ll query(ll l, ll r) {
  ll ans = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ans += t[l++];
    if (r & 1) ans += t[--r];
  }
  return ans;
}

void modify(ll p, ll val) {
  for (t[p += n] = val; p > 1; p >>= 1) {
    t[p >> 1] = t[p] + t[p^1];
  }
}

void modify_range(ll l, ll r, ll val) {
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) t[l++] += val;
    if (r & 1) t[--r] += val;
  }
}

int main() {
  //cin.tie(0);
  //ios_base::sync_with_stdio(0);
  build();

  ll q, n2;
  cin >> n2 >> q;
  n = 2 * n2;

  vector<ll> v(n, 0);

  for (int i = 0; i < n2; i++) {
    cin >> v[i];
  }

  ll head = 0;
  for (int i = 0; i < q; i++) {
    char op;
    cin >> op;

    if (op == 'm') {
      ll quant;
      cin >> quant;
      head += quant;
    } else if (op == 'd') {
      if (head != n2 - 1) {
        ll old = query(head, head + 1);
        modify(head, old + 1);
        //n2--;
      } else {
        ll old = query(0, head + 1);
        ll old_start = query(0, 1);
        modify(0, old_start - old);
      }
    } else {
      ll q = query(0, head + 1) + head;
      //cout << " head " << head << " q " << q << '\n';
      cout << v[q] << '\n';
    }

    //for (int i = 0; i < n; i++) {
    //  cout << query(0, i + 1) << " ";
    //}
    //cout << '\n';
  }
}

/*
 *
 * 0000000
 * 0123456
 * 0010000
 * 0011111
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * */
