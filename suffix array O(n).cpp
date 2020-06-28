/**
 * Usage suffix_array s1(string)
 * s1.sufar[] is suffix array
 * s1.lcp is lcp array
 */
class suffix_array {
	//DC3 Credits:algo2.iti.kit.edu/documents/jacm05-revised.pdf
	static bool leq(int a1, int a2, int b1, int b2) {
		return (a1 < b1) || (a1 == b1 && a2 <= b2);
	}
	static bool leq(int a1, int a2, int a3, int b1, int b2, int b3) {
		return (a1 < b1) || (a1 == b1 && leq(a2, a3, b2, b3));
	}
	static void radix(auto a, auto b, auto r, int n, int k) {
		vector <int> cnt(k + 1, 0);
		for(int i = 0; i < n; ++i)
			cnt[r[a[i]]]++;
		for(int i = 1; i <= k; ++i)
			cnt[i] += cnt[i - 1];
		for(int i = n - 1; i >= 0; --i)
			b[--cnt[r[a[i]]]]=a[i];
	}
	static void dc3(auto s, auto sa, int n, int k) {
		int n0 = (n + 2) / 3, n1 = (n + 1) / 3, n2 = n / 3, n02 = n0 + n2;
		vector <int> s12(n02 + 3), sa12(n02 + 3), s0(n0), sa0(n0);
		s12[n02] = s12[n02 + 1] = s12[n02 + 2] = 0;
		sa12[n02] = sa12[n02 + 1] = sa12[n02 + 2] = 0;
		for (int i = 0,j = 0; i < n + n0 - n1; ++i)
			if (i % 3 != 0)
				s12[j++] = i;
		radix(s12.begin(), sa12.begin(), s + 2, n02, k);
		radix(sa12.begin(), s12.begin(), s + 1, n02, k);
		radix(s12.begin(), sa12.begin(), s, n02, k);
		int name = 0, c0 = -1, c1 = -1, c2 = -1;
		for (int i = 0; i < n02; ++i) {
			if (s[sa12[i]] != c0 || s[sa12[i] + 1] != c1 || s[sa12[i] + 2] != c2) {
				name++;
				c0 = s[sa12[i]];
				c1 = s[sa12[i] + 1];
				c2 = s[sa12[i] + 2];
			}
			(sa12[i] % 3 == 1? s12[sa12[i] / 3]: s12[sa12[i] / 3 + n0]) = name;
		}
		if (name < n02) {
			dc3(s12.begin(), sa12.begin(), n02, name);
			for (int i = 0; i < n02; ++i)
				s12[sa12[i]] = i + 1;
		} else {
			for (int i = 0; i < n02; ++i)
				sa12[s12[i] - 1] = i;
		}
		for (int i = 0, j = 0; i < n02; ++i)
			if (sa12[i] < n0)
				s0[j++] = 3 * sa12[i];
		radix(s0.begin(), sa0.begin(), s, n0, k);
		for(int p = 0, t = n0 - n1, u = 0; u < n; ++u) {
			int i = (sa12[t] < n0)? 3 * sa12[t] + 1: 3 * (sa12[t] - n0) + 2, j = sa0[p];
			if (sa12[t] < n0? leq(s[i], s12[sa12[t] + n0], s[j], s12[j / 3])
				: leq(s[i], s[i + 1], s12[sa12[t] - n0 + 1], s[j],
					s[j + 1], s12[j / 3 + n0])) {
				sa[u] = i;
				if (++t == n02)
					for (u++; p < n0; ++p,++u)
						sa[u] = sa0[p];
			} else {
				sa[u] = j;
				if (++p == n0)
					for (u++; t < n02; ++t,++u)
						sa[u] = (sa12[t] < n0)? 3 * sa12[t] + 1: 3 * (sa12[t] - n0) + 2;
			}
		}
	}
	void gen_lcp() {
		int n = s.size();
		vector <int> rank(n);
		for (int i = 0; i < n; ++i)
			rank[sufar[i]] = i;
		for (int i = 0, k = 0; i < n; ++i) {
			if (rank[i] < n - 1) {
				int j = sufar[rank[i] + 1];
				while (max(i, j) + k < n && s[i + k] == s[j + k])
					k++;
				lcp[rank[i]] = k;
				if (k > 0)
					k--;
			}
		}
	}
	public:
	string s;
	vector <int> sufar,lcp;
	suffix_array(string &s):s(s), sufar(s.size() + 1) {
		int n = s.size();
		vector <int> scopy(s.begin(), s.end());
		scopy.resize(n + 3);
		dc3(scopy.begin(), sufar.begin(), n + 1, 255);
		sufar.erase(sufar.begin());
		lcp.resize(n - 1);
		gen_lcp();
	}
};