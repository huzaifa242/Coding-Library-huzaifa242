//Usage pre_lca(root) for precomputation and lca(u,v) for LCA
//LCA O(1)
#define lgs 20
vector<int> adjlst[MAX],euler,depth;
int foc[MAX],lvl[MAX],par[MAX],ptr;
class sparse_table
{
	private:
	vector<vector<int> > sprs;
	int n;
	public:
	sparse_table()
	{}
	sparse_table(int size)
	{
		n=size;
		sprs.assign(n,vector<int>(lgs,-1));
	}
	void setsize(int size)
	{
		n=size;
		sprs.assign(n,vector<int>(lgs,-1));
	}
	void build()
	{
		int i,j;
		for(i=0;i<n;i++)
		sprs[i][0]=i;
		for(j=1;j<lgs;j++)
		{
			for(i=0;i+(1<<j)<=n;i++)
			{
				int u=sprs[i][j-1],v=sprs[i+(1<<(j-1))][j-1];
				sprs[i][j]=(depth[u]>depth[v]?v:u);
			}
		}
	}
	int query(int l, int r)
	{
		int i=log2(r-l+1),j;
		int u=sprs[l][i];
		int v=sprs[r-(1<<i)+1][i];
		return (depth[u]>depth[v]?v:u);
	}
} bld_sprs;

void lca_dfs(int x,int pr,int dep)
{
	lvl[x]=dep;
	par[x]=pr;
	if(foc[x]==-1)
	foc[x]=ptr;
	euler.push_back(x);
	depth.push_back(dep);
	ptr++;
	for(int i=0;i<adjlst[x].size();i++)
	{
		if(pr!=adjlst[x][i])
		{
			lca_dfs(adjlst[x][i],x,dep+1);
			euler.push_back(x);
			depth.push_back(dep);
			ptr++;
		}
	}
	return;
}
void pre_lca(int root)
{
	int i,j;
	ptr=0;
	memset(foc,-1,sizeof(foc));
	lca_dfs(root,root,0);
	/*cout<<"foc:\n";
	for(i=1;i<=n;i++)
	cout<<foc[i]<<" ";
	cout<<"\n";
	cout<<"euler:\n";
	cout<<euler<<endl;
	cout<<"depth:\n";
	cout<<depth<<endl;*/
	bld_sprs.setsize(depth.size());
	bld_sprs.build();
}
int lca(int u, int v)
{
	if(u==v)
	return u;
	else if(foc[u]>foc[v])
	swap(u,v);
	return euler[bld_sprs.query(foc[u],foc[v])];
}
int dist(int u,int v)
{
	return lvl[u]+lvl[v]-2*lvl[lca(u,v)];
}