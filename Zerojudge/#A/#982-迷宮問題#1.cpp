#include<iostream>
#include<queue>
#include<utility>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int n;
int dist[100][100];
bool m[100][100];
char tmp;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int x, y, k;
queue<pair<int, int>> Q;
void bfs(int i, int j){
	m[i][j] = true;
	Q.push({i, j});
	while(!Q.empty()){
		x = Q.front().first, y = Q.front().second; Q.pop();
		m[x][y] = true;
		for(k = 0; k < 4; k++){
			if(x + dx[k] >= n or x + dx[k] < 0) continue;
			if(y + dy[k] >= n or y + dy[k] < 0) continue;
			if(!m[x + dx[k]][y + dy[k]]){
				dist[x + dx[k]][y + dy[k]] = dist[x][y] + 1;
				Q.push({x + dx[k], y + dy[k]});
			}
		}
	}
}

int main(){eek
	cin >> n;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			cin >> tmp;
			m[i][j] = (tmp=='#');
		}
	}
	bfs(1, 1);
	if(dist[n-2][n-2] == 0)
		cout << "No solution!";
	else
		cout << dist[n-2][n-2]+1;
	return 0;
}