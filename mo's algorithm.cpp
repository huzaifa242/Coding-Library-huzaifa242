//USE int64_t ALWAYS
//implement insert,remove and calc function
//rest is taken care of 
class Mo
{
	private:
	class Query
	{
		public:
		mutable int l,r,id,od;
		private:
		const int rot_delta[4]={3,0,0,1};
		int hilbert_curve(int u,int v,int pw,int rot)
		{
			if(pw==0)
				return 0;
			int hp= 1LL<<(pw-1LL);
			int p=(u<hp?(v<hp?0:3):(v<hp?1:2));
			p=(p+rot) & 3;
			u&=(u^hp);
			v&=(v^hp);
			rot=(rot + rot_delta[p]) & 3;
			int sbsq= 1LL<<(2LL*pw -2LL);
			int ord=p*sbsq;
			int add=hilbert_curve(u,v,pw-1,rot);
			ord+=(p==1||p==2)?add:(sbsq-add-1);
			return ord;
		}
		public:
		Query()
		{}
		Query(int _l,int _r,int _id)
		{
			l=_l;
			r=_r;
			id=_id;
			od=hilbert_curve(l,r,21,0);
		}
		void operator =(Query qq)const
		{
			l=qq.l;
			r=qq.r;
			id=qq.id;
			od=qq.od;
		}
		bool operator < (Query qq) const
		{
			return od<qq.od;
		}
	};
	vector<Query> qry;
	public:
	vector<int> ans;
	Mo()
	{}
	void add_query(int l,int r,int id)
	{
		qry.push_back(Query(l,r,id));
		ans.push_back(0);
	}
	void insert(int u)
	{
		//insert index u to active range
	}
	void remove(int u)
	{
		//remove index u from active range
	}
	int calc()
	{
		//calculate ans for current range 
		return ;
	}
	void solve()
	{
		sort(qry.begin(),qry.end());
		int l=0,r=-1;
		for(auto q:qry)
		{
			while(r<q.r)insert(++r);
			while(r>q.r)remove(r--);
			while(l<q.l)remove(l++);
			while(l>q.l)insert(--l);
			ans[q.id]=calc();
		}
	}
};