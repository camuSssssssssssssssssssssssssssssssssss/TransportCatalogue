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
#include <unordered_set>
#include <functional>
#include "domain.h"
#include "geo.h"




namespace infocatalogueclass {
    class TransportCatalogue {
    public:

        
        struct StopsHasher {
            size_t operator()(const std::pair<const domain::Stop*, const domain::Stop*>& points) const {
                size_t hash_first = std::hash<const void*>{}(points.first);
                size_t hash_second = std::hash<const void*>{}(points.second);
                return hash_first + hash_second * 37;
            }
        };

        void AddBusRoute(const domain::Bus&);
        void AddBusStop(const domain::Stop&);
        const domain::Bus* FindBusRoute(const std::string&) const;
        domain::Stop* FindBusStop(const std::string&) const;
        const domain::RouteInfo BusRouteInformation(const std::string&) const;
        size_t UniqueStopsCount(const std::string&) const;
        std::set<std::string>BusToStop(const std::string&) const;
        void SetStopDistance(domain::Stop*, domain::Stop*, int);
        int GetStopDistance(const domain::Stop*, const domain::Stop*) const;

        

    private:
        std::deque<domain::Bus> buses_;
        std::deque<domain::Stop> stops_;
        std::unordered_map<std::string_view, const domain::Bus*> finderbus_;
        std::unordered_map<std::string_view, domain::Stop*> finderstop_;
        std::unordered_map<std::string, std::set<std::string>> bustoforstop_;
        std::unordered_map<std::pair<const domain::Stop*, const domain::Stop*>, int, StopsHasher> stop_distances;
    };
}
