#include<iostream>
#include<algorithm>
#include<bitset>
using namespace std;

int N, M;
bitset<100> mask;
int dfs(int layer, int cnt, bitset<100> l, bitset<100> m, bitset<100> r){
	l<<=1, r>>=1; l&=mask, r&=mask;

	if(layer >= N){
		if(((l|m|r)&mask) == mask) return cnt;
		else return 8e7;
	}

	bitset<100> tmp = ~(l|m|r), cur;
	if(tmp.count() == 0) return dfs(layer + 1, cnt, l, m, r);
	int ans = 8e7;
	for(int i = 0; i < M; ++i){
		if(tmp[i]){
			cur[i] = 1;
			ans = min(ans, dfs(layer+1, cnt+1, l|cur, m|cur, r|cur));
			cur[i] = 0;
		}
	}
	// ans = min(ans, dfs(layer+1, cnt, l, m, r));
	return ans;
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	// if(N > M) swap(N, M);
	for(int i = 0; i < M; ++i)
		mask[i] = 1;
	cout << dfs(0, 0, bitset<100>(), bitset<100>(), bitset<100>());
	return 0;
}