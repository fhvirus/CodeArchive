#include<iostream>
using namespace std;

int main(){
	int n, ptr, tmp;
	cin>>n;
	ptr = 1;
	for(int i = 0; i < n; i++){
		cin>>tmp;
		if(tmp > ptr){
			while(ptr < tmp)cout<<ptr++<<'\n';
		}
		ptr = tmp + 1;
	}
	if(tmp == n)cout<<"good job";
	return 0;
}