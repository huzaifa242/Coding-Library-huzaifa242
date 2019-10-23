//can be used as sparse segment tree
//supports point update and range query
//use wisely very powerful code ahead
//Usage Avl_tree<int,int> t1(<function>);
struct data{
	data(){}
	data(data a){
	//assign this=a;
	}
};
template<typename T,typename G>
class Avl_tree{
	private:
	function<G(G,G)> merge;
	struct node{
		T key,l,r;
		G val,all;
		int height;
		node *left,*right;
		node(T k,G v){
			key=k;
			val=v;
			l=k;r=k;
			height=1;
			left=NULL;
			right=NULL;
		}
		void merge(){
			l=left?left->l:key;
			r=right?right->r:key;
			all(val);
			if(left)
			all=merge(all,left->val);
			if(right)
			all=merge(all,right->val);
		}
	}*root;
	int tot;
	int get_height(node *t)
	{ return (t?t->height:0);}
	void calc_height(node *t)
	{ t->height=max(get_height(t->left),get_height(t->right))+1;}
	int get_balancefactor(node *t)
	{ return (t?get_height(t->left)-get_height(t->right):0); }
	void rotate_left(node *t){
		node *tmp=t;
		t=t->right;
		tmp->right=t->left;
		t->left=tmp;
		calc_height(tmp);
		tmp.merge();
		calc_height(t);
		t.merge();
	}
	void rotate_right(node *t){
		node *tmp=t;
		t=t->left;
		tmp->left=t->right;
		t->right=tmp;
		calc_height(tmp);
		tmp.merge();
		calc_height(t);
		t.merge();
	}
	void balance(node *t){
		if(t==NULL)
			return;
		calc_height(t);
		int bf=get_balancefactor(t);
		if(bf>1){
			if(get_balancefactor(t->left)<0)
				rotate_left(t->left);
			rotate_right(t);
		}else if(bf< -1){
			if(get_balancefactor(t->right)>0)
				rotate_right(t->right);
			rotate_left(t);
		}
	}
	bool insert(node *t, T k, G v)
	{
		if(t==NULL){
			t=new node(k,v);
			t.merge();
			return true;
		}
		if(t->key==k){
			t->val=v;
			t.merge();
			return false;
		}
		int bl;
		if(k< t->key)
			bl=insert(t->left,k,v);
		else
			bl=insert(t->right,k,v);
		balance(t);
		t.merge();
		return bl;
	}
	bool erase(node *t, T k){
		if(t==NULL)
			return false;
		if(t->key==k){
			if(t->left && t->right){
				node *tmp=t->right;*par=NULL;
				while(tmp->left){
					par=tmp;
					tmp=tmp->left;
				}
				t->key=tmp->key;
				t->val=tmp->val;
				if(par){
					if(!erase(par->left,par->left->key))
						return false;
				}else if(!erase(t->right,t->right->key))
					return false;
			}else{
				node *tmp=(t->left?t->left:t->right);
				delete t;
				t=tmp;
			}
			balance(t);
			t.merge();
			return true;
		}else if(t->key > k && erase(t->left,k)){
			balance(t);
			t.merge();
			return true;
		}else if(t->key < k && erase(t->right,k)){
			balance(t);
			t.merge();
			return true;
		}
		return false;
	}
	G query(node *t, T x, T y){
		if(t->r < x || t->l >y){
			G grbg;
			return grbg;
		}
		if(t->l >=x && t->r <=y)
			return t->all;
		G tr;
		if(t->key >=x &&  t->r <=y)
			tr=(t->val);
		if(t->left)
			if(t->left->r >= x)
				tr=merge(tr,query(t->left,x,y));
		if(t->right)
			if(t->right->l <=y)
				tr=merge(tr,query(t->right,x,y));
		return tr;
	}
	public:
	Avl_tree(auto fnc){
		merge=fnc;
		root=NULL;
		tot=0;
	}
	int size()
	{ return tot; }
	bool empty()
	{ return tot==0; }
	bool insert(T k,G v){
		if(insert(root,k,v)){
			tot++;
			return true;
		}
		return false;
	}
	bool erase(T k){
		if(erase(root,k)){
			tot--;
			return true;
		}
		return false;
	}
	G* find(T k){
		node *t=root;
		while(t){
			if(k== t->key)
				return &(t->val);
			else if(k<t->key)
				t=t->left;
			else
				t=t->right;
		}
		retrun NULL;
	}
	void update(T id, G val){
		//preprocess for update here  
		insert(id,val);
	}
	G query(T x, T y){
		return query(root,x,y);
	}
};
