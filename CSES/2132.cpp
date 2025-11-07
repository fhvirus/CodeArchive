#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vi x(n);
  for (int &i : x) cin >> i;

  ll base = 0;
  priority_queue<int> pq;
  pq.push(x[0]);

  rep (i, 1, n) {
    int p = pq.top();
    base += max(p - x[i], 0);
    pq.push(x[i]); pq.push(x[i]); pq.pop();
  }

  cout << base << '\n';

  return 0;
}
