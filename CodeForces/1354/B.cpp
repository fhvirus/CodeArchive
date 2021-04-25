#include<iostream>
#include<vector>
#include<utility>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){eek
	int T, ans;
	string in;
	cin >> T;
	for(;T;--T){
		cin >> in;
		ans = 8e7;
		vector<pair<char, int>> s;
		for(char i: in){
			if(s.empty() or s.back().first != i)
				s.push_back({i, 1});
			else
				s.back().second++;
		}
		int m = s.size()-1;
		for(int i = 1; i < m; i++)
			if(s[i-1].first != s[i+1].first)
				ans = min(ans, s[i].second + 2);
		if(ans > in.size()) ans = 0;
		cout << ans << '\n';
	}
	return 0;
}