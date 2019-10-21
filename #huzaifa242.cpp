/***********************************************************
	When you are inspired by passion 
	and you want to live for the current moment

	When your every thought and action
	has the power to become the story of your future

	When difficulties stand to demolish your Glory
	Just remember that Life is a 'Golden adverse Story'

	Withstand it to acheive your passion and dreams
	more amazingly more easily.

	Why then? When writing the story of your Life
	You want to Let someone else hold your pen

					huzaifa242©

***********************************************************/
#include <bits/stdc++.h>
using namespace std;
#define int int32_t
#define MAX 100005
#define x first 
#define y second

int seed;
mt19937 rng(seed=chrono::steady_clock::now().time_since_epoch().count());
inline int rnd(int l=0,int r=INT_MAX)
{return uniform_int_distribution<int>(l,r)(rng);}

template <typename T,typename G>
ostream& operator << (ostream& out, const pair<T,G> &a) 
{return out<<"("<<a.x<<" , "<<a.y<<")";}

template <typename T>
ostream& operator << (ostream& out, const vector<T> &a) 
{out<<"[";for(const auto &i:a)out<<i<<" , ";return out<<"]";}

template <typename T>
ostream& operator << (ostream& out, const set<T> &a) 
{out<<"{";for(const auto &i:a)out<<i<<" , ";return out<<"}";}

template <typename T,typename G>
ostream& operator << (ostream& out, const map<T,G> &a) 
{out<<"<";for(const auto &i:a)out<<i<<" , ";return out<<">";}

template<typename T, size_t N>
typename enable_if<!is_same<typename remove_cv<T>::type, char>::value,
ostream&>::type operator<<(ostream& out, T(&a)[N])
{out<<'[';for(size_t i=0;i<N;++i)out<<a[i]<<" , ";out << ']';return out;}

signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);cout.tie(NULL);
	#ifndef ONLINE_JUDGE
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);  
	#endif
	//code goes here!!
	return 0;
}
