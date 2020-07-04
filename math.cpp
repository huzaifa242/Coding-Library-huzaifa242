const long double PI = acos(-1.0);
/**
 * Mod function
 * Multiply large Number num>=1e9 use Modulo
 * Power Function A raised to B use modulo
 * Modulo Inverse use modulo
 */
const int mod = 998244353;
int md(int x, int mdo = mod) {
	x %= mdo;
	return x < 0? x + mdo: x;
}
int multi(int a, int b, int mdo = mod) {
	int pro = 0;
	a = md(a, mdo);
	while (b) {
		if (b & 1)
			pro = md(md(pro, mdo) + md(a, mdo), mdo);
		a = md(a * 2, mdo);
		b >>= 1;
	}
	return pro;
}
int pwr(int a, int n, int mdo = mod) {
	if (n == 0)
		return md(1, mdo);
	else if (n == 1)
		return md(a, mdo);
	int x = pwr(a, n / 2, mdo);
	if (max(x, md(a, mdo)) < int(1e9))
		x = md(x * x, mdo);
	else
		x = md(multi(x, x, mdo), mdo);
	if (n & 1) {
		if (max(x, md(a, mdo)) < int(1e9))
			x = md(x * md(a, mdo), mdo);
		else
			x = md(multi(x, md(a, mdo), mdo), mdo);
	}
	return x;
}
// ge can solve ax + by = gcd(a,b)
int ge(int a, int b, int *x, int *y){
	if (a == 0) {
		*x = 0, *y = 1;
		return b;
	}
	int x1, y1;
	int gcd = ge(b % a, a, &x1, &y1);
	*x = y1 - (b / a) * x1;
	*y = x1;
	return gcd;
}
int  modinv(int a, int m = mod){
	int x, y;
	int g = ge(a, m, &x, &y);
	// if g!=1 modinv doesn't exist;
	assert(g == 1);
	int p = (x % m + m) % m;
	return p;
}
// factorial precalc needs modulo
vector <int> fct, ifct;
void factorials(int n) {
	fct.resize(n + 1);
	ifct.resize(n + 1);
	fct[0] = 1;
	for (int i = 1; i <= n; ++i)
		fct[i] = md(fct[i - 1] * i);
	ifct[n] = modinv(fct[n]);
	for (int i = n; i > 0; --i)
		ifct[i - 1] = md(ifct[i] * i);
}
// nCr factorial needs factorials
int ncr(int n, int r) {
	if(n < 0 || r <0  || n < r)
		return 0;
	return md(fct[n] * md(ifct[r] * i fct[n - r]));
}
//Prime Factor Generator
vector <vector <int> > prmfct;
void prmfactgenerator(int n) {
	prmfct.clear();
	prmfct.resize(n + 1);
	for (int i = 2; i <= n; ++i) {
		if (!prmfct[i].size()) {
			for (int j = i; j <= n; j += i)
				prmfct[j].push_back(i);
		}
		debug(i,prmfct[i]);
	}
}
/**
 * Linear Sieve to get all prime Numbers
 * prime contains all prime number [2,MAX)
 * isprime[x] has the smallest prime divisor of x 
 */
vector <int> prime, isprime;
void sieve(int n) {
	isprime.resize(n, 0);
	for (int i = 2; i < n; ++i) {
		if (isprime[i] == 0) {
			prime.push_back(i);
			isprime[i] = i;
		}
		for (int j = 0; j < (int)prime.size() && i * prime[j] < n; ++j) {
			isprime[prime[j] * i] = prime[j];
			if(i % prime[j] == 0)
				break;
		}
	}
}
//nCr Matrix use modulo
int ncr[MAX][MAX];
void ncomr() {
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (j == 0 || j == i)
				ncr[i][j] = 1;
			else
				ncr[i][j] = md(ncr[i - 1][j - 1] + ncr[i - 1][j]);
		}
	}
}
//Primality Test take power Funtion
//needs pwr(a,n),multi(a,b) and sieve()
bool miller(int d, int n) {
	int a = rnd(1, n);
	int x = pwr(a, d, n); 
	if (x == 1 || x == n - 1) 
	   return true; 
	while (d != n - 1) { 
		x = multi(x, x, n); 
		d*= 2; 
		if (x == 1)
			return false; 
		if (x == n - 1)
			return true; 
	} 
	return false; 
}
bool prime_chk(int n) {
	if (n < MAX)
		return isprime[n] == n;
	if (n % 3 == 0 || n % 5 == 0 || n % 2 == 0)
		return false;
	int pp2 = n - 1;
	while (pp2 % 2 == 0)
		pp2/= 2;
	for (int i = 0; i < 4; ++i)
		if (!miller(pp2,n))
			return false;
	return true;
}
//Count all Divisors of n O(n^(1/3))
//needs prime_chk and miller
int count_div(int n) {
	int sm = 1;
	int nn = n, p2 = 1;
	for(int i = 0; i < prime.size(); ++i){
		int p = prime[i];
		if (p * p * p > n)
			break;
		int t = 1;
		while (n % p == 0) {
			n/= p;
			t++;
		}
		sm *= t;
	}
	int sq = sqrt(n);
	if (prime_chk(n))
		sm *= 2;
	else if (sq * sq == n && prime_chk(sq))
		sm *= 3;
	else if (n != 1)
		sm *= 4;
	return sm;
}
/**
 * Lagrange Interpolation requires factorials()
 * works in O(n) for f(x) = y such that x = 1, 2, 3, ....
 * Also try to keep size of given values more than 2 or 3
 * handle x = 0 case seprately even though values.size() > 0 
 * if x != 1, 2, 3, ... use below formulae
 * y=f(x) y0,y1,..yn and x0,x1,..xn
 * f(x) = (x-x2)(x-x3)..(x-xn)*y1/(x1-x2)(x1-x3)..(x1-xn) +
 * (x-x1)(x-x3)..(x-xn)*y2/(x2-x1)(x2-x3)..(x2-xn)+ ....
 * upto n terms.
 */
int lagrange_polynomial(vector <int> &value, int k) {
	int n = value.size();
	if (k < n)
		return value[k];
	factorials(n);
	int numerator = 1;
	for (int i = 0; i < n; ++i) 
		numerator = md(numerator * md(k - i));
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		int denominator = md(modinv(md(k - i)) * md(ifct[i] * ifct[n - 1 - i]));
		int coefficient = md(numerator * denominator);
		if ((n - i)&1)
			ans = md(ans + md(coefficient * value[i]));
		else
			ans = md(ans - md(coefficient * value[i]));
	}
	return ans;
}