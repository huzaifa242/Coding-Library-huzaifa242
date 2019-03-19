/*priority Queue Structure
priority_queue<pqnode, vector<pqnode>,pqcmp> pq;*/
struct pqnode
{
	//priority queue Node
};
struct pqcmp
{
	bool operator()(const pqnode a,const pqnode b)
	{
		//<-asc  >-desc
	}
};
deque<T> dq;
dq.push_back();
dq.push_front();
dq.front();
dq.back();
dq.pop_front();
dq.pop_back();

set<T> s;
s.insert(10);
s.erase(10);

queue<T> qu;
qu.push();
qu.front();
qu.back();
qu.pop();

stack<T> st;
st.push();
st.top();
st.pop();

__gcd(a,b);