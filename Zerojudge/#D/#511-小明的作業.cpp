#include<iostream>
using namespace std;

int main(){
	int a,b,c,score=0,i;
	for(i=0;i<5;i++){
		cin>>a>>b>>c;
		if(a+b>c&&a+c>b&&b+c>a)
			score++;
	}
	cout<<score<<endl;
	return 0;
}