/**
 * Example Usage "aaaba"
 * palins[1][i] : 12121
 * palins[0][i] : 01100
 * lrg[i]  is   : 32311
 * palins[1][i] - how many palindromes of odd length with center at i
 * to get longest length palindrome at i do: 2*palins[1][i]-1;
 * palins[0][i] - how many palindromes of even length with center at i
 * to get longest length palindrome at i do: 2*palins[0][i];
 * lrg[i] - The length of the longest palindrome starting at i.
 */
vector <int> manacher(vector <int> &s) {
	int n = s.size();
	vector <vector <int> > palins(2, vector <int> (n));
	vector <int> lrg(n, 1);
	for(int z = 0; z < 2; ++z){
		for(int i = 0, l = 0, r = -1; i < n; ++i) {
			int k = (i > r? z: min(palins[z][l + r - i + !z], r - i + 1));
			while (i + k < n && i - k - !z >= 0 && s[i + k] == s[i - k - !z])
				k++;
			palins[z][i] = k--;
			if(i + k - !z > r){
				l = i - k - !z;
				r = i + k;
			}
		}
	}
	for(int i = 0; i < n; ++i) {
		int ol = 2 * palins[1][i] - 1, el = 2 * palins[0][i];
		lrg[i - ol / 2] = max(lrg[i - ol / 2], ol);
		lrg[i - el / 2] = max(lrg[i - el / 2], el);
	}
	for(int i = 1; i < n; ++i) {
		lrg[i] = max(lrg[i], lrg[i - 1] - 2);
	}
	return lrg;
}