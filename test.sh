#!/bin/bash
usage="Usage modes are:

To use this script file do following setup
--> Create following files in one directory
--> Put this Script file within the directory with below mentioned files
1. create brute.cpp (Correct code file)
2. create casegen.cpp (To generate Test Cases)
3. create wrong.cpp (Code to be Tested)
4. create checker.cpp (optional create only if required)

perf: It does time based Testing. (Basically Chaecks for TLE)
pre-requisites:
-Modify casegen.cpp to produce inputs of Upper Limit constraint (Large Subtask) 
command: ./test.sh pref <codefile with .cpp extension>

stress: It does Correctness Testing. (Basically Checks for WA)
pre-requisites:
-Modify casegen.cpp for small constraint inputs so that Brute Force can run (Small Subtask)
command: ./test.sh stress <codefile with .cpp extension> <custom checker program in cpp>

generate: It generates lots of test case files by running caegen.cpp multiple times
command: ./test.sh generate <number of test files>

answer: It runs brute force on files produce by generate option and gives .ans file for testcases
pre-requisites
-Use it only after generate option
-After this use test option
command: ./test.sh answer

test: It runs actual code on files produce by generate option and gives .ans file for testcases
pre-requisites
-Use it only after answer option
command: ./test.sh test <codefile with .cpp extension> <custom checker program in cpp>

Additional Notes:
-custom checker program should takes 2 command line argument first is brute force output 
second is codefile output.
-giving codefile is optional, by default it takes codefile=\"wrong.cpp\" so override it for default behavior
-if you provide custom checker program, then you must give codefile name. 
because custom checker is argument 3 so argument 2(codefile name) is must.
"
mode="$1"
if [[ "$mode" == "-help" ]]; then
	echo "$usage"
elif [[ "$mode" == "perf" ]]; then
	if [[ -z "$2" ]]; then
		codefile="wrong.cpp"
	else
		codefile="$2"
	fi
	i=0
	g++ -o casegen casegen.cpp -D ONLINE_JUDGE
	g++ -o wrong $codefile -D ONLINE_JUDGE
	while true
	do
		echo "Test $((i+=1))"
		./casegen > testcase
		time ./wrong < testcase > /dev/null
		echo "------------"
		echo
	done
elif [[ "$mode" == "stress" ]]; then
	if [[ -z "$3" ]]; then
		compareoutput="diff -Z"
	else
		customcomparator="$3"
		g++ -o compare $customcomparator -D ONLINE_JUDGE
		compareoutput="./checker"
	fi
	if [[ -z "$2" ]]; then
		codefile="wrong.cpp"
	else
		codefile="$2"
	fi
	i=0
	g++ -o casegen casegen.cpp -D ONLINE_JUDGE
	g++ -o brute brute.cpp -D ONLINE_JUDGE
	g++ -o wrong $codefile -D ONLINE_JUDGE
	brutans="brutans.out"
	tstans="tstans.out"
	while (( $? == 0 ))
	do
		echo "Test $((i+=1))"
		./casegen > testcase
		./brute < testcase > $brutans
		./wrong < testcase > $tstans
		$compareoutput  $brutans $tstans
	done
elif [[ "$mode" == "generate" ]]; then
	n="$2"
	if [[ "$n" == "" ]]; then n=10; fi
	
	rm -rf tests
	mkdir -p tests
	g++ -o casegen casegen.cpp -D ONLINE_JUDGE
	for i in $(seq $n); do
		infile=$(printf "tests/%03d.in" $i)
		echo "Generate $infile"
		./casegen > $infile
	done
elif [[ "$mode" == "answer" ]]; then
	g++ -o brute brute.cpp -D ONLINE_JUDGE
	for infile in tests/*.in; do
		echo "Generate answer for $infile"
		base=${infile%.in}
		ansfile=$base.ans
		./brute < $infile > $ansfile
	done
elif [[ "$mode" == "test" ]]; then
	if [[ -z "$3" ]]; then
		compareoutput="diff -Z"
	else
		customcomparator="$3"
		g++ -o compare $customcomparator -D ONLINE_JUDGE
		compareoutput="./checker"
	fi
	if [[ -z "$2" ]]; then
		codefile="wrong.cpp"
	else
		codefile="$2"
	fi
	g++ -o wrong $codefile -D ONLINE_JUDGE
	for infile in tests/*.in; do
		base=${infile%.in}
		ansfile=$base.ans
		outfile=$base.out
		
		echo "Test $infile"
		./wrong < $infile > $outfile
		$compareoutput $ansfile $outfile
	done
else
	echo "Invalid Command. Use \"./test.sh -help\" for documentation"
	exit 1
fi