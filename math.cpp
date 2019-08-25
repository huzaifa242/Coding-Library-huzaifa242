const long double PI=acos(-1.0);
#define mod 1000000007
//Mod function
int md(int x,int mdo=mod)
{
	while(x<0)
	x+=mdo;
	return x%mdo;
}
//Multiply large Number num>=1e9 use Modulo
int multi(int a, int b, int mdo=mod)
{
	int pro=0;
	a=md(a,mdo);
	while(b)
	{
		if(b&1)
		pro=md(md(pro,mdo)+md(a,mdo),mdo);
		a=md(a*2,mdo);
		b>>=1;
	}
	return pro;
}
//Power Function A raised to B use modulo
int pwr(int a,int n,int mdo=mod)
{
	if(n==0)
	return 1;
	else if(n==1)
	return md(a,mdo);
	else if(n&1)
	{
		int x=pwr(a,n/2,mdo);
		if(x<mdo)
		return md(md(md(x,mdo)*md(x,mdo),mdo)*a,mdo);
		else
		return md(multi(md(multi(x,x,mdo),mdo),a,mdo),mdo);
	}
	else
	{
		int x=pwr(a,n/2,mdo);
		if(x<mdo)
		return md(md(md(x,mdo)*md(x,mdo),mdo)*1,mdo);
		else
		return md(multi(md(multi(x,x,mdo),mdo),1,mdo),mdo);
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
//prime contains all prime number [2,MAX)
//isprime[x] has the smallest prime divisor of x 
int isprime[MAX];
vector<int> prime;
void sieve()
{
	memset(isprime,0,sizeof(isprime));
	int i,j;
	for(i=2;i<MAX;i++)
	{
		if(isprime[i]==0)
		{
			prime.push_back(i);
			isprime[i]=i;
		}
		for(j=0;j<(int)prime.size() && i*prime[j]<MAX;j++)
		{
			isprime[prime[j]*i]=prime[j];
			if(i%prime[j] ==0)
			break;
		}
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
//Primality Test take power Funtion
bool miller(int d,int n)
{
	int a = 2 + rand() % (n - 4);
	int x=pwr(a,d,n); 
	if(x==1 || x==n-1) 
	   return true; 
	while(d!=n-1) 
	{ 
		x=(x*x)%n; 
		d*=2; 
		if(x==1)
			return false; 
		if(x==n-1)
			return true; 
	} 
	return false; 
}

bool prime_chk(int n)
{
	if(n<MAX)
		return isprime[n]==n;
	int pp2=n-1;
	while(pp2%2==0)
		pp2/=2;
	for(int i=0;i<20;i++)
		if(!miller(pp2,n))
			return false;
	return true;
}