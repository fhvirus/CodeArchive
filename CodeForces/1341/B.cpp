#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int a[200000];
int peaks[200000];

int main(){OW0
	int T, n, k;
	cin >> T;
	while(T--){
		cin >> n >> k;
		for(int i = 0; i < n; i++)
			cin >> a[i];
		peaks[0] = 0;
		for(int i = 1; i < n-1; i++){
			if(a[i-1] < a[i] and a[i+1] < a[i]){
				peaks[i] = peaks[i-1]+1;
			} else {
				peaks[i] = peaks[i-1];
			}
		}
		peaks[n-1] = peaks[n-2];
		int maxcnt = 0, maxidx = 0;
		for(int i = 0; i + k - 1 < n; i++){
			if(peaks[i+k-2] - peaks[i] > maxcnt){
				maxcnt = peaks[i+k-2] - peaks[i];
				maxidx = i;
			}
		}
		cout << maxcnt+1 << ' ' << maxidx+1 << '\n';
	}
	return 0;
}