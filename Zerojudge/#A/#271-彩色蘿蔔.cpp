#include<iostream>
#include<sstream>
#include<string>
using namespace std;

int main(){
	int s,x,y,z,w,n,m,dokun,carrot;
	bool alive;
	stringstream stream;
	string in;
	cin>>s;
	for(int i=0;i<s;i++){
		dokun=0;alive=1;
		cin>>x>>y>>z>>w>>n>>m;
		getline(cin,in);
		getline(cin,in);
		if(in==""){
			cout<<m<<'g'<<endl;
		} else {
			stream.clear();
			stream<<in;
			while(stream>>carrot){
				m-=dokun*n;
				if(m<=0){
					cout<<"bye~Rabbit\n";
					alive=0;
					stream.str("");
					break;
				}
				if(carrot==1)m+=x;
				else if(carrot==2)m+=y;
				else if(carrot==3)m-=z;
				else if(carrot==4){
					m-=w;
					dokun++;
				}
				if(m<=0){
					cout<<"bye~Rabbit\n";
					alive=0;
					stream.str("");
					break;
				}
			}
			if(alive){
				cout<<m<<'g'<<endl;
			}
		}
	}
	return 0;
}
