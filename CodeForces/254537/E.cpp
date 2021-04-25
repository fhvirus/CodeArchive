#include<iostream>
#include<queue>
#include<vector>
#include<functional>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

const int MAXN = 4 * 1e5;

int a[MAXN], b[MAXN];
priority_queue<int, vector<int>, greater<int>> ramen;

int main(){OW0
	int n, k, x;
	long long S = 0;
	cin >> n >> k;
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}
	cin >> x;
	for(int i = 0; i < n; i++){
		cin >> b[i];
	}
	for(int i = 0; i < n; i++){
		ramen.push(b[i]);
		while(!ramen.empty() and k < a[i]){
			S += ramen.top();
			k += x;
			ramen.pop();
		}
		if(k < a[i] and ramen.empty()){
			cout << -1;
			return 0;
		}
	}
	cout << S;
	return 0;
}