#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;

int readInt(){
	static int ans = 0;
	static bool minus = false;
	static char ch;
	ch = getchar();
	while(1){
		if(ch == '-') break;
		if(ch >= '0' or ch <= '9') break;
		ch = getchar();
	}
	if(ch == '-') minus = true;
	else ans = ch - '0';
	while(1){
		ch = getchar();
		if(ch > '9' or ch < '0') break;
		ans = ans * 10 + (ch - '0');
	}
	return minus ? -ans : ans;
}

// RMQ structure by 2qbx
map<int, long long> mp;
void init(){
	mp.clear();
}
long long getmax(int h){
	auto it = mp.lower_bound(h);
	if(it == mp.begin()) return 0;
	return prev(it)->second; 
}
void ins(int h, long long dp){
	auto it = mp.upper_bound(h);
	if(it != mp.begin() and prev(it)->second >= dp) return;
	while(it != mp.end() and it->second <= dp) mp.erase(it++);
	mp[h] = dp;
}

const int MAXN = 2e5;
int n, q, x, id[MAXN], i, k, H;
long long w[MAXN], h[MAXN], f[MAXN];
long long dp[2][MAXN];

int main(){
	n = readInt(); q = readInt();
	for(i = 0; i < n; i++){
		w[i] = readInt();
		h[i] = readInt();
		f[i] = readInt();
		id[i] = i;
	}
	sort(id, id+n, [](int a, int b){
		if(w[a] != w[b]) return w[a] < w[b];
		return h[a] > h[b];
	});

	init();
	for(i = 0; i < n; i++){
		k = id[i], H = h[k];
		dp[0][k] = f[k] + getmax(H);
		ins(H, dp[0][k]);
	}

	init();
	for(i = n-1; i >= 0; i--){
		k = id[i], H = 100001 - h[k];
		dp[1][k] = f[k] + getmax(H);
		ins(H, dp[1][k]);
	}

	for(;q;--q){
		x = readInt();
		x--;
		printf("%lld\n", dp[0][x] + dp[1][x] - f[x]);
	}
	return 0;
}