#include<iostream>
using namespace std;

int main(){
	int T, a1, a2, b1, b2;
	cin >> T;
	while(T--){
		cin >> a1 >> b1 >> a2 >> b2;
		if( (a1 == a2 and b1+b2 == a1) or
			(a1 == b2 and b1+a2 == a1) or
			(b1 == a2 and a1+b2 == b1) or
			(b1 == b2 and a1+a2 == b1)){
			cout << "Yes\n";
		} else {
			cout << "No\n";
		}
	}
	return 0;
}