#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

inline int period(string s){
	for(int i = 1; i < s.size(); i++){
		if(s[i]!=s[0]) return 2;
	}
	return 1;
}

int main(){OW0
	int T;
	string in;
	cin >> T;
	while(T--){
		cin >> in;
		if(period(in) == 1)
			cout << in << '\n';
		else{
			for(int i = 0; i < in.size(); i++)
				cout << "10";
			cout << '\n';
		}
	}
	return 0;
}