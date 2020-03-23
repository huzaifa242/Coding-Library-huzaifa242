//Usage pre_lca(root) for precomputation and lca(u,v) for LCA
//LCA O(1)
#define lgs 20
vector<vector<int> > adjlst;
vector<int> euler,depth,foc,lvl,par;
int ptr,n;
class sparse_table{
	private:
	vector<vector<int> > sprs;
	int n;
	int merge(int u, int v){
		return depth[u]>depth[v]?v:u;
	}
	public:
	sparse_table(){}
	sparse_table(int size){
		n=size;
		sprs.assign(n,vector<int>(lgs,-1));
	}
	void setsize(int size){
		n=size;
		sprs.assign(n,vector<int>(lgs,-1));
	}
	void build(){
		int i,j;
		for(i=0;i<n;i++)
		sprs[i][0]=i;
		for(j=1;j<lgs;j++){
			for(i=0;i+(1<<j)<=n;i++){
				sprs[i][j]=merge(sprs[i][j-1],sprs[i+(1<<(j-1))][j-1]);
			}
		}
	}
	int query(int l, int r){
		int i=log2(r-l+1),j;
		return merge(sprs[l][i], sprs[r-(1<<i)+1][i]);
	}
} bld_sprs;

void lca_dfs(int u,int p,int lv){
	lvl[u]=lv;
	par[u]=p;
	if(foc[u]==-1)
		foc[u]=ptr;
	euler.push_back(u);
	depth.push_back(lv);
	ptr++;
	for(auto &v:adjlst[u]){
		if(p==v)
			continue;
		lca_dfs(v,u,lv+1);
		euler.push_back(u);
		depth.push_back(lv);
		ptr++;
	}
	return;
}
void pre_lca(int root){
	ptr=0;
	foc.assign(n+1,-1);
	lvl.resize(n+1);
	par.resize(n+1);
	euler.clear();
	depth.clear();
	lca_dfs(root,root,0);
	bld_sprs.setsize(depth.size());
	bld_sprs.build();
}
int lca(int u, int v){
	if(u==v)
		return u;
	else if(foc[u]>foc[v])
		swap(u,v);
	return euler[bld_sprs.query(foc[u],foc[v])];
}
int dist(int u,int v){
	return lvl[u]+lvl[v]-2*lvl[lca(u,v)];
}