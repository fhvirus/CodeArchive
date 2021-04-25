#include<iostream>
#include<queue>
#include<utility>
using namespace std;

#define pii pair<int, int>
#define x first
#define y second

const int dx[8] = {1, 3, 3, 1, -1, -3, -3, -1};
const int dy[8] = {3, 1, -1, -3, -3, -1, 1, 3};
const int ox[8] = {0, 1, 1, 0, 0, -1, -1, 0};
const int oy[8] = {1, 0, 0, -1, -1, 0, 0, 1};

int n, g[100][100];
bool vis[100][100];
inline bool ok(int i, int j, int d){
	return i+dx[d] >= 0 and j+dy[d] >= 0 and i+dx[d] < 100 and j+dy[d] < 100 and !g[i+dx[d]][j+dy[d]] and
		!g[i+ox[d]][j+oy[d]] and vis[i+dx[d]][j+dy[d]] == 0;
}
pii s, t;

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;
	for(int i = 0, a, b; i < n; ++i){
		cin >> a >> b;
		g[a][b] = true;
	}
	cin >> s.x >> s.y;
	cin >> t.x >> t.y;
	if(s == t){
		cout << 0;
		return 0;
	}

	queue<pii> q;
	q.push(s);
	vis[s.x][s.y] = 1;
	while(!q.empty()){
		pii u = q.front(); q.pop();
		for(int d = 0; d < 8; ++d){
			if(!ok(u.x, u.y, d)) continue;
			pii v = {u.x + dx[d], u.y + dy[d]};
			vis[v.x][v.y] = vis[u.x][u.y] + 1;
			if(v == t){
				cout << vis[v.x][v.y] - 1;
				return 0;
			}
			q.push(v);
		}
	}

	cout << "impossible";
	return 0;
}
