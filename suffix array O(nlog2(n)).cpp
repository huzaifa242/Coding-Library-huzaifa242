/**
 * Usage suffix_array s1(string)
 * s1.sufar[] is suffix array
 * s1.lcp(i,j) returns lcp of s[u..n-1] ans s[v..n-1]
 */
class suffix_array {
	struct info {
		int f, s, id;
		bool operator < (info &a) const {
			return (f == a.f)? (s == a.s)? id < a.id: s < a.s: f < a.f;
		}
	};
	vector <vector <int> > p;
	vector<info> l;
	void gen_sufar() {
		int n = s.size(), i, j;
		p.push_back(vector <int> (n, 0));
		for (i = 0; i < n; ++i)
			p[0][i] = (int)s[i];
		for (i = 1; (1 << (i - 1)) < n; ++i) {
			p.push_back(vector <int> (n, 0));
			for (j = 0; j < n; ++j) {
				int nxt = (j + (1 << (i - 1)) < n? p[i - 1][j + (1 << (i - 1))]: -1);
				l[j] = {p[i - 1][j], nxt, j};
			}
			sort(l.begin(), l.end());
			for(j = 1; j < n; ++j)
				p[i][l[j].id] = (l[j].f == l[j - 1].f && l[j].s == l[j - 1].s? p[i][l[j - 1].id]: j);
		}
		j = i - 1;
		if (n == 0)
			p[0][0] = 0;
		for (i = 0; i < n; ++i)
			sufar[p[j][i]] = i;
	}
	public:
	string s;
	vector <int> sufar;
	suffix_array(string &s):s(s), sufar(s.size()) {
		int n = s.size();
		p.clear();
		l.resize(n);
		gen_sufar();
	}
	int lcp(int u, int v) {
		int sm = 0;
		if (u == v)
			return s.size() - i;
		for (int i = p.size() - 1; i >= 0 && u < s.size() && v < s.size(); --i) {
			if (p[i][u] == p[i][v]) {
				u += (1 << i);
				v += (1 << i);
				sm += (1 << i);
			}
		}
		return sm;
	}
};