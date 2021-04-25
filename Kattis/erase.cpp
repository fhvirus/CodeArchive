#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int N;
	string a, b;
	bool ans = true;
	cin >> N;
	cin.ignore();
	getline(cin, a);
	getline(cin, b);
	if(N % 2){
		for(int i = 0; i < a.size(); i++){
			if(a[i] == b[i]){
				ans = false;
				break;
			}
		}
	} else {
		for(int i = 0; i < a.size(); i++){
			if(a[i] != b[i]){
				ans = false;
				break;
			}
		}
	}
	cout << "Deletion " << (ans ? "succeeded" : "failed");
	return 0;
}