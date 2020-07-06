//usage fft<type> f1; ntt n1(mod);
//for ntt use modulo stuff from math
//codeforces 754e for useful trick
template <typename T>
class fft {
	using cd = complex<double>;
	const double PI = acos(-1.0);
	int round_pow2(int n) {
		if (n & (n - 1)) {
			int pw = 1;
			while (pw < n)
				pw <<= 1;
			return pw;
		}
		return n;
	}
	void transform(vector <cd> &a, bool invert) {
		int n = a.size();
		for (int i = 1,j = 0; i < n; ++i){
			int bit = (n >> 1);
			for (; j & bit; bit >>= 1)
				j ^= bit;
			j ^= bit;
			if (i < j)
				swap(a[i], a[j]);
		}
		for (int len = 2; len <= n; len <<= 1) {
			double ang = 2 * PI / len * (invert? -1: 1);
			cd wlen(cos(ang), sin(ang));
			for (int i = 0; i < n; i+= len) {
				cd w(1);
				for (int j = 0; j < len / 2; ++j) {
					cd u = a[i + j], v = a[i + j + len / 2] * w;
					a[i + j] = u + v;
					a[i + j + len / 2] = u - v;
					w *= wlen;
				}
			}
		}
		if (invert) {
			for (auto &x : a)
				x /= n;
		}
	}
	void transform(vector <vector <cd> > &a, bool invert) {
		int n = a.size(), m = a[0].size();
		for (int i = 0; i < n; ++i)
			transform(a[i], invert);
		for (int j = 0; j < m; ++j) {
			vector <cd> b(n, 0);
			for (int i = 0; i < n; ++i)
				b[i] = a[i][j];			
			transform(b, invert);
			for(int i = 0; i < n; ++i)
				a[i][j] = b[i];
		}
	}
	public:
	vector <T> multiply(vector <T> &a, vector <T> &b) {
		int n = round_pow2(a.size() + b.size());
		bool eq = (a == b);
		vector <cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
		fa.resize(n);
		fb.resize(n);
		transform(fa, false);
		if(eq)
			fb = fa;
		else
			transform(fb, false);
		for (int i = 0; i < n; ++i)
			fa[i] *= fb[i];
		transform(fa, true);
		vector <T> result(n);
		for (int i = 0; i < n; ++i)
			result[i] = round(fa[i].real());
		while (n > 0 && result[n - 1] == 0)
			n--;
		result.resize(n);
		return result;
	}
	vector <vector <T> > multiply(vector <vector <T> > &a, vector <vector <T> > &b) {
		int n = round_pow2(a.size() + b.size());
		int m = round_pow2(a[0].size() + b[0].size());
		bool eq = (a == b);
		vector <vector <cd> > fa(a.begin(), a.end()), fb(b.begin(), b.end());
		fa.resize(n);
		fb.resize(n);
		for (auto &f : fa)
			f.resize(m);
		for (auto &f : fb)
			f.resize(m);
		transform(fa, false);
		if (eq)
			fb = fa;
		else
			transform(fb, false);
		for (int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				fa[i][j] *= fb[i][j];
		transform(fa, true);
		vector <vector <T> > result(n, vector <T>(m));
		int rn = 0,rm = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				result[i][j] = fa[i][j];
				if (result[i][j].real() != (0)) {
					rn = max(rn, i + 1);
					rm = max(rm, j + 1);
				}
			}
		}
		result.resize(rn);
		for (auto &f : result)
			f.resize(rm);
		return result;
	}
};

class ntt {
	int mod, proot, max_base, base;
	vector <int> roots = {0,1}, rev = {0,1};
	int round_pow2(int n) {
		while (n & (n - 1)) {
			n = (n | (n - 1)) + 1;
		}
		return n;
	}
	int find_primitive_root() {
		int i = 2,j = (1 << max_base),k = (1 << (max_base - 1));
		while (true) {
			if (pwr(i, j, mod) == 1) {
				if (pwr(i, k, mod) != 1) {
					return i;
				}
			}
			i++;
		}
		assert(false);
	}
	void ensure_base(int nbase) {
		if (nbase <= base)
			return;
		assert(nbase <= max_base);
		rev.resize(1 << nbase);
		for (int i = 0; i < (1 << nbase); ++i)
			rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
		roots.resize(1 << nbase);
		while (base < nbase) {
			int z = pwr(proot, 1 << (max_base - 1 - base), mod);
			for (int i = 1 <<(base - 1); i < (1 << base); ++i) {
				roots[i << 1] = roots[i];
				roots[(i << 1) + 1]= md(roots[i] * z, mod);
			}
			base++;
		}
	}
	void transform(vector<int> &a, bool invert) {
		int n = a.size();
		if (invert)
			reverse(a.begin() + 1,a.end());
		assert(n == round_pow2(n));
		int zeros = __builtin_ctz(n);
		ensure_base(zeros);
		int shift = base - zeros;
		for (int i = 0; i < n; ++i) {
			if (i < (rev[i] >> shift))
				swap(a[i], a[rev[i] >> shift]);
		}
		for (int i = 1; i < n; i<<= 1){
			for (int j = 0; j < n; j+= 2 * i){
				for (int k = 0; k < i; ++k){
					int even = a[j + k];
					int odd = md(a[i + j + k] * roots[i + k], mod);
					a[j + k] = md(even + odd, mod);
					a[i + j + k] = md(even - odd, mod);
				}
			}
		}
		if (invert) {
			int nrev = modinv(n, mod);
			for (int &x : a)
				x = md(x * nrev, mod);
		}
	}
	public:
	ntt(int _mod) {
		mod = _mod;
		max_base = 0;
		base = 1;
		int tot = mod - 1;
		while (tot % 2 == 0) {
			max_base++;
			tot/= 2;
		}
		proot = find_primitive_root();
	}
	vector <int> multiply(vector <int> &a, vector<int> &b) {
		int n = (int) (a.size() + b.size() - 1);
		int nbase = 0;
		while ((1 << nbase) < n) nbase++;
		ensure_base(nbase);
		int sz = 1 << nbase;
		a.resize(sz);
		b.resize(sz);
		bool eq = (a == b);
		transform(a,false);
		if(eq)
			b = a;
		else
			transform(b,false);
		for (int i = 0; i < sz; ++i)
			a[i] = md(a[i] * b[i], mod);
		transform(a, true);
		a.resize(n);
		return a;
	}
};

template <typename T, typename G>
vector <G> multiply_all(vector <vector <G> > &polys,T &trans){
	if (polys.empty())
		return {1};
	auto cmp = [&](vector <G> a,vector <G> b){
		return a.size() > b.size();
	};
	priority_queue <vector <G>, vector <vector <G> >, decltype(cmp)> pq(cmp);
	for (auto &p : polys)
		pq.push(p);
	while (pq.size() > 1) {
		auto a = pq.top();pq.pop();
		auto b = pq.top();pq.pop();
		pq.push(trans.multiply(a, b));
	}
	return pq.top();
}
template <typename T, typename G>
vector <G> poly_pow(vector<G> &poly, int n, T &trans){
	if(n == 0)
		return {1};
	if(n == 1)
		return poly;
	vector <G> x = poly_pow(poly, n/2, trans);
	x = trans.multiply(x, x);
	if (n & 1)
		x = trans.multiply(x, poly);
	return x;
}