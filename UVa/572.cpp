#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int m, n;
char s[100][100];

void dfs(int i, int j){
	if(s[i][j] == '*') return;
	s[i][j] = '*';
	if(i < m-1) dfs(i+1, j  );
	if(i > 0)	dfs(i-1, j  );
	if(j < n-1) dfs(i  , j+1);
	if(j > 0)	dfs(i  , j-1);
	if(i < m-1 and j < n-1) dfs(i+1, j+1);
	if(i < m-1 and j > 0  ) dfs(i+1, j-1);
	if(i > 0   and j < n-1) dfs(i-1, j+1);
	if(i > 0   and j > 0  ) dfs(i-1, j-1);
}

int main(){OW0
	while(cin>>m>>n and m){
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
				cin >> s[i][j];
			}
		}
		int cnt = 0;
		for(int i = 0; i < m; i++){
			for(int j = 0; j < n; j++){
				if(s[i][j] == '@'){
					dfs(i, j);
					cnt++;
				}
			}
		}
		cout << cnt <<'\n';
	}
	return 0;
}