#include<iostream>
#include<iomanip>
#include<utility>
using namespace std;

int main(){
	int p,d,a[1000],b[1000],dnum,atmp,btmp,aw=0,bw=0;
	double v=0;
	cin>>p>>d;
	fill(a,a+1000,0);fill(b,b+1000,0);
	for(int i=0;i<p;i++){
		cin>>dnum>>atmp>>btmp;
		a[dnum-1]+=atmp,b[dnum-1]+=btmp;
	}
	for(int i=0;i<d;i++){
		aw+=a[i]<b[i]?a[i]:a[i]-(a[i]+b[i])/2-1;
		bw+=a[i]>b[i]?b[i]:b[i]-(a[i]+b[i])/2-1;
		v+=a[i]+b[i];
		cout<<(a[i]<b[i]?'B':'A')<<' '<<(a[i]<b[i]?a[i]:a[i]-(a[i]+b[i])/2-1)<<' '<<(a[i]>b[i]?b[i]:b[i]-(a[i]+b[i])/2-1)<<'\n';
	}
	cout<<setprecision(10)<<fixed<<(aw>bw?aw-bw:bw-aw)/v;
}