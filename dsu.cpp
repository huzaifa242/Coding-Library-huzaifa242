//Disjoint Set Union
// DON'T FORGET TO INITIALIZE PARENT
/*Find parent is post order. i.e. first  reaches
  representative element, then it takes the value
  and while returning it updates corresponding children
  1->2->3->4->5     first it reaches 5 then updates par[4]=5
  then updates par[3]=par[4](which is now 5)*/
long long int par[MAX],sz[MAX],connected;
void clr_dsu(int n)
{
	for(int i=0;i<MAX;i++)
	{
		par[i]=i;
		sz[i]=0;
	}
	connected=n;
}
void find_par(long long int k)
{
	if(par[par[k]]==k)//reached representative element now update will start
	return;
	find_par(par[k]);// grandparent update. Parent is not
	// Condition for Grandparent updated and not parent
	par[k]=par[par[k]];//Parent Updated
	// Condition when parent is Updated
}
// For each Query peform find_par(u),find_par[v]
void union_all(long long int u, long long int v)
{
	find_par(u);
	find_par(v);
	if(par[u]!=par[v])
	{
		connected--;
		sz[par[u]]+=sz[par[par[v]]];
		sz[par[par[v]]]=0;
	}
	par[par[v]]=par[u];
}
