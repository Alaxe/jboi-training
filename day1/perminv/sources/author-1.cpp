//Author: Petar Nyagolov
#include <bits/stdc++.h>

using namespace std;

const int MOD = (1e9) + 7;

int n,c;
int dp[1024][10024];

int get_sum(int *arr, int from, int to) {
    int ans=arr[to];
    if(from>0) {
        ans-=arr[from-1];
        ans+=MOD;
        ans%=MOD;
    }
    return ans;
}

int main() {
    int i,j,c;
    
    scanf("%d %d", &n, &c);
    for(i=0;i<=c;i++) dp[1][i]=1;
    for(i=2;i<=n;i++) {
        for(j=0;j<=c;j++) {
            dp[i][j]=get_sum(dp[i-1],max(0,j-i+1),j);
        }
        for(j=1;j<=c;j++) {
            dp[i][j]=(dp[i][j]+dp[i][j-1])%MOD;
        }
    }
    printf("%d\n", get_sum(dp[n],c,c));
    
    return 0;
}
