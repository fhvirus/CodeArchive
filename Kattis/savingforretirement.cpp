#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int b, br, bs, a, as;
	cin>>b>>br>>bs>>a>>as;
	int bm = (br - b) * bs;
	cout<< a + bm / as + 1;
	return 0;
}