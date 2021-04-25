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

#include<algorithm>
using namespace std;
const int N = 1e5;
struct food{
    int c, p;
} f[N];
int n, t;
struct maxHeap{
public:
    int val[N], end = 1;
    void push(int v){
        int p = end++;
        val[p] = v;
        while(p > 1){
            if(val[p] > val[p>>1]) swap(val[p], val[p>>1]);
            p >>= 1;
        }
    }
    int top(){
        return val[1];
    }
    int empty(){
        return end == 1;
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
    n = R();
    FOR(i,n) f[i].c = R(), f[i].p = R();
    std::sort(f, f+n, [](food a, food b){
        return a.p > b.p;
    });
    t = R();
    int idx = 0;
    long long ans = 0;
    for(; t; --t){
        while(idx < n and f[idx].p >= t) pq.push(f[idx++].c);
        if(pq.empty()) --ans;
        else ans += pq.top(), pq.pop();
    }
    printf("%lld\n", ans);
}