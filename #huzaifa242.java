import java.io.*;
import java.util.*;
import java.math.*;
import java.text.*;

public class class_name
{
	private boolean ONLINE_JUDGE=System.getProperty("ONLINE_JUDGE") != null;
	private boolean INTERACTIVE=false;
	private boolean TESTCASES=false;
	private int MAX=100005;
	private long mod=(long)998244353;//1e9+7;
	private int INT_MAX=Integer.MAX_VALUE;
	private int INT_MIN=Integer.MIN_VALUE;
	private long LLONG_MAX=Long.MAX_VALUE;
	private long LLONG_MIN=Long.MIN_VALUE;
	
	Reader cin;
	Writer cout;

	void preprocess() throws Exception
	{
		//Preprocess Here!!
	}

	void solve(int tc) throws Exception
	{
		//code goes here!!
	}

	void run() throws Exception
	{
		cin=!ONLINE_JUDGE || INTERACTIVE? new Reader("input.txt"):new Reader();
		cout=!ONLINE_JUDGE || INTERACTIVE? new Writer("output.txt"):new Writer();

		preprocess();
		int i,t=TESTCASES? cin.getint():1;
		for(i=1;i<=t;i++)
			solve(i);
		cout.flush();
		cout.close();
	}

	public static void main(String[] args) throws Exception
	{
		new class_name().run();
	}

	class Reader
	{
		BufferedReader br;
		StringTokenizer st;
		public Reader()
		{
			br = new BufferedReader(
				new InputStreamReader(System.in));
		}
		public Reader(String f) throws Exception
		{
			br = new BufferedReader(new FileReader(f));
		}
		String get() throws Exception
		{
			while (st == null || !st.hasMoreElements())
			{
				try{
					st =new StringTokenizer(br.readLine());
				}catch (IOException  e){
					throw new Exception(e.toString());
				}
			}
			return st.nextToken();
		}
		String getline() throws Exception
		{
			String str = "";
			try{   
				str = br.readLine();
			}catch (IOException e){
				throw new Exception(e.toString());
			}  
			return str;
		}
		int getint() throws Exception
		{
			return Integer.parseInt(get());
		}
		long getlong() throws Exception
		{
			return Long.parseLong(get());
		}
		double getdouble() throws Exception
		{
			return Double.parseDouble(get());
		}
		BigInteger getbigint() throws Exception
		{
			return new BigInteger(get());
		}
		BigDecimal getbigdouble() throws Exception
		{
			return new BigDecimal(get());
		}
	}
	class Writer
	{
		PrintWriter pr;
		public Writer()
		{
			pr=new PrintWriter(System.out);
		}
		public Writer(String f) throws Exception
		{
			pr=new PrintWriter(f);
		}
		void print(Object o) throws Exception
		{
			pr.print(o);
		}
		void println(Object o) throws Exception
		{
			pr.println(o);
		}
		void flush() throws Exception
		{
			pr.flush();
		}
		void close() throws Exception
		{
			pr.close();
		}
		void printflush(Object o) throws Exception
		{
			println(o);
			flush();
		}
	}
	class pair<T,G>
	{
		T x; G y;
		public pair(){}
		public pair(T x,G y)
		{
			this.x=x;
			this.y=y;
		}
		public String toString()
		{
			return " <"+x.toString()+","+y.toString()+"> ";
		}
	}
}