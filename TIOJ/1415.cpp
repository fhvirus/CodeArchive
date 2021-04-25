#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0'&&c!=-1);if(c==-1)return 0;a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<queue>
#include<functional>
typedef std::priority_queue<int, std::vector<int>, std::less<int>> mxheap;
typedef std::priority_queue<int, std::vector<int>, std::greater<int>> mnheap;

const int N = 1e6 + 225;
int n, k;
short cnt[N];
mxheap mx;
mnheap mn;

int main(){
	while((n = R()) != 0){
		int ans = 0;
		for(int i = 0; i < N; ++i) cnt[i] = 0;
		mx = mxheap();
		mn = mnheap();
		for(int i = 0; i < n; ++i){
			k = R();
			for(int a; k; --k){
				a = R();
				mx.push(a);
				mn.push(a);
				cnt[a]++;
			}
			while(cnt[mx.top()] == 0) mx.pop();
			while(cnt[mn.top()] == 0) mn.pop();
			ans += mx.top() - mn.top();
			--cnt[mx.top()], --cnt[mn.top()];
			mx.pop(), mn.pop();
		}
		W(ans);
	}
	write(1,OB,OP);
}