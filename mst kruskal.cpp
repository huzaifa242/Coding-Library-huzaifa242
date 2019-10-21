//Usage kruskal(). mst holds new tree
// adjlst stores <weight,node>
struct edg{
	int u,v,w,id;
}edglst[MAX];
vector<pair<int,int> > adjlst[MAX],mst[MAX];
int n,m;
//Class DSU here
int krushkal(){
	dsu d1(n);
	int sm=0;
	sort(edglst,edglst+m,[&](edg a,edg b){return a.w<b.w;});
	for(int i=0;i<m;i++){
		int u=edglst[i].u,v=edglst[i].v;
		if(d1.get_par(u)!=d1.get_par(v)){
			sm+=edglst[i].w;
			mst[u].push_back({edglst[i].w,v});
			mst[v].push_back({edglst[i].w,u});
			d1.union_all(u,v);
		}
	}
	return sm;
}