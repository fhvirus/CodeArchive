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

const int kN = 100001;
const int kK = 256;
const int kL = 31;
int N, Q, A[kN], L[kN], R[kN];
int ans[kN];

namespace Trie {
	int ch[(kN + kK) * kL][2];
	int tot, tmp;
	void init() {
		tot = tmp = 0;
		ch[0][0] = ch[0][1] = 0;
	}
	int newNode(bool isTemp) {
		++tmp;
		if (!isTemp) ++tot;
		ch[tmp][0] = 0;
		ch[tmp][1] = 0;
		return tmp;
	}
	vector<pii> tmpOps;
	void undo() {
		tmp = tot;
		for (auto &[i, j]: tmpOps)
			ch[i][j] = 0;
		tmpOps.clear();
	}

	void insert(int x, bool isTemp) {
		int u = 0;
		for (int l = kL - 1; l >= 0; --l) {
			int i = (x >> l & 1);
			int &v = ch[u][i];
			if (v == 0) {
				if (isTemp) tmpOps.pb(u, i);
				v = newNode(isTemp);
			}
			u = v;
		}
	}
	int query(int x) {
		int u = 0, r = 0;
		for (int l = kL - 1; l >= 0; --l) {
			int i = (x >> l & 1) ^ 1;
			if (ch[u][i]) r ^= (1<<l);
			else i ^= 1;
			u = ch[u][i];
		}
		return r;
	}
};

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

	cin >> N >> Q;
	for (int i = 1; i <= N; ++i) {
		cin >> A[i];
		A[i] ^= A[i-1];
	}
	for (int i = 1; i <= Q; ++i) {
		cin >> L[i] >> R[i];
		--L[i];
	}

	vector<int> ids;
	for (int i = 1; i <= Q; ++i) {
		if (L[i] / kK != R[i] / kK) {
			ids.pb(i);
			continue;
		}
		Trie::init();
		Trie::insert(A[L[i]], 0);
		for (int p = L[i]+1; p <= R[i]; ++p) {
			ans[i] = max(ans[i], Trie::query(A[p]));
			Trie::insert(A[p], 0);
		}
	}
	sort(AI(ids), [&](int i, int j) {
		if (L[i] / kK != L[j] / kK)
			return L[i] / kK < L[j] / kK;
		return R[i] < R[j];
	});

	int lst = -1, ml = 0, mr = 0, mv = 0;
	for (int &id: ids) {
		int ql = L[id], qr = R[id];
		if (L[id] / kK != lst) {
			lst = L[id] / kK;
			Trie::init();
			ml = (lst+1) * kK;
			mr = ml;
			mv = 0;
			Trie::insert(A[ml], 0);
		}
		while (mr < qr) {
			++mr;
			mv = max(mv, Trie::query(A[mr]));
			Trie::insert(A[mr], 0);
		}
		int cur = mv;
		while (ml > ql) {
			--ml;
			cur = max(cur, Trie::query(A[ml]));
			Trie::insert(A[ml], 1);
		}
		ans[id] = cur;
		Trie::undo();
		ml = (lst+1) * kK;
	}

	for (int i = 1; i <= Q; ++i)
		cout << ans[i] << '\n';
	return 0;
}
