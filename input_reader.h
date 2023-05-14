#pragma once
#include "transport_catalogue.h"

#include <iostream>
#include <string>

/*input_reader.h, input_reader.cpp — чтение запросов на заполнение базы;*/

void FillTransportCatalogue(std::ifstream& in, TransportCatalogue& catalogue);

