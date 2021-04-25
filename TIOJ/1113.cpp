#include<unistd.h>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline char RC(){static char buf[65536],*p=buf,*q=buf;return p==q&&(q=(p=buf)+read(0,buf,65536))==buf?-1:*p++;}
inline bool RS(char a[]){
    
    return true;
}

char a[8], s;

int main(){
    while(RS(a)){
        int ptr = 0;
        while((a[0] = RC()) < 'a' and a[0] != -1);
        if(a[0] == -1) return 0;
        while((a[++ptr] = RC()) >= 'a');
        a[ptr] = '\0';
        sort(a, a + ptr);
        do {puts(a);} while(next_permutation(a, a+ptr));
        putchar_unlocked('\n');
    }
}