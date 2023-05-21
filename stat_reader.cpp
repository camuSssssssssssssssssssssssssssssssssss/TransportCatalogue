#include "stat_reader.h"

#include <iomanip>

void OutTransport(TransportCatalogue& catalogue) {
    size_t requests_count;
    std::cin >> requests_count;
    for (size_t i = 0; i < requests_count; ++i) {
        std::string keyword, line;
        std::cin >> keyword;
        std::getline(std::cin, line);
        if (keyword == "Bus") {
            OutBus(catalogue, line);
        }
        if (keyword == "Stop") {
            OutStop(catalogue, line);
        }
    }
}

void OutBus(TransportCatalogue& ctlg, std::string inf) {
    std::string route_number = inf.substr(1, inf.npos);
    if (ctlg.FindBusRoute(route_number)) {
        std::cout << "Bus " << route_number << ": " << ctlg.BusRouteInformation(route_number).stops_count << " stops on route, "
            << ctlg.BusRouteInformation(route_number).unique_stops_count << " unique stops, " << ctlg.BusRouteInformation(route_number).route_length << " route length, "
            << ctlg.BusRouteInformation(route_number).curvature << " curvature\n";
    }
    else {
        std::cout << "Bus " << route_number << ": not found\n";
    }
}


void OutStop(TransportCatalogue& ctlg, std::string inf){
    if (ctlg.FindBusStop(inf) == nullptr) {
        std::cout << "Stop " << inf << ": not found" << std::endl;
    }
    else {
        auto a = ctlg.BusToStop(inf);
        if (a.empty()) {
            std::cout << "Stop " << inf << ": no buses" << std::endl;
        }
        else {
            std::cout << "Stop " << inf << ": buses ";
            for (const auto& bus : a) {
                std::cout << bus << " ";
            }
            std::cout << std::endl;
        }
    }
}
