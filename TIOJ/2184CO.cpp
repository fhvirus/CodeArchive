#pragma GCC optimize("Ofast")
#include "lib2184.h"
#define ll int64_t
inline bool check(ll n, ll N){
	return n > N ? true : Compare(n);
}
ll find_k(ll N) {
	ll l = 1, r = 1, m;

	while(!check(r*2, N)) r *= 2;

	l = r, r *= 2;
	if(r > N) r = N;
	while(l < r){
		m = (l + r) / 2 + 1;
		if(check(m, N)) r = m - 1;
		else l = m;
	}
    return l;
}