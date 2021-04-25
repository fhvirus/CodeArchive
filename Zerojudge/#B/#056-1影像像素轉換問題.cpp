#include<iostream>
#include<iomanip>
using namespace std;

int main(){
	int n,i;
	long double R,G,B,s;
	while(cin>>n){
		s=0;
		for(i=0;i<n*n;i++){
			cin>>R>>G>>B;
			cout<<fixed<<setprecision(4)
				<< 0.5149 * R + 0.3244 * G + 0.1607 * B + 1e-6 <<' '
				<< 0.2654 * R + 0.6704 * G + 0.0642 * B + 1e-6 <<' '
				<< 0.0248 * R + 0.1248 * G + 0.8504 * B + 1e-6 <<endl;
			s+=0.2654 * R + 0.6704 * G + 0.0642 * B + 1e-6;
		}
		cout<<"The average of Y is "<<fixed<<setprecision(4)<<s/n/n<<endl;
	}
	return 0;
}