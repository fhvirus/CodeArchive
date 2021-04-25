#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int a[200000];

inline int sign(int x){return x >= 0 ? 1:-1;}

int main(){OW0
	int T, n;
	cin >> T;
	while(T--){
		cin >> n;
		for(int i = 0; i < n; i++) cin >> a[i];
		long long dpsum = 0, lastsign = (a[0]>=0?1:-1), cur = a[0];
		for(int i = 0; i < n; i++){
			if(sign(a[i]) == lastsign){
				if(a[i] > cur) cur = a[i];
			} else {
				dpsum += cur;
				lastsign = sign(a[i]);
				cur = a[i];
			}
		}
		dpsum += cur;
		cout << dpsum << '\n';

	}
	return 0;
}