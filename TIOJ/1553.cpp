#include <bits/stdc++.h>
using namespace std;
#ifdef OWO
#define debug(args...) _debug(#args,args)
#define _OO(args...) ostream& operator<<(ostream&O,args)
#define _DEF(S) template<class...T>_OO(S<T...>);
#define _DEC(S,B,E,F) template<class...T>_OO(S<T...>s){O<<B;int c=0;for(auto i:s)O<<(c++?", ":"")<<F;return O<<E;}
_DEF(vector);_DEF(deque);_DEF(set);_DEF(multiset);_DEF(unordered_set);_DEF(map);_DEF(unordered_map);_DEF(pair);_DEF(tuple);template<class T,size_t N>_OO(array<T,N>);
_DEC(vector,'[',']',i);_DEC(deque,'[',']',i);_DEC(set,'{','}',i);_DEC(multiset,'{','}',i);_DEC(unordered_set,'{','}',i);_DEC(map,'{','}',i.first<<':'<<i.second);_DEC(unordered_map,'{','}',i.first<<':'<<i.second);
template<class...T>_OO(pair<T...>p){return O<<'('<<p.first<<','<<p.second<<')';}template<class...T>_OO(tuple<T...>t){return O<<'(',apply([&O](T...s){int c=0;(...,(O<<(c++?", ":"")<<s));},t),O<<')';}template<class T,size_t N>_OO(array<T,N>a){return O<<vector<T>(begin(a),end(a));}
template<class...T>void _debug(const char* s,T...a){int c=sizeof...(T);if(!c){cerr<<"\033[1;32mvoid\033[0m\n";return;}(cerr<<"\033[1;32m("<<s<<") = (",...,(cerr<<a<<(--c?", ":")\033[0m\n")));}
#else
#define debug(...) ((void)0)
#endif

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  const auto mad = [&](int u, int v) {
    return u + v >= n ? u + v - n : u + v; };

  vector<int> sc(n), dp(n);
  if (n % 2 == 1) sc = a;
  for (int len = n % 2; len + 2 < n; len += 2) {
    for (int i = 0; i < n; ++i) {
      dp[i] = a[i] + min(sc[mad(i, 1)], sc[mad(i, 2)]);
      dp[i] = max(dp[i], a[mad(i, len + 1)] +
          min(sc[i], sc[mad(i, 1)]));
    }
    swap(dp, sc);
  }

  int tot = accumulate(begin(a), end(a), 0), cnt = 0, max_v = 0;
  for (int i = 0; i < n; ++i) {
    int v = a[i] + min(sc[mad(i, 1)], sc[mad(i, 2)]);
    cnt += (v * 2 > tot);
    max_v = max(max_v, v);
  }

  cout << cnt << ' ' << max_v << '\n';

  return 0;
}
