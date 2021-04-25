#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

#define justinlaiorz ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

const int N = 1e5;
int t, n;
string s;

int main(){ justinlaiorz
	cin >> t;
	for(; t; --t){
		cin >> n >> s;
		if(s.size() % 2 == 1){
			bool hasodd = false;
			for(int i = 0; i < n; i += 2){
				if((s[i] - '0') % 2 == 1){
					hasodd = true;
					break;
				}
			}
			cout << (hasodd ? 1 : 2) << '\n';
		} else {
			bool has = false;
			for(int i = 1; i < n; i += 2){
				if((s[i] - '0') % 2 == 0){
					has = true;
					break;
				}
			}
			cout << (has ? 2 : 1) << '\n';
		}
	}
	return 0;
}