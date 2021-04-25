#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<unistd.h>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<15;
inline char readchar(){
    static char buf[S], *p = buf, *q = buf;
    return (p==q&&(q=(p=buf)+read(0, buf, S))==buf) ? -1 : *p++;
}
inline int R(){
    int ans = 0; char c = readchar();
    while(c<'0') c=readchar();
    while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
    return ans;
}

#include<cstdio>
#include<algorithm>
using namespace std;
const int N = 3000;

struct point{
    int x, y;
    point(){}
    point(int x, int y): x(x), y(y){}
    bool operator<(const point &rhs) const{
        return x != rhs.x ? x < rhs.x : y < rhs.y;
    }
    point operator-(const point &rhs){
        return {x - rhs.x, y - rhs.y};
    }
    int operator*(const point &rhs){
        return x * rhs.y - y * rhs.x;
    }
} P[N];
int n, ANS, A, B, jizz;
short id[N], l, u, c, L[N], U[N], C[N];

inline bool cross(int o, int a, int b){
    return (P[a] - P[o]) * (P[b] - P[o]) >= 0;
}
inline int dis(int a, int b){
    return (P[a].x-P[b].x)*(P[a].x-P[b].x) + (P[a].y-P[b].y)*(P[a].y-P[b].y);
}

int main(){
    while((n = R()) != 0){
        FOR(i,n) P[i] = {R(), R()}, id[i] = i;
        sort(id, id + n, [](int a, int b){return P[a] < P[b];});
        l = u = 0;
        FOR(i,n){
            while(l >= 2 and cross(L[l-2], L[l-1], id[i])) --l;
            while(u >= 2 and cross(U[u-2], id[i], U[u-1])) --u;
            L[l++] = id[i];
            U[u++] = id[i];
        }

        c = 0;
        for(int i = 0; i < u; ++i) C[c++] = U[i];
        for(int i = l - 2; i > 0; --i) C[c++] = L[i];
        for(int i = c; i < c<<1; ++i) C[i] = C[i - c];

        ANS = A = B = 0;
        for(short i = 0, j = 1, k; i < c; ++i){
            k = C[j];
            while(dis(C[i], C[j+1]) >= dis(C[i], C[j])){
                if(dis(C[i], C[j+1]) == dis(C[i], C[j])) k = min(k, C[j+1]);
                else k = C[j+1];
                ++j;
            }
            jizz = dis(C[i], k);
            if(jizz > ANS)
                ANS = jizz, A = C[i], B = k;
            else if(jizz == ANS){
                if(min(C[i], k) < A or (min(C[i], k) == A and max(C[i], k) < B))
                    A = C[i], B = k;
            }
            if(A > B) swap(A, B);
        }
        if(A >= 1000) putchar_unlocked(A / 1000 + '0');
        if(A >= 100) putchar_unlocked(A % 1000 / 100 + '0');
        if(A >= 10) putchar_unlocked(A % 100 / 10 + '0');
        putchar_unlocked(A % 10 + '0');
        putchar_unlocked(' ');
        if(B >= 1000) putchar_unlocked(B / 1000 + '0');
        if(B >= 100) putchar_unlocked(B % 1000 / 100 + '0');
        if(B >= 10) putchar_unlocked(B % 100 / 10 + '0');
        putchar_unlocked(B % 10 + '0');
        putchar_unlocked('\n');
    }
}