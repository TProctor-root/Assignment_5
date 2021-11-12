//#include <boost/math/distributions/chi_squared.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstdint>
#include <fstream>
using namespace std;

vector<int> hashes(65536);
int bins[16];

void test(int n) {
	for (int i = 0; i < n; ++i) {
		cout << hashes.at(i) << endl;
	}
}

void testbins() {
	for (int i = 0; i < 16; ++i) {
		cout << bins[i] << endl;
	}
}

/*
float pearsonTest() {
	double math = 99170 / 65536.0;
	double c2 = 0;
	for (int i = 0; i < 65536; ++i) {
		c2 += pow(math - hashes[i], 2) / math;
	}
	boost::math::chi_squared c2d(65535.0);
	float p = boost::math::cdf(c2d, c2);
	return p = (1 - p) * 100.0;
}
*/

void seperateBins() {
	int a;
	for (int i = 0; i < 16; ++i) {
		a = 0;
		for (int j = i * 1008; j < (i + 1) * 1008; ++j) {
			a += hashes.at(j);
		}
		bins[i] = a;
	}
	a = 0;
	for (int j = 64 * 1008; j < 65536; ++j) {
		a += hashes.at(j);
	}
	bins[64] = a;
}

void binsGraph(string graph) {
	cout << graph  << " Hash Table" << endl;
	cout << "__________________________________________________________________________________________________________________" << endl;

	for (int i = 0; i < 16; ++i) {
		cout << i << "\t| ";
		int stars = bins[i] / 50;
		/*
		if (stars > 100)
			cout << "This bin contains more than 5 times the amount of hashes than an evenly distributed bin should have.";
		else
		*/
		for (int j = 0; j < stars; ++j) {
			cout << '*';
		}
		cout << endl;
	}

	//cout << "\nThe probability that the hashes are not far from a uniform distribution is: " << fixed << setprecision(2) << pearsonTest() << "%.\n";
}

void distributionTable(string graph) {
	seperateBins();
	binsGraph(graph);
}

void stringLength() {
	string x;
	ifstream inStream;
	inStream.open("assignment5.txt"); // inStream.open("/usr/share/dict/words");
	if (inStream.is_open()) {
		while (getline(inStream, x)) {
			inStream >> x;
			uint16_t a = x.length() % 65536;	
			hashes.at(a)++;
		}
		distributionTable("String Length");
		hashes.clear();
	}
}

void firstCharacter() {
	string x;
	ifstream inStream;
	inStream.open("assignment5.txt"); // inStream.open("/usr/share/dict/words");
	if (inStream.is_open()) {
		while (getline(inStream, x)) {
			inStream >> x;
			uint16_t a = x[0];	
			hashes.at(a)++;
		}
		distributionTable("First Character");
		hashes.clear();
	}
}

void sumCharacters() {
	string x;
	ifstream inStream;
	inStream.open("assignment5.txt"); // inStream.open("/usr/share/dict/words");
	if (inStream.is_open()) {
		while (getline(inStream, x)) {
			inStream >> x;
			uint16_t a = x[0];
			for (int i = 1; i < x.length(); ++i) {
				a = (a + x[i]) % 65536;
			}
			hashes.at(a)++;
		}
		distributionTable("Additive Checksum");
		hashes.clear();
	}
}

void remainder() {
	string x;
	ifstream inStream;
	inStream.open("assignment5.txt"); // inStream.open("/usr/share/dict/words");
	if (inStream.is_open()) {
		while (getline(inStream, x)) {
			inStream >> x;
			uint16_t a = x[0] + 128;
			for (int i = 1; i < x.length(); ++i) {
				a = (256 * a + x[i] + 128) % 65413;
			}
			hashes.at(a)++;
		}
		distributionTable("Remainder");
		hashes.clear();
	}
}

void multiplicative() {
	string x;
	ifstream inStream;
	inStream.open("assignment5.txt"); // inStream.open("/usr/share/dict/words");
	if (inStream.is_open()) {
		while (getline(inStream, x)) {
			inStream >> x;
			double a = x[0];
			for (int i = 0; i < x.length(); ++i) {
				a = fmod(256 * a + 0.6180339887 * x[i], 1);
			}
			a *= 65536;
			hashes.at(uint16_t(a))++;
		}
		distributionTable("Multiplicative");
		hashes.clear();
	}
}

int main() {
	int i;
	cout << "Enter: \n1 for String Length \n2 for First Character \n3 for Additive Checksum \n4 for Remainder \n5 for Multiplicative \n6 to end program\n";
	cout << "Your Input: ";
	cin >> i;
	//Somehow a loop with do only one, a switch will do each function seperately and correctly
	switch (i) {
	case 1:
		system("CLS");
		stringLength();
		break;
	case 2:
		system("CLS");
		firstCharacter();
		break;
	case 3:
		system("CLS");
		sumCharacters();
		break;
	case 4:
		system("CLS");
		remainder();
		break;
	case 5:
		system("CLS");
		multiplicative();
		break;
	case 6:
		system("CLS");
		return 0;
	default:
		cout << "Invalid Choice, Restart the program \n";
		//Not a loop, remember the loop problem comment I mention
	}
	cout << endl;
	system("PAUSE");
	return 0;
}
