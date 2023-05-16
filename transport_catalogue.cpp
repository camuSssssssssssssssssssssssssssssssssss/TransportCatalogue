#include "transport_catalogue.h"

void TransportCatalogue::AddRoute(const std::string& route_number, const std::vector<std::string>& route_stops, bool circular_route) {
    buses_.push_back({ route_number, route_stops, circular_route });
    finderbus_[buses_.back().number] = &buses_.back();
}

void TransportCatalogue::AddStop(const std::string& stop_name, Coordinates& coordinates) {
    stops_.push_back({ stop_name, coordinates });
    finderstop_[stops_.back().name] = &stops_.back();
}

const Bus* TransportCatalogue::FindRoute(const std::string& route_number) const {
    if (finderbus_.count(route_number)) {
        return finderbus_.at(route_number);
    }
    return nullptr;
}

const Stop* TransportCatalogue::FindStop(const std::string& stop_name) const {
    if (finderstop_.count(stop_name)) {
        return finderstop_.at(stop_name);
    }
    return nullptr;
}

const RouteInfo TransportCatalogue::RouteInformation(const std::string& route_number) const {
    RouteInfo info;
    auto count = info.stops_count;
    auto length = info.route_length;
    auto bus = FindRoute(route_number);
    if (bus->circular_route) {
        count = bus->stops.size();
        info.stops_count
    }
    else {
        count = bus->stops.size() * 2 - 1;
    }

    for (size_t i = 1; i < bus->stops.size(); ++i) {

    }
    info.route_length =
    info.stops_count = count;
    info.unique_stops_count = UniqueStopsCount(route_number);

    return info;

    /*Bus 256: 6 stops on route, 5 unique stops, 4371.02 route length
          Bus 750 : 5 stops on route, 3 unique stops, 20939.5 route length
          Bus 751 : not found*/
}

size_t TransportCatalogue::UniqueStopsCount(const std::string& route_number) const {
    std::unordered_set<std::string>unique;
    for (const auto& stop : finderbus_.at(route_number)->stops) {
        unique.insert(stop);
    }
    return unique.size();
}


