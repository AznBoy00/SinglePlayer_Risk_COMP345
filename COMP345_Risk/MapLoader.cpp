#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "MapLoader.h"
#include <algorithm>
using namespace std;

MapLoader::MapLoader(std::string fileDirectory) {
	ifstream inputfilestream;
	inputfilestream.open(fileDirectory);

	string line;
	bool hasTerritories = false;
	bool hasMap = false;
	bool hasContinents = false;

	Map* m = new Map();
	while (getline(inputfilestream, line)) {
		//if the [Territory] header is found and line is not empty, start reading
		if (hasTerritories && !line.empty()) {
			//create a country based on the info read on that line
			Country* territory = new Country();
			stringstream ss(line);
			string word;
			vector<string> lineVector;
			//store each read word in the line into a vector
			while (getline(ss, word, ',')) {
				lineVector.push_back(word);
			}
			//set Country's member values based on the words that are read
			if (!m->isMapContainsCountry(lineVector.at(0))) {

				territory->setNameOfCountry(lineVector.at(0));
				territory->setCoordinateX(stoi(lineVector.at(1))); //converting X to int
				territory->setCoordinateY(stoi(lineVector.at(2))); //converting Y to int
				territory->setContinent(lineVector.at(3));
				m->setContainedCountryInMap(territory); //add that country to the list of countries in the map

			}
			else {
				cout << "Error: Duplicate country.";
				exit(0);
			}


		}
		//Checks for Map, Continent and Territories headers to validate map
		if (line.find("[Map]") != string::npos) {
			hasMap = true;
		}
		if (line.find("[Continents]") != string::npos) {
			hasContinents = true;
		}
		if (line.find("[Territories]") != string::npos && hasMap && hasContinents) {
			hasTerritories = true;

		}
	}
	hasTerritories = false;
	inputfilestream.clear();
	inputfilestream.seekg(0, std::ios::beg);
	while (getline(inputfilestream, line)) {
		//if the [Territory] header is found, start reading
		if (hasTerritories && !line.empty()) {
			stringstream ss(line);
			string word;
			vector<string> lineVector;
			//store each read word in the line into a vector
			while (getline(ss, word, ',')) {
				lineVector.push_back(word);
			}
			Country* territory = m->getCountryByName(lineVector.at(0));
			for (int i = 4; i < lineVector.size(); i++) {
				territory->setNeighboringCountry(m->getCountryByName(lineVector.at(i)));
			}
			cout << "Country name is: " << territory->getNameOfCountry() << endl;
			cout << "X: " << territory->getCoordinateX() << " Y: " << territory->getCoordinateY() << endl;
			cout << "Continent: " << territory->getContinent() << endl;
			cout << "Neighbors: ";
			for (int i = 0; i<territory->getNeighboringCountries().size(); i++) {
				cout << territory->getNeighboringCountries().at(i)->getNameOfCountry() << " ";
			}
			cout << endl;
		}

		if (line.find("[Territories]") != string::npos && hasMap && hasContinents) {
			hasTerritories = true;

		}
	}

	//If no checks are passed, map is invalid.
	if (!hasMap || !hasContinents || !hasTerritories) {
		cout << "Invalid map.";
		exit(0);
	}

	//Check for number of countries
	cout << "Number of countries: " << m->getContainedCountriesInMap().size() << endl;
	//Check neighbors to check graph connectivity
	//cout << m->getContainedCountries.at(0)->getNeighboringCountries().at(0)->getNeighboringCountries.at(0)->getNeighboringCountries.at(0).getCountryName();
	Country* test = m->getContainedCountriesInMap().at(0);
	cout << test->getNeighboringCountries().at(0)->getNameOfCountry();
	cout << test->getNeighboringCountries().at(0)->getNeighboringCountries().at(0)->getNameOfCountry();
	//delete m;

}