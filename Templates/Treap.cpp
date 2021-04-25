int val[N], l[N], r[N], sz[N], cnt = 1;
unsigned pri[N];
int tag[N];
inline unsigned ran(){
	static int x = 131;
	return ++(x *= 0xdefaced);
}
inline int newNode(int v){
	val[cnt] = v;
	l[cnt] = r[cnt] = 0;
	sz[cnt] = 1;
	tag[cnt] = 0;
	pri[cnt] = ran();
	return cnt++;
}
inline int Sz(int u){
	return u ? sz[u] : 0;
}
inline void push(int u){
	// push down tag
	// do something
	// clear tag
}
inline void pull(int u){
	sz[u] = Sz(l[u]) + Sz(r[u]) + 1;
	// update something?
}
void split(int o, int &a, int &b, int k){
	push(o);
	if(!o){
		a = b = 0;
		return;
	}
	if(v[a] <= k){
		a = o;
		splitBySize(r[o], r[a], b, k);
		pull(a);
	} else {
		b = o;
		splitBySize(l[o], a, l[b], k);
		pull(b);
	}
}
void splitBySize(int o, int &a, int &b, int k){
	push(o);
	if(!o){
		a = b = 0;
		return;
	}
	if(Sz(l[o]) + 1 <= k){
		a = o;
		splitBySize(r[o], r[a], b, k - Sz(l[o]) - 1);
		pull(a);
	} else {
		b = o;
		splitBySize(l[o], a, l[b], k);
		pull(b);
	}
}
int merge(int a, int b){
	push(a), push(b);
	if(!a or !b) return a ? a : b;
	if(pri[a] < pri[b]){
		r[a] = merge(r[a], b);
		pull(a);
		return a;
	}
	l[b] = merge(a, l[b]);
	pull(b);
	return b;
}
void inorder_traverse(int u){
	push(u);
	if(l[u]) inorder_traverse(l[u]);
	// cout << u << ' ';
	if(r[u]) inorder_traverse(r[u]);
}