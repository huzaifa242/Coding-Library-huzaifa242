//Disjoint Set Union
// DON'T FORGET TO INITIALIZE PARENT
/*Find parent is post order. i.e. first  reaches
  representative element, then it takes the value
  and while returning it updates corresponding children
  1->2->3->4->5     first it reaches 5 then updates par[4]=5
  then updates par[3]=par[4](which is now 5)*/
long long int dsu[MAX],sz[MAX],connected;
void clr_dsu(int n)
{
	for(int i=0;i<MAX;i++)
	{
		dsu[i]=i;
		sz[i]=0;
	}
	connected=n;
}
void find_par(long long int k)
{
	if(dsu[dsu[k]]==k)//reached representative element now update will start
	return;
	find_par(dsu[k]);// grandparent update. Parent is not
	// Condition for Grandparent updated and not parent
	dsu[k]=dsu[dsu[k]];//Parent Updated
	// Condition when parent is Updated
}
// For each Query peform find_par(u),find_par[v]
void union_all(long long int u, long long int v)
{
	find_par(u);
	find_par(v);
	if(dsu[u]!=dsu[v])
	{
		connected--;
		sz[dsu[u]]+=sz[dsu[dsu[v]]];
		sz[dsu[dsu[v]]]=0;
	}
	dsu[dsu[v]]=dsu[u];
}
