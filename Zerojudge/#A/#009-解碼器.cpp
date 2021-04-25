#include<iostream>
#include<cstring>
using namespace std;

int main(){
	string i;
	int j;
	while(getline(cin, i)){
		for(j=0;j<i.length();j++){
			i[j]-='1'-'*';
		}
		cout<<i<<endl;
	}
	return 0;
}