#include<iostream>
#include<utility>
using namespace std;

#define MAXN 10000
class stack{
	int ptr=0;
	int v[MAXN];
public:
	void clear(){
		fill(v,v+MAXN,0);
		ptr=0;
	}
	bool isEmpty(){
		return !ptr;
	}
	bool isFull(){
		return ptr>=MAXN;
	}
	void push(int x){
		if(!isFull())v[ptr++]=x;
		else cout<<"Stack is full.\n";
	}
	void pop(){
		if(!isEmpty()) ptr--;
		return;
	}
	int top(){
		if(isEmpty()) return -1;
		return v[ptr-1];
	}
};

int main(){
	int n,in[MAXN],iptr,tptr;
	bool yn;
	stack s;
	s.clear();
	while(cin>>n&&n){
		while(cin>>in[0]&&in[0]){
			s.clear();
			yn=true;
			tptr=1;
			for(int i=1;i<n;i++){
				cin>>in[i];
			}
			for(int i=0;i<n&&yn;i++){
				if(in[i]<tptr&&s.top()!=in[i]){
					yn=0;
					break;
				}
				while(in[i]!=s.top()){
					s.push(tptr++);
				}
				s.pop();
			}
			cout<<(yn?"Yes\n":"No\n");
		}
		cout<<'\n';
		continue;
	}
	return 0;
}