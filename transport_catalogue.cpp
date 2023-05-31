#include "transport_catalogue.h"

void infocatalogueclass::TransportCatalogue::AddBusRoute(const domain::Bus& businfo) {
    buses_.push_back(businfo);
    finderbus_[buses_.back().number] = &buses_.back();

    for (const auto& inf : buses_.back().stops) {
        bustoforstop_[inf].insert(businfo.number);
    }
}

void infocatalogueclass::TransportCatalogue::AddBusStop(const domain::Stop& stopinfo) {
    stops_.push_back(stopinfo);
    finderstop_[stops_.back().name] = &stops_.back();

}

const domain::Bus* infocatalogueclass::TransportCatalogue::FindBusRoute(const std::string& route_number) const {
    if (finderbus_.count(route_number)) {
        return finderbus_.at(route_number);
    }
    else
        return nullptr;
}

domain::Stop* infocatalogueclass::TransportCatalogue::FindBusStop(const std::string& stop_name) const {
    if (finderstop_.count(stop_name)) {
        return finderstop_.at(stop_name);
    }
    else
        return nullptr;
}

const domain::RouteInfo infocatalogueclass::TransportCatalogue::BusRouteInformation(const std::string& route_number) const {

    domain::RouteInfo info{};
    auto find_ = finderbus_.find(route_number);

    auto bus = FindBusRoute(route_number);
    if (!bus) {
        std::cout << "notFound"; return { 0,0,0 };
    }

    if (bus->circular_route) {
        info.stops_count = bus->stops.size();
    }
    else {
        info.stops_count = bus->stops.size() * 2 - 1;
    }

    double length = 0.0;
    double geo_length = 0.0;


    for (size_t i = 1; i < bus->stops.size(); ++i) {

        geo_length += geo::ComputeDistance(finderstop_.at(find_->second->stops[i - 1])->coordinates, finderstop_.at(find_->second->stops[i])->coordinates);
        if (bus->circular_route != true) {
            length += GetStopDistance(finderstop_.at(find_->second->stops[i - 1]), finderstop_.at(find_->second->stops[i])) +
                GetStopDistance(finderstop_.at(find_->second->stops[i]), finderstop_.at(find_->second->stops[i - 1]));
        }
        else {
            length += GetStopDistance(finderstop_.at(find_->second->stops[i - 1]), finderstop_.at(find_->second->stops[i]));
        }
        
    }
    if (bus->circular_route != true) {
        geo_length *= 2;
    }

    info.unique_stops_count = UniqueStopsCount(route_number);
    info.route_length = length;
    info.curvature = length / geo_length;
    return info;
}

size_t infocatalogueclass::TransportCatalogue::UniqueStopsCount(const std::string& route_number) const {
    std::unordered_set<std::string>unique;
    for (const auto& stop : finderbus_.at(route_number)->stops) {
        unique.insert(stop);
    }
    return unique.size();
}

std::set<std::string>infocatalogueclass::TransportCatalogue::BusToStop(const std::string& stop_name) const {
    if (bustoforstop_.count(stop_name)) {
        return bustoforstop_.at(stop_name);
    }
    return {};
}

void infocatalogueclass::TransportCatalogue::SetStopDistance(domain::Stop* from, domain::Stop* to, int dist) {
    stop_distances[{from, to}] = dist;
}

int infocatalogueclass::TransportCatalogue::GetStopDistance(const domain::Stop* from, const domain::Stop* to) const {
    if (stop_distances.count({ from, to })) {
        return stop_distances.at({ from, to });
    }
        
    else if (stop_distances.count({ to, from })) {
        return stop_distances.at({ to, from });
    }

    else {
        return 0;
    } 
}
