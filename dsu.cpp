//Disjoint Set Union
// DON'T FORGET TO INITIALIZE PARENT
// in union_all(u,v) v is joined into u.
/*Find parent is post order. i.e. first  reaches
  representative element, then it taues the value
  and while returning it updates corresponding children
  1->2->3->4->5     first it reaches 5 then updates par[4]=5
  then updates par[3]=par[4](which is now 5)*/
void find_par(int u)
{
	if(par[par[u]]==u)//reached representative element now update will start
	return;
	find_par(par[u]);// grandparent update. Parent is not
	// Condition for Grandparent updated and not parent
	par[u]=par[par[u]];//Parent Updated
	// Condition when parent is Updated
}
class dsu
{
	private:
	int par[MAX],sz[MAX];
	void find_par(int u)
	{
		if(par[par[u]]==u)
		return;
		find_par(par[u]);
		par[u]=par[par[u]];
	}
	public:
	int connected;
	dsu(){}
	dsu(int n)
	{
		for(int i=0;i<=n;i++)
		{
			par[i]=i;
			sz[i]=0;
		}
		connected=n;
	}
	int get_par(int u)
	{
		find_par(u);
		return par[u];
	}
	int get_size(int u)
	{
		return sz[get_par(u)];
	}
	void union_all(int u, int v)
	{
		if(get_par(u)!=get_par(v))
		{
			connected--;
			sz[par[u]]+=sz[par[par[v]]];
			sz[par[par[v]]]=0;
		}
		par[par[v]]=par[u];
	}
}
