#pragma GCC optimize("Ofast")
#include<unistd.h>
char OB[65536]; int OP;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}
inline void W(int n){static char buf[12],p;if(n==0)OB[OP++]='0';p=0;while(n)buf[p++]='0'+(n%10),n/=10;for(--p;p>=0;--p)OB[OP++]=buf[p];OB[OP++]='\n';if(OP>65516)write(1,OB,OP),OP=0;}

#include<algorithm>
using namespace std;

#define ff first
#define ss second
#define pb push_back
#define For(i,n) for(int i=0;i<n;++i)

const int N = 1e5 + 225;
int n, a[N], b[N], tmp[N], app[N];
char cmd[N*2 + 6666];
int id[N*2 + 6666], cnt;

void dq(int l, int r){
    if(r - l == 1){
        cmd[cnt++] = 'T';
        cmd[cnt++] = 'U';
        cmd[cnt++] = 'P';
        id[cnt-1] = a[0];
        return;
    }
    int m = (l + r) / 2;
    dq(l, m);

    for(int i = 0; i < r - l; ++i){
        cmd[cnt++] = 'T';
        tmp[i] = a[i];
    }
    
    // go through b[m, r)
    fill(app, app + n + 1, N);
    for(int i = m; i < r; ++i){
        app[b[i]] = min(app[b[i]], i);
    }
    sort(tmp, tmp + r - l, [&](int i, int j){
        return app[i] < app[j];
    });
    int p = r - l - 1;
    tmp[r - l] = 0;
    for(int i = r - l - 1; i >= 0; --i){
        if(tmp[i] == tmp[i + 1]){
            cmd[cnt++] = 'P';
            id[cnt-1] = tmp[i];
            a[p--] = tmp[i];
        }
    }
    for(int i = r - l - 1; i >= 0; --i){
        if(tmp[i] != tmp[i + 1]){
            cmd[cnt++] = 'P';
            id[cnt-1] = tmp[i];
            a[p--] = tmp[i];
        }
    }
    dq(m, r);
}

int main(){
    n = R();
    For(i,n) a[i] = R();
    For(i,n) b[i] = R();

    fill(app, app + n + 1, N);
    For(i,n) app[b[i]] = min(app[b[i]], i);
    For(i,n){
        tmp[i] = a[i];
        cmd[cnt++] = 'T';
    }
    sort(tmp, tmp + n, [](int i, int j){
        return app[i] < app[j];
    });
    int p = n-1;
    for(int i = n-1; i >= 0; --i){
        if(tmp[i] == tmp[i + 1]){
            cmd[cnt++] = 'P';
            id[cnt-1] = tmp[i];
            a[p--] = tmp[i];
        }
    }
    for(int i = n-1; i >= 0; --i){
        if(tmp[i] != tmp[i + 1]){
            cmd[cnt++] = 'P';
            id[cnt-1] = tmp[i];
            a[p--] = tmp[i];
        }
    }

    dq(0, n);

    W((cnt - n) / 2);
    for(int i = 0; i < cnt; ++i){
        OB[OP++] = cmd[i];
        if(cmd[i] == 'P') OB[OP++] = ' ', W(id[i]);
        else OB[OP++] = '\n';
        if(OP>65516)write(1,OB,OP),OP=0;
    }

    write(1,OB,OP);
	return 0;
}
