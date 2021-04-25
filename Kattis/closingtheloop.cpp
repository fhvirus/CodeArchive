#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int T, n;
	vector<int> r, b;
	string in;
	cin>>T;
	for(int k = 1; k <= T; k++){
		cout<<"Case #"<<k<<": ";
		cin>>n;
		r.clear(); b.clear();
		for(int i = 0; i < n; i++){
			cin>>in;
			if(in.back()=='B'){
				in.pop_back();
				b.push_back(stoi(in));
			}else{
				in.pop_back();
				r.push_back(stoi(in));
			}
		}
		sort(r.begin(), r.end(), greater<int>());
		sort(b.begin(), b.end(), greater<int>());
		int num = min(r.size(), b.size()), ans = 0;
		for(int i = 0; i < num; i++){
			ans += r[i] + b[i];
		}
		ans -= num * 2;
		cout<<ans<<'\n';
	}
	return 0;
}