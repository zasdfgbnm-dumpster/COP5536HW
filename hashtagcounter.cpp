#include "fibonacci.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <functional>
#include <map>
#include <regex>
#include <cctype>
#include <algorithm>

using namespace std;

using fh_t = fibonacci_heap<int,string,greater<int>>;

fh_t fh;
map<string,fh_t::node> m;
ofstream out("output_file.txt");

// test if a string is an integer
// code modified from stackoverflow: http://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
inline bool is_integer(const string & s) {
	return regex_match(s,regex("[0-9]+"));
}

// handle the case when it is #tag n
void handletag(string cmd,int count) {
	string tag = cmd.substr(1);
	if(m.count(tag)>0)
		fh.decrease_key(m[tag], m[tag].key()+count);
	else
		m[tag] = fh.insert(count,tag);
}

// handle the case when printing a result is asked
void print(int count) {
	string tags[count];
	if(count > 0) {
		fh_t::node n = fh.remove();
		tags[0] = n.data();
		out << tags[0];
	}
	for(int i=1;i<count;i++) {
		fh_t::node n = fh.remove();
		tags[i] = n.data();
		out << "," << tags[i];
	}
	out << endl;
	for(string &t:tags)
		m[t] = fh.insert(m[t]);
}

int main(int argc,char **argv) {
	ifstream in(argv[1]);
	string command;
	int count;

	while(true) {
		in >> command;
		if(command[0]=='#') {
			in >> count;
			handletag(command,count);
		} else if(is_integer(command))
			print(stoi(command));
		else
			return 0;
	}
}
