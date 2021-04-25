#pragma Os
#define U unsigned
#include<unistd.h>
inline char Z(){static char B[20],*p=B,*q=B;return(p==q&&(q=(p=B)+read(0,B,20))==B)?-1:*p++;}
inline int R(){int A=0,c=Z();while(c<'0')c=Z();while(c>='0')A=A*10+(c^'0'),c=Z();return A;}
char o[30],E[30];
int p,Ep,n,T,d[200],e,A,a=1e9,b,c,i,j;
inline void W(U n){p=Ep=0;while(n)E[Ep++]=n%10+'0',n/=10;for(--Ep;Ep>=0;--Ep)o[p++]=E[Ep];o[p++]=' ';write(1,o,p);}
int main(){n=R();T=n,A=n*4+2;
for(i=1;i*i <= n;++i)if(n%i==0)d[e++]=i;
for(i=1;i<e;++i)while(T%d[i]==0)T/=d[i];
if(T>1)d[e++]=T;
for(i=0;i<e;++i)for(j=i;j<e;++j){U w=d[i],h=d[j];if(1*w*h*h>n)break;if(n%(w*h)==0){U C=(w*h+n/w+n/h)*2,J=n/h/w;if(C!=A?C<A:(w!=a?w<a:(h!=b?h<b:(J<c?1:0)))) A=C,a=w,b=h,c=n/w/h;}}
W(A),W(a),W(b),W(c);return 0;}