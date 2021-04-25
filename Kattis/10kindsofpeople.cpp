#include<iostream>
#include<vector>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int r, c;
char m[1000][1000];
int s[1000][1000];

void dfs(int x, int y, int id){
	if(s[x][y])return;
	s[x][y] = id;
	if(x < r-1 and !s[x+1][y] and m[x+1][y] == m[x][y]){
		dfs(x+1, y, id);
	}
	if(x > 0 and !s[x-1][y] and m[x-1][y] == m[x][y]){
		dfs(x-1, y, id);
	}
	if(y < c-1 and !s[x][y+1] and m[x][y+1] == m[x][y]){
		dfs(x, y+1, id);
	}
	if(y > 0 and !s[x][y-1] and m[x][y-1] == m[x][y]){
		dfs(x, y-1, id);
	}
	return;
}

int main(){OW0
	cin>>r>>c;
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			cin>>m[i][j];
			s[i][j]=0;
		}
	}
	int setnum = 1;
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			if(!s[i][j]) dfs(i,j,setnum++);
		}
	}

	int n, x1, y1, x2, y2;
	cin>>n;
	while(n--){
		cin>>x1>>y1>>x2>>y2;
		x1--, y1--, x2--, y2--;
		if(s[x1][y1]==s[x2][y2]){
			if(m[x1][y1]=='1')cout<<"decimal\n";
			else cout<<"binary\n";
		}else{
			cout<<"neither\n";
		}
	}
	return 0;
}