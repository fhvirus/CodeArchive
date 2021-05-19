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

const int inf = 1e9 + 7;

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

	int n, k; cin >> n >> k;
	vector<int> a; a.pb(inf);

	int lst, cur, sgn = -1; cin >> lst;
	for(int i = 1; i < n; ++i){
		cin >> cur;
		int v = cur - lst;
		if(v * sgn >= 0) a.back() += v * sgn;
		else sgn = -sgn, a.pb(v * sgn);
		lst = cur;
	}
	if(sgn > 0) a.pb(inf);
	else a.back() += inf;
	n = a.size();

	int ovr = n / 2 - k;
	int sum = 0;
	for(int i = 1; i < n; i += 2) sum += a[i];

	if(ovr <= 0){
		cout << sum;
		return 0;
	}

	vector<int> b, e;
	while(ovr > 0){
		b.assign(1, inf);
		e = a;
		nth_element(begin(e), begin(e) + ovr - 1, end(e));

		int bnd = e[ovr - 1], cnt = 0, cst = 0;
		for(int i = 1; i < n and cnt <= ovr; ++i){
			b.pb(a[i]);
			while(cnt <= ovr and b.size() >= 3 and end(b)[-2] <= bnd and end(b)[-1] >= end(b)[-2]){
				cst += end(b)[-2];
				++cnt;
				end(b)[-3] += end(b)[-1] - end(b)[-2];
				b.pop_back(); b.pop_back();
			}
		}

		if(cnt == ovr){
			cout << sum - cst;
			return 0;
		}

		if(cnt < ovr){
			ovr -= cnt;
			sum -= cst;
			swap(a, b);
			n = a.size();
			continue;
		}
		
		// else cnt > ovr
		--bnd; cnt = cst = 0;
		b.clear();
		for(int i = 1; i < n and cnt <= ovr; ++i){
			b.pb(a[i]);
			while(cnt <= ovr and b.size() >= 3 and end(b)[-2] <= bnd and end(b)[-1] >= end(b)[-2]){
				cst += end(b)[-2];
				++cnt;
				end(b)[-3] += end(b)[-1] - end(b)[-2];
				b.pop_back(); b.pop_back();
			}
		}
		ovr -= cnt;
		sum -= cst;
		cout << sum - ovr * (bnd + 1);
		break;
	}
	return 0;
}
