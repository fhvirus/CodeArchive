#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

const int N = 1e5 + 10;
int t, n, a[N], app[N];

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;
	for(int i = 0; i < n; ++i){
		cin >> a[i];
		app[a[i]] ++;
	}

	int mex = 1;
	while(app[mex]) ++mex;

	if(a[0] < mex and app[a[0]] > 1)
	return 0;
}