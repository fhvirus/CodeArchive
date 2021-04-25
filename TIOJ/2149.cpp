#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int N = 1001, C = 1024;
int n, m, s, t;
ll dis[N][C];
template<typename T> using mheap = priority_queue<T, vector<T>, greater<T>>;
mheap<tuple<ll, int, int>> pq;
vector<tuple<int, int, int>> adj[N];

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> n >> m >> s >> t;
    for(int i = 0, u, v, x, y; i < m; ++i){
        cin >> u >> v >> x >> y;
        adj[u].push_back({v, x, y});
        adj[v].push_back({u, x, y});
    }
    memset(dis, -1, sizeof(dis));
    dis[s][0] = 0;
    pq.push({0, s, 0});
    while(!pq.empty()){
        auto [d, u, x] = pq.top(); pq.pop();
        if(dis[u][x] == -1 or dis[u][x] < d) continue;
        for(auto[v, y, c]: adj[u]){
            if(dis[v][x^y] == -1 or dis[v][x^y] > d + c){
                dis[v][x^y] = d + c;
                pq.push({d + c, v, x ^ y});
            }
        }
    }
    cout << dis[t][0];
	return 0;
}
