//Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return c;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}

#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#include<functional>
using namespace std;

#define pii pair<int,int>
#define ff first
#define ss second

const int N = 1e5;
int n;
pii x[N], y[N];
bool solve(pii *p){
	int ptr = 0;
	sort(p, p + n);
	priority_queue<int, vector<int>, greater<int>> pq;
	for(int i = 1; i <= n; ++i){
		while(ptr < n and p[ptr].ff <= i){
			pq.push(p[ptr].ss);
			++ptr;
		}
		if(pq.empty() or pq.top() < i) return false;
		pq.pop();
	}
	return true;
}
int main(){
	while((n = R()) != -1){
		for(int i = 0; i < n; ++i){
			x[i] = {R(), R()}; y[i] = {R(), R()};
		}
		puts(solve(x) and solve(y) ? "YES" : "NO");
	}
	return 0;
}
