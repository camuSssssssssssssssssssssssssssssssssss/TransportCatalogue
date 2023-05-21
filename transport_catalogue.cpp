#include "transport_catalogue.h"

void TransportCatalogue::AddBusRoute(Bus& businfo) {
    buses_.push_back(businfo);
    finderbus_[buses_.back().number] = &buses_.back();
    for (const auto& stop : buses_.back().stops) {
        bustoforstop_[stop].insert(businfo.number);
    }

}

void TransportCatalogue::AddBusStop(Stop& stopinfo) {
    stops_.push_back(stopinfo);
    finderstop_[stops_.back().name] = &stops_.back();
}

const Bus* TransportCatalogue::FindBusRoute(const std::string& route_number) const {
    if (finderbus_.count(route_number)) {
        return finderbus_.at(route_number);
    }
    else
        return nullptr;
}

Stop* TransportCatalogue::FindBusStop(const std::string& stop_name) const {
    if (finderstop_.count(stop_name)) {
        return finderstop_.at(stop_name);
    }
    else
        return nullptr;
}

const RouteInfo TransportCatalogue::BusRouteInformation(const std::string& route_number) const {

    RouteInfo info{};
    auto find_ = finderbus_.find(route_number);

    auto bus = FindBusRoute(route_number);
    if (!bus){ 
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
        length += ComputeDistance(finderstop_.at(find_->second->stops[i - 1])->coordinates, finderstop_.at(find_->second->stops[i])->coordinates);
        if (bus->circular_route != true) {
            geo_length += GetStopDistance(finderstop_.at(find_->second->stops[i - 1]), finderstop_.at(find_->second->stops[i])) +
                GetStopDistance(finderstop_.at(find_->second->stops[i]), finderstop_.at(find_->second->stops[i - 1]));
        }
        else {
            GetStopDistance(finderstop_.at(find_->second->stops[i - 1]), finderstop_.at(find_->second->stops[i]));
        }
        
    }
    if (bus->circular_route != true) {
        length *= 2;
    }

    info.unique_stops_count = UniqueStopsCount(route_number);
    info.route_length = length;
    info.curvature = geo_length;
    return info;
}

size_t TransportCatalogue::UniqueStopsCount(const std::string& route_number) const {
    std::unordered_set<std::string>unique;
    for (const auto& stop : finderbus_.at(route_number)->stops) {
        unique.insert(stop);
    }
    return unique.size();
}

std::set<std::string>TransportCatalogue::BusToStop(const std::string& stop_name) const {
    if (bustoforstop_.count(stop_name)) {
        return bustoforstop_.at(stop_name);
    }
    return {};
}


void TransportCatalogue::SetStopDistance(Stop* from, Stop* to, int dist){
    from->stop_distances[to->name] = dist;
}

int TransportCatalogue::GetStopDistance(const Stop* f, const Stop* t) const{
    if (f->stop_distances.count(t->name)) {
        return f->stop_distances.at(t->name);
    }   
    else if (t->stop_distances.count(f->name)) {
        return t->stop_distances.at(f->name);
    }
    else {
        return 0;
    }     
}



