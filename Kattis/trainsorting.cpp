#include<iostream>
#include<vector>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

inline int max(int a, int b){
	return a > b ? a : b;
}

int lis(vector<int> a){
	if(a.empty()) return 0;

	vector<int> l;
	l.push_back(a[0]);
	for(int i = 1; i < a.size(); ++i){
		int n = a[i];
		if(n > l.back())
			l.push_back(n);
		else
			*lower_bound(l.begin(), l.end(), n) = n;
	}
	return l.size();
}

int main(){OW0
	int a[2000], n;
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> a[i];

	int ans = 0;
	for(int i = 0; i < n; i++){
		vector<int> in, de;
		for(int j = i + 1; j < n; j++){
			if(a[j] > a[i]) in.push_back(a[j]);
			if(a[j] < a[i]) de.push_back(-a[j]);
		}
		ans = max(ans, 1 + lis(in) + lis(de));
	}
	cout << ans;
	return 0;
}