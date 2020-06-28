/**
 * Usage call kmp(text,pattern)
 * for generic usage it is made of int
 * delim is delimator. for vector match use suitable like -1 or 0
 * pos in kmp function returns 0-based vector of starting index of substring occurence
 */
vector <int> shift_table(vector <int> &s) {
	vector <int> sft(s.size());
	for (int i = 1, j; i < s.size(); ++i) {
		j = sft[i - 1];
		while (j > 0 && s[j] != s[i]) {
			j = sft[j - 1];
		}
		if (s[j] == s[i])
			j++;
		sft[i] = j;
	}
	return sft;
}
vector <int> kmp(vector <int> &txt, vector <int> &pat) {
	int delim = 0;
	vector <int> cur;
	for (auto &u : pat)
		cur.push_back(u);
	cur.push_back(delim);
	for (auto &u : txt)
		cur.push_back(u);
	vector <int> pos,lps = shift_table(cur);
	for (int i = pat.size() + 1; i <= pat.size() + txt.size(); ++i)
		if (lps[i] >= pat.size())
			pos.push_back(i - 2 * pat.size());
	return pos;
}