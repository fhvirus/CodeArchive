#pragma GCC optimize("Ofast")
#pragma loop_opt(on)

#include<iostream>
using namespace std;

char eek[1000001];

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n;
	string a, b;
	cin >> n;
	getline(cin, a);
	for(; n; --n){
		getline(cin, a); getline(cin, b);
		puts((a.size() == b.size() ? (a > b ? "0" : "1") : (a.size() > b.size() ? "0" : "1")));
	}
}