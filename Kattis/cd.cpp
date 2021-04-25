#include<iostream>
#include<set>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int n, m, tmp, ans;
	set<int> jack;
	while(cin>>n>>m && (n || m)){
		jack.clear();
		ans = 0;
		for(int i = 0; i < n; i++){
			cin>>tmp;
			jack.insert(tmp);
		}
		for(int i = 0; i < n; i++){
			cin>>tmp;
			if(jack.count(tmp))ans++;
		}
		cout<<ans<<'\n';
	}
	return 0;
}