//Author: Petar Nyagolov
#include <bits/stdc++.h>
#define time ailhgjaghak

using namespace std;

const int N = 1<<17;

int n,m;
vector < int > v[N];
bool used[N];
int parent[N],current_time,low[N],time[N];
int ans;

void dfs(int node) {
    int i;
    used[node]=true;
    time[node]=++current_time;
    low[node]=current_time;
    for(i=0;i<(int)(v[node].size());i++) {
        if(!used[v[node][i]]) {
            parent[v[node][i]]=node;
            dfs(v[node][i]);
            low[node]=min(low[node],low[v[node][i]]);
            if(low[v[node][i]]>time[node]) ++ans;
        }
        else if(v[node][i]!=parent[node]) {
            low[node]=min(low[node],time[v[node][i]]);
        }
    }
}

int main() {
    int i,x,y;

    scanf("%d %d", &n, &m);
    for(i=1;i<=m;i++) scanf("%d %d", &x, &y),v[x].push_back(y),v[y].push_back(x);
    for(i=1;i<=n;i++) if(!used[i]) dfs(i);
    printf("%d\n", ans);

    return 0;
}
