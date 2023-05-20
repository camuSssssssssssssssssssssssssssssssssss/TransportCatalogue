#include "input_reader.h"

void FillCatalogue(TransportCatalogue& catalogue) {
	size_t requests_count;
	std::cin >> requests_count;
	for (size_t i = 0; i < requests_count; ++i) {
		std::string keyword, line;
		std::cin >> keyword;

		if (keyword == "Stop") {
			std::getline(std::cin, line);
			ParseStop(catalogue, line);
		}
		else if (keyword == "Bus") {
			std::getline(std::cin, line);
			ParseBus(catalogue, line);
		}
	}
}

void ParseStop(TransportCatalogue& catalogue, std::string line) {
    std::unordered_map<std::string, int> distance_;

    std::string stop_name = line.substr(1, line.find_first_of(':') - line.find_first_of(' ') - 1);

    double lat = std::stod(line.substr(line.find_first_of(':') + 2));
    double lng = std::stod(line.substr(line.find_first_of(',') + 2));
    Coordinates stop_coordinates = { lat, lng };

    // Извлекаем информацию о расстояниях

	
	
}

void ParseBus(TransportCatalogue& catalogue, std::string line) {
	std::string route_number = line.substr(1, line.find_first_of(':') - 1);
	auto stopdata = line.substr(line.find(':') + 2);

	line.erase(0, line.find_first_of(':') + 2);
	auto [route_stops, circular_route] = FillRoute(line);
	catalogue.AddBusRoute(route_number, route_stops, circular_route);
	route_stops.clear();
	
}

std::pair<std::vector<std::string>, bool> FillRoute(std::string& line) {
	std::vector<std::string> stops;
	bool circular_route = false;
	std::string stop_name;
	auto pos = line.find('>') != line.npos ? '>' : '-';
	while (line.find(pos) != line.npos) {
		stop_name = line.substr(0, line.find_first_of(pos) - 1);
		stops.push_back(stop_name);
		line.erase(0, line.find_first_of(pos) + 2);
	}
	stop_name = line.substr(0, line.npos - 1);
	stops.push_back(stop_name);
	if (pos == '>') circular_route = true;

	return std::make_pair(stops, circular_route);
}

