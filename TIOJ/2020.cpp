#pragma Ofast
#pragma GCC target("avx2")
#include<unistd.h>
char dp[5050] = {1,2,1,3,3,1,4,2,4,1,5,4,4,5,1,6,3,2,3,5,1,7,5,5,5,5,5,1,8,4,5,2,5,4,7,1,9,6,3,6,6,3,6,7,1,10,5,6,4,2,4,6,5,6,1,11,7,6,6,6,6,6,6,7,6,1,12,6,4,3,6,2,6,3,4,5,7,1,13,8,7,7,6,6,6,6,7,7,8,7,1,14,7,7,5,7,5,2,5,7,5,7,5,7,1,15,9,5,7,3,4,8,8,4,3,7,5,8,7,1,16,8,8,4,7,5,7,2,7,5,7,4,8,7,7,1,17,10,8,8,7,7,7,8,8,7,7,7,8,7,8,9,1,18,9,6,6,7,3,7,6,2,6,7,3,7,6,5,7,8,1,19,11,9,8,8,7,7,7,7,7,7,7,7,7,7,9,11,8,1,20,10,9,5,4,6,7,4,8,2,8,4,7,6,4,5,8,6,9,1,21,12,7,9,8,5,3,7,5,7,7,5,7,3,5,8,9,5,8,8,1,22,11,10,7,8,6,9,6,8,6,2,6,8,6,8,6,8,7,8,6,8,1,23,13,10,9,8,8,8,9,8,8,8,8,8,8,8,8,8,8,9,8,8,8,1,24,12,8,6,9,4,8,3,5,6,9,2,9,6,5,3,8,4,9,5,7,7,8,1,25,14,11,10,5,8,8,9,8,4,8,8,8,8,4,8,9,8,8,5,8,8,12,8,1,26,13,11,8,9,7,8,7,9,6,8,6,2,6,8,6,9,7,8,7,8,8,8,7,8,1,27,15,9,10,9,6,8,8,3,8,8,6,8,8,6,8,8,3,8,8,6,8,10,7,11,8,1,28,14,12,7,9,7,4,5,8,7,8,5,9,2,8,5,8,7,8,5,4,7,9,5,10,7,9,1,29,16,12,11,10,9,10,8,9,8,8,8,9,8,8,9,8,8,8,9,8,9,9,10,11,8,11,9,1,30,15,10,9,6,5,9,7,6,3,8,4,9,8,2,8,9,4,8,3,6,7,9,5,5,8,6,7,9,1,31,17,13,11,10,9,9,10,9,8,9,8,8,8,8,8,8,8,8,9,8,8,10,8,9,9,11,9,16,9,1,32,16,13,8,10,8,9,4,9,7,8,5,8,7,9,2,9,7,8,5,8,7,9,4,9,8,10,7,10,7,11,1,33,18,11,12,10,7,9,10,6,9,3,6,8,8,6,10,10,6,8,8,6,3,9,6,10,9,7,9,9,6,9,9,1,34,17,14,10,11,8,9,8,9,7,9,7,8,7,8,8,2,8,8,7,8,7,9,7,9,8,9,7,9,8,9,9,9,1,35,19,14,12,7,10,5,9,10,5,10,9,9,4,5,10,9,9,10,5,4,9,9,9,5,10,9,5,9,5,9,10,9,9,1,36,18,12,9,11,6,11,6,4,7,9,3,9,7,6,6,10,2,11,6,6,7,9,3,9,7,4,6,10,5,11,7,7,8,9,1,37,20,15,13,11,10,10,9,9,9,9,9,10,9,9,9,9,9,9,9,9,9,9,10,9,9,9,9,9,9,10,10,9,9,10,10,1,38,19,15,11,11,9,10,8,10,8,9,7,9,7,9,7,10,7,2,7,10,7,9,7,9,7,9,7,10,7,9,9,9,10,9,8,9,1,39,21,13,13,12,8,10,11,7,9,9,7,3,9,6,9,9,6,10,9,6,9,9,6,9,3,7,9,9,7,9,10,8,9,9,7,9,9,1,40,20,16,10,8,9,10,5,10,4,9,6,9,7,5,4,9,8,9,2,9,8,9,4,5,7,9,6,9,4,9,5,9,8,7,6,11,9,9,1,41,22,16,14,12,11,10,11,10,9,9,9,10,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,10,9,9,9,11,14,9,9,9,1,42,21,14,12,12,7,6,9,7,8,10,5,10,3,7,7,10,5,10,7,2,7,10,5,10,7,7,3,10,5,10,8,7,9,5,5,9,8,7,8,9,1,43,23,17,14,12,11,12,10,10,10,9,9,10,9,9,9,10,9,10,9,9,9,9,10,9,10,9,9,9,9,9,9,9,10,10,10,11,9,10,11,18,9,1,44,22,17,11,13,10,11,7,11,8,4,6,9,9,9,6,9,8,9,6,9,2,9,6,9,8,9,6,9,8,9,6,4,8,9,7,11,8,9,6,11,8,10,1,45,24,15,15,9,9,11,10,5,6,10,7,9,9,3,10,9,4,9,6,8,9,9,8,6,9,4,9,10,3,9,9,7,9,6,5,10,9,8,7,12,7,10,10,1,46,23,18,13,13,10,11,9,10,8,11,8,9,8,9,9,9,8,9,8,9,8,2,8,9,8,9,8,9,8,9,8,9,8,9,8,10,9,11,8,10,8,10,8,10,1,47,25,18,15,13,12,11,12,11,10,10,10,9,9,10,9,10,9,9,9,9,9,9,9,9,9,9,9,9,9,9,10,9,9,10,10,10,9,9,10,12,9,15,11,10,10,1,48,24,16,12,13,8,11,6,8,9,10,4,10,8,7,3,9,5,9,6,7,9,13,2,11,9,7,6,9,5,9,3,7,8,10,4,10,9,8,5,11,7,10,7,7,8,10,1,49,26,19,16,14,12,7,12,11,10,10,10,10,5,9,11,10,9,9,10,5,9,9,9,9,9,9,5,10,9,9,10,10,9,5,10,10,9,10,9,12,5,12,10,12,10,14,10,1,50,25,19,14,10,11,13,10,11,5,10,8,11,8,6,9,11,8,9,4,9,8,11,8,2,8,11,8,9,4,9,8,11,9,6,8,10,8,9,5,11,8,10,8,6,11,10,8,10,1,51,27,17,16,14,10,12,11,8,10,10,8,10,10,7,11,3,7,9,10,7,10,10,8,9,9,8,10,10,7,10,9,7,3,9,7,10,10,8,10,10,7,11,10,8,10,10,9,10,10,1,52,26,20,13,14,11,12,8,11,9,10,7,4,8,10,7,10,9,9,6,9,8,10,6,11,2,12,6,10,8,9,6,9,9,10,7,10,8,4,7,10,8,11,8,10,8,11,7,11,8,10,1,53,28,20,17,14,13,12,11,12,11,11,10,10,10,10,10,11,10,9,9,9,9,10,11,11,9,9,11,11,9,9,9,9,9,10,11,10,10,10,10,10,10,11,10,10,10,13,10,14,10,10,11,1,54,27,18,15,15,9,12,10,6,9,10,6,11,8,7,8,10,3,11,8,7,8,11,6,12,8,2,8,12,6,11,8,7,8,11,3,10,8,7,8,10,6,10,8,5,10,10,7,10,11,8,8,10,1,55,29,21,17,11,13,12,13,11,7,5,10,11,10,6,10,11,10,12,6,9,4,10,9,6,9,10,10,9,6,9,10,4,9,6,10,10,10,10,6,10,10,10,5,7,10,10,10,13,6,10,10,10,10,1,56,28,21,14,15,12,8,7,12,9,11,7,11,4,10,5,10,8,10,7,5,8,10,5,10,9,12,2,12,8,10,5,10,8,5,7,10,8,10,5,10,4,11,7,10,9,12,5,7,10,10,7,10,9,12,1,57,30,19,18,15,11,14,13,9,11,12,8,10,10,8,10,10,7,3,10,7,10,10,7,10,10,7,10,10,7,10,10,7,10,10,7,10,3,7,10,10,7,10,10,7,10,11,9,10,10,11,10,11,8,10,10,1,58,29,22,16,15,12,13,11,12,10,11,9,10,10,10,8,10,9,11,8,10,8,10,8,11,9,12,8,2,8,12,9,10,8,10,8,10,8,11,9,10,8,10,9,10,9,11,10,10,11,10,8,10,11,10,9,10,1,59,31,22,18,16,14,13,12,12,11,11,11,10,10,10,10,11,10,10,10,11,10,10,10,10,10,11,10,10,10,10,11,10,10,10,10,10,11,10,10,10,10,10,10,10,10,11,10,11,11,10,10,14,10,11,10,10,10,1,60,30,20,15,12,10,13,9,9,6,11,5,10,9,4,7,11,6,10,3,7,8,10,4,6,9,8,8,12,2,11,8,8,9,6,4,10,8,7,3,10,6,11,7,4,9,10,5,10,5,8,8,11,6,7,7,9,9,10,1,61,32,23,19,16,14,13,12,12,11,11,11,11,10,10,11,10,10,11,10,10,10,10,11,10,11,10,10,11,10,10,11,10,10,11,10,11,10,10,10,10,10,10,10,11,10,10,10,11,10,11,11,12,10,11,10,10,11,20,10,1,62,31,23,17,16,13,13,11,13,10,11,9,11,9,11,10,10,9,11,8,10,9,10,8,10,8,10,8,10,8,2,8,10,8,10,8,10,8,10,9,10,8,11,8,10,10,11,8,11,9,10,9,11,11,10,9,10,12,10,9,10,1,63,33,21,19,16,12,9,14,7,12,11,9,12,6,8,10,10,5,10,10,3,10,10,7,10,10,5,6,10,7,12,11,7,10,6,5,10,10,7,10,10,3,10,10,5,10,10,8,6,10,9,10,11,5,10,7,8,10,11,8,13,10,1,64,32,24,16,17,13,15,8,12,10,12,8,11,9,10,4,11,9,10,7,10,8,10,5,10,8,10,7,10,9,10,2,10,9,10,7,10,8,10,5,10,8,10,7,10,9,11,4,10,9,10,8,12,10,11,7,10,10,12,7,12,11,11,1,65,34,24,20,13,15,14,14,13,8,11,11,5,11,7,12,10,10,10,7,10,10,11,10,6,4,10,10,11,6,10,10,10,10,6,11,10,10,4,6,10,10,10,10,7,10,10,10,12,7,10,5,11,10,8,10,10,10,11,7,10,10,12,10,1,66,33,22,18,17,11,14,12,10,10,6,7,11,9,8,10,11,6,10,9,9,3,10,6,10,8,8,8,10,6,10,10,2,10,10,6,10,8,8,8,10,6,10,3,8,9,10,6,11,10,8,9,11,7,5,9,8,9,10,6,10,9,8,9,10,1,67,35,25,20,17,15,14,13,13,12,12,11,12,11,11,12,12,10,10,10,10,10,10,11,11,10,10,10,11,10,12,11,10,10,10,10,10,11,10,10,10,10,11,10,10,10,10,10,10,10,10,10,11,10,11,10,12,10,13,11,15,10,11,12,12,11,1,68,34,25,17,17,14,14,10,13,11,13,8,12,9,11,8,4,9,10,7,10,9,10,7,10,8,10,7,10,8,11,8,10,2,10,8,11,8,10,7,10,8,10,7,10,9,10,7,10,9,4,8,11,9,10,7,10,9,12,8,11,9,11,9,11,9,12,1,69,36,23,21,18,13,14,13,10,12,12,9,12,11,8,11,11,8,10,11,8,10,3,9,10,11,8,10,10,8,10,11,8,10,10,8,11,10,8,10,10,8,11,10,8,3,10,8,11,10,8,11,11,8,11,10,9,11,11,8,11,10,8,11,10,8,11,11,1,70,35,26,19,14,14,10,12,13,7,12,10,11,5,7,9,12,10,10,5,6,10,10,9,7,9,10,4,10,5,10,10,10,9,2,9,10,10,10,5,10,4,10,9,7,9,10,9,6,5,10,10,11,9,7,5,11,9,11,5,11,9,6,10,7,9,11,9,11,1,71,37,26,21,18,16,16,15,14,12,12,12,11,11,11,11,11,11,10,11,10,10,14,10,10,10,10,10,11,10,10,11,10,10,10,10,10,10,11,10,10,10,10,10,10,10,10,11,10,10,11,10,11,10,11,11,10,10,12,10,12,11,11,12,11,10,20,11,11,11,1,72,36,24,18,18,12,15,9,8,11,12,6,11,11,9,6,12,4,10,7,8,9,10,3,10,9,5,7,10,6,10,6,9,10,10,2,11,11,9,6,10,6,10,7,5,9,10,3,10,9,8,7,10,4,10,6,9,10,11,5,11,11,7,7,12,7,11,8,8,9,12,1,73,38,27,22,18,16,15,15,13,13,12,12,11,11,11,11,11,11,12,10,10,11,12,10,12,10,10,10,10,10,11,11,10,10,10,11,11,10,10,10,11,10,10,10,10,10,10,12,10,10,11,10,10,12,10,11,11,11,11,11,12,10,11,12,12,10,16,11,11,11,20,12,1,74,37,27,20,19,15,15,13,14,11,12,10,12,10,11,9,11,9,13,9,10,9,11,9,10,10,10,9,11,9,10,9,10,9,10,9,2,9,10,9,10,9,10,9,11,9,10,10,10,9,11,9,10,9,11,9,10,9,11,9,11,10,12,10,10,9,11,9,11,10,11,10,11,1,75,39,25,22,15,14,15,14,11,9,13,10,12,11,5,11,11,8,11,7,8,10,11,9,3,10,8,10,10,4,10,10,8,10,8,8,10,10,8,8,10,8,10,10,4,10,10,8,10,3,9,11,10,8,7,10,8,11,11,5,11,10,8,11,8,8,11,11,12,7,11,8,11,11,1,76,38,28,19,19,15,15,11,14,11,12,9,13,10,11,8,12,10,4,8,10,9,11,7,10,9,10,7,10,9,10,7,10,10,10,7,10,2,10,7,10,10,10,7,10,9,10,7,10,9,10,7,11,9,10,7,4,10,11,7,11,9,11,9,11,9,11,10,11,9,11,8,12,9,11,1,77,40,28,23,19,17,11,14,14,13,7,12,12,7,12,12,12,11,12,11,6,5,12,12,12,10,12,6,10,10,10,10,5,11,6,12,12,10,10,12,12,6,11,5,10,10,10,10,6,10,10,12,12,11,5,6,10,12,11,12,11,12,7,11,11,5,13,11,11,6,11,11,15,11,11,11,1,78,39,26,21,19,13,17,13,11,12,13,8,6,10,9,11,11,7,11,9,8,9,11,7,12,3,9,9,11,6,10,9,8,9,11,6,13,10,2,9,12,6,11,9,8,9,10,6,11,9,9,3,12,7,11,9,8,9,11,7,11,9,8,10,5,8,11,9,8,9,11,7,11,9,8,9,11,1,79,41,29,23,20,17,16,16,14,13,14,12,12,12,11,11,11,11,11,11,11,11,11,10,13,10,13,11,10,10,10,11,10,10,10,11,10,10,10,10,10,10,11,10,10,10,11,10,10,10,11,11,10,10,10,11,11,11,11,10,11,10,11,11,10,11,12,11,11,11,16,12,17,11,11,11,11,11,1,80,40,29,20,16,16,16,10,15,8,13,9,13,10,8,5,11,10,12,4,12,9,11,6,7,9,10,7,11,5,10,4,10,9,7,8,12,9,10,2,10,9,12,8,7,9,10,4,10,5,11,7,10,9,7,6,10,9,12,4,12,9,11,5,8,9,11,8,12,7,12,6,11,11,7,9,11,9,12,1,81,42,27,24,20,15,16,16,9,13,13,10,13,12,9,13,12,6,12,11,8,11,11,8,11,10,3,12,11,8,10,11,8,10,10,6,12,10,8,10,10,8,10,11,6,10,10,8,11,10,8,11,12,3,10,11,8,10,11,8,11,11,6,12,12,8,12,12,10,11,13,7,13,11,11,11,13,8,14,12,1,82,41,30,22,20,16,16,14,14,12,13,11,13,10,12,11,11,10,11,9,11,9,11,9,11,10,11,9,12,9,11,9,11,9,11,9,11,9,11,9,2,9,11,9,11,9,11,9,11,9,11,9,12,9,11,9,11,9,11,9,11,9,11,10,11,9,12,9,11,9,11,11,11,13,11,9,11,9,11,9,11,1,83,43,30,24,20,18,16,15,15,14,13,13,12,12,12,13,12,11,11,11,11,11,11,11,12,11,13,11,13,10,10,10,12,10,11,11,11,10,10,12,10,10,12,10,10,11,11,11,10,12,10,10,10,11,10,10,10,12,11,11,11,11,11,11,11,11,13,12,11,11,13,11,14,11,11,12,11,11,20,11,14,11,1,84,42,28,21,21,14,12,12,12,12,13,7,12,6,9,9,13,7,11,8,4,10,11,5,11,10,8,3,10,7,10,7,8,10,6,5,11,10,9,7,12,2,12,7,8,10,11,5,6,10,8,7,10,7,10,3,8,10,11,5,11,10,4,8,11,7,12,9,9,5,11,5,11,9,10,8,7,7,11,8,9,9,11,1,85,44,31,25,17,18,18,15,15,10,13,13,12,12,8,12,5,11,11,8,11,11,11,12,7,11,13,11,13,7,12,10,10,4,7,11,11,10,12,8,12,10,10,12,8,12,10,11,11,7,4,10,10,12,7,12,11,11,11,7,12,11,11,11,8,11,11,5,11,7,12,11,13,12,8,11,12,11,12,9,11,11,13,11,1,86,43,31,23,21,17,17,14,15,12,14,11,12,12,12,10,12,10,11,10,11,9,11,9,11,10,12,9,11,9,10,9,10,10,10,9,11,10,10,9,13,9,2,9,11,9,10,10,11,9,10,10,10,9,10,9,11,9,12,9,11,9,11,9,11,9,11,10,11,10,11,10,11,11,11,9,11,10,11,11,12,12,11,9,11,1,87,45,29,25,21,16,17,17,12,14,13,11,13,12,10,12,13,9,11,11,10,11,11,8,11,12,9,11,3,8,11,11,8,10,11,8,11,10,9,11,11,8,11,11,8,11,11,9,10,11,8,11,10,8,11,11,8,3,11,9,12,11,8,11,11,9,11,11,9,11,11,10,12,11,11,12,11,8,13,11,11,11,11,9,12,11,1,88,44,32,22,21,17,17,11,15,13,8,10,13,11,12,7,12,11,11,8,11,4,12,6,11,9,11,9,11,9,11,6,5,9,11,8,11,9,11,6,13,9,11,2,11,9,13,6,11,9,11,8,11,9,5,6,11,9,11,8,11,9,11,6,11,4,11,8,11,9,12,7,11,11,11,8,7,9,11,6,11,11,13,8,13,10,11,1,89,46,32,26,22,19,17,17,16,14,14,13,14,12,12,12,13,12,11,12,11,11,11,11,11,11,11,11,13,11,13,11,11,10,12,12,11,11,10,10,12,10,11,11,11,11,10,12,10,10,11,11,12,12,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,11,11,11,11,11,14,12,13,11,19,11,11,11,12,11,1,90,45,30,24,18,15,17,15,10,9,15,9,13,11,6,10,12,5,11,6,9,10,11,7,7,9,6,9,12,3,11,10,8,9,7,4,11,9,9,6,13,8,12,9,2,9,12,8,13,6,9,9,11,4,7,9,8,10,11,3,11,9,6,9,7,7,11,9,9,6,11,5,11,10,5,9,11,8,11,7,6,12,11,7,8,10,9,10,11,1,91,47,33,26,22,19,13,16,15,14,14,13,7,8,12,12,12,12,11,12,7,11,11,12,11,5,11,7,11,11,12,12,11,11,6,11,11,11,5,11,12,6,11,12,11,11,12,11,6,12,11,5,11,11,11,6,11,11,12,11,11,11,7,11,5,11,12,11,11,7,12,11,12,11,11,12,8,5,13,12,11,11,14,7,12,12,11,11,12,11,1,92,46,33,23,22,18,19,13,16,13,14,10,13,11,13,9,12,10,13,8,11,11,4,8,12,9,11,8,11,9,11,9,11,9,11,8,11,9,11,8,11,9,12,8,11,2,11,8,13,9,11,8,11,9,11,8,11,9,11,8,11,9,11,8,11,9,12,8,4,9,11,8,13,10,11,9,11,11,12,8,13,10,12,8,13,10,11,8,12,10,12,1,93,48,31,27,22,17,18,16,13,15,14,11,14,13,10,13,13,9,14,11,9,11,11,10,11,11,9,11,11,8,3,12,9,11,11,8,11,11,8,11,11,8,11,11,8,11,11,8,11,11,8,11,11,8,11,11,8,11,11,9,11,3,8,11,11,8,11,11,10,11,11,8,11,11,9,11,11,9,11,11,11,11,12,9,11,11,14,11,12,9,12,11,1,94,47,34,25,23,18,18,15,16,13,14,12,14,11,12,12,13,11,12,10,11,10,15,10,11,9,11,9,12,10,13,9,11,10,11,9,11,9,11,9,11,9,12,9,12,9,2,9,13,9,11,9,11,9,11,9,11,9,11,9,11,9,11,10,12,9,11,9,11,10,12,10,11,10,11,9,11,9,11,10,12,12,11,9,11,12,11,11,11,10,11,10,11,1,95,49,34,27,19,20,18,18,16,11,14,14,14,13,9,12,12,12,5,8,11,12,11,11,8,12,11,11,11,7,11,12,11,11,7,11,11,4,11,7,11,11,12,11,7,11,11,11,11,7,11,11,11,11,7,11,4,11,11,7,11,11,12,11,7,11,11,11,11,7,11,11,11,11,7,5,12,11,12,9,13,11,11,11,11,12,11,11,12,8,11,11,11,11,1,96,48,32,24,23,16,18,12,13,13,14,8,13,11,10,6,12,8,13,9,9,10,13,4,11,10,9,8,12,7,11,3,8,9,12,5,11,9,8,6,11,7,12,9,9,12,13,2,14,11,9,9,12,7,11,6,8,9,11,5,12,9,8,3,11,7,12,8,9,10,11,4,13,10,9,9,12,8,12,5,10,11,12,7,12,10,10,7,11,7,12,8,11,10,11,1,97,50,35,28,23,20,18,18,16,15,15,14,13,13,13,14,12,12,12,12,11,11,12,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,13,11,13,11,14,11,12,11,18,11,14,12,11,11,11,11,1,98,49,35,26,23,19,14,16,17,14,14,12,13,7,13,12,13,11,12,10,7,10,12,10,13,10,11,5,11,9,13,11,11,10,7,9,12,9,11,10,11,5,11,9,11,9,11,9,2,9,11,9,11,9,11,5,11,10,11,9,12,9,7,10,11,10,13,9,11,5,11,10,12,10,11,9,7,10,11,9,13,12,12,5,11,12,11,10,12,12,7,10,11,13,11,10,11,1,99,51,33,28,24,18,20,17,11,15,9,12,13,13,10,14,12,7,13,12,9,6,12,10,11,11,6,11,11,9,12,12,3,11,11,6,11,11,8,11,11,8,12,6,6,11,12,10,11,11,10,12,11,6,6,12,8,11,11,8,11,11,6,11,11,3,12,11,9,11,11,6,11,11,10,12,6,9,12,12,7,11,14,9,12,11,9,7,12,6,12,13,9,11,13,9,14,11,1,100,50,36,25,20,19,19,14,16,10,15,11,14,13,9,10,13,11,13,5,12,10,13,8,4,11,11,8,12,6,11,9,11,11,7,8,11,9,11,4,11,9,11,8,8,11,14,8,11,2,11,8,12,11,8,8,11,9,11,4,11,9,11,8,7,11,11,9,11,6,12,8,11,10,4,8,11,9,12,5,12,11,13,8,8,10,11,8,12,6,11,11,13,10,9,8,12,10,12,1,};
const int S = 10;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}
char outbuf[S], eek[20];
int outp, eekp;
inline void W(int n){
    if(n == 0) outbuf[outp++] = '0';
    eekp = 0;
    while(n) eek[eekp++] = n % 10 + '0', n /= 10;
    for(--eekp; eekp >= 0; --eekp) outbuf[outp++] = eek[eekp];
    outbuf[outp++] = '\n';
	write(1, outbuf, outp);
}
int main(){
	short n = R(), m = R();
	n = (n == m ? 1 : (n > m ? dp[n * (n-1) / 2 + m - 1] : dp[m * (m-1) / 2 + n - 1]));
	W(n);
	return 0;
}