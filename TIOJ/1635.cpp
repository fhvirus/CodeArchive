#pragma Ofast
#pragma loop-opt(on)
#pragma GCC target("avx,avx2")
#include"lib1635.h"

int n, l, r, m;
int main(){
	n = Initialize();
	l = 1, r = n;
	while(l < r){
		m = (l + r) / 2;
		(Max(m, m + 1) == m) ? r = m : l = m + 1;
	}
	Report(l);
}