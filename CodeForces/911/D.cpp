#include<iostream>
using namespace std;
const int N = 1500;
int n, a[N], q, l, r;
bool jizz;
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;
	for(int i = 0; i < n; ++i) cin >> a[i];
	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n; ++j)
			if(a[i] > a[j]) jizz = !jizz;
	cin >> q;
	for(; q; --q){
		cin >> l >> r;
		int jiz = r - l + 1;
		int eek = jiz * (jiz - 1) / 2;
		jizz ^= (eek & 1);
		cout << (jizz ? "odd\n" : "even\n");
	}
}