#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int a[100001];

int main(){OW0;
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}
	sort(a, a+n);
	int l = 0, r = m - 1, mid = (l+r)/2;
	long long sum = 0, minsum;
	for(int i = l; i <= r; i++){
		sum += abs(a[i] - a[mid]);
	}
	minsum = sum;
	while(r + 1 < n){
		if(m % 2){
			sum += a[++r] - a[mid];
			mid++;
			sum -= a[mid] - a[l++];
		} else {
			mid++;
			sum -= a[mid] - a[l++];
			sum += a[++r] - a[mid];
		}
		if(minsum > sum) minsum = sum;
	}
	cout << minsum;
	return 0;
}