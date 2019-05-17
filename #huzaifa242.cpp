/**************************************************************
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

		huzaifa242 copyright

**************************************************************/
#include <bits/stdc++.h>
using namespace std;
#define MAX 100005
#define x first 
#define y second

long long int seed;
mt19937 rng(seed=chrono::steady_clock::now().time_since_epoch().count());
inline long long int rnd(long long int l=0,long long int r=0xFFFFFFFFFFFFFFFL)
{return uniform_int_distribution<long long int>(l,r)(rng);}

template <typename Arg1,typename Arg2>
ostream& operator << (ostream& out, const pair<Arg1,Arg2> &a) 
{return out<<"("<<a.x<<" , "<<a.y<<")";}

template <typename Arg1>
ostream& operator << (ostream& out, const vector<Arg1> &a) 
{out<<"[";for(const auto &i:a)out<<i<<" , ";return out<<"]";}

template <typename Arg1>
ostream& operator << (ostream& out, const set<Arg1> &a) 
{out<<"{";for(const auto &i:a)out<<i<<" , ";return out<<"}";}

template <typename Arg1,typename Arg2>
ostream& operator << (ostream& out, const map<Arg1,Arg2> &a) 
{out<<"<";for(const auto &i:a)out<<i<<" , ";return out<<">";}

template<typename T, size_t N>
typename enable_if<!is_same<typename remove_cv<T>::type, char>::value,
ostream&>::type operator<<(ostream& out, T(&a)[N])
{out<<'[';for(size_t i=0;i<N;++i)out<<a[i]<<" , ";out << ']';return out;}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	#ifndef ONLINE_JUDGE
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);  
	#endif
	//code goes here!!
	return 0;
}
