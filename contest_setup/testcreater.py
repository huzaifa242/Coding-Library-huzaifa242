import socket
import json
import os
import shutil

port = int(os.environ['CODING_PORT'])
testing_path = os.path.join(os.environ['TESTING_HOME'],"Tests")


def codechef_filename(contest_url):
	pos = contest_url.rfind('/')+1 
	return contest_url[pos:]

def atcoder_filename(contest_url):
	pos = contest_url.rfind('/')+1 
	return contest_url[pos:]

def codeforces_filename(contest_url):
	pos = contest_url.rfind('/')+1 
	name = contest_url[pos:]
	end = contest_url.rfind('/',0,pos-1)+1 
	pos = contest_url.rfind('/',0,end-1)+1 
	return str(contest_url[pos:end-1] + name)

def get_file_name(contest_url):
	if contest_url.find('atcoder') >= 0:
		return atcoder_filename(contest_url).lower()
	elif contest_url.find('codechef') >= 0:
		return codechef_filename(contest_url).lower()
	elif contest_url.find('codeforces') >= 0:
		return codeforces_filename(contest_url).lower()

def create_test_file(test, path):
	input = open(path+'.in','w')
	input.write(test['input'])
	input.close()
	output = open(path+'.ans','w')
	output.write(test['output'])
	output.close()

def create_test_directory(tests, directory):
	cur_dir=os.path.join(testing_path,directory)
	if os.path.exists(cur_dir):
		shutil.rmtree(cur_dir)
	os.mkdir(cur_dir, 0o777)
	i=0
	for test in tests:
		cur_file = os.path.join(cur_dir,str(i))
		create_test_file(test,cur_file)
		i = i + 1
	return 

listener = socket.socket()
listener.bind(('',port))
listener.listen()
# print('listening on '+ str(port))
while True:
	connection , address = listener.accept();
	data = str(connection.recv(4096*4096).decode())
	trim_at=data.find('\r\n\r\n');
	data = json.loads(data[trim_at:])
	data['name']=get_file_name(data['url'])
	create_test_directory(data['tests'],data['name'])

	# print(json.dumps(data))
	# print(data['name'])
	connection.close();