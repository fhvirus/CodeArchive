#include<iostream>
using namespace std;

char map[50][50];
int ans=0,w,h;

void dfs(int x,int y){
	if(map[y][x]=='G'){
		ans++;
	}
	if (map[y][x+1]=='T'||
		map[y-1][x]=='T'||
		map[y][x-1]=='T'||
		map[y+1][x]=='T'||
		map[y][x]=='#'){map[y][x]='#';return;}
	map[y][x]='#';
	if(x<w-1&&map[y][x+1]!='#')dfs(x+1,y);
	if(y>0&&map[y-1][x]!='#')dfs(x,y-1);
	if(x>0&&map[y][x-1]!='#')dfs(x-1,y);
	if(y<h-1&&map[y+1][x]!='#')dfs(x,y+1);
	return;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int px,py;
	cin>>w>>h;
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			cin>>map[i][j];
			if(map[i][j]=='P')px=j,py=i;
		}
	}
	dfs(px,py);
	cout<<ans;
	return 0;
}