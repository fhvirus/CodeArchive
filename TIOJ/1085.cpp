#include<iostream>
#include<queue>
#include<stack>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

bool G[50][50][50];
int dist[50][50][50];
int pre[50][50][50];
int x, y, z;

struct point{
	int x, y, z;
	point(int x, int y, int z): x(x), y(y), z(z){}
};

const int dx[6] = {1, -1, 0, 0, 0, 0};
const int dy[6] = {0, 0, 1, -1, 0, 0};
const int dz[6] = {0, 0, 0, 0, 1, -1};

int main(){eek
	cin >> z >> y >> x;
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			for(int k = 0; k < z; k++){
				cin >> G[i][j][k];
			}
		}
	}

	queue<point> Q;
	dist[0][0][0] = 1;
	Q.push(point(0, 0, 0));
	while(!Q.empty()){
		point now = Q.front(); Q.pop();
		for(int i = 0; i < 6; i++){
			point nxt(now.x+dx[i], now.y+dy[i], now.z+dz[i]);
			if(nxt.x >= x or nxt.x < 0) continue;
			if(nxt.y >= y or nxt.y < 0) continue;
			if(nxt.z >= z or nxt.z < 0) continue;
			if(dist[nxt.x][nxt.y][nxt.z]) continue;
			if(!G[nxt.x][nxt.y][nxt.z]){
				dist[nxt.x][nxt.y][nxt.z] = dist[now.x][now.y][now.z] + 1;
				pre[nxt.x][nxt.y][nxt.z] = i;
				Q.push(nxt);
			}
		}
	}

	if(!dist[x-1][y-1][z-1] or G[0][0][0]){
		cout << "no route";
		return 0;
	}

	stack<point> ans;
	int i;
	x--, y--, z--;
	while(x or y or z){
		ans.push(point(x, y, z));
		i = pre[x][y][z];
		x -= dx[i], y -= dy[i], z -= dz[i];
	}
	cout << "(1,1,1)";
	while(!ans.empty()){
		point now = ans.top();
		cout << "->(" << now.z+1 <<','<< now.y+1 <<','<< now.x+1 <<')';
		ans.pop(); 
	}
	return 0;
}