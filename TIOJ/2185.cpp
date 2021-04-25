#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]=' ';if(OP>65516)write(1,OB,OP),OP=0;}

#include<algorithm>
using namespace std;
const int M = 712271227, G = 13, N = 1<<17, K = N * 38;
int gpow[N];

int n, m, a[N], id[N];
int root[N];

int va[K], le[K], ri[K], otp = 1;
void init(int &nd, int l, int r){
    if(l + 1 == r){
        va[otp] = a[l];
        nd = otp++;
        return;
    }
    nd = otp++;
    int m = (l + r) / 2;
    init(le[nd], l, m);
    init(ri[nd], m, r);
    va[nd] = (va[le[nd]] * gpow[r - m] + va[ri[nd]]) % M;
}
int modify(int &nd, int p, int v, int l, int r){
    if(p < l or r <= p) return nd;
    if(l + 1 == r){ va[otp] = v; return otp++;}

    int m = (l + r) / 2;
    int cur = otp++;
    le[cur] = modify(le[nd], p, v, l, m);
    ri[cur] = modify(ri[nd], p, v, m, r);
    va[cur] = (va[le[cur]] * gpow[r - m] + va[ri[cur]]) % M;
    return cur;
}

inline bool cmp(int i, int j){
    if(va[root[i]] == va[root[j]]) return i < j;
    i = root[i], j = root[j];
    while(le[i] != 0){
        (va[le[i]] != va[le[j]]) ? 
            (i = le[i], j = le[j]):
            (i = ri[i], j = ri[j]);
    }
    return va[i] < va[j];
}

int main(){
    gpow[0] = 1;
    for(int i = 1; i < N; ++i) gpow[i] = gpow[i-1] * G % M;

    n = R(), m = R();
    for(int i = 0; i < n; ++i) a[i] = R();
    for(int i = 0; i < m; ++i) id[i] = i;

    init(root[0], 0, n);
    for(int i = 1, x, y; i < m; ++i){
        x = R() - 1, y = R() - 1;
        root[i] = modify(root[i-1], x, a[y], 0, n);
        root[i] = modify(root[i], y, a[x], 0, n);
        swap(a[x], a[y]);
    }

    sort(id, id + m, cmp);

    for(int i = 0; i < m; ++i) W(id[i]);
    write(1,OB,OP);
    return 0;
}