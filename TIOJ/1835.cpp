/* TIOJ 2e5 submissions~~~~
                 /'.    /|    .'\
           ,._   |+i\  /++\  / +|    ,,
           |*+'._/+++\/+ ++\/+++<_.-'+|
      :-.  \ ++++?++ +++++*++++++ +++ /  .-:
      |*+\_/++++ +++*++ ++++++ ++?++++\_/ +|
  ,    \*+++++ ++++ +++*+++ ++++ +++ +++++/   ,
  \'-._> +________*++__++++__+++__++++__*<_.-'/
   `>*+++|        |+|  |++|  |+|  |++/  |++++<'
_,-'+ * +|   _____++|  |++|  |+|  |+/  /+ +*+'-._
'-.*+++++|  |+++++++|  |__|  |*|  |/  /+ ++++++.-'
    > *++|  |___++++|        |+|  |  / *++ +++< 
_,-'* +++|   ___|+ +|   __   |+|    /+++ ++++++'-._
`-._+ +*+|  |++++++*|  |++|  |+|   /       ++ +_.-'
   _`\+++|__|++++ *+|__|++|__|+|__/  IRUS    /`_
  /+++_+* + +++++ ++ + ++++ +++++ ++ ++++ ++_+*+\
  '--' `>*+++ +++++ +++++*++++  +++ ++++ ?<' '--'
       /++_++ ++ ++++++ ++?+ +++++*+++ ++++ \
       |_/ `\++ ++ +++*++++++++++ ++++*./`\_|
            /+*.-.*+ +_ ++*+ _+++ .-.* +\
            | /   | +/ `\?+/` \*+|    \ |
             '    \.'    |/    './     '
*/

#include<cstdio>
#include<cstring>

const int N = 1024;
int n;
char a[N], b[N], prv[N][N], lcs[N];
short len[N][N], lena, lenb;

inline void LCS(){
    lena = strlen(a); lenb = strlen(b);
    for(int i = 0; i <= lena; ++i) len[i][0] = 0;
    for(int j = 0; j <= lenb; ++j) len[0][j] = 0;

    for(int i = 1; i <= lena; ++i){
        for(int j = 1; j <= lenb; ++j){
            if(a[i-1] == b[j-1]) len[i][j] = len[i-1][j-1] + 1, prv[i][j] = 0;
            else{
                if(len[i-1][j] < len[i][j-1])
                    len[i][j] = len[i][j-1], prv[i][j] = 1;
                else if(len[i-1][j] > len[i][j-1])
                    len[i][j] = len[i-1][j], prv[i][j] = 2;
                else{
                    if(a[i-1] < b[j-1]) len[i][j] = len[i][j-1], prv[i][j] = 1;
                    else len[i][j] = len[i-1][j], prv[i][j] = 2;
                }
            }
        }
    }

    int l = len[lena][lenb];
    if(l == 0){ puts("妹萌えこそ正義なのさ！"); return;}
    lcs[l] = '\0';
    while(l > 0)
        if(prv[lena][lenb] == 0)
            lcs[--l] = a[--lena], --lenb;
        else if(prv[lena][lenb] == 1)
            --lenb;
        else
            --lena;
    puts(lcs);
}

int main(){
    scanf("%d", &n);
    for(; n; --n){
        scanf("%s %s", a, b);
        LCS();
    }
    return 0;
}