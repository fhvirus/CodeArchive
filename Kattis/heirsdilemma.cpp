#include<iostream>
#include<set>
using namespace std;

set<int>digits;

int check(int n){
	digits.clear();
	int tmp = n;
	while(tmp != 0){
		if(tmp % 10 == 0
		or digits.count(tmp % 10) != 0
		or n % (tmp % 10) != 0)	return 0;
		digits.insert(tmp % 10);
		tmp /= 10;
	}
	return 1;
}

int main(){
	int l, r, ans = 0;
	cin>>l>>r;
	for(int i = l + (l % 2); i <= r; i += 2){
		ans += check(i);
	}
	cout<<ans;
	return 0;
}