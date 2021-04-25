#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int e,f,c,ans=0;
	cin>>e>>f>>c;
	e+=f;
	while(e>=c){
		ans+=e/c;
		e=e/c+e%c;
	}
	cout<<ans;
	return 0;
}