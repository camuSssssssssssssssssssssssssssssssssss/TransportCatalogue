#pragma once

#include "geo.h"

#include <deque>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <set>
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
    void AddBusRoute(const std::string& route_number, const std::vector<std::string>& route_stops, bool circular_route);
    void AddBusStop(const std::string& stop_name, Coordinates& coordinates);
    const Bus* FindBusRoute(const std::string& route_number) const;
    const Stop* FindBusStop(const std::string& stop_name) const;
    const RouteInfo BusRouteInformation(const std::string& route_number) const;
    size_t UniqueStopsCount(const std::string& route_number) const;
    std::set<std::string>BusToStop(const std::string& stop_name) const;

private:
    std::deque<Bus> buses_;
    std::deque<Stop> stops_;
    std::unordered_map<std::string_view, const Bus*> finderbus_;
    std::unordered_map<std::string_view, const Stop*> finderstop_;
    std::unordered_map<std::string, std::set<std::string>>bustoforstop;
    

        /*
        
        Bus 256
        Bus 750
        Bus 751

        Stop Samara
        Stop Prazhskaya
        Stop Biryulyovo Zapadnoye
        
        */
  
    /*
    Bus 256: 6 stops on route, 5 unique stops, 4371.02 route length
    Bus 750: 5 stops on route, 3 unique stops, 20939.5 route length
    Bus 751: not found

    Stop Samara : not found
    Stop Prazhskaya : no buses
    Stop Biryulyovo Zapadnoye : buses 256 828
    
    */
};
