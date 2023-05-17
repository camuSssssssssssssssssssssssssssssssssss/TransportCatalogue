#include "stat_reader.h"

#include <iomanip>

void ProcessRequests(TransportCatalogue& catalogue) {
    size_t requests_count;
    std::cin >> requests_count;
    for (size_t i = 0; i < requests_count; ++i) {
        std::string line;
        std::cin >> line;
        if (line.empty()) 
            break;
        std::getline(std::cin, line);
        std::string route_number = line.substr(1, line.npos);
        if (catalogue.FindRoute(route_number)) {
            std::cout << "Bus " << route_number << ": " << catalogue.RouteInformation(route_number).stops_count << " stops on route, " << catalogue.RouteInformation(route_number).unique_stops_count << " unique stops, " << catalogue.RouteInformation(route_number).route_length << " route length\n";
        }
        else {
            std::cout << "Bus " << route_number << ": not found\n";
        }
    }
}
