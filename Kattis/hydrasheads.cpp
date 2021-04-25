#include<iostream>
using namespace std;

int main(){
	int h, t, moves;
	while(cin>>h>>t){
		if(h == 0 and t == 0)return 0;
		moves = 0;
		while(!(t % 2 == 0 && (h + t / 2) % 2 == 0)){
			t++;
			moves++;
		}
		moves += t / 2;
		h += t / 2;
		moves += h / 2;
		cout<<moves<<'\n';
	}
	return 0;
}