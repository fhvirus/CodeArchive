struct BIT{
    int n, val[N];
    inline void init(int _n){
        n = _n;
        for(int i = 0; i <= n; ++i)
            val[i] = 0;
    }
    inline void init(int _n, int v[]){
        n = _n;
        for(int i = 1; i <= n; ++i)
            val[i] = 0;
        for(int i = 1; i <= n; ++i){
            val[i] += v[i];
            if(i + (i & -i) <= n)
                val[i + (i & -i)] += val[i];
        }
    }
    inline void modify(int p, int v){
        for(; p <= n; p += p & -p) val[p] += v;
    }
    inline int query(int p){
        int ans = 0;
        for(; p > 0; p -= p & -p) ans += val[p];
        return ans;
    }
    inline int query(int l, int r){ // [l, r)
        return query(r - 1) - query(l - 1);
    }
    inline int search(int v){
        int sum = 0, p = 0;
        for(int i = 31 - __builtin_clz(n); i > 0; --i)
            if(p + (1 << i) <= n and sum + val[p + (1 << i)] < v)
                p += 1 << i, sum += val[p];
        return p + 1;
    }
} bit;