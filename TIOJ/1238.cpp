#pragma GCC optimize("Ofast")
#include<cstdio>

const int N = 505, Q = 50000;
int n;
char g[N][N];
int h, t;
int x[Q], y[Q];
const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
bool ok(int i, int j, int d){
    return i + dx[d] >= 0 and i + dx[d] < n and j + dy[d] >= 0 and j + dy[d] < n and g[i + dx[d]][j + dy[d]] != '#';
}

void bfs(int i, int j){
    g[i][j] = '#';
    x[t] = i, y[t] = j, ++t;
    while(h != t){
        int i = x[h], j = y[h]; ++h, h -= (h >= Q ? Q : 0);
        for(int d = 0; d < 4; ++d)
            if(ok(i, j, d)){
                x[t] = i + dx[d], y[t] = j + dy[d], ++t, t -= (t >= Q ? Q : 0);
                g[x[t-1]][y[t-1]] = '#';
            }
    }
}

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        scanf("%s", g[i]);

    bool yas = false;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j){
            if(g[i][j] == 'x'){
                if(yas){
                    puts("Weak!");
                    return 0;
                }
                bfs(i, j);
                yas = true;
            }
        }
    puts("Strong!");

    return 0;
}
