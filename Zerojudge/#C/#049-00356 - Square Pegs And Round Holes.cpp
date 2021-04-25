#include<iostream>
using namespace std;

int main(){
	int n,onc,inc,i,j;
	bool first=true;
	while(cin>>n){
		onc=0;inc=0;
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				if((i+1)*(i+1)+(j+1)*(j+1)<=(2*n-1)*(2*n-1)/4){
					inc++;
				}
				else if(i*i+j*j<=(2*n-1)*(2*n-1)/4){
					onc++;
				}
			}
		}
		if(!first)cout<<endl;
		cout<<"In the case n = "<<n<<", "
			<<onc*4<<" cells contain segments of the circle.\nThere are "
			<<inc*4<<" cells completely contained in the circle.\n";
		first=false;
	}
	return 0;
}