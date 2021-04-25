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
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

#include<algorithm>
using namespace std;
const int N = 5e5;

struct minMaxHeap{
public:
    int val[N+1];
    int end = 1;
    // void push(int v){
    //     int p = end++;
    //     val[p] = v;
    //     while(p > 1){
    //         if(val[p] > val[p>>1]) swap(val[p], val[p>>1]);
    //         p >>= 1;
    //     }
    // }
    // int top(){
    //     return val[1];
    // }
    int empty(){
        return end == 1;
    }
    int size(){
    	return end - 1;
    }
    // void pop(){
    //     int p = 1;
    //     val[p] = val[--end];
    //     while(p < end>>1){
    //         if(val[p] > val[p<<1] and val[p] > val[p<<1|1]) return;
    //         if(val[p<<1] > val[p<<1|1]) swap(val[p], val[p<<1]), p = p<<1;
    //         else swap(val[p], val[p<<1|1]), p = p<<1|1;
    //     }
    //     if(p << 1 >= end) return;
    //     if((p << 1 | 1) == end and val[p] < val[p<<1]) swap(val[p], val[p<<1]);
    //     else{
    //         if(val[p<<1] > val[p<<1|1]) swap(val[p], val[p<<1]);
    //         else swap(val[p], val[p<<1|1]);
    //     }
    // }
    void verifyMin(int p){
    	while(p > 3){
    		if(val[p] < val[p>>2]) swap(val[p], val[p>>2]);
    		p >>= 1;
    	}
    }
    void verifyMax(int p){
		while(p > 3){
    		if(val[p] > val[p>>2]) swap(val[p], val[p>>2]);
    		p >>= 1;
    	}
    }
    bool isMinLevel(int p){
    	return ((31 - __builtin_clz(p))&1) == 0;
    }
    void push(int v){
    	int p = end++;
        val[p] = v;
        if(isMinLevel(p)){
        	if(p != 1 and val[p] > val[p>>1]) swap(val[p], val[p>>1]);
        	verifyMin(p);
        } else {
        	if(p != 1 and val[p] < val[p>>1]) swap(val[p], val[p>>1]);
        	verifyMax(p);
        }
    }
    int min(){
    	return val[1];
    }
    int max(){
    	if(end == 2) return val[1];
    	if(end == 3) return val[2];
    	return val[2] > val[3] ? val[2] : val[3];
    }
    // 以下待修
    int child_min(int p){
    	if(p << 2 | 3 >= end){

    	}
    	return val[p<<2]
    }
    void pop_min(){
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
    void pop_max(){

    }
} mmheap;

int freq[10001];

int main(){
	int n;
	while((n = R()) != 0){
		if(n > 0) mmheap.push(n);
		else if(!mmheap.empty()){
			if(n == -1) printf("%d ", mmheap.min()), mmheap.pop_min();
			else printf("%d ", mmheap.max()), mmheap.pop_max();
		}
	}
	return 0;
}