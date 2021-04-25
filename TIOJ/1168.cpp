#include "lib1168.h"
const int N = 500001;
struct eek{
	int val, id;
	bool operator<(const eek &rhs) const{
		return val < rhs.val;
	}
};
struct heap{
	eek val[N];
	int siz;
	void push(eek v){
		val[siz++] = v;
		std::push_heap(val, val + siz);
		if(siz >= N) siz = N-1;
	}
	eek top(){ return val[0];}
	void pop(){
		std::pop_heap(val, val + siz);
		--siz;
	}
} mn, mx;
int tot;
bool out[N];

void pop_big(){
	while(out[mx.top().id]) mx.pop();
	out[mx.top().id] = true;
	mx.pop();
}
void pop_small(){
	while(out[mn.top().id]) mn.pop();
	out[mn.top().id] = true;
	mn.pop();
}
void push(int s){
	mx.push({s, tot});
	mn.push({-s, tot});
	++tot;
}
int big(){
	while(out[mx.top().id]) mx.pop();
	return mx.top().val;
}
int small(){
	while(out[mn.top().id]) mn.pop();
	return -mn.top().val;
}