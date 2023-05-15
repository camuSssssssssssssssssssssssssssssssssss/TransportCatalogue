#include "input_reader.h"

void CatalogueFill(std::istream& in, TransportCatalogue catalogue) {
	size_t count;										//количество запросов
	in >> count;
	for (size_t i = 0; i <= count; ++i) {
		std::string line, key;
		std::getline(in, line);
		key = line.substr(0, line.find(' '));
		if (key == "Stop") {
			std::string stop_name = line.substr(line.find(' ') + 1, line.find_first_of(':') - line.find(' ') - 2);				//поиск имени остановки
			std::string latandlong = line.substr(line.find(':') + 1);															//значения Х и Y
			double latitude = std::stod(latandlong.substr(latandlong.find_first_of(" "), latandlong.find_first_of(",")));		//значение X
			double longitude = std::stod(latandlong.substr(latandlong.find_first_of(",") + 1, latandlong.find_last_of(" ")));	//значение Y
			Coordinates coord = { latitude, longitude };																		//добавление в координаты
			catalogue.AddStop(stop_name, coord);																				//добавление остановки
		}

		else if (key == "Bus") {
			std::string bus_number = line.substr(line.find(' ') + 1, line.find_first_of(':') - line.find(' ') - 1); //номер автобуса
			auto [stop_route, circular_r] = RouteFill(line);														//название остановок маршрута и тип маршрута
			catalogue.AddBus(bus_number,stop_route,circular_r);														//добавляю маршрут
		}
	}
}


std::pair<std::vector<std::string>, bool> RouteFill(std::string& line) {											//заполняю маршрут
	std::vector<std::string> route_stops;																			
	bool circular_route = false;																					//если нет '>', то false

	std::string stop_name;
	std::size_t pos = 0;
	while (pos < line.length()) {
		std::size_t next_pos = line.find_first_of("->", pos);						/*В каждой итерации цикла происходит поиск следующего вхождения разделителя -> в строке с помощью функции find_first_of. 
																					Если вхождение найдено, то извлекается подстрока между текущей позицией pos и найденным вхождением next_pos.
																					Эта подстрока представляет собой отдельную остановку в маршруте, которая добавляется в вектор route_stops.*/
		if (next_pos == std::string::npos) {										/*Затем значение переменной pos обновляется,
																					чтобы указывать на позицию после найденного вхождения разделителя ->, 
																					и цикл переходит к следующей итерации для поиска следующей остановки.*/
			stop_name = line.substr(pos);
			route_stops.push_back(stop_name);
			break;
		}
		stop_name = line.substr(pos, next_pos - pos);
		route_stops.push_back(stop_name);
		pos = next_pos + 2;
	}

	circular_route = line.find(">") != std::string::npos;

	return std::make_pair(route_stops, circular_route);
}
