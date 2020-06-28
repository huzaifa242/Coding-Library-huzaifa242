/**
 * Usage call z_algo(pattern+"#"+text)
 * "#" is delimator. for vector match use suitable like -1
 */
vector <int> z_algo(vector <int> &s) {
	vector <int> zeta(s.size());
	for (int i = 1,l = 0,r = 0; i < s.size(); ++i) {
		if (i <= r)
			zeta[i] = min(r - i + 1, zeta[i - l]);
		while (i + zeta[i] < s.size() && s[zeta[i]] == s[i + zeta[i]])
			zeta[i]++;
		if (i + zeta[i] - 1 > r) {
			l = i;
			r = i + zeta[i] - 1;
		}
	}
	return zeta;
}