#include<iostream>
using namespace std;

int chek[10]={0,2,4,6,8,1,3,5,7,9};

int main(){
	string in;
	int T,sum;
	cin>>T;
	cin.ignore();
	while(T--){
		getline(cin,in);
		sum=0;
		for(int i=in.size()-1;i>=0;i--){
			if((in.size()-1-i)%2)sum+=chek[in[i]-'0'];
			else sum+=in[i]-'0';
		}
		if(sum%10==0)cout<<"PASS\n";
		else cout<<"FAIL\n";
	}

	return 0;
}