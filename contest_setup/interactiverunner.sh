#!/bin/bash
codefile="$1"
directory=`basename "$codefile"`
if [[ -z "$2" ]]; then
	custominteractor="$TESTING_HOME""/defaultinteractor.cpp"
	interactiverunner="$TESTING_HOME""/defaultinteractor"
else
	interactiverunner="$2"	
	ext=".cpp" # put extension here
	custominteractor="$interactiverunner$ext" 
fi
# Compile interactor if required. put correct value of custominteractor
g++ -o "${interactiverunner}" "${custominteractor}" -D ONLINE_JUDGE -D LOCAL
compile=$((g++ -o "$codefile" "$codefile".cpp -D ONLINE_JUDGE -D LOCAL >&2) 2>&1) 
echo $directory
if [[ ${#compile} -le 3 ]]; then
	# below step is the running command
	timeout 10 python3 "$CONTEST_SETUP/interactor.py"  "$interactiverunner" 0 -- "$codefile"
	cp "$codefile.cpp" "$HOME/Desktop/submit.cpp"
else
	echo "$compile"
fi