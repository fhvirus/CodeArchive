#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	string e, k;
	cin>>e>>k;
	int s = k.size();
	for(int i = 0; i < e.size(); i++){
		k.push_back((e[i]-k[i]+26)%26 + 'A');
	}
	k.erase(0, s);
	cout<<k;
	return 0;
}