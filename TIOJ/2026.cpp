#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2")
#pragma loot-opt(on)
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}


#include<queue>
#include<functional>
std::priority_queue<int> mx;
std::priority_queue<int, std::vector<int>, std::greater<int>> mn;

int q, cmd, x;
int main(){
    q = R();
    cmd = R(), x = R();
    mx.push(x);
    for(--q; q; --q){
        cmd = R();
        if(cmd == 1){
            x = R();
            (x < mx.top() ? mx.push(x) : mn.push(x));
            if(mx.size() > mn.size() + 1) mn.push(mx.top()), mx.pop();
            if(mx.size() < mn.size()) mx.push(mn.top()), mn.pop();
        } else W(mx.top());
    }
    write(1,OB,OP);
}