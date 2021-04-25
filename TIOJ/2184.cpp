#pragma GCC optimize("Ofast")
#include<iostream>
#include<cstdint>
using namespace std;
#ifdef OWO
int64_t ans = 100000000000000ll, cost;
bool Compare(int64_t v) {
	cost += v;
	return v > ans;
}
#else
#include "lib2184.h"
#endif
int64_t find_k(int64_t N) {
	int64_t l = 1, r = 1, m, cost = 0;

	auto check = [&](int64_t n){
		return n > N ? true : (cost += n, Compare(n));
	};

	while(!check(r*2)) r *= 2;

	l = r, r <<= 1;
	while(l < r){
		m = (l + r) / 2;
		if(check(m + 1)) r = m;
		else l = m + 1;
	}
    return l;
}
#ifdef OWO
int main() {
	cout << (find_k(100000000000000ll) == ans) << "\nCost : " << cost / ans;
}
#endif