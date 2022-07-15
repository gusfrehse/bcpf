#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    deque<ll> dq;

    ll n, q;
    cin >> n >> q;

    for (int i = 0; i < n; i++) {
      ll t;
      cin >> t;
      dq.push_back(t);
    }

    auto head = dq.begin();
    for (int i = 0; i < q; i++) {
      char op;
      cin >> op;

      if (op == 'q') {
        cout << *head << '\n';
      } else if (op == 'm') {
        ll amount;
        cin >> amount;
        advance(head, amount);
      } else {
        head = dq.erase(head);
      }
    }
}
