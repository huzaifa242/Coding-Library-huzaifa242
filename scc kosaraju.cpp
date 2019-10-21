//Usage kosaraju().
//compo[i] in Kosaraju = compo[lb-i+1] in tarjan 
//lbl[i] has label of each node
//compo[i] has all the node that are strongly connected
vector<int> adjlst[MAX],iadj[MAX],compo[MAX],vis,lbl;
int n,m;
stack<int> scc;
void st_dfs(int u, int p){
	vis[u]=1;
	for(auto v:adjlst[u]){
		if(vis[v])
			continue;
		st_dfs(v,u);
	}
	scc.push(u);
}
void i_graph(){
	for(int i=1;i<=n;i++){
		for(auto j:adjlst[i])
		iadj[j].push_back(i);
	}
}
void scc_dfs(int u,int p, int lb){
	vis[u]=1;
	compo[lb].push_back(u);
	lbl[u]=lb;
	for(auto v:iadj[u]){
		if(!vis[v])
		scc_dfs(v,u,lb);
	}
}
int kosaraju(){
	int ptr=0;
	vis.assign(n+1,0);
	lbl.assign(n+1,0);
	while(!scc.empty())
	scc.pop();
	for(int i=0;i<=n;i++){
		iadj[i].clear();
		compo[i].clear();
	}
	for(int i=1;i<=n;i++){
		if(!vis[i])
		st_dfs(i,0);
	}
	i_graph();
	vis.assign(n+1,0);
	while(!scc.empty()){
		auto u=scc.top();
		scc.pop();
		if(!vis[u]){
			scc_dfs(u,0,++ptr);
		}
	}
	return ptr;
}