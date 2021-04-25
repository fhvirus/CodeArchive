#include<iostream>
#include<set>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int T, n, a;
	set<int> s;
	cin >> T;
	for(;T;T--){
		cin >> n;
		s.clear();
		for(int i = 0; i < n; i++){
			cin >> a;
			s.insert(a);
		}
		bool can = false;
		int ans = 1;
		for(; ans < 1024; ans++){
			bool h = true;
			for(auto i: s){
				if(s.find(i ^ ans) == s.end()){
					h = false;
					break;
				}
			}
			if(h){
				can = true;
				break;
			}
		}
		if(can) cout << ans << '\n';
		else cout << "-1\n";
	}
	return 0;
}