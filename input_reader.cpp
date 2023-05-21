#include "input_reader.h"

#include <string>
#include <vector>
#include <cmath>

void FillTransportCatalogue(TransportCatalogue& catalogue) {
    
    size_t requests_count;

    std::vector<std::string> buses_;
    std::vector<std::string> stops_;
    std::vector<std::string> stop_distances_;

    std::cin >> requests_count;
    for (size_t i = 0; i < requests_count; ++i) {
        std::string keyword, line;
        std::cin >> keyword;
        std::getline(std::cin, line);
        if (keyword == "Stop") {
            stops_.push_back(line);
        }
        if (keyword == "Bus") {
            buses_.push_back(line);
        }
    }
    stop_distances_ = stops_;
    for (auto& stop_ : stops_) {
        Stop stop = ParseStop(stop_);
        catalogue.AddBusStop(stop);
    }
    for (auto& stop_ : stop_distances_) {
        AddStopDistances(stop_, catalogue);
    }
    for (auto& bus_ : buses_) {
        Bus bus = ParseBus(bus_);
        catalogue.AddBusRoute(bus);
        bus = {};
    }
}

Stop ParseStop(std::string& line) {
    Stop stop;
    std::string stop_name = line.substr(1, line.find_first_of(':') - line.find_first_of(' ') - 1);
    double lat = std::stod(line.substr(line.find_first_of(':') + 2, line.find_first_of(',') - 1));
    double lng;
    line.erase(0, line.find_first_of(',') + 2);
    if (line.find_last_of(',') == line.npos) {
        lng = std::stod(line.substr(0, line.npos - 1));
        line.clear();
    }
    else {
        lng = std::stod(line.substr(0, line.find_first_of(',')));
        line.erase(0, line.find_first_of(',') + 2);
    }
    Coordinates stop_coordinates = { lat, lng };

    stop.name = stop_name;
    stop.coordinates = stop_coordinates;

    return stop;
}

Bus ParseBus(std::string& line) {
    Bus bus_info;
    std::vector<std::string> route_stops;
    std::string route_number = line.substr(1, line.find_first_of(':') - 1);
    line.erase(0, line.find_first_of(':') + 2);
    bool circular_route = false;
    std::string stop_name;
    auto pos = line.find('>') != line.npos ? '>' : '-';
    while (line.find(pos) != line.npos) {
        stop_name = line.substr(0, line.find_first_of(pos) - 1);
        route_stops.push_back(stop_name);
        line.erase(0, line.find_first_of(pos) + 2);
    }
    stop_name = line.substr(0, line.npos - 1);
    route_stops.push_back(stop_name);
    if (pos == '>') circular_route = true;

    bus_info.circular_route = circular_route;
    bus_info.number = route_number;
    bus_info.stops = route_stops;
    return bus_info;
}

void AddStopDistances(std::string& line, TransportCatalogue& catalogue) {
    if (!line.empty()) {
        std::string stop_from_name = ParseStop(line).name;
        Stop* from = catalogue.FindBusStop(stop_from_name);

        while (!line.empty()) {
            int distanse = 0;
            std::string stop_to_name;
            distanse = std::stoi(line.substr(0, line.find_first_of("m to ")));
            line.erase(0, line.find_first_of("m to ") + 5);
            if (line.find("m to ") == line.npos) {
                stop_to_name = line.substr(0, line.npos - 1);
                Stop* to = catalogue.FindBusStop(stop_to_name);
                catalogue.SetStopDistance(from, to, distanse);
                if (!catalogue.FindBusStop(to->name)->stop_distances.count(from->name)) {
                    catalogue.SetStopDistance(to, from, distanse);
                }
                line.clear();
            }
            else {
                stop_to_name = line.substr(0, line.find_first_of(','));
                Stop* to = catalogue.FindBusStop(stop_to_name);
                catalogue.SetStopDistance(from, to, distanse);
                if (!catalogue.FindBusStop(to->name)->stop_distances.count(from->name)) {
                    catalogue.SetStopDistance(to, from, distanse);
                }
                line.erase(0, line.find_first_of(',') + 2);
            }
        }
    }
}

