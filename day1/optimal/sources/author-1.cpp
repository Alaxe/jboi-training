//Author: Petar Nyagolov
#include <bits/stdc++.h>

using namespace std;

const int N = 1<<20;

int n,m,q;
int x[N],y[N],z[N];
int row,col;
long long cnt_row[N],cnt_col[N],all,pos,ans;

int main() {
    int i;

    scanf("%d %d %d", &n, &m, &q);
    for(i=1;i<=q;i++) scanf("%d %d %d", &x[i], &y[i], &z[i]),cnt_row[x[i]]+=z[i],cnt_col[y[i]]+=z[i],all+=z[i];
    pos=((all+1)>>1);
    for(i=1;i<=1000000;i++) cnt_row[i]+=cnt_row[i-1],cnt_col[i]+=cnt_col[i-1];
    for(i=1;i<=1000000;i++) if(cnt_row[i]>=pos) {
        row=i;
        break;
    }
    for(i=1;i<=1000000;i++) if(cnt_col[i]>=pos) {
        col=i;
        break;
    }
    for(i=1;i<=q;i++) ans+=((abs(x[i]-row)+abs(y[i]-col))*1ll*z[i]);
    printf("%lld\n", ans);

    return 0;
}
