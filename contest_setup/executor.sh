#!/bin/bash
if [[ -z "$2" ]]; then
	customcomparator="$TESTING_HOME""/defaultchecker.cpp"
	compareoutput="$TESTING_HOME""/defaultchecker"
else
	customcomparator="$3"
	compareoutput="./checker"	
fi
g++ -o "${compareoutput}" "${customcomparator}" -D ONLINE_JUDGE -D LOCAL
codefile="$1"
compile=$((g++ -o "$codefile" "$codefile".cpp -D ONLINE_JUDGE -D LOCAL >&2) 2>&1) 
directory=`basename "$codefile"`
if [[ ${#compile} -le 3 ]]; then
	for infile in "$TESTING_HOME"/Tests/"$directory"/*.in; do
		base=${infile%.in}
		ansfile=$base.ans
		outfile=$base.out
		running=`basename "$infile"`
		echo "Test $directory/$running"
		cat "$infile"
		echo ""
		timeout 5 "$codefile" < "$infile" > "$outfile"
		"$compareoutput" "$ansfile" "$outfile" 
		cp "$codefile.cpp" "$HOME/Desktop/submit.cpp"
	done
else
	echo "$compile"
fi