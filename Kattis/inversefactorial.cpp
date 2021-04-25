#include<iostream>
#include<cmath>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){
	string in;
	cin>>in;
	int x = in.size();
	int i;
	double sum;
	if(x < 10){
		int a = stoi(in), i, ans;
		for(i = 1, ans = 1; ans < a; i++, ans *= i);
		cout<<i;
		return 0;
	}
	for(i = 1, sum = 0;sum < x - 1; sum += log10(i++));
	cout << i - 1;
	return 0;
}