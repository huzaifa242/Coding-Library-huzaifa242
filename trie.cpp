//present() checks if current bit is set in any element
//in thr range of indices l to r
//to store the indices, ps is used no big deal
//for simplicity use vector to push positions if required
//modify present accordingly
//insert and remove are multi-purpose so rock everywhere
//find is for string implementation so be wise
struct node{
	node* a[2];
	bitset<MAX> ps;
	//rest of the data
};
class Trie{
	private:
	const int lgs=31;
	node* head;
	bool present(node *cur,int l,int r,int b){
		if(!cur->a[b])
			return false;
		return (((cur->a[b]->ps)<<l)>>(MAX-r+l-1)).count() > 0;
	}
	public:
	Trie(){
		head= new node();
	}
	void insert(int x,int p){
		trie *cur=head;
		int i;
		for(i=lgs-1;i>=0;i--){
			int bt=(x>>i)&1;
			if(!cur->a[bt])
				cur->a[bt]=new trie();
			cur=cur->a[bt];
			cur->ps[p]=1;
			//Do operation
		}
	}
	void remove(int x,int p){
		trie *cur=head;
		int i;
		for(i=lgs-1;i>=0;i--){
			int bt=(x>>i)&1;
			cur=cur->a[bt];
			cur->ps[p]=0;
			//Do operation
		}
	}
	bool find(string &x){
		trie *cur=head;
		int i;
		for(i=0;i<x.length();i++){
			int bt=x[i]-'a';
			if(!cur->a[bt])
			return false;
			cur=cur->a[bt];
		}
		return true;
	}
	int maxor(int l,int r,int x){
		trie *cur=head;
		int i,ans=0;
		for(i=lgs-1;i>=0;i--){
			int bt=present(cur,l,r,!(x>>i)&1)?(!((x>>i)&1)):((x>>i)&1);
			ans|=(bt<<i);
			cur=cur->a[bt];
		}
		return ans;
	}
};