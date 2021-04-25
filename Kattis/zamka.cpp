#include<iostream>
using namespace std;

int digsum(int n){
	int sum=0;
	while(n>0){
		sum+=n%10;
		n/=10;
	}
	return sum;
}

int main(){
	int l,d,x,n,m,tmp;
	cin>>l>>d>>x;
	n=l;m=d;
	while(digsum(n)!=x)n++;
	while(digsum(m)!=x)m--;
	cout<<n<<' '<<m;
	return 0;
}