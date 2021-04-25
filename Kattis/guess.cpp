#include<iostream>
using namespace std;

int main(){
	string in;
	int l=1,r=1001;
	cout<<500<<endl;
	while(cin>>in&&in!="correct"){
		if(in=="lower")r=(l+r-1)/2;
		else l=(l+r-1)/2+1;
		cout<<(l+r-1)/2<<endl;
	}
	return 0;
}