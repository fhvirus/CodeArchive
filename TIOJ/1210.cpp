#pragma GCC optimize("Ofast")
#include<unistd.h>
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline int R(){static char c;int a;while((c=RC())<'0');a=c^'0';while((c=RC())>='0')a*=10,a+=c^'0';return a;}

#include<cstdio>
const int N = 10001;
int n, d[N], c[N];

int main(){
    while(n = R(), n != 0){
        for(int i = 1; i <= n; ++i) ++c[R()];
        int p = N - 1;
        for(int i = 1; i <= n; ++i){
            while(c[p] == 0) --p;
            d[i] = p, --c[p];
        }

        bool eek = true;
        int sum = 0;
        for(int i = 1; i <= n; ++i) sum += d[i];
        if(!eek or sum % 2 == 1 or d[0] >= n){ puts("No"); continue;}

        int pre = 0, suf = 0, sp = n;
        for(int i = 1; i <= n; ++i){
            pre += d[i];
            while(sp > i and d[sp] <= i) suf += d[sp], --sp;
            if(i > sp) suf -= d[i], ++sp;
            if(pre > i * (i - 1) + suf + (sp - i) * i){ eek = false; break;}
        }
        puts(eek ? "Yes" : "No");
    }
	return 0;
}
