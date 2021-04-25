#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 1010;
int t, n, x, a[N], b[N];

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> t;
	while(t--){
		cin >> n >> x;
		for(int i = 0; i < n; ++i)
			cin >> a[i];
		for(int i = 0; i < n; ++i)
			cin >> b[i];
		sort(a, a + n);
		sort(b, b + n);
		bool ans = true;
		for(int i = 0; i < n; ++i){
			if(a[i] + b[n - i - 1] > x){
				ans = false;
				break;
			}
		}
		cout << (ans ? "Yes\n" : "No\n");
	}
	return 0;
}