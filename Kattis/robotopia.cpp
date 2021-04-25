#include<iostream>
#include<cmath>
using namespace std;

#define OW0 ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

int main(){OW0
	int T, l1, l2, lt, a1, a2, at, d, xu, yu;
	cin>>T;
	while(T--){
		cin>>l1>>a1>>l2>>a2>>lt>>at;
		d  = l1 * a2 - a1 * l2;
		xu = lt * a2 - l2 * at;
		yu = l1 * at - lt * a1;

		if(!d){
			bool hadOne = false, onlyOne = true;
			int x, ansx;
			for(x = 1; x * l1 < lt; x++){
				if((lt - x * l1) % l2 == 0){
					if(!hadOne){
						hadOne = true;
						ansx = x;
					}
					else{
						onlyOne = false;
						break;
					}
				}
			}
			if(hadOne && onlyOne){
				cout << ansx <<' '<< (lt - ansx * l1) / l2 <<'\n';
			}else{
				cout<<"?\n";
			}
		}
		else if(abs(d) > abs(xu) || abs(d) > abs(yu)){
			cout<<"?\n";
		}
		else if(xu % d || yu % d){
			cout<<"?\n";
		}
		else if(xu == 0 || yu == 0){
			cout<<"?\n";
		}
		else{
			cout<< xu / d <<' '<< yu / d <<'\n';
		}
	}
	return 0;
}