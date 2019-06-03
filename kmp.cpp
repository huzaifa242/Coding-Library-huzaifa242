//Usage call kmp(text,pattern)
//"#" is delimator. for vector match use suitable like -1
//pos in kmp function returns 0-based vector of starting index of substing occurence
vector<int> shift_table(string &s)
{
	int i,j;
	vector<int> sft(s.size());
	for (i=1;i<s.size();i++)
	{
		j=sft[i-1];
		while(j>0 && s[i]!=s[j])
		j=sft[j-1];
		if (s[i]==s[j])
		j++;
		sft[i]=j;
	}
	return sft;
}
vector<int> kmp(string txt,string pat)
{
	string cur=pat+"#"+txt;
	vector<int> pos,lps=shift_table(cur);
	int i;
	for(i=pat.size()+1;i<=pat.size()+txt.size();i++)
	{
		if(lps[i]>=pat.size())
			pos.push_back(i- 2*pat.size());
	}
	return pos;
}