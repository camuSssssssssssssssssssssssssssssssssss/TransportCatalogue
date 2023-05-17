#pragma once

#include "geo.h"
#include "transport_catalogue.h"

#include <iostream>

/*input_reader.h, input_reader.cpp — чтение запросов на заполнение базы;*/

void FillCatalogue(std::istream& in, TransportCatalogue& catalogue);

std::pair<std::vector<std::string>, bool> FillRoute(std::string& line);

