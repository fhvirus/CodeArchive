#include<iostream>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int x, y, rx, ry, rtx, rty, n, s;
	char d;
	while(cin>>x>>y && (x||y)){
		cin>>n;
		rx = ry = rtx = rty = 0;
		while(n--){
			cin>>d>>s;
			if(d=='u'){
				rty += s;
				ry = min(ry + s, y-1);
			}else if(d=='d'){
				rty -= s;
				ry = max(ry - s, 0);
			}else if(d=='r'){
				rtx += s;
				rx = min(rx + s, x-1);
			}else if(d=='l'){
				rtx -= s;
				rx = max(rx - s, 0);
			}
		}
		cout<<"Robot thinks "<<rtx<<' '<<rty
			<<"\nActually at "<<rx<<' '<<ry
			<<"\n\n";
	}
	return 0;
}