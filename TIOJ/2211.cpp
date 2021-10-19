#pragma GCC optimize("Ofast")
#include "lib2211.h"
#include<vector>
using namespace std;

const int kK = 400;

signed main(){
	int N = Init();
	vector<int> a(kK+1); a[0] = 1;
	for(int i = 1; i <= kK; ++i){
		a[i] = Query(1, i);
		if(a[i] == 1) Report(a[i-1]);
	}
	for(int i = kK * 2; i <= N; i += kK){
		int u = Query(1, i);
		for(int j = 0; j <= kK; ++j){
			if(a[j] == u){
				int cyc = i - j;
				int v = Query(1, cyc-1);
				Report(v);
			}
		}
	}

	return 0;
}

