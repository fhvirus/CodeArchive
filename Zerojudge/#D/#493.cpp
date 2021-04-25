#include<iostream>
#include<algorithm>
#include<vector>
#include<sstream>
#include<iomanip>
#include<complex>
#include<cmath>
using namespace std;

typedef long long int INT64;
typedef unsigned int UINT32;
const INT64 M = 50000000001507329LL;
const INT64 G = 3;
const UINT32 MAXN = 262144;

const int base = 10000;
const int baseDigits = 4 ;

class BigInt{
public:
	vector<INT64> a;
	int sign;

	//Constructors
	BigInt(): sign(1){}

	BigInt(long long v){
		*this = v;
	}

	BigInt(string s){
		read(s);
	}

	string toString(){
		stringstream ss;
		ss << *this;
		string s;
		ss >> s;
		return s;
	}

	int size(){
		if(a.empty())return 0;
		int ans = (a.size()-1) * baseDigits;
		for(int tmp = a.back(); tmp; tmp/=10, ans++);
		return ans;
	}

	int digitSum(){
		string s = toString();
		int ans = 0;
		for(auto i: s)ans += i - '0';
		return ans;
	}

	BigInt abs() const{
		BigInt tmp = *this;
		tmp.sign = 1;
		return tmp;
	}

 	void recalc(){
 		a.push_back(0);
 		for(INT64 i = 0, carry = 0; i < a.size() || carry; i++){
 			a[i]+=carry;
 			carry = a[i] / base;
 			a[i] %= base;
 		}
 		trim();
 	}

/********************************/
/*								*/
/*	Input and Output funcs		*/
/*								*/
/********************************/

	//Cut of leading zeros
	void trim(){
		while(!a.empty() and !a.back())
			a.pop_back();
		if(a.empty())
			sign = 1;
	}

	//Read string and convert it to BigInt
	void read(const string &s){
		int pos = 0;
		a.clear();
		sign = 1;
		while(pos < (int)s.size() && (s[pos] == '-' || s[pos] == '+')){
			if(s[pos]=='-')
				sign = -sign;
			pos++;
		}
		for(int i = s.size()-1; i >= pos; i -= baseDigits){
			INT64 tmp = 0;
			for(int j = max(pos, i - baseDigits + 1); j <= i; j++){
				tmp = tmp * 10 + s[j] - '0';
			}
			a.push_back(tmp);
		}
		trim();
	}

	//Read from standard input
	friend istream& operator>>(istream& stream, BigInt& v){
		string s;
		stream >> s;
		v.read(s);
		return stream;
	}

	//Print to standard ouput
	friend ostream& operator<<(ostream& stream, const BigInt& v){
		if(v.sign == -1)
			stream << '-';

		if(v.a.empty()){
			stream << 0;
		}else{
			//最高位長度不定，直接輸出
			stream << v.a.back();
			//記得減二，最高位不用再輸出一次
			for(int i = (int)v.a.size() - 2; i >= 0; i--){
				stream << setw(baseDigits) << setfill('0') << v.a[i];
			}
		}
		return stream;
	}

/********************************/
/*								*/
/*			= Operator			*/
/*								*/
/********************************/

	void operator=(const BigInt &v){
		sign = v.sign;
		a = v.a;
	}

	void operator=(INT64 v){
		sign = 1;
		a.clear();
		if(v < 0)
			sign = -1, v = -v;
		for(; v > 0; v /= base)
			a.push_back(v % base);
	}

/********************************/
/*								*/
/*		Boolean Operator		*/
/*								*/
/********************************/

	bool operator< (const BigInt &v) const{
		if(sign != v.sign)
			return sign < v.sign;
		if(a.size() != v.a.size())
			return a.size() * sign < v.a.size() * v.sign;
		for(int i = a.size() - 1; i >= 0; i--){
			if(a[i] != v.a[i])
				return a[i] * sign < v.a[i] * sign;
		}
		return false;
	}

	bool operator> (const BigInt &v)const{
		return v < *this;
	}
	bool operator<=(const BigInt &v)const{
		return !(v > *this);
	}
	bool operator>=(const BigInt &v)const{
		return !(v < *this);
	}
	bool operator==(const BigInt &v)const{
		return !(v < *this || v > *this);
	}
	bool operator!=(const BigInt &v)const{
		return (v < *this || v > *this);
	}

/********************************/
/*								*/
/*		Arithmetic Operator		*/
/*								*/
/********************************/

	BigInt operator-() const{
		BigInt tmp = *this;
		tmp.sign = -sign;
		return tmp;
	}

	BigInt operator+(const BigInt &v) const{
		if(sign == v.sign){
			BigInt tmp = v;

			for(int i = 0, carry = 0; i < (int) max(a.size(), v.a.size()) || carry; i++){
				if(i == (int) tmp.a.size())
					tmp.a.push_back(0);
				tmp.a[i] += carry + (i < (int)a.size() ? a[i] : 0);
				carry = tmp.a[i] >= base;
				if(carry)
					tmp.a[i] -= base;
			}
			return tmp;
		}
		return *this - (-v);
	}

	BigInt operator-(const BigInt &v) const{
		if(*this == v)return BigInt(0);
		if(sign == v.sign){
			if(abs() > v.abs()){
				BigInt tmp = *this;
				for(int i = 0, carry = 0; i < (int)v.a.size() || carry; i++){
					tmp.a[i] -= carry + (int)(i < v.a.size()? v.a[i] : 0);
					carry = tmp.a[i] < 0;
					if(carry)
						tmp.a[i] += base;
				}
				tmp.trim();
				return tmp;
			}
			return -(v - *this);
		}
		return *this + (-v);
	}

	void operator+=(const BigInt &v){
		*this = *this + v;
	}
	void operator-=(const BigInt &v){
		*this = *this - v;
	}
};

/********************************/
/*								*/
/*		Now it's NTT Time		*/
/*								*/
/********************************/

INT64 mmul(INT64 a, INT64 b){
	INT64 y = (INT64)((double)a * b / M + .5);
	INT64 r = (a * b - y * M) % M;
	return r < 0 ? r + M : r;
}

INT64 mpow(INT64 a, INT64 b){
	INT64 tmp = a, ans = 1;
	if(a > M)a %= M;
	for(; b; b>>=1, tmp = mmul(tmp, tmp))
		if(b&1) ans = mmul(ans,tmp);
	return ans;
}

//BOUND must be some power of 2
UINT32 BOUND, LOGBOUND;
//Why 20?
INT64 W[20];
void init(int n){
	LOGBOUND = 0;
	while((1<<LOGBOUND) < n)LOGBOUND++;
	BOUND = (1<<LOGBOUND);
	for(int i = 0; i < 20; i++)
		W[i] = mpow(G, (M-1)/(1<<i));
}

UINT32 P[MAXN];
void revBit(){
	P[0] = 0;
	UINT32 hbptr = -1;
	for(int i = 1; i < BOUND; i++){
		if(!(i & (i-1))) hbptr++;
		P[i] = P[i - (1<<hbptr)] + (1<<(LOGBOUND - hbptr - 1));
	}
}

void ntt(INT64* in, INT64* out, bool inv = false){
	for(int i = 0; i < BOUND; i++)
		out[i] = in[P[i]];
	for(int len = 1, layer = 1; len < BOUND; len *= 2, layer++){
		for(int g = 0; g < BOUND; g += len * 2){
			INT64 a, b, w = 1;
			for(int i = 0; i < len; i++){
				a = out[g+i];
				b = mmul(out[g+i+len], w);
				out[g+i] 	 = (a + b) % M;
				out[g+i+len] = (a - b + M) % M;
				w = mmul(w, W[layer]);
			}
		}
	}
	if(inv){
		for(int i = 1; i * 2 < BOUND; i++)
			swap(out[i], out[BOUND - i]);
		INT64 invn = mpow(BOUND, M-2);
		for(int i = 0; i < BOUND; i++)
			out[i] = mmul(out[i], invn);
	}
	return;
}

INT64 tmpa[MAXN], tmpb[MAXN], outa[MAXN];
void mult(BigInt &a, BigInt &b, BigInt &c){
	init(max(a.a.size(), b.a.size()));
	LOGBOUND++;
	BOUND<<=1;
	revBit();

	for(int i = 0; i < a.a.size(); i++)tmpa[i] = a.a[i];
	for(int i = a.a.size(); i < BOUND; i++)tmpa[i] = 0;
	for(int i = 0; i < b.a.size(); i++)tmpb[i] = b.a[i];
	for(int i = b.a.size(); i < BOUND; i++)tmpb[i] = 0;

	ntt(tmpa, outa);
	ntt(tmpb, tmpa);
	for(int i = 0; i < BOUND; i++){
		outa[i] = mmul(outa[i],tmpa[i]);
	}
	ntt(outa, tmpa, 1);

	c.a.resize(BOUND);
	for(int i = 0; i < BOUND; i++){
		c.a[i] = tmpa[i];
	}
	while(c.a.size()&&c.a.back() == 0)c.a.pop_back();
	c.recalc();
}

void power(BigInt a, int n, BigInt &c){
	BigInt ta, tb, ans = 1, cur = a;
	for(int i = 0; (1<<i) <= n; i++){
		if((1<<i) & n){
			ta = ans;
			tb = cur;
			mult(ta, tb, ans);
		}
		ta = cur;
		tb = cur;
		mult(ta, tb, cur);
	}
	c = ans;
}

/********************************/
/*								*/
/*		Main Program Here		*/
/*								*/
/********************************/

int main(){
	BigInt a, c;
	int n;
	cin >> a >> n;
	power(a, n, c);
	if(a < 0 and n % 2)
		cout << -c;
	else
		cout << c;
	return 0;
}