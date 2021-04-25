#pragma Ofast
#pragma loop-opt(on)
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
#define ll long long
#define FOR(i, n) for(int i = 0; i < n; ++i)
#define debug(x) cerr << #x << " is " << x << '\n';
const int N = 2000 + 1;
const int INF = 8e7;
int n, m;

struct point{
	int x, y;
} light[N], rob[N], robmax[N];
inline int eek(int a, int b){
	return a > b ? 0 : b - a + 1;
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> m;
	FOR(i, n) cin >> rob[i].x >> rob[i].y;
	FOR(i, m) cin >> light[i].x >> light[i].y;
	FOR(i, n){
		robmax[i].x = robmax[i].y = 0;
		FOR(j, m){
			int x = eek(rob[i].x, light[j].x), y = eek(rob[i].y, light[j].y);
			// if(x == y) robmax[i].x = max(robmax[i].x, x), robmax[i].y = max(robmax[i].y, y);
			if(x <= y) robmax[i].x = max(robmax[i].x, x);
			else robmax[i].y = max(robmax[i].y, y);
		}
	}
	int x = 0, y = 0;
	FOR(i, n){
		x = max(robmax[i].x, x),
		y = max(robmax[i].y, y);
	}
	// cout << x << ' ' << y << '\n';
	cout << x + y << endl;
	return 0;
}