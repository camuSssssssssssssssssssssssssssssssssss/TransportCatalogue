#include "stat_reader.h"

#include <iomanip>

void OutTransport(TransportCatalogue& catalogue) {
    size_t requests_count;
    std::cin >> requests_count;
    for (size_t i = 0; i < requests_count; ++i) {
        std::string line, key;
        std::cin >> key;
        std::getline(std::cin, line);
        if (key == "Bus") {
            std::string route_number = line.substr(1, line.npos);
            if (catalogue.FindBusRoute(route_number)) {
                std::cout << "Bus " << route_number << ": " << catalogue.BusRouteInformation(route_number).stops_count << " stops on route, " << catalogue.BusRouteInformation(route_number).unique_stops_count << " unique stops, " << catalogue.BusRouteInformation(route_number).route_length << " route length\n";
            }
            else {
                std::cout << "Bus " << route_number << ": not found\n";
            }
        }

        else if (key == "Stop") {
            std::string stopinfo = line.substr(1, line.npos);
            if (!catalogue.FindBusStop(stopinfo))
                std::cout << "Stop: " << stopinfo << ": not found" << std::endl;
            else {
                if (catalogue.BusToStop(stopinfo).empty()) {
                    std::cout << "Stop: " << stopinfo << ": no buses" << std::endl;
                }
                else {
                    std::cout << "Stop: " << stopinfo << ": buses ";
                    for (const auto& elsestop : catalogue.BusToStop(stopinfo)) {
                        std::cout << elsestop << " ";
                    }
                    std::cout << std::endl;
                }
            }

        }
        
    }
    
}
