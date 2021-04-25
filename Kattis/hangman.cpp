#include<iostream>
#include<set>
using namespace std;

int main(){
	string in,guess;
	int n=0;
	set<char> word;
	getline(cin,in);
	getline(cin,guess);
	for(int i=0;i<in.size();i++){
		word.insert(in[i]);
	}
	for(int i=0;i<26;i++){
		if(word.count(guess[i])==0)n++;
		else word.erase(guess[i]);
		if(word.size()==0)break;
	}
	cout<<(n>=10?"LOSE":"WIN");
	return 0;
}