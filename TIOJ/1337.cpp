#include<iostream>
#include<algorithm>
#include<utility>
#include<vector>
#include<queue>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define PB push_back
#define F first
#define S second
typedef pair<int, int> Pair;

#define MAXN 200005

vector<Pair> m;
vector<int> d;
int n, k;

int covered[MAXN];
bool check(int P){
	priority_queue<int> pq;
	fill(covered, covered + MAXN, 0);
	int cntK = k, cntP = 0, index = 0;
	for(int i = 0; i < d.size(); i++){
		while(index < n and m[index].F == i){
			cntP++;
			covered[m[index].S]++;
			pq.push(m[index].S);
			index++;
		}
		if(covered[i] != 0){
			cntP -= covered[i];
		}
		int tmp = cntP - P;
		if(tmp > 0){
			cntK -= tmp;
			cntP -= tmp;
			while(tmp--){
				covered[pq.top()]--;
				pq.pop();
			}
			if(cntK < 0)return false;
		}
	}
	return true;
}

int main(){OW0
	cin>>n>>k;
	int a, b;
	for(int i = 0; i < n; i++){
		cin>>a>>b;
		m.PB({a,b});
		d.PB(a);
		d.PB(b);
	}
	sort(m.begin(), m.end());
	sort(d.begin(), d.end());
	d.resize(unique(d.begin(), d.end()) - d.begin());
	for(int i = 0; i < m.size(); i++){
		m[i].F = lower_bound(d.begin(), d.end(), m[i].F) - d.begin();
		m[i].S = lower_bound(d.begin(), d.end(), m[i].S) - d.begin();
	}

	int L = 0, R = n + 1, M;
	while(R - L > 0){
		M = (L + R) / 2;
		if(check(M))R = M;
		else L = M + 1;
	}
	cout<<L;
	return 0;
}