#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
inline int max(int a, int b){
	return a > b ? a : b;
}
inline int min(int a, int b){
	return a < b ? a : b;
}

#include<algorithm>
#include<cstring>
struct bigint{
    char val[101], dig;
    bigint(){
        val[0] = '0';
        val[1] = '\0';
        dig = 1;
    }
    inline bool operator< (const bigint &rhs) const{
        if(dig != rhs.dig) return dig < rhs.dig;
        for(int i = dig-1; i >= 0; --i)
            if(val[i] != rhs.val[i])
                return val[i] < rhs.val[i];
        return false;
    }
    inline void R(){
        dig = 0;
        char c = readchar();
        while((c > '9' or c < '0') and c != EOF)
            c = readchar();
        while(c <= '9' and c >= '0')
            val[dig++] = c, c = readchar();
        val[dig] = '\0';
        std::reverse(val, val+dig);
    }
    inline void operator=(const bigint &rhs){
        dig = rhs.dig;
        for(int i = 0; i < dig; ++i)
            val[i] = rhs.val[i];
    }
    inline bigint operator-(const bigint &rhs) const{
        bigint res = *this;
        int i = 0; bool carry = false;
        for(; i < rhs.dig; ++i){
            if(carry){
                if(res.val[i] == '0'){
                    carry = true;
                    res.val[i] = '9';
                } else {
                    carry = false;
                    res.val[i]--;
                }
            }
            if(res.val[i] < rhs.val[i]){
                carry = true;
                res.val[i] += 10;
            }
            res.val[i] -= (rhs.val[i] - '0');
        }
        for(; i < res.dig; ++i){
            if(carry){
                if(res.val[i] == '0'){
                    carry = true;
                    res.val[i] = '9';
                } else {
                    carry = false;
                    res.val[i]--;
                }
            }
        }
        while(res.val[i] > '9' or res.val[i] < '1')
            --i;
        res.dig = i+1;
        res.val[res.dig] = '\0';
        return res;
    }
};
inline bigint max(bigint a, bigint b){
	return a < b ? b : a;
}
inline bigint min(bigint a, bigint b){
	return a < b ? a : b;
}

int n, dir;
bigint l, r, ans, pos;

int main(){
	n = R(); l.R(); r.R();
	FOR(i,n){
		pos.R();
		dir = R();
		if(dir == 1){
			ans = max(ans, pos - l);
		} else if(dir == 2){
			ans = max(ans, r - pos);
		} else {
			ans = max(ans, min(r - pos, pos - l));
		}
	}
	std::reverse(ans.val, ans.val + ans.dig);
	puts(ans.val);
	return 0;
}