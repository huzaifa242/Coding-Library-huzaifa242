class suffix_automata {
	const int alpha = 131;
	public:
	int sz, last;
	vector <int> link, len;
	vector <vector <int> > to;
	suffix_automata() {
		sz = 1;
		last = 0;
		len.push_back(0);
		link.push_back(0);
		to.push_back(vector <int> (alpha, 0));
	}
	void add(char c) {
		len.push_back(0);
		link.push_back(0);
		to.push_back(vector <int> (alpha, 0));
		int p = last;
		last = sz++;
		len[last] = len[p] + 1;
		for (; to[p][c] == 0; p = link[p])
			to[p][c] = last;
		if (to[p][c] == last) {
			link[last] = 0;
			return;
		}
		int q = to[p][c];
		if (len[q] == len[p] + 1) {
			link[last] = q;
			return;
		}
		len.push_back(0);
		link.push_back(0);
		to.push_back(vector <int> (alpha, 0));
		int c1 = sz++;
		to[c1] = to[q];
		link[c1] = link[q];
		len[c1] = len[p] + 1;
		link[last] = link[q] = c1;
		for (; to[p][c] == q; p = link[p])
			to[p][c] = c1;
	}
	bool find(string &s) {
		int cur = 0;
		for (auto c : s) {
			cur = to[cur][c];
			if (cur == 0)
				return false;
		}
		return true;
	}
};