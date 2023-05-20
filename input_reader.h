#pragma once

#include "geo.h"
#include "transport_catalogue.h"

#include <iostream>

/*input_reader.h, input_reader.cpp — чтение запросов на заполнение базы;*/

void FillCatalogue(TransportCatalogue&);

void ParseStop(TransportCatalogue&, std::string);
void ParseBus(TransportCatalogue&, std::string);
std::pair<std::vector<std::string>, bool> FillRoute(std::string& line);

