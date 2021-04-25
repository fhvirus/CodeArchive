#include<iostream>
using namespace std;

#define owo ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int a[100], n;

int snap(int l, int r){
	if(r - l == 1) return 1;
	int m = (l + r)/2;
	int left =  snap(l, m);
	int right = snap(m, r);
	if(left == m-l and right == r-m and a[m-1] <= a[m])
		return left + right;
	else return left > right ? left : right;
}

int main(){owo
	cin>>n;
	for(int i = 0; i < n; i++){
		cin>>a[i];
	}
	cout<<snap(0, n);
	return 0;
}