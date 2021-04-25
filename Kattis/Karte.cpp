#include<iostream>
#include<set>
using namespace std;

int main(){
	string in,tmp;
	set<string> cards;
	getline(cin,in);
	int p,k,h,t;
	p=k=h=t=13;

	for(int i=0;i<in.length();i+=3){
		tmp=in.substr(i,3);
		if(cards.count(tmp)){
			cout<<"GRESKA";
			return 0;
		}
		cards.insert(tmp);
		if(tmp[0]=='P')p--;
		else if(tmp[0]=='K')k--;
		else if(tmp[0]=='H')h--;
		else if(tmp[0]=='T')t--;
	}
	cout<<p<<' '<<k<<' '<<h<<' '<<t;

	return 0;
}