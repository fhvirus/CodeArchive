#include<iostream>
using namespace std;

const int kN = 100001;

int N, Q, f[kN];
int groupID[kN], groupPos[kN], groupSiz[kN], groupStart[kN], tot;
int all[kN], eek;

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N;
	for(int i = 1; i <= N; ++i) cin >> f[i];
	for(int i = 1; i <= N; ++i){
		if(groupID[i]) continue;
		++tot;
		int u = i, cnt = 0;
		groupStart[tot] = eek+1;
		do {
			groupID[u] = tot;
			groupPos[u] = cnt++;
			all[++eek] = u;
			u = f[u];
		} while(u != i);
		groupSiz[tot] = cnt;
	}
	cin >> Q;
	for(int a, b, i = 0; i < Q; ++i){
		cin >> a >> b;
		int pos = groupStart[groupID[a]];
		pos += (groupPos[a] + b) % groupSiz[groupID[a]];
		cout << all[pos] << '\n';
	}
	return 0;
}

