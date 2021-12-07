// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int,int> pii; typedef pair<ll,ll> pll;
#define ff first
#define ss second
#define pb emplace_back
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;} 
#ifdef OWO
#define debug(args...) SDF(#args, args)
#define OIU(args...) ostream& operator<<(ostream&O,args)
#define LKJ(S,B,E,F) template<class...T>OIU(S<T...>s){O<<B;int c=0;for(auto i:s)O<<(c++?", ":"")<<F;return O<<E;}
LKJ(vector,'[',']',i)LKJ(deque,'[',']',i)LKJ(set,'{','}',i)LKJ(multiset,'{','}',i)LKJ(unordered_set,'{','}',i)LKJ(map,'{','}',i.ff<<':'<<i.ss)LKJ(unordered_map,'{','}',i.ff<<':'<<i.ss)
template<class...T>void SDF(const char* s,T...a){int c=sizeof...(T);if(!c){cerr<<"\033[1;32mvoid\033[0m\n";return;}(cerr<<"\033[1;32m("<<s<<") = (",...,(cerr<<a<<(--c?", ":")\033[0m\n")));}
template<class T,size_t N>OIU(array<T,N>a){return O<<vector<T>(AI(a));}template<class...T>OIU(pair<T...>p){return O<<'('<<p.ff<<','<<p.ss<<')';}template<class...T>OIU(tuple<T...>t){return O<<'(',apply([&O](T...s){int c=0;(...,(O<<(c++?", ":"")<<s));},t),O<<')';}
#else
#pragma GCC optimize("Ofast")
#define debug(...) ((void)0)
#endif

const int kN = 20;
const int dx[4] = {  1, -1,  0,  0 };
const int dy[4] = {  0,  0,  1, -1 };
int N, Q, e[kN][kN];
int ans[kN][kN][kN][kN][2];

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N;
	for(int i = 0; i < N; ++i)
		for(int j = 0; j < N; ++j)
			cin >> e[i][j];

	for(int si = 0; si < N; ++si)
		for(int sj = 0; sj < N; ++sj){
			auto &dis = ans[si][sj];
			for(int i = 0; i < N; ++i)
				for(int j = 0; j < N; ++j)
					dis[i][j][0] = dis[i][j][1] = 1e9;
			dis[si][sj][0] = e[si][sj];
			dis[si][sj][1] = 0;

			queue<pii> q;
			vector<vector<bool>> vis(N, vector<bool>(N, false));
			vis[si][sj] = true;
			q.emplace(si, sj);
			while(!q.empty()){
				auto [i, j] = q.front(); q.pop();
				for(int x, y, d = 0; d < 4; ++d){
					x = i + dx[d]; y = j + dy[d];
					if(x < 0 or x >= N or y < 0 or y >= N) continue;
					bool d0 = chmin(dis[x][y][0], dis[i][j][0] + e[x][y]);
					bool d1 = chmin(dis[x][y][1], min(dis[i][j][1] + e[x][y], dis[i][j][0]));
					if(d0 or d1){
						vis[x][y] = true;
						q.emplace(x, y);
					}
				}
			}
		}

	cin >> Q;
	for(int x0, y0, x1, y1, i = 0; i < Q; ++i){
		cin >> x0 >> y0 >> x1 >> y1;
		--x0; --y0; --x1; --y1;
		cout << ans[x0][y0][x1][y1][1] << '\n';
	}
	return 0;
}
