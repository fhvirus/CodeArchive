#include<iostream>
using namespace std;

int main(){
	int a;
	cin>>a;
	cout<<(a>=6&&a<12)*590+(a>=12&&a<18)*790+(a>=18&&a<60)*890+(a>=60)*399<<endl;
}