#include<unistd.h>
inline char RC(){static char buf[2000],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,1000))==buf?-1:*p++;}
char OB[5000],c;int OP,C;
int main(){while(1){c=RC();if(c==-1)break;if(c<58){c-='0';C=C*10+c;}else{if(C==0)++C;for(;C;--C){OB[OP++]=c;if(OP>4999)write(1,OB,OP),OP=0;}}}write(1,OB,OP);return 0;}
