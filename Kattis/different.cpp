#include<iostream>
#include<sstream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
typedef unsigned long long int ull;
int main(){OW0
	ull a, b;
	while(cin>>a>>b){
		cout<<(a>b? a-b : b-a)<<'\n';
	}
	return 0;
}