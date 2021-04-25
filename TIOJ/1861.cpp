#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

const int N = 1e5;
#include<algorithm>
using namespace std;

struct minHeap{
public:
    int val[N+1], end = 1;
    void init(){
    	end = 1;
    }
    void push(int v){
        int p = end++;
        val[p] = v;
        while(p > 1){
            if(val[p] < val[p>>1]) swap(val[p], val[p>>1]);
            p >>= 1;
        }
    }
    int top(){
        return val[1];
    }
    int empty(){
        return end == 1;
    }
    int size(){
    	return end - 1;
    }
    void pop(){
        int p = 1;
        val[p] = val[--end];
        while(p < end>>1){
            if(val[p] < val[p<<1] and val[p] < val[p<<1|1]) return;
            if(val[p<<1] < val[p<<1|1]) swap(val[p], val[p<<1]), p = p<<1;
            else swap(val[p], val[p<<1|1]), p = p<<1|1;
        }
        if(p << 1 >= end) return;
        if((p << 1 | 1) == end and val[p] > val[p<<1]) swap(val[p], val[p<<1]);
        else{
            if(val[p<<1] < val[p<<1|1]) swap(val[p], val[p<<1]);
            else swap(val[p], val[p<<1|1]);
        }
    }
} pq;
int n, x, y;
long long ans;

int main(){
	while(true){
		if((n=R()) == 0) break;
		pq.init();
		FOR(i,n) x = R(), pq.push(x);
		ans = 0;
		while(pq.size() > 1){
			x = pq.top(); pq.pop();
			y = pq.top(); pq.pop();
			ans += x + y;
			pq.push(x + y);
		}
		printf("%lld\n", ans);
	}
	return 0;
}