#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int twopowers[31];
void init(){
	twopowers[0] = 3;
	for(int i = 1; i < 31; i++)
		twopowers[i] = twopowers[i-1]<<1 | 1;
}


int main(){OW0
	int T, n;
	init();
	cin >> T;
	while(T--){
		cin >> n;
		for(int i = 0; i < 31; i++){
			if(n % twopowers[i] == 0){
				cout << n / twopowers[i] << '\n';
				break;
			}
		}
	}
	return 0;
}