#include<iostream>
#include<vector>
#include<queue>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define INF 2147483647

struct point{
	int r, c;
	point(): r(0), c(0){};
};

int R, C;
int maze[1000][1000];
vector<vector<bool>> vis(1000, vector<bool>(1000));



int main(){OW0
	int T;
	string in;
	cin >> T;
	while(T--){
		for(int r = 0; r < R; r++){
			cin >> in;
			for(int c = 0; c < C; c++){
				if(in[c] == '#') maze[r][c] = 0;
				if(in[c] == '.') maze[r][c] = INF;
				if(in[c] == '#') maze[r][c] = 0;
				if(in[c] == '#') maze[r][c] = 0;
			}
		}
	}
	return 0;
}