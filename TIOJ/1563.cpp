#include<iostream>
#include<utility>
#include<algorithm>
using namespace std;

#define owo ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int m, n;
pair<string, int> s[10];

int main(){owo
	while(cin >> m >> n){
		for(int i = 0; i < n; i++){
			cin >> s[i].first;
			while(s[i].first.size() < m) s[i].first += ' ';
		}
		for(int i = 0; i < n; i++) s[i].second = 100 - i * 10;
		sort(s, s+n);
		for(int i = 0; i < n; i++) cout << s[i].first << "  $" << s[i].second << '\n';
		if(n == 0) cout << "No one\n";
	}
	return 0;
}