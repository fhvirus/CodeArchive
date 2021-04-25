#include<iostream>
using namespace std;

int main(){
	int n;
	string in;
	cin >> n >> in;
	int p = 0, r;
	for(r = p; r < n-1; r++){
		if(in[r] == 'R') break;
	}
	r++;
	cout << r << '\n';
	for(p = 0; p < n-1; p++){
		if(in[p] == 'L'){
			r--;
			cout << r+1 <<'\n';
		} else {
			if(p < n-2 && in[p+1] == 'R'){
				r++;
				cout << r+1 <<'\n';
			} else {
				for(; r < n-1; r++){
					if(in[r] == 'R') break;
				}
				cout << r+1 << '\n';
			}
		}
	}

	return 0;
}