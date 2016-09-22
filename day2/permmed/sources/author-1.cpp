//Auhor: Petar Nyagolov
#include <bits/stdc++.h>

using namespace std;

const int N = 1<<18, OFFSET = 1<<17;;

int n,b,a[N];
int pos,cnt_left[N],cnt_right[N];
long long ans;
int sum;

int main() {
    int i;
    
    scanf("%d %d", &n, &b);
    for(i=1;i<=n;i++) {
        scanf("%d", &a[i]);
        if(a[i]==b) pos=i;
    }
    ++cnt_left[0+OFFSET];
    ++cnt_right[0+OFFSET];
    for(i=pos-1;i>=1;i--) {
        if(a[i]>b) ++sum;
        else --sum;
        ++cnt_left[sum+OFFSET];
    }
    sum=0;
    for(i=pos+1;i<=n;i++) {
        if(a[i]<b) ++sum;
        else --sum;
        ++cnt_right[sum+OFFSET];
    }
    for(i=0;i<N;i++) ans+=cnt_left[i]*1ll*cnt_right[i];
    printf("%lld\n", ans);

    return 0;
}
