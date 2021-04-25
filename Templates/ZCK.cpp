struct ZCK{
	#define ll long long
	int n;
	ll val[N<<1], tag[N];
	inline void init(int _n, ll v[]){
		n = _n;
		for(int i = 0; i < n; ++i) val[i + n] = v[i];
		for(int i = n - 1; i > 0; --i)
			val[i] = val[i<<1] = val[i<<1|1], tag[i] = 0;
	}
	inline void upd(int p, ll v, int h){
		val[p] += v<<h;
		if(p < n) tag[p] += v;
	}
	inline void push(int p){
		for(int h = 31 - __builtin_clz(n); h >= 0; --h){
			int i = p>>h;
			if(tag[i>>1] == 0) continue;
			upd(i, tag[i>>1], h);
			upd(i^1, tag[i>>1], h);
			tag[i>>1] = 0;
		}
	}
	inline void pull(int p){
		for(int h = 1; p > 1; ++h, p>>=1)
			val[p>>1] = val[p] + val[p^1] + (tag[p>>1]<<h);
	}
	inline void modify(int l, int r, ll v){
		int ll = l, rr = r, h = 0;
		push(l + n), push(r + n - 1);
		for(l += n, r += n; l < r; l >>= 1, r >>= 1, ++h){
			if(l&1) upd(l++, v, h);
			if(r&1) upd(--r, v, h);
		}
		pull(ll + n), pull(rr + n - 1);
	}
	inline ll query(int l, int r){
		ll ans = 0;
		push(l + n), push(r + n - 1);
		for(l += n, r += n; l < r; l >>= 1, r >>= 1){
			if(l&1) ans += val[l++];
			if(r&1) ans += val[--r];
		}
		return ans;
	}
}