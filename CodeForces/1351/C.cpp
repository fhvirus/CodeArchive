#include<iostream>
#include<set>
#include<iostream>
using namespace std;

#define eek ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){eek
	int T;
	cin >> T;
	cin.ignore();
	string in;
	while(T--){
		getline(cin, in);
		set<pair<double, double>> path;
		double x = 0, y = 0;
		int ans = 0;
		for(auto i: in){
			if(i == 'N'){
				if(path.count({x, y+0.5})) ans += 1;
				else ans += 5;
				path.insert({x, y+0.5});
				y++;
			} else if(i == 'S'){
				if(path.count({x, y-0.5})) ans += 1;
				else ans += 5;
				path.insert({x, y-0.5});
				y--;
			} else if(i == 'E'){
				if(path.count({x+0.5, y})) ans += 1;
				else ans += 5;
				path.insert({x+0.5, y});
				x++;
			} else if(i == 'W'){
				if(path.count({x-0.5, y})) ans += 1;
				else ans += 5;
				path.insert({x-0.5, y});
				x--;
			}
			path.insert({x, y});
		}
		cout << ans << '\n';
	}
	return 0;
}