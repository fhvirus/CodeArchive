#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
inline char readchar(){
	const int S = 1<<18;
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
inline double RB(){
	double ans = 0, times = .1;
	int c = readchar();
	while(c != '.') c = readchar();
	c = readchar();
	while(c>='0' and c<='9') ans += times * (c-'0'), times*=.1, c=readchar();
	return ans;
}

#include<algorithm>
using namespace std;

int n;
double in, ans, a, b;

struct maxHeap{
public:
    double val[256];
    int end = 1;
    void push(double v){
        int p = end++;
        val[p] = v;
        while(p > 1){
            if(val[p] > val[p>>1]) swap(val[p], val[p>>1]);
            p >>= 1;
        }
    }
    double top(){
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
            if(val[p] > val[p<<1] and val[p] > val[p<<1|1]) return;
            if(val[p<<1] > val[p<<1|1]) swap(val[p], val[p<<1]), p = p<<1;
            else swap(val[p], val[p<<1|1]), p = p<<1|1;
        }
        if(p << 1 >= end) return;
        if((p << 1 | 1) == end and val[p] < val[p<<1]) swap(val[p], val[p<<1]);
        else{
            if(val[p<<1] > val[p<<1|1]) swap(val[p], val[p<<1]);
            else swap(val[p], val[p<<1|1]);
        }
    }
} pq;

int main(){
	for(n = R();n;--n){
		in = RB();
		pq.push(-in);
	}
	while(pq.size() > 1){
		a = pq.top(); pq.pop();
		b = pq.top(); pq.pop();
		ans += a + b;
		pq.push(a + b);
	}
	printf("%.2lf", -ans);
	return 0;
}