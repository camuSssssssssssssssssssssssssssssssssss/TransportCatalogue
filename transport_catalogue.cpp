#include "transport_catalogue.h"

void TransportCatalogue::AddStop(const std::string& s_name, Coordinates& coordinate) {
    all_bus_stop_.push_back({ s_name, coordinate });
    stopname_to_stop_[s_name] = &all_bus_stop_.back(); //добавление ключа[s_name] в unordered_map, значение - указатель на последний элемент.
}

void TransportCatalogue::AddBus(const std::string& route_name, const std::vector<std::string>& st_name, bool circular_route) {
    all_bus_info_.push_back({ route_name, st_name, circular_route });
    busname_to_bus_[route_name] = &all_bus_info_.back(); //добавление ключа[route_name] в unordered_map, значение - указатель на последний элемент.
}

const Stop* TransportCatalogue::FindStop(std::string& stop_name) const {
    auto it = stopname_to_stop_.find(stop_name);
    if (it == stopname_to_stop_.end()) {
        return nullptr;                         //если не нашли значение по ключу
    }
    return (*it).second;
}

const Bus* TransportCatalogue::FindBus(std::string& b_name) const {
    auto it = busname_to_bus_.find(b_name);
    if (it == busname_to_bus_.end()) {
        return nullptr;                         //если не нашли значение по ключу
    }
    return it->second;
}

const InfoRoute TransportCatalogue::GetBusInfo(std::string& route_name) {

}

size_t TransportCatalogue::StopsUniqueCount(std::string& route) const{

}


