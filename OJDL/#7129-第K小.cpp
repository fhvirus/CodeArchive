#include<iostream>
using namespace std;

unsigned ran(){
	return rand();
	static unsigned x=23;
	return ++(x*=0xdefaced);
}

struct node{
	node* l,*r;
	int v;
	unsigned pri,size;
	node(int x):v(x),l(NULL),r(NULL),pri(ran()),size(1){}
};
int S(node* i){
	return i?i->size:0;
}
void update(node *i){
	if(!i)return;
	i->size=S(i->l)+S(i->r)+1;
}
void split(node* now,int k,node* &a,node* &b){
	if(!now){
		a=b=NULL;
		return;
	}
	if(now->v<k){
		a=now;
		split(now->r,k,a->r,b);
		update(a);
	}
	else{
		b=now;
		split(now->l,k,a,b->l);
		update(b);
	}
	return;
}

void splitBySize(node* now,int k,node* &a,node* &b){
	if(!now){
		a=b=NULL;
		return;
	}
	if(now->l&&now->l->size<k){
		a=now;
		splitBySize(now->r,k-(now->l->size+1),a->r,b);
		update(a);
	}
	else{
		b=now;
		splitBySize(now->l,k,a,b->l);
		update(b);
	}
	return;
}

node* merge(node* a,node* b){
	if(!a)return b;
	if(!b)return a;
	if(a->pri>b->pri){
		a->r=merge(a->r,b);
		update(a);
		return a;
	}else{
		b->l=merge(a,b->l);
		update(b);
		return b;
	}
}
void erase(node* &n,int val){
	node* a,*b,*c,*d;
	split(n,val,a,b);
	split(b,val+1,c,d);
	n=merge(a,d);
}

void insert(node* &n,int val){
	node* a,*b;
	erase(n,val);
	split(n,val,a,b);
	n=merge(merge(a,new node(val)),b);
}


int query(node* n,int k){
	if(S(n->l)+1==k){
		return n->v;
	}else if(S(n->l)<k){
		return query(n->r,k-(S(n->l)+1));
	}else return query(n->l,k);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin>>n;
	string cmd;
	int v;
	node* nd=NULL;
	while(n--){
		cin>>cmd>>v;
		if(cmd=="add"){
			insert(nd,v);
		}else if(cmd=="erase"){
			erase(nd,v);
		}else{
			cout<<query(nd,v)<<'\n';
		}
	}
	return 0;
}