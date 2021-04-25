#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

inline int abs(int a){
	return a < 0 ? -a : a;
}

bool h[3001];
int main(){OW0
	int n, a, b;
	while(cin >> n){
		memset(h, 0, 3000);
		cin >> a;
		for(int i = 1; i < n; i++){
			cin >> b;
			h[abs(a-b)] = true;
			a = b;
		}
		if(all_of(h+1, h+n, [](bool a){return a;})) cout << "Jolly\n";
		else cout << "Not Jolly\n";
	}
	return 0;
}