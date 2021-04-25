#pragma GCC optimize("Ofast")
#include<iostream>
#include<queue>
#include<functional>
using namespace std;

const int N = 2e5 + 225;
int n, a[N], app[N];

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;
	for(int i = 0; i < n-1; ++i){
		cin >> a[i];
		++app[a[i]];
	}
	cout << a[0] << '\n';
	priority_queue<int, vector<int>, greater<int>> pq;
	for(int i = 1; i <= n; ++i)
		if(app[i] == 0) pq.push(i);
	for(int i = n-2; i >= 0; --i){
		cout << pq.top() << ' ' << a[i] << '\n'; pq.pop();
		if(app[a[i]] == 0) pq.push(a[i]);
	}
	return 0;
}

