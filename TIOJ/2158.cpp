#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<map>
using namespace std;

#define ll long long
const int N = 2000+1;

int n, m;

struct ramen{
	int x, y, d;
} r[N];
struct point{
	int x, y;
} p[N];
struct jizz{
	int dist, d, id;
};
inline int dist(point p, ramen r){
	return max(abs(p.x - r.x), abs(p.y - r.y));
}

map<int, int> have[N];

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> m;
	for(int i = 0; i < n; ++i){
		cin >> r[i].x >> r[i].y >> r[i].d;
	}
	for(int i = 0; i < m; ++i){
		cin >> p[i].x >> p[i].y;
	}
	for(int i = 0; i < m; ++i){
		vector<jizz> ramens;
		for(int j = 0; j < n; ++j)
			ramens.push_back({dist(p[i], r[j]), r[j].d, j});
		sort(ramens.begin(), ramens.end(), [](jizz a, jizz b){
			return a.dist != b.dist ? a.dist > b.dist : a.d < b.d;
		});
		vector<jizz> dq;
		for(auto j: ramens){
			while(!dq.empty() and dq.back().d <= j.d) dq.pop_back();
			dq.push_back(j);
		}
//		cout << "Jizz " << i << ": \n";
//		for(auto j: dq)
//			cout << j.dist << ' ' << j.d << ' ' << j.id << '\n';
//			cout << endl;

		for(int i = 0; i < dq.size(); ++i){
			have[dq[i].id][dq[i].dist]++;
			if(i != 0) 
				have[dq[i].id][dq[i-1].dist]--;
		}
	}

//	for(int i = 0; i < n; ++i){
//		cout << i << ": \n";
//		for(auto j: have[i]){
//			cout << j.first << ' ' << j.second << '\n';
//		}
//		cout << endl;
//	}

	vector<int> des;
	for(int i = 0; i < n; ++i)
		for(auto j: have[i])
			des.push_back(j.first);

	sort(des.begin(), des.end());
	des.resize(unique(des.begin(), des.end()) - des.begin());
	vector<int> cnt(des.size() + 10, 0);
	for(int i = 0; i < n; ++i){
		int cur = 0, last = 0;
		for(auto j: have[i]){
			 cur += j.second;
			 if(cur > 0 and last <= 0)
			 	cnt[lower_bound(des.begin(), des.end(), j.first) - des.begin()]++;
			 else if(cur <= 0 and last > 0)
			 	cnt[lower_bound(des.begin(), des.end(), j.first) - des.begin()]--;
			 last = cur;
		}
	}
	int ans = cnt[0];
	for(int i = 1; i < cnt.size(); ++i){
		cnt[i] += cnt[i-1];
		ans = max(ans, cnt[i]);
	}
	cout << ans;
}