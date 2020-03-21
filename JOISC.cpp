// JOISC -> LOJ

#include <cstdlib>

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int ask(const string& sentence) {
	cout << sentence << endl;
	int x;
	cin >> x;
	return x;
}

int main() {
	system("ls > tmp.txt");

	ifstream tmp("tmp.txt");

	ofstream data("data.yml");

	map<string, vector<string> > mp;
	string title, filename;
	while (tmp >> filename) {
		if (filename.size() < 5) continue;
		if (filename.substr(filename.size() - 3) == ".in") {
			string token = filename.substr(0, filename.size() - 3);
			int pos = token.find('-');
			mp[token.substr(0, pos)].push_back(token);
		}
	}

	data << "subtasks:\n";

	for (const auto& pr : mp) {
		int sc = 0;
		if (pr.first != "sample") {
			cout << "taskcase: " << pr.first << endl;
			sc = ask("score?");
		}
		data <<
"  - score: " << sc << "\n"
"    type: min\n"
"    cases: [";
		for (const auto& token : pr.second) {
			if (token == pr.second.back()) break;
			data << '\'' << token << "', ";
		}
		data << '\'' << pr.second.back() << "']\n";
	}

	data <<
"inputFile: '#.in'\n"
"outputFile: '#.out'\n";

	return 0;
}
