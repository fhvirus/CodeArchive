#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int T, n;
	vector<int>deck;
	cin>>T;
	while(T--){
		cin>>n;
		deck.clear();
		for(int i = n; i > 0; i--){
			deck.push_back(i);
			rotate(deck.begin(), deck.begin() + i % deck.size(), deck.end());
		}
		reverse(deck.begin(), deck.end());
		for(auto i: deck)cout<<i<<' ';
		cout<<'\n';
	}
	return 0;
}