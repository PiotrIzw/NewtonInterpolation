#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

class NewtonInterpolation {

private:
	string line;
	fstream file;
	float x[100], y[100], searchedValue = 1.0, numberOfNodes[1], result, resultTemp = 0;
	void loadData(string filename, float array[]);
public:

	float findPolynomial(string filenumberOfNodes,
		string fileInterpolationNodes,
		string fileFunctionValues,
		float x);
};

void NewtonInterpolation::loadData(string filename, float array[]) {
	int i = 0;
	file.open(filename, ios::in);
	if (file.good() == true)
	{
		while (!file.eof())
		{
			getline(file, line);
			array[i] = stof(line); // stof - konwersja string do float
			i++;
		}
		file.close();
	}
}


float NewtonInterpolation::findPolynomial(string filenumberOfNodes,
	string fileInterpolationNodes,
	string fileFunctionValues, float point) {

	loadData(filenumberOfNodes, numberOfNodes);
	loadData(fileInterpolationNodes, x);
	loadData(fileFunctionValues, y);

	for (int i = 0; i < numberOfNodes[0] - 1; i++) {
		for (int j = 0; j < numberOfNodes[0] - 1 - i; j++) {
			y[j] = (y[j + 1] - y[j]) / (x[i + j + 1] - x[j]); //przypisywanie wartosci ilorazu roznicowego
			//cout << "Wspolczynnik wielomianu: rzad nr. " << i + 1 << ": " << y[j] << endl;
		}
		cout << y[0]; //wyswietlamy wspolczynnik wielomianu

		int k = 0;
		while (k <= i) {
			cout << "(x - " << x[k] << ")"; //dalsza czesc wzoru
			searchedValue *= (point - x[k]);
			k++;
		}
		if (i < numberOfNodes[0] - 2) cout << " + "; //formatowanie wyswietlania znaku +
		cout << endl;

		searchedValue *= y[0];
		resultTemp += searchedValue;
		searchedValue = 1.0;
	}

	result = resultTemp;
	resultTemp = 0;
	return result;
}


int main()
{
	NewtonInterpolation test;

	float x;
	while (true) {
		cout << "Podaj punkt: ";
		cin >> x;
		cout << "Wartosc wielomianu dla punktu " << x << " wynosi: " <<
			test.findPolynomial("numberofnodes.txt", "xvalues.txt", "yvalues.txt", x) << endl;
	}

	system("Pause");
	return 0;
}
