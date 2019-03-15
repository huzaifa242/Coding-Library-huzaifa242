//Usage lis(); 
int a[MAX],ls[MAX],n;
int repl_pos(int l,int r,int x)
{
	int ans=r,m;
	while(l<=r)
	{
		m=(l+r)/2;
		if(ls[m]>=x)
		{
			r=m-1;
			ans=m;
		}
		else
		l=m+1;
	}
	return ans;
}
int lis()
{
	memset(ls,0,sizeof(ls));
	int i,lisp=1;
	ls[0]=a[0];
	for(i=1;i<n;i++)
	{
		if(a[i]>ls[lisp-1])//for repeated allowed change here
		ls[lisp++]=a[i];
		else
		ls[repl_pos(0,lisp-1,a[i])]=a[i];
	}
	return lisp;
}