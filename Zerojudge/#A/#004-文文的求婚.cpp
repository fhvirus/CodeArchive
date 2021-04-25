#include<iostream>
using namespace std;

int main(){
	int i;
	while(cin>>i){
		if(i%4!=0||(i%100==0&&i%400!=0)){
			cout<<"平年"<<endl;
		} else {
			cout<<"閏年"<<endl;
		}
	}
	return 0;
}