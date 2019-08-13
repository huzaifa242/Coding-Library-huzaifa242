class Matrix
{
	public:
	int n,m;
	vector<vector<int> > a;
	
	Matrix(int sz)
	{
		n=sz;m=sz;
		a.assign(n,vector<int>(m,0));
	}
	Matrix(int _n,int _m)
	{
		n=_n;m=_m;
		a.assign(n,vector<int>(m,0));
	}
	Matrix operator*(Matrix b)
	{
		Matrix c(n,b.m);
		if(m!=b.n)
			return c;
		int i,j,k;
		for(i=0;i<n;i++)
		for(j=0;j<m;j++)
		for(k=0;k<b.m;k++)
			c.a[i][j]=md(c.a[i][j] + md(a[i][k]*b.a[k][j]));
		return c;
	}
	void prt()
	{
		for(auto i:a)
		{
			for(auto j:i)
				cout<<j<<" ";
			cout<<'\n';
		}
	}
};

Matrix matxpo(Matrix &a, int n)
{
	if(n==0)
	{
		Matrix b(a.n);
		int i;
		for(i=0;i<b.n;i++)
			b.a[i][i]=1;
		return b;
	}
	else if(n==1)
		return a;
	Matrix x=matxpo(a,n/2);
	x=(x*x);
	if(n&1)
		x=(x*a);
	return x;
}

//determinant from cp-algos/determinant-gauss

int determinant(Matrix a)
{
	long double eps=1e-9;
	int dt=1;
	int i,j,k;
	for(i=0;i<a.n;i++)
	{
		k=i;
		for(j=i+1;j<a.n;j++)
		if(abs(a.a[j][i])>abs(a.a[k][i]))
		k=j;
		if(a.a[k][i]==0)//use a.a[k][i]<eps
			return 0;
		swap(a.a[i],a.a[k]);
		if(i!=k)
			dt=md(-dt);
		dt=md(dt*a.a[i][i]);
		for(j=i+1;j<a.n;j++)
			a.a[i][j]=md(a.a[i][j]*modinv(a.a[i][i]));
		for(j=0;j<a.n;j++)
			if(j!=i && abs(a.a[j][i]))//use abs(a.a[j][i])>eps
				for(k=i+1;k<a.n;k++)
				a.a[j][k]=md(a.a[j][k]- md(a.a[i][k] * a.a[j][i]));
	}
	// a.prt();
	return dt;
}