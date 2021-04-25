#include<iostream>
using namespace std;

int main(){
	int n,m,a,b,bst,avg,i,j,tmp;
	cin>>n;
	for(i=0;i<n;i++){
		bst=4195;
		avg=0;
		cin>>m;
		for(j=0;j<m;j++){
			cin>>a>>b;
			tmp=a*60+b;
			if(tmp<bst){bst=tmp;}
			avg+=tmp;
		}
		avg/=m;
		cout<<"Track "<<i+1<<":\nBest Lap: "<<bst/60<<" minute(s) "<<bst%60<<" second(s).\n"
			<<"Average: "<<avg/60<<" minute(s) "<<avg%60<<" second(s).\n\n";
	}
	return 0;
}