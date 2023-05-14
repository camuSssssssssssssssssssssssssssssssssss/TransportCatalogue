#include "transport_catalogue.h"

void TransportCatalogue::AddStop(const std::string& s_name, Coordinates& coordinate){
    all_bus_stop_.push_back({s_name, coordinate});
}

void TransportCatalogue::AddBus(const std::string& route_name, const std::vector<std::string>&st_name, bool circular_route){
    all_bus_info_.push_back({route_name, st_name, circular_route});
}

const Stop* TransportCatalogue::FindStop(std::string& stop_name) const {

}

const Bus* TransportCatalogue::FindBus(std::string& b_name) const {

}

const InfoRoute TransportCatalogue::GetBusInfo(std::string& route_name){

}

size_t TransportCatalogue::StopsUniqueCount(std::string& unique_bus_name){

}

