#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define MAXN 200000

signed main(){OW0
	long long n;
	cin >> n;
	string s = "codeforces";
	long long t[10] = {1,1,1,1,1,1,1,1,1,1}, sum = 1, ptr = 0;
	while(sum < n){
		t[ptr]++;
		ptr = (ptr == 9 ? 0 : ptr+1);
		sum = 1;
		for(int i = 0; i < 10; i++){
			sum *= t[i];
		}
	}
	for(int i = 0; i < 10; i++)
		for(int j = 0; j < t[i]; j++)
			cout << s[i];
	return 0;
}