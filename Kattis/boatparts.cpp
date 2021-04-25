#include<iostream>
#include<set>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int p, n;
	string in;
	set<string> parts;
	cin>>p>>n;
	for(int i = 1; i <= n; i++){
		cin>>in;
		parts.insert(in);
		if(parts.size() == p){
			cout<<i;
			return 0;
		}
	}
	cout<<"paradox avoided";
	return 0;
}