#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while(((c=RC())<'0'||c>'9')&&c!='-'&&c!=-1);if(c=='-'){a=0;while((c=RC())>='0'&&c<='9')a*=10,a-=c^'0';}else{a=c^'0';while((c=RC())>='0'&&c<='9')a*=10,a+=c^'0';}return a;}

#include<cstdio>
#include<deque>
using namespace std;

const int MAXN = 5e5+1;
int n, k, h[MAXN], b[MAXN], maxid = 0, maxb = -8e7, sum = 0;
deque<int> view;
int main(){
	n = R(), k = R()-1;
	for(int i = 1; i <= n; ++i) h[i] = R();
	for(int i = 1; i <= n; ++i) b[i] = R();
	for(int i = 1; i <= n; ++i){
		if(!view.empty() and view.front() < i - k){
			sum -= b[view.front()];
			view.pop_front();
		}
		while(!view.empty() and h[view.back()] <= h[i]){
			sum -= b[view.back()];
			view.pop_back();
		}
		view.push_back(i);
		sum += b[i];
		if(sum > maxb){
			maxb = sum;
			maxid = i;
		}
	}
	printf("%d %d", maxid, maxb);
	return 0;
}