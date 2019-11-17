//Usage dijkstra(source). get_path(source, any_node), ssst holds new tree
// adjlst stores <weight,node>
// for multi-source djikstra put all the sources in pq with dst=0
vector<pair<int,int> > adjlst[MAX],ssst[MAX];
int par[MAX],vis[MAX],n,m;
int dst[MAX];
vector<int> path;
void dijkstra(int u){
	int i;
	par.assign(n+1,0);
	vis.assign(n+1,0);
	for(i=0;i<=n;i++){
		dst[i]=LLONG_MAX;
		ssst[i].clear();
	}
	priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > pq;
	pq.push({0LL,u});
	par[u]=u;
	dst[u]=0;
	while(!pq.empty()){
		auto pp=pq.top();
		pq.pop();
		if(!vis[pp.y]){
			vis[pp.y]=1;
			for(auto v:adjlst[pp.y]){
				if(dst[v.y]>dst[pp.y]+v.x){
					dst[v.y]=dst[pp.y]+v.x;
					par[v.y]=pp.y;
					pq.push({dst[v.y],v.y});
				}
			}
		}
	}
	for(i=1;i<=n;i++){
		if(par[i]!=i){
			ssst[i].push_back({dst[i]-dst[par[i]],par[i]});
			ssst[par[i]].push_back({dst[i]-dst[par[i]],i});
		}
	}
}
//u must be source
void get_path(int u, int v){
	//cout<<"Distance: "<<dst[v]<<endl;
	//cout<<"Path \n";
	if(dst[v]==LLONG_MAX)
		cout<<-1<<"\n";
	else{
		for(i=v;par[i]!=i;i=par[i])
			path.push_back(i);
		path.push_back(u);
		for(i=path.size()-1;i>=0;i--)
			cout<<path[i]<<" ";
		cout<<"\n";
	}
}