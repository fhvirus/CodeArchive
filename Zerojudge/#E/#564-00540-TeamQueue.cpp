#include<iostream>
#include<utility>
#include<string>
#include<map>
using namespace std;

#define MAXN 1010

class queue{
	int front, rear;
	int value[MAXN];
public:
	void clear(){
		fill(value,value+MAXN,0);
		front=0,rear=0;
	}
	void push(int n){
		if(rear<MAXN-1)value[rear++]=n;
		else value[rear]=n,rear=0;
	}
	int pop(){
		if(front<MAXN-1)return value[front++];
		else{
			int t=front;
			front=0;
			return value[MAXN-1];
		}
	}
	bool isEmpty(){
		if(front==rear)return 1;
		return 0;
	}
	int top(){
		return value[front];
	}
};

int main(){
	int teamnum,membnum,num,cnt=1;
	map<int,int> team;
	string command;
	while(cin>>teamnum&&teamnum){
		for(int i=0;i<teamnum;i++){
			cin>>membnum;
			for(int j=0;j<membnum;j++){
				cin>>num;
				team[num]=i;
			}
		}
		queue main,teams[teamnum];
		cout<<"Scenario #"<<cnt++<<'\n';
		while(cin>>command&&command!="STOP"){
			if(command=="ENQUEUE"){
				cin>>num;
				if(teams[team[num]].isEmpty()){
					teams[team[num]].push(num);
					main.push(team[num]);
				}else{
					teams[team[num]].push(num);
				}
			}else if(command=="DEQUEUE"){
				cout<<teams[main.top()].pop()<<'\n';
				if(teams[main.top()].isEmpty())main.pop();
			}
		}
	}
	return 0;
}