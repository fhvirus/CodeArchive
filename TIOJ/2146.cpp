#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(long long n){char OB[20],OP=0,buf[20],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];write(1,OB,OP);}


#define ll long long
#define pii pair<int, int>
#define ff first
#define ss second
#define For(i,n) for(int i=0;i<n;++i)

const int N = 5e5 + 225;
int n, m, a[N], tmp[N];
bool app[N];

ll dq(int l, int r){
    if(r - l == 1) return 0;
    int m = (l + r) / 2;
    ll ans = dq(l, m) + dq(m, r);
    int lptr = l, rptr = m;
    for(int i = l; i < r; ++i){
        if(lptr < m and (rptr == r or a[lptr] < a[rptr])){
            tmp[i] = a[lptr++];
            ans += rptr - m;
        } else {
            tmp[i] = a[rptr++];
        }
    }
    for(int i = l; i < r; ++i) a[i] = tmp[i];
    return ans;
}

int main(){
	n = R(), m = R();
    for(int i = 0, u, v; i < m; ++i){
        u = R(), v = R();
        a[v-1] = u;
        app[u] = true;
    }
    int p = 1;
    for(int i = 0; i < n; ++i){
        if(a[i] == 0){
            while(app[p]) ++p;
            a[i] = p++;
        }
    }
    W(dq(0, n));
	return 0;
}
