#define PI 3.1415926535897932384626
#define mod 1000000007
//Mod function
int md(int x)
{
	while(x<0)
	x+=mod;
	return x%mod;
}
//Multiply large Number num>=1e9 use Modulo
int multi(int a, int b)
{
	int pro=0;
	a=md(a);
	while(b)
	{
		if(b&1)
		pro=md(md(pro)+md(a));
		a=md(a*2);
		b>>=1;
	}
	return pro;
}
//Power Function A raised to B use modulo
int pwr(int a,int n)
{
	if(n==0)
	return 1;
	else if(n==1)
	return a;
	else if(n&1)
	{
		int x=pwr(a,n/2);
		if(x<mod)
		return md(md(md(x)*md(x))*a);
		else
		return md(multi(md(multi(x,x)),a));
	}
	else
	{
		int x=pwr(a,n/2);
		if(x<mod)
		return md(md(md(x)*md(x))*1);
		else
		return md(multi(md(multi(x,x)),1));
	}
}
//Modulo Inverse use modulo
int ge(int a, int b, int *x, int *y)
{
	if (a == 0)
	{
		*x = 0, *y = 1;
		return b;
	}
	int x1, y1;
	int gcd = ge(b%a, a, &x1, &y1);
	*x = y1 - (b/a) * x1;
	*y = x1;
	return gcd;
}
int  modinv(int a, int m=mod)
{
	int x, y;
	int g = ge(a, m, &x, &y);
	int p = (x%m + m) % m;
	return p;
}
//Prime Factor Generator
vector <int> prmfct[MAX];
void prmfactgenerator()
{
	int i,j;
	for(i=2;i<MAX;i++)
	{
		if(!prmfct[i].size())
		{
			for(j=i;j<MAX;j+=i)
			prmfct[j].push_back(i);
		}
		/*cout<<i<<"#"<<endl;
		for(j=0;j<prmfct[i].size();j++)
		cout<<prmfct[i][j]<<" ";
		cout<<endl;*/
	}
}
//Linear Sieve to get all prime Numbers
bool isprime;
vector<int> prime;
void sieve()
{
	memset(isprime,true,sizeof(isprime));
	int i,j;
	for(i=2;i<MAX;i++)
	{
		if(isprime[i])
		prime.push_back(i);
		for(j=0;j<(int)prime.size() && i*prime[j]<MAX;j++)
		{
			isprime[prime[j]*i]=false;
			if(i%prime[j] ==0)
			break;
		}
	}
}
//Matrix Exponentation mat=2*2 use modulo
void multex(int a[2][2],int c[2][2])
{
	int i,j,k,b[2][2]={0};
	for(i=0;i<2;i++)
	for(j=0;j<2;j++)
	for(k=0;k<2;k++)
	{
		b[i][j]+=md(a[i][k]*c[k][j]);
		b[i][j]=md(b[i][j]);
	}
	for(i=0;i<2;i++)
	for(j=0;j<2;j++)
	a[i][j]=b[i][j];
}
void matexp(int a[2][2],int ans[2][2],int s)
{
	int i,j;
	if(s==1)
	{
		ans[0][0]=a[0][0];
		ans[0][1]=a[0][1];
		ans[1][0]=a[1][0];
		ans[1][1]=a[1][1];
	}
	else if(s%2)
	{
		matexp(a,ans,s/2);
		multex(ans,ans);
		multex(ans,a);
	}
	else
	{
		matexp(a,ans,s/2);
		multex(ans,ans);
	}
}
//nCr Matrix use modulo
int ncr[MAX][MAX];
void ncomr()
{
	int i,j;
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<=i;j++)
		{
			if(j==0||j==i)
			ncr[i][j]=1;
			else
			ncr[i][j]=md(ncr[i-1][j-1]+ncr[i-1][j]);
		}
	}
}
