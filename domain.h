#pragma once
#include "geo.h"
#include <vector>
#include <string>
#include <unordered_map>



namespace domain{

        

        struct Bus {
            std::string number;
            std::vector<std::string> stops;
            bool circular_route;
        };

        

        struct Stop {
            std::string name;
            geo::Coordinates coordinates;
        };
        
        


        

        struct RouteInfo {
            size_t stops_count;
            size_t unique_stops_count;
            double route_length;
            double curvature;
        };

        

}

