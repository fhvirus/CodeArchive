#include<cstdio>
#include<algorithm>
#include<map>
using namespace std;

// Fast IO
int readInt(){
	static char ch;
	static int  ans = 0;
	static bool minus = false;
	ch = getchar();
	while(true){
		if(ch == '-') break;
		if(ch >= '0' and ch <= '9') break;
		ch = getchar();
	}

	if(ch == '-') minus = true;
	else ans = ch - '0';

	while(true){
		ch = getchar();
		if(ch > '9' or ch < '0') break;
		ans = ans * 10 + (ch - '0');
	}
	return minus ? -ans : ans;
}

// RMQ struct
map<int, long long> M;
void init(){
	M.clear();
}
long long getmax(int h){
	auto it = M.lower_bound(h);
	if(it == M.begin()) return 0;
	return prev(it)->second;
}
void ins(int h, long long dp){
	auto it = M.upper_bound(h);
	if(it != M.begin() and prev(it)->second >= dp) return;
	while(it != M.end() and it->second <= dp) M.erase(it++);
	M[h] = dp;
}

constexpr int MAXN = 2e5;
int w[MAXN], h[MAXN], id[MAXN];
long long f[MAXN], dp[2][MAXN];

int main(){
	int n, q;
	n = readInt(); q = readInt();
	for(int i = 0; i < n; i++){
		w[i] = readInt();
		h[i] = readInt();
		f[i] = readInt();
		id[i] = i;
	}

	sort(id, id + n, [](int a, int b){
		if(w[a] != w[b]) return w[a] < w[b];
		return h[a] > h[b];
	});

	init();
	for(int i = 0; i < n; i++){
		int k = id[i], H = h[k];
		dp[0][k] = f[k] + getmax(H);
		ins(H, dp[0][k]);
	}

	init();
	for(int i = n-1; i >= 0; i--){
		int k = id[i], H = 100001 - h[k];
		dp[1][k] = f[k] + getmax(H);
		ins(H, dp[1][k]);
	}

	int x;
	for(;q;q--){
		x = readInt();
		x--;
		printf("%lld\n", dp[0][x] + dp[1][x] - f[x]);
	}
	return 0;
}