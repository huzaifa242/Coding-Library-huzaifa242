//Usage pre_lca(root) for precomputation and lca(u,v) for LCA
//LCA O(1)
#define lgs 20
vector<int> adjlst[MAX],euler,depth;
int foc[MAX],lvl[MAX],par[MAX],ptr,min_sprs[MAX][lgs];
void lca_dfs(int x,int pr,int dep)
{
	lvl[x]=dep;
	par[x]=pr;
	if(foc[x]==-1)
	foc[x]=ptr;
	euler.push_back(x);
	depth.push_back(dep);
	ptr++;
	//cout<<x<<"$"<<par[x]<<" "<<lvl[x]<<"\n";
	for(int i=0;i<adjlst[x].size();i++)
	{
	    //cout<<adjlst[x][i]<<"#\n";
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
void bld_sprs(int n)
{
	memset(min_sprs,-1,sizeof(min_sprs));
	int i,j;
	for(i=1;i<n;i++)
	{
		min_sprs[i-1][0]=(depth[i]>depth[i-1])?i-1:i;
	}
	for(j=1;j<lgs;j++)
	{
		for(i=0;i<n;i++)
		{
			if(min_sprs[i][j-1]!=-1  && min_sprs[i+(1<<(j-1))][j-1]!=-1)
			{
				min_sprs[i][j]=
				(depth[min_sprs[i][j-1]] > depth[min_sprs[i+(1<<(j-1))][j-1]]) ? 
				min_sprs[i+(1<<(j-1))][j-1]: min_sprs[i][j-1];
			}
			else
			break;
			//cout<<min_sprs[i][j]<<" ";
		}
		//cout<<"\n";
	}
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
	for(i=0;i<euler.size();i++)
	cout<<euler[i]<<" ";
	cout<<"\n";
	cout<<"depth:\n";
	for(i=0;i<depth.size();i++)
	cout<<depth[i]<<" ";
	cout<<"\n";*/
	bld_sprs(depth.size());
}
int sprs_query(int l, int r)
{
	long long int i=log2(r-l);
	if(l==r)
	return l;
	if(depth[min_sprs[l][i]]> depth[min_sprs[r-(1<<i)][i]])
	return min_sprs[r-(1<<i)][i];
	else
	return min_sprs[l][i];
}
int lca(int u, int v)
{
	if(u==v)
	return u;
	else if(foc[u]>foc[v])
	swap(u,v);
	return euler[sprs_query(foc[u],foc[v])];
}