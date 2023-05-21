#pragma once
#include "transport_catalogue.h"
#include <iostream>
/*stat_reader.h, stat_reader.cpp — чтение запросов на вывод и сам вывод;*/
void OutTransport(TransportCatalogue& catalogue);
void OutBus(TransportCatalogue&, std::string);
void OutStop(TransportCatalogue&, std::string);
