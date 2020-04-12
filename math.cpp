const long double PI=acos(-1.0);
//Mod function
//Multiply large Number num>=1e9 use Modulo
//Power Function A raised to B use modulo
//Modulo Inverse use modulo
const int mod = 1000000007;
int md(int x,int mdo=mod){
	while(x<0)
		x+=mdo;
	return x%mdo;
}
int multi(int a, int b, int mdo=mod){
	int pro=0;
	a=md(a,mdo);
	while(b){
		if(b&1)
			pro=md(md(pro,mdo)+md(a,mdo),mdo);
		a=md(a*2,mdo);
		b>>=1;
	}
	return pro;
}
int pwr(int a,int n,int mdo=mod){
	if(n==0)
		return md(1,mdo);
	else if(n==1)
		return md(a,mdo);
	int x=pwr(a,n/2,mdo);
	if(max(x,md(a,mdo))< int(1e9))
		x=md(x*x,mdo);
	else
		x=md(multi(x,x,mdo),mdo);
	if(n&1){
		if(max(x,md(a,mdo))< int(1e9))
			x=md(x*md(a,mdo),mdo);
		else
			x=md(multi(x,md(a,mdo),mdo),mdo);
	}
	return x;
}
int ge(int a, int b, int *x, int *y){
	if (a == 0){
		*x = 0, *y = 1;
		return b;
	}
	int x1, y1;
	int gcd = ge(b%a, a, &x1, &y1);
	*x = y1 - (b/a) * x1;
	*y = x1;
	return gcd;
}
int  modinv(int a, int m=mod){
	int x, y;
	int g = ge(a, m, &x, &y);
	int p = (x%m + m) % m;
	return p;
}
// nCr factorial needs Modulo
vector<int> fct(MAX),ifct(MAX);
void ncomr(){
	int i;
	fct[0]=1;
	for(i=1;i<MAX;i++){
		fct[i]=md(fct[i-1]*i);
	}
	ifct[MAX-1]=modinv(fct[MAX-1]);
	for(i=MAX-1;i>0;i--){
		ifct[i-1]=md(ifct[i]*i);
	}
}
int ncr(int n, int r){
	if(n<0 || r<0 || n<r)
		return 0;
	return md(fct[n]*md(ifct[r]*ifct[n-r]));
}
//Prime Factor Generator
vector<vector<int> > prmfct(MAX);
void prmfactgenerator(){
	int i,j;
	for(i=2;i<MAX;i++){
		if(!prmfct[i].size()){
			for(j=i;j<MAX;j+=i)
				prmfct[j].push_back(i);
		}
		// cout<<i<<": ";
		// cout<<prmfct[i];
	}
}
//Linear Sieve to get all prime Numbers
//prime contains all prime number [2,MAX)
//isprime[x] has the smallest prime divisor of x 
vector<int> prime,isprime;
void sieve(int n){
	isprime.resize(n,0);
	int i,j;
	for(i=2;i<n;i++){
		if(isprime[i]==0){
			prime.push_back(i);
			isprime[i]=i;
		}
		for(j=0;j<(int)prime.size() && i*prime[j]<n;j++){
			isprime[prime[j]*i]=prime[j];
			if(i%prime[j] ==0)
				break;
		}
	}
}
//nCr Matrix use modulo
int ncr[MAX][MAX];
void ncomr(){
	int i,j;
	for(i=0;i<MAX;i++){
		for(j=0;j<=i;j++){
			if(j==0||j==i)
				ncr[i][j]=1;
			else
				ncr[i][j]=md(ncr[i-1][j-1]+ncr[i-1][j]);
		}
	}
}
//Primality Test take power Funtion
//needs pwr(a,n),multi(a,b) and sieve()
bool miller(int d,int n){
	int a = rnd(1LL,n);
	int x=pwr(a,d,n); 
	if(x==1LL || x==n-1LL) 
	   return true; 
	while(d!=n-1LL){ 
		x=multi(x,x,n); 
		d*=2LL; 
		if(x==1LL)
			return false; 
		if(x==n-1LL)
			return true; 
	} 
	return false; 
}
bool prime_chk(int n){
	if(n<MAX)
		return isprime[n]==n;
	if(n%3LL==0||n%5LL==0||n%2LL==0)
		return false;
	int pp2=n-1LL;
	while(pp2%2LL==0)
		pp2/=2LL;
	for(int i=0;i<4;i++)
		if(!miller(pp2,n))
			return false;
	return true;
}
//Count all Divisors of n O(n^(1/3))
//needs prime_chk and miller
int count_div(int n){
	int sm=1,i;
	int nn=n,p2=1;
	for(i=0;i<prime.size();i++){
		int p=prime[i];
		if(p*p*p > n)
			break;
		int t=1;
		while(n%p==0){
			n/=p;
			t++;
		}
		sm*=t;
	}
	int sq=sqrt(n);
	if(prime_chk(n))
		sm*=2LL;
	else if(sq*sq==n && prime_chk(sq))
		sm*=3LL;
	else if(n!=1)
		sm*=4LL;
	return sm;
}