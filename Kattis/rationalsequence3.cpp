#include<iostream>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	long long T,n,k,m,p,q;
	cin>>T;
	while(T--){
		cin>>k>>n;
		p=0;q=m=1;
		while(m<=n)m<<=1;
		m>>=1;
		while(m>=1){
			if(m&n)p=p+q;
			else q=p+q;
			m>>=1;
		}
		cout<<k<<' '<<p<<'/'<<q<<'\n';
	}
	return 0;
}