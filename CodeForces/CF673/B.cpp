#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int t, n, k, a[100000], eql, eqr;

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> t;
	for(; t; --t){
		cin >> n >> k;
		for(int i = 0; i < n; ++i){
			cin >> a[i];
		}
		eql = eqr = 0;
		for(int i = 0; i < n; ++i){
			if(k % 2 == 0 and a[i] == k / 2){
				if(eql > eqr){
					cout << "1 ";
					++eqr;
				} else {
					cout << "0 ";
					++eql;
				}
			} else if(a[i] <= k / 2){
				cout << "0 ";
			} else {
				cout << "1 ";
			}
		}
		cout << '\n';
	}
}