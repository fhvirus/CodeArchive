#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
 
int main() {
	cin.tie(0) -> sync_with_stdio(0);
	
	int n; cin >> n;
	vector<int> x(n);
	for (int &i: x) cin >> i;
 
	sort(begin(x), end(x));
 
	cout << (unique(begin(x), end(x)) - begin(x)) << '\n';
 
	return 0;
}
