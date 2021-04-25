#include<iostream>
#include<algorithm>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,a,b,c;
	cin>>n;
	while(n--){
		cin>>a>>b>>c;
		if(a<b)swap(a,b);
		cout<<(a+b==c||a-b==c||a*b==c||(a/b==c&&a%b==0)?"Possible\n":"Impossible\n");
	}
	return 0;
}