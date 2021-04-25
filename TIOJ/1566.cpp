#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline unsigned R(){static char c;unsigned a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n, char e){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=e;if(OP>65516)write(1,OB,OP),OP=0;}

#include<vector>
#include<deque>
#include<utility>
using namespace std;

#define ff first
#define ss second
#define pb emplace_back

int main(){
	int n, m;
	unsigned k, h;
	deque<pair<unsigned, int>> mx, mn;
	vector<pair<int, int>> ans;

	n = R(), m = R(), k = R();
	for(int i = 1; i <= n; ++i){
		h = R();
		while(!mx.empty() and mx.front().ss + m <= i) mx.pop_front();
		while(!mn.empty() and mn.front().ss + m <= i) mn.pop_front();
		while(!mx.empty() and mx.back().ff <= h) mx.pop_back();
		while(!mn.empty() and mn.back().ff >= h) mn.pop_back();
		mx.pb(h, i);
		mn.pb(h, i);
		if(mx.front().ff - mn.front().ff == k)
			ans.pb(max(1, i - m + 1), i);
	}
	for(int i = n + 1; i <= n + m; ++i){
		while(!mx.empty() and mx.front().ss + m <= i) mx.pop_front();
		while(!mn.empty() and mn.front().ss + m <= i) mn.pop_front();
		if(mx.front().ff - mn.front().ff == k)
			ans.pb(max(1, i - m + 1), n);
	}
	W(ans.size(), '\n');
	for(auto i: ans) W(i.ff, ' '), W(i.ss, '\n');
	write(1,OB,OP);
	return 0;
}
