#include<cstdio>
#include<iostream>
#include<string>
using namespace std;

int main(){
	string ans;
	char ch;
	ch = getchar();
	while(ch != EOF){
		if(ch == '<' and ans.size()) ans.pop_back();
		else ans += ch;
		ch = getchar();
	}
	cout << ans;
	return 0;
}