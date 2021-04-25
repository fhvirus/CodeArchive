#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include"lib1871.h"
#include<utility>
#include<algorithm>
using namespace std;

const int N = 1e6+1;
int n, q, val[21][N], *a;

inline int query(int l, int r){
	int d = 31 - __builtin_clz(r - l);
	return min(val[d][l], val[d][r - (1<<d)]);
}

int main(){
	n = futa::init();
	a = futa::momo_gives_you_list_of_futa();
	q = futa::momo_tells_you_q();
	for(int i = 0; i < n; ++i)
		val[0][i] = a[i];
	for(int i = 1; i < 21; ++i)
		for(int j = 0; j + (1<<i) <= n; ++j)
			val[i][j] = min(val[i-1][j], val[i-1][j + (1<<(i-1))]);
	for(; q; --q){
		auto p = futa::momo_asks();
		futa::you_tell_momo(query(p.first, p.second + 1));
	}
}