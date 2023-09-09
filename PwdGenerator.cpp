#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<cmath>

using namespace std;

// Factorial
uint32_t fact(uint32_t n) {
	if (n < 2) return 1;
	else return n * fact(n - 1);
}

// Normalize string
string norm(string s) {
	string r = s;
	transform(r.begin(), r.end(), r.begin(), ::tolower);
	r[0] = toupper(r[0]);
	return r;
}

// String states
string sstate(string s, short m) {
	string r=s;
	if (m == 1) r = toupper(s[0]);
	if (m == 2) r = tolower(s[0]);
	if (m == 3) r = norm(s);
	if (m == 4) transform(r.begin(), r.end(), r.begin(), ::tolower);
	if (m == 5) transform(r.begin(), r.end(), r.begin(), ::toupper);
	return r;
}

// Year states
string ystate(short y, short m) {
	if (m == 1) return to_string(y);
	if (m == 2) return to_string(y % 100);
	if (m == 3) return '0' + to_string(y % 100);
}

// Other int states
string istate(short i, short m) {
	if (m == 1) return to_string(i);
	if (m == 2) return '0'+to_string(i);
}

int main() {
	// Get infos
	string fname, lname, file;
	short yob, mob, dob;
	cout << "File name : ";
	cin >> file;
	cout << "First name : ";
	cin >> fname;
	cout << "Last name : ";
	cin >> lname;
	cout << "Year of birth : ";
	cin >> yob;
	cout << "Month of birth : ";
	cin >> mob;
	cout << "Day of birth : ";
	cin >> dob;
	// Set limits
	short i[5], ylim = 3, mlim = 2, dlim = 2;
	if (yob % 100 < 10) ylim++;
	if (mob < 10) mlim++;
	if (dob < 10) dlim++;
	// Open file
	ofstream log(file);
	//Loop trough password elements
	for (i[0] = 0; i[0] < 6; i[0]++) {
		for (i[1] = 0; i[1] < 6; i[1]++) {
			for (i[2] = 0; i[2] < ylim; i[2]++) {
				for (i[3] = 0; i[3] < mlim; i[3]++) {
					for (i[4] = 0; i[4] < dlim; i[4]++) {
						// Declare vector for elements and put them in
						vector<string> v;
						if (i[0] != 0) v.push_back(sstate(fname, i[0]));
						if (i[1] != 0) v.push_back(sstate(lname, i[1]));
						if (i[2] != 0) v.push_back(ystate(yob, i[2]));
						if (i[3] != 0) v.push_back(istate(mob, i[3]));
						if (i[4] != 0) v.push_back(istate(dob, i[4]));
						// Loop trough the different orders of elements
						for (short j = 0; j < fact(v.size()); j++) {
							// Copy vector
							vector<string> w;
							for (short k = 0; k < v.size(); k++)
								w.push_back(v[k]);
							// Order elements into pwd
							stringstream pwd;
							for (short k = w.size(); k > 0; k--) {
								short ix = floor((double)(j % fact(k)) / fact(k - 1));
								pwd << w[ix];
								w.erase(w.begin() + ix);
							}
							// If pwd isn't empty save it
							if (i[0] + i[1] + i[2] + i[3] + i[4] > 0) log << pwd.str() << '\n';
						}
					}
				}
			}
		}
	}
	log.close();
}