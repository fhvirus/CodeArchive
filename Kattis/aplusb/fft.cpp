#include<iostream>
#include<algorithm>
#include<cmath>
#include<complex>
#include<vector>
using namespace std;

typedef long long int ll;
typedef complex<double> cd;

const double PI=M_PI;

#define MAX 600000
#define ADD 50000

#define pb push_back

ll revBit[MAX];
cd W[MAX];
ll logBound,bound;

void bitRev(){
	ll highBitPtr=-1;
	for(ll i=1;i<bound;i++){
		if((i&(i-1))==0)highBitPtr++;
		revBit[i]=revBit[i^(1<<highBitPtr)]+(1<<(logBound-highBitPtr-1));
	}
}

void calc(){
	W[0]=1;
	for(int i=1;i<bound;i++){
		W[i]=cd(cos(2*PI/bound*i),sin(2*PI/bound*i));
	}
}

void fft(cd *arr,bool inverse){
	for(int i=0;i<bound;i++){
		if(i<revBit[i])swap(arr[i],arr[revBit[i]]);
	}
	cd a,b;
	for(int len=1;len<bound;len<<=1){
		for(int g=0;g<bound;g+=2*len){
			for(int i=0;i<len;i++){
				a=arr[g+i];
				if(inverse)b=arr[g+i+len]*conj(W[bound/len/2*i]);
				else b=arr[g+i+len]*W[bound/len/2*i];
				arr[g+i]=a+b;
				arr[g+i+len]=a-b;
			}
		}
	}
	if(inverse){
		for(int i=0;i<bound;i++){
			arr[i]/=bound;
		}
	}
}

cd tmpa[MAX],tmpb[MAX];
void mult(vector<ll> &a,vector<ll> &b,vector<ll> &c){
	logBound=0;
	while((1<<logBound)<a.size()||(1<<logBound)<b.size())logBound++;
	logBound++;
	bound=(1<<logBound);

	bitRev();
	calc();

	for(int i=0;i<a.size();i++)tmpa[i]=cd(a[i],0);
	for(int i=a.size();i<bound;i++)tmpa[i]=cd(0,0);
	for(int i=0;i<b.size();i++)tmpb[i]=cd(b[i],0);
	for(int i=b.size();i<bound;i++)tmpb[i]=cd(0,0);

	fft(tmpa,0);
	fft(tmpb,0);
	for(int i=0;i<bound;i++){
		tmpa[i]*=tmpb[i];
	}
	fft(tmpa,1);

	c.resize(bound);
	for(int i=0;i<bound;i++){
		c[i]=tmpa[i].real()>0?tmpa[i].real()+.5:tmpa[i].real()-.5;
	}
	while(c.size()&&c.back()==0)c.pop_back();
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	ll n;cin>>n;
	vector<ll> freq(100001,0);
	vector<ll> nums;
	vector<ll> ansf;
	ll tmp,zeros=0;
	for(int i=0;i<n;i++){
		cin>>tmp;
		if(!tmp)zeros++;
		nums.pb(tmp+ADD);
		freq[tmp+ADD]++;
	}

	mult(freq,freq,ansf);

	for(auto i:nums)ansf[i*2]--;

	ll ans=0;
	for(auto i:nums)ans+=ansf[i+ADD];
	ans-=(ll)(2*zeros*(n-1));
	cout<<ans;
	return 0;
}