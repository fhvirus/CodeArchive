#include<iostream>
#include<algorithm>
using namespace std;

int main(){
	string in, ae = "ae";
	int all, cnt;
	all = cnt = 0;
	while(cin>>in){
		all++;
		if(search(in.begin(), in.end(), ae.begin(), ae.end()) != in.end())cnt++;
	}
	cout<<(all * 2 <= cnt * 5 ? 
		"dae ae ju traeligt va":
		"haer talar vi rikssvenska");
	return 0;
}