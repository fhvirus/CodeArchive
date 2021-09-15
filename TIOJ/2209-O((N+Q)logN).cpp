#include<iostream>
#include<cassert>
using namespace std;

const int kN = 100000;
const int kQ = 800;
const int kL = 17;

int N, Q, f[kL][kN+1];

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	assert(cin >> N);
	assert(1 <= N and N <= kN);
	for(int i = 1; i <= N; ++i)
		assert(cin >> f[0][i]);

	for(int l = 1; l < kL; ++l)
		for(int i = 1; i <= N; ++i)
			f[l][i] = f[l-1][f[l-1][i]];

	assert(cin >> Q);
	assert(1 <= Q and Q <= kQ);
	for(int a, b, i = 0; i < Q; ++i){
		assert(cin >> a >> b);
		assert(1 <= a and a <= N);
		assert(0 <= b and b <  N);
		for(int l = 0; l < kL; ++l)
			if(b >> l & 1) a = f[l][a];
		cout << a << '\n';
	}

	return 0;
}

