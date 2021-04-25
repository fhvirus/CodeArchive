#include<iostream>
#include<cstring>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
int w[501][501], dist[501][501], n;

void floyd_warshall(){
	for(int i = 0; i <= n; i++){
		for(int j = 0; j <= n; j++){
			dist[i][j] = (i==j ? 0 : w[i][j]);
		}
	}

	for(int k = 1; k <= n; k++){
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= n; j++){
				if( dist[i][k] != -1 and 
					dist[k][j] != -1 and
					(dist[i][k] + dist[k][j] < dist[i][j] or dist[i][j] == -1)){
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
}

int main(){OW0
	int m, q, a, b, c;
	cin >> n >> m;
	memset(w, -1, sizeof(w));
	for(;m;m--){
		cin >> a >> b >> c;
		if(w[a][b] == -1 or (w[a][b] != -1 and w[a][b] > c))
			w[a][b] = w[b][a] = c;
	}
	floyd_warshall();
	cin >> q;
	for(;q;q--){
		cin >> a >> b;
		cout << dist[a][b] << '\n';
	}
	return 0;
}