#include<iostream>
#include<iomanip>
#include<cmath>
#include<algorithm>
using namespace std;

string ring="ABCDEFGHIJKLMNOPQRSTUVWXYZ \'";
double dis(char a,char b){
	double aa=ring.find(a),bb=ring.find(b);
	if(aa>bb)swap(aa,bb);
	return min(bb-aa,aa+28-bb)/28*4*M_PI;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	string quote;
	int n;
	double ans;
	cin>>n;
	cin.ignore();
	while(n--){
		ans=0;
		getline(cin,quote);
		for(int i=0;i<quote.size()-1;i++){
			ans+=dis(quote[i],quote[i+1]);
		}
		ans+=quote.size();
		cout<<setprecision(10)<<fixed<<ans<<'\n';
	}
	return 0;
}