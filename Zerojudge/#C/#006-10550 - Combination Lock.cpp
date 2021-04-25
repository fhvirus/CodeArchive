#include<iostream>
using namespace std;

int main(){
	int s,a,b,c,ans;
	while(cin>>s>>a>>b>>c&&(s!=0||a!=0||b!=0||c!=0)){
		ans=1080+((s+40-a)%40+(b+40-a)%40+(b+40-c)%40)*9;
		cout<<ans<<endl;
	}
	return 0;
}