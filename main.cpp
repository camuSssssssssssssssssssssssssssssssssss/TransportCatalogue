#include <iostream>
#include <string>
#include <vector>

//#include "transport_catalogue.h"
//#include "input_reader.h"
//#include "stat_reader.h"

void CatalogueFill(std::istream& in) {
	size_t count;										//количество запросов
	in >> count;
	for (size_t i = 0; i <= count; ++i) {
		std::string line, key;
		std::getline(in, line);
		key = line.substr(0, line.find(' '));
		if (key == "Stop") {
			std::string stop_name = line.substr(line.find(' ') + 1, line.find_first_of(':') - line.find(' ') - 2);
			std::string latandlong = line.substr(line.find(':') + 1);
			double latitude = std::stod(latandlong.substr(latandlong.find_first_of(" "), latandlong.find_first_of(",")));
			double longitude = std::stod(latandlong.substr(latandlong.find_first_of(",") + 1, latandlong.find_last_of(" ")));
		}

		else if (key == "Bus") {

		}
	}

}

//std::pair<std::vector<std::string>, bool>RouteFill(std::string& info) {
//
//}
// main.cpp — точка входа.
int main() {
        	CatalogueFill(std::cin);
	//TransportCatalogue transport_catalogue;

 //   CatalogueFill(std::cin, transport_catalogue);
    
}

//10
//Stop Tolstopaltsevo : 55.611087, 37.208290
//Stop Marushkino : 55.595884, 37.209755
//Bus 256 : Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye
//Bus 750: Tolstopaltsevo - Marushkino - Rasskazovka
//Stop Rasskazovka : 55.632761, 37.333324
//Stop Biryulyovo Zapadnoye : 55.574371, 37.651700
//Stop Biryusinka : 55.581065, 37.648390
//Stop Universam : 55.587655, 37.645687
//Stop Biryulyovo Tovarnaya : 55.592028, 37.653656
//Stop Biryulyovo Passazhirskaya : 55.580999, 37.659164
//3
//Bus 256
//Bus 750
//Bus 751






