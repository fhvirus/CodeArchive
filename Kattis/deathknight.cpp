#include<iostream>
#include<algorithm>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int n, ans = 0;
	string s, ss = "CD";
	cin>>n;
	while(n--){
		cin>>s;
		if(search(s.begin(), s.end(), ss.begin(), ss.end()) == s.end())ans++;
	}
	cout<<ans;
	return 0;
}