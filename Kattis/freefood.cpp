#include<iostream>
#include<iomanip>
using namespace std;

unsigned l[367];

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n,a,b,ans=0;
	cin>>n;
	while(n--){
		cin>>a>>b;
		l[a]++,l[b+1]--;
	}
	for(int i=1;i<366;i++){
		l[i]+=l[i-1];
		if(l[i])ans++;
	}
	cout<<ans;
	return 0;
}