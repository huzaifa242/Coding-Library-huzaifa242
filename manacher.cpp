// Example Usage "aaaba"
// odd[i] is :    12121
// evn[i] is :    01100
// odd[i] - how many palindromes of odd length with center at i
// to get longest length palindrome at i do: 2*odd[i]-1;
vector<int> odd_palindromes(string &s){
	int n=s.size();
	vector<int> odd(n);
	int l=0,r=-1;
	for(int i=0;i<n;i++){
		int k=(i>r?0:min(odd[l+r-i],r-i))+1;
		while(i+k<n && i-k>=0 && s[i+k]==s[i-k]) 
			k++;
		odd[i]=k--;
		if(i+k>r){
			l=i-k;
			r=i+k;
		}
	}
	return odd;
}
// evn[i] - how many palindromes of even length with center at i
// to get longest length palindrome at i do: 2*evn[i];
vector<int> even_palindromes(string &s) {
	int n=s.size();
	vector<int> evn(n);
	int l=0,r=-1;
	for(int i=0;i<n;i++){
		int k=(i>r?0:min(evn[l+r-i+1],r-i+1))+1;
		while(i+k-1< n && i-k>=0 && s[i+k-1]==s[i-k])
			k++;
		evn[i]=--k;
		if(i+k-1>r){
			l=i-k;
			r=i+k-1;
		}
	}
	return evn;
}