//Author: Petar Nyagolov
#include <bits/stdc++.h>
 
using namespace std;
 
const int MOD = (1e9) + 7;
const int N = 101;
const int M = 102;
const int D = 1002;
 
int tests,current_case;
int n,m,d,q;
int a[202];
bool used[N][M][D];
int state[N][M][D];
 
int fmod(int a, int b) {
    if(a>=0) return a%b;
    return b-abs(a)%b;
}
 
int recurse(int pos, int taken, int remainder) {
    if(taken==m) {
        if(remainder==0) return 1;
        else return 0;
    }
    if(pos>n) return 0;
    if(used[pos][taken][remainder]) return state[pos][taken][remainder];
    int ans=(recurse(pos+1,taken,remainder)+recurse(pos+1,taken+1,(remainder+fmod(a[pos],d))%d))%MOD;
    used[pos][taken][remainder]=true;
    state[pos][taken][remainder]=ans;
    return ans;
}
 
int main() {
    int i;
 
	scanf("%d %d %d", &n, &m, &d);
	for(i=1;i<=n;i++) scanf("%d", &a[i]);
	printf("%d\n", recurse(1,0,0));
 
    return 0;
}
 
