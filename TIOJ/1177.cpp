#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
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

int m, n;
bool grid[1001][1001];

struct point{
	int f, x, y;
	bool operator== (const point &rhs) const{
		return x == rhs.x and y == rhs.y;
	}
	bool operator< (const point &rhs) const{
		return f > rhs.f;
	}
	point operator+ (const point &rhs) const{
		return (point){f+1, x + rhs.x, y + rhs.y};
	}
	bool isValid(){
		return x > 0 and y > 0 and x <= m and y <= m and !grid[x][y];
	}
} s, e, dir[4] = {
	{0, 1, 0},
	{0, -1, 0},
	{0, 0, 1},
	{0, 0, -1}
};
inline int h(point p){
	return abs(p.x - e.x + abs(p.y - e.y));
}

bool closed[1001][1001];
int F[1001][1001], G[1001][1001];
priority_queue<point> pq;
void aStar(){
	for(int i = 0; i <= m; ++i)
		for(int j = 0; j <= m; ++j)
			F[i][j] = 1e9;
	F[s.x][s.y] = 0;
	pq.push(s);
	point u, v;
	int newG, newF;
	while(!pq.empty()){
		u = pq.top(); pq.pop();
		for(int i = 0; i < 4; ++i){
			v = u + dir[i];
			if(v.isValid()){
				if(v == e){
					printf("%d", v.f);
					return;
				}
				if(!closed[v.x][v.y] and !grid[v.x][v.y]){
					newF = u.f+1;
					newG = newF + h(v);
					if(F[v.x][v.y] > newF){
						pq.push(v);
						F[v.x][v.y] = newF;
						G[v.x][v.y] = newG;
					}
				}
			}
		}
	}
	return;
}

int main(){
	m = R(); n = R();
	for(int i = 0; i < n; ++i)
		grid[R()][R()] = true;
	s = (point){0, R(), R()}; e = (point){0, R(), R()};

	if(!s.isValid() or !e.isValid()){
		puts("-1");
		return 0;
	}
	if(s == e){
		puts("0");
		return 0;
	}

	for(int i = 0; i <= m; ++i)
		grid[i][0] = grid[0][i] = true;
	aStar();
	return 0;
}
