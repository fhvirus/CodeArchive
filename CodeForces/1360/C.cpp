#include<iostream>
#include<algorithm>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int a[50];
int main(){OW0
	int t, n, cnt0, cnt1;
	bool ans;
	cin >> t;
	for(;t;--t){
		cin >> n;
		cnt0 = cnt1 = 0;
		ans = false;
		for(int i = 0; i < n; i++){
			cin >> a[i];
			if(a[i] % 2) cnt1++;
			else cnt0++;
		}
		if(cnt0 % 2 == 0 and cnt1 % 2 == 0){
			ans = true;
		} else {
			sort(a, a + n);
			for(int i = 0; i < n-1; i++){
				if(a[i] == a[i+1] - 1 and cnt0 > 0 and cnt1 > 0){
					cnt0--;
					cnt1--;
					i++;
				}
				if(cnt0 % 2 == 0 and cnt1 % 2 == 0){
					ans = true;
					break;
				}
			}
		}
		cout << (ans ? "YES\n" : "NO\n");
	}
	return 0;
}