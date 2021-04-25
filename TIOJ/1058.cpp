#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<iostream>
#include<sstream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	string a, b;
	stringstream ss;
	cin >> a >> b;
	int aa, bb;
	ss << a;
	ss >> aa;
	ss.clear(); ss.str("");
	ss << b;
	ss >> bb;
	if(aa > bb){
		cout << a;
		return 0;
	}
	if(aa < bb){
		cout << b;
		return 0;
	}
	for(int i = 0;;++i){
		if(a[i] > b[i]){
			cout << a;
			return 0;
		}
		if(a[i] < b[i]){
			cout << b;
			return 0;
		}
	}
	return 0;
}