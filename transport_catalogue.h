#pragma once

#include "geo.h"

#include <deque>
#include <string>
#include <unordered_map>
#include <vector>
#include <optional>
#include <stdexcept>
#include <unordered_set>

struct Bus {
    std::string number;
    std::vector<std::string> stops;
    bool circular_route;
};

struct Stop {
    std::string name;
    Coordinates coordinates;
};

struct RouteInfo {
    size_t stops_count;
    size_t unique_stops_count;
    double route_length;
};

class TransportCatalogue {
public:
    void AddRoute(const std::string& route_number, const std::vector<std::string>& route_stops, bool circular_route);
    void AddStop(const std::string& stop_name, Coordinates& coordinates);
    const Bus* FindRoute(const std::string& route_number) const;
    const Stop* FindStop(const std::string& stop_name) const;
    const RouteInfo RouteInformation(const std::string& route_number) const;
    size_t UniqueStopsCount(const std::string& route_number) const;

private:
    std::deque<Bus> buses_;
    std::deque<Stop> stops_;
    std::unordered_map<std::string_view, const Bus*> finderbus_;
    std::unordered_map<std::string_view, const Stop*> finderstop_;
};
