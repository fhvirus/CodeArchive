#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

const int N = 3e5 + 225;
int n, m;
bool a[N], b[N];

int main(){
    n = R(), m = R();
    for(int k; m; --m) k = R(), b[k] = !b[k];
    for(int i = 1; i <= n; ++i)
        if(b[i]){
            for(int j = i; j <= n; j += i)
                a[j] = !a[j];
        }
    int ans = 0;
    for(int i = 1; i <= n; ++i)
        ans += a[i];
    W(ans);
    for(int i = 1; i <= n; ++i)
        if(a[i]) W(i);
    write(1,OB,OP);
	return 0;
}
