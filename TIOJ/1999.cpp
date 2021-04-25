#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#include<algorithm>
using namespace std;
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p == q and (q = (p = buf) + fread(buf, 1, S, stdin)) == buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while((c > '9' or c < '0') and c != EOF) c = readchar();
	while(c <= '9' and c >= '0') ans = (ans<<3) + (ans<<1) + (c^'0'), c = readchar();
	return ans;
}

const int N = 1e6;
int n, m, a, b, ans;

struct minHeap{
    int val[N+1], end = 1;
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
    int max(){
    	int ans = 0;
    	for(int p = 1; p < end; ++p) ans = ans > val[p] ? ans : val[p];
    	return ans;
    }
} pq;

int main(){
	n = R(); m = R();
	if(n <= m){
		ans = 0;
		while(n--) ans = max(ans, R());
		printf("%d", ans);
		return 0;
	}

	for(int i = 0; i < m; ++i) pq.push(R());
	for(int i = m; i < n; ++i){
		a = pq.top(); pq.pop();
		pq.push(a + R());
	}

	printf("%d", pq.max());
}