// PA -> LOJ

#include <cstdlib>

#include <fstream>
#include <iostream>

using namespace std;

int main() {
	system("ls > tmp.txt");

	ifstream tmp("tmp.txt");

	static char mx[11];
	string title, filename;
	while (tmp >> filename) {
		if (filename.size() < 5) continue;
		if (filename.substr(filename.size() - 3) == ".in") {
			int p = 0;
			while (!isdigit(filename[p])) ++p;
			title = filename.substr(0, p);
			if (filename[p] != '0') {
				int tc = atoi(filename.substr(p, filename.size() - p - 4).c_str());
				mx[tc] = max(mx[tc], filename[filename.size() - 4]);
				//cerr << filename << ' ' << title << ' ' << tc << ' ' << filename[filename.size() - 4] << '\n';
			}
		}
	}

	ofstream data("data.yml");

	data <<
"subtasks:\n"
"  - score: 0\n"
"    type: min\n"
"    cases: ['0']\n";

	for (int i = 1; i <= 10; ++i) {
		data <<
"  - score: 10\n"
"    type: min\n"
"    cases: [";
		for (char c = 'a'; c < mx[i]; ++c)
			data << '\'' << i << c << "', ";
		data << '\'' << i << mx[i] << "']\n";
	}
	
	data <<
"inputFile: '" << title << "#.in'\n"
"outputFile: '" << title << "#.out'\n";

	return 0;
}
