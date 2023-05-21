#pragma once

#include "geo.h"

#include <deque>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <set>
#include <map>
#include <functional>
#include <unordered_set>


struct Bus {
    std::string number;
    std::vector<std::string> stops;
    bool circular_route;
};


struct Stop {
    std::string name;
    Coordinates coordinates;
    std::unordered_map<std::string, int> stop_distances;
};

struct RouteInfo {
    size_t stops_count;
    size_t unique_stops_count;
    double route_length;
    double curvature;
};


class TransportCatalogue {
public:
    void AddBusRoute(Bus&);
    void AddBusStop(Stop&);
    const Bus* FindBusRoute(const std::string& route_number) const;
    Stop* FindBusStop(const std::string& stop_name) const;
    const RouteInfo BusRouteInformation(const std::string& route_number) const;
    size_t UniqueStopsCount(const std::string& route_number) const;
    std::set<std::string>BusToStop(const std::string& stop_name) const;
    void SetStopDistance(Stop* from, Stop* to, int distance);
    int GetStopDistance(const Stop* from, const Stop* to) const;

private:
    std::deque<Bus> buses_;
    std::deque<Stop> stops_;
    std::unordered_map<std::string_view, const Bus*> finderbus_;
    std::unordered_map<std::string_view, Stop*> finderstop_;
    std::unordered_map<std::string, std::set<std::string>> bustoforstop_;
};
