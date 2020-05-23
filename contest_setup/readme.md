# Setup Sublime for competetive coding

#### If any of the step doesn't take effect, try closing and reopening Sublime Text 3.

#### The below steps are with assumption that you already have competitve companion plugin in your browser

#### Install Sublime Text 3

#### Go to Browse Package and go to Parent directory of Sublime-Text-3 give it 777 Permission

#### Get Package Control from https://packagecontrol.io/installation

#### Get PackageResourceViewer(edit built in things) from https://packagecontrol.io/packages/PackageResourceViewer

#### Get sublime-text-2-buildview(build Output on side) from https://packagecontrol.io/packages/sublime-text-2-buildview

#### Copy following config in sublime-> preferences-> settings-> user
```
	{
		"font_size": 13,
		"caret_style": "blink",
		"caret_extra_top": 0,
		"caret_extra_bottom": 0,
		"caret_extra_width": 1,
		"highlight_line": true,
		"fade_fold_buttons": false,
		"save_on_focus_lost": true,
	}
````

#### Declare following environment variables (Below are for Ubuntu set in \~/.profile):
For the whole setup to work the directory structure must be as follows:
````bash
|---CODING_HOME
|	|---Testing (This is your TESTING_HOME)
|	|	|---Tests (Below level would be created by testcreater.py)
|	|	|	|---Problem_1_TestCases (All Test cases for this Problem are inside this directory)
|	|	|	|---Problem_2_TestCases
|	|	|	|---Problem_3_TestCases
|	|---contest_setup (This is your CONTEST_SETUP)
|	|	|---executor.sh
|	|	|---interactiverunner.sh
|	|	|---interactor.py
|	|	|---testadder.py
|	|	|---testcreater.py	
````

Below is my personal setting for environment variable. Modify it accordinh to your system based on above Directory Structure.

```
	export CODING_PORT=2421;
	export CODING_HOME='/media/procyon/New Volume2/Coding';
	export TESTING_HOME=$CODING_HOME/Testing;
	export CONTEST_SETUP=$CODING_HOME/contest_setup;
	alias codingon='python3 "$CONTEST_SETUP/testcreater.py" &';`
```
#### Create sublime command for Adding Custom Test Cases
	* create a new sublime plugin
	* paste content of testadder.py in that file without any modification and save it.
	* go to preferences-> key bindings -> user section and paste below command
  	`{ "keys": ["ctrl+shift+i"], "command": "customtestadder" },`
	* try this and test this thoroughly

#### Add -D LOCAL flag to existing build system (Ready for Topcode now)

#### Add custom build system for Competitive Coding Non-Interactive Problems
````
{
	"shell_cmd": "\"\\$CONTEST_SETUP/executor.sh\" \"${file_path}/${file_base_name}\"",
	"selector": "source.c++",
}
````

#### Add custom build system for Competitive Coding Interactive Problems
````
{
	"shell_cmd": "\"\\$CONTEST_SETUP/interactiverunner.sh\" \"${file_path}/${file_base_name}\" \"\\$TESTING_HOME/Tests/${file_base_name}/interactor\"",
	"selector": "source.c++",
}
````

## Snippet Handling
* Edit inbuilt snipets properly.
* Make new snippets for following
	* pair (from map)
	* set (from vector)
	* tests 
	* codejam