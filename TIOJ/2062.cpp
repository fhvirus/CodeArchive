#include<cstdio>
#include<vector>
using namespace std;

const int MAXN = 1000001;
vector<int> color;
vector<vector<int>> G;
int n, m, a, b, S = 0, T = 0;

bool isbipartite = true;

int readInt () {
	bool minus = false;
	int result = 0;
	char ch;
	ch = getchar();
	while (true) {
		if (ch == '-') break;
		if (ch >= '0' && ch <= '9') break;
		ch = getchar();
	}
	if (ch == '-') minus = true; else result = ch-'0';
	while (true) {
		ch = getchar();
		if (ch < '0' || ch > '9') break;
		result = result*10 + (ch - '0');
	}
	if (minus)
		return -result;
	else
		return result;
}

void dfs(int s){
	if(color[s] == 1) S++;
	else T++;
	for(auto i: G[s]){
		if(!color[i]){
			color[i] = -color[s];
			dfs(i);
		} else if(color[i] == color[s]){
			isbipartite = false;
			return;
		}
	}
}

int main(){
	n = readInt(); m = readInt();
	color.resize(n+1);
	G.resize(n+1);
	for(int i = 0; i < m; i++){
		a = readInt(); b = readInt();
		G[a].push_back(b);
		G[b].push_back(a);
	}
	for(int i = 1; i <= n and isbipartite; i++){
		if(!color[i])
			color[i] = 1, dfs(i);
	}
	if(isbipartite){
		printf("%d %d\n", S, T);
		for(int i = 1; i <= n; i++){
			if(color[i] == 1)
				printf("%d ", i);
		}
		printf("\n");
		for(int i = 1; i <= n; i++){
			if(color[i] != 1)
				printf("%d ", i);
		}
	} else {
		printf("-1");
	}
	return 0;
}