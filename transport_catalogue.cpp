#include "transport_catalogue.h"
#include <iostream>

void TransportCatalogue::AddBusRoute(const std::string& route_number, const std::vector<std::string>& route_stops, bool circular_route) {

    buses_.push_back({ route_number, route_stops, circular_route });
    std::string_view a = buses_.back().number;
    finderbus_[a] = &buses_.back();
}

void TransportCatalogue::AddBusStop(const std::string& stop_name, Coordinates& coordinates) {

    stops_.push_back({ stop_name, coordinates });
    std::string_view b = stops_.back().name;
    finderstop_[b] = &stops_.back();
}

const Bus* TransportCatalogue::FindBusRoute(const std::string& route_number) const {
    if (finderbus_.count(route_number)) {
        return finderbus_.at(route_number);
    }
    else
        return nullptr;

}

const Stop* TransportCatalogue::FindBusStop(const std::string& stop_name) const {
    if (finderstop_.count(stop_name)) {
        return finderstop_.at(stop_name);
    }
    else
        return nullptr;
}

// КОД ВЫШЕ РАБОТАЕТ


const RouteInfo TransportCatalogue::BusRouteInformation(const std::string& route_number) const {

    RouteInfo info{};
    auto find_ = finderbus_.find(route_number);

    auto bus = FindBusRoute(route_number);
    if (!bus) { std::cout << "notFound"; return { 0,0,0 }; }

    if (bus->circular_route) {
        info.stops_count = bus->stops.size();
    }
    else {
        info.stops_count = bus->stops.size() * 2 - 1;
    }

    double length = 0.0;
    for (size_t i = 1; i < bus->stops.size(); ++i){
        length += ComputeDistance(finderstop_.at(find_->second->stops[i - 1])->coordinates, finderstop_.at(find_->second->stops[i])->coordinates); //bug
    }
    if (find_->second->circular_route != true) {
            length *= 2;
    }

    info.unique_stops_count = UniqueStopsCount(route_number);
    info.route_length = length;

    return info;
}

size_t TransportCatalogue::UniqueStopsCount(const std::string& route_number) const {
    std::unordered_set<std::string>unique;
    for (const auto& stop : finderbus_.at(route_number)->stops) {
        unique.insert(stop);
    }
    return unique.size();
}



