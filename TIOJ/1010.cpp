#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	string a, b;
	cin >> a >> b;
	int ans = a.size() < b.size() ? a.size() : b.size();
	while(ans and a.substr(0, ans) != b.substr(b.size() - ans, ans))
		ans--;
	cout << ans;
	return 0;
}