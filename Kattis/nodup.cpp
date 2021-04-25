#include<iostream>
#include<set>
using namespace std;

int main(){
	set<string> words;
	string in;
	bool repeat=0;
	while(cin>>in){
		if(words.find(in)!=words.end()){
			repeat=1;
			break;
		}
		words.insert(in);
	}
	cout<<(!repeat?"yes":"no");
	return 0;
}