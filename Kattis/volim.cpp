#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int init, n;
	cin>>init>>n;
	int sec, ct = 0;
	char ans;
	while(n--){
		cin>>sec>>ans;
		ct += sec;
		if(ct >= 210)break;
		if(ans == 'T'){
			if(init == 8)init = 1;
			else init++;
		}
	}
	cout<<(init);
	return 0;
}