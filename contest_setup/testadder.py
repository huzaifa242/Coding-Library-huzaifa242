import os
def read_from(add):
	file=open(add,"r")
	content=file.read()
	file.close()
	return content

def create_test_file(test, path):
	input = open(path+'.in','w')
	input.write(test['input'])
	input.close()
	output = open(path+'.ans','w')
	output.write(test['output'])
	output.close()


def adder(name):
	input_path=os.path.join(os.environ['CODING_HOME'])
	testing_path = os.path.join(os.environ['TESTING_HOME'],"Tests")
	input=read_from(os.path.join(input_path,"input.txt"))
	answer=read_from(os.path.join(input_path,"output.txt"))
	if len(input) == 0:
		return
	cur_dir=os.path.join(testing_path,name)
	if not os.path.exists(cur_dir):
		os.mkdir(cur_dir, 0o777)
		test={'input':input, 'output':answer}
		cur_file = os.path.join(cur_dir,str(0))
		create_test_file(test,cur_file)
		return
	else:
		i=0
		for file in os.listdir(cur_dir):
			j=int(os.path.splitext(file)[0])
			if j>=i:
				i=j+1
		test={'input':input, 'output':answer}
		cur_file = os.path.join(cur_dir,str(i))
		create_test_file(test,cur_file)
		return

# example usage: adder(1234d) where 1234d is filename without extension

import sublime
import sublime_plugin
class customtestadderCommand(sublime_plugin.TextCommand):
	def run(self, edit):
		file_name = os.path.basename(self.view.file_name())
		file_name = os.path.splitext(file_name)[0]
		adder(file_name)
