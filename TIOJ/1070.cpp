#include <cstdio>
#include <cstring>
#include <cctype>

int main(){
  char a[101], b[101];
  while (true) {
    fgets(a, 100, stdin);
    fgets(b, 100, stdin);
    if (strcmp(a, "END\n") == 0 and strcmp(b, "END\n") == 0)
      break;

    if (strcmp(a, b) != 0) {
      puts("Password settings are not consistent.");
      continue;
    }

    int len = (int) strlen(a) - 1;
    if (8 > len or len > 12) {
      puts("Password should contain 8 to 12 characters.");
      continue;
    }

    int upper = 0, lower = 0, digit = 0;
    for (int i = 0; i < len; ++i) {
      upper += (isupper(a[i]) ? 1 : 0);
      lower += (islower(a[i]) ? 1 : 0);
      digit += (isdigit(a[i]) ? 1 : 0);
    }
    int other = len - upper - lower - digit;

    if (upper == 0) {
      puts("Password should contain at least one upper-case alphabetical character.");
      continue;
    }
    if (lower == 0) {
      puts("Password should contain at least one lower-case alphabetical character.");
      continue;
    }
    if (digit == 0) {
      puts("Password should contain at least one number.");
      continue;
    }
    if (other == 0) {
      puts("Password should contain at least one special character.");
      continue;
    }

    bool symmetric = true;
    for (int i = 0, j = len - 1; i < j; ++i, --j)
      symmetric &= (a[i] == a[j]);
    if (symmetric) {
      puts("Symmetric password is not allowed.");
      continue;
    }

    bool non_circular = true;
    for (int c_len = 3; c_len <= 6; ++c_len) {
      bool is_c = true;
      for (int i = c_len; i < len; ++i)
        is_c &= (a[i] == a[i - c_len]);
      non_circular &= not is_c;
    }
    if (not non_circular) puts("Circular password is not allowed.");
    else puts("Password is valid.");
  }
}

