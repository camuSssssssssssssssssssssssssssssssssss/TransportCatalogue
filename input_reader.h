#pragma once

#include "geo.h"
#include "transport_catalogue.h"

#include <iostream>

/*input_reader.h, input_reader.cpp — чтение запросов на заполнение базы;*/

void FillTransportCatalogue(TransportCatalogue&);

Bus ParseBus(std::string&);
Stop ParseStop(std::string& line);
void AddStopDistances(std::string& line, TransportCatalogue& catalogue);

