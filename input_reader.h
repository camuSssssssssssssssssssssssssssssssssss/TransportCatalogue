#pragma once
#include "transport_catalogue.h"

#include <iostream>
#include <string>

/*input_reader.h, input_reader.cpp — чтение запросов на заполнение базы;*/

void CatalogueFill(std::istream& in, TransportCatalogue catalogue);
std::pair<std::vector<std::string>, bool> RouteFill(std::string& line);

