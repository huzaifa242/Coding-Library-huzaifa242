//Usage prim(source). mst holds new tree
// adjlst stores <weight,node>
vector<pair<int,int> > adjlst[MAX],mst[MAX],par,vis;
int n,m;
int dst[MAX];
vector<int> path;
int prim(int u){
	int i;
	par.assign(n+1,0);
	vis.assign(n+1,0);
	for(i=0;i<=n;i++){
		dst[i]=LLONG_MAX;
		mst[i].clear();
	}
	int sm=0;
	priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > pq;
	pq.push(make_pair(0LL,u));
	par[u]=u;
	dst[u]=0;
	while(!pq.empty()){
		auto pp=pq.top();
		pq.pop();
		if(!vis[pp.y]){
			vis[pp.y]=1;
			sm+=pp.x;
			for(auto v:adjlst[pp.y]){
				if(dst[v.y]>v.x && vis[v.y]==0){
					dst[v.y]=v.x;
					par[v.y]=pp.y;
					pq.push({dst[v.y],v.y});
				}
			}
		}
	}
	for(i=1;i<=n;i++){
		if(par[i]!=i){
			mst[i].push_back({dst[i],par[i]});
			mst[par[i]].push_back({dst[i],i});
		}
	}
	return sm;
}
