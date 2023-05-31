#include "json_reader.h"

json::Node jReader::JsonReadInfo::BusReq() const {
	if (!input_.GetRoot().AsMap().count("base_requests")) {
		return nullptr;
	}
	return input_.GetRoot().AsMap().at("base_requests");
}

json::Node jReader::JsonReadInfo::StopReq() const
{
	return json::Node();
	
}

void jReader::JsonReadInfo::ParseInfo(infocatalogueclass::TransportCatalogue& ctlg) {
	
	domain::Bus bus_info;
	domain::Stop stop_info;
	json::Array array = BusReq().AsArray();
	for (const auto& arr : array) {
		auto info_type = arr.AsMap().at("type").AsString();
		if (info_type == "Bus") {
			std::vector<std::string>stops;
			std::string bus_name;
			bool circular;
			bus_name = arr.AsMap().at("name").AsString();
			for (auto& stop : arr.AsMap().at("stops").AsArray()) {
				stops.push_back(stop.AsString());
			}
			circular = arr.AsMap().at("is_roundtrip").AsBool();
			bus_info.number = bus_name;
			bus_info.stops = stops;
			bus_info.circular_route = circular;
			ctlg.AddBusRoute(bus_info);
		}
		else if (info_type == "Stop") {
			std::string stop_name;
			stop_name = arr.AsMap().at("name").AsString();
			auto longitude = arr.AsMap().at("longitude").AsDouble();
			auto latitude = arr.AsMap().at("latitude").AsDouble();
			geo::Coordinates stop_coordinate = { latitude, longitude };
			stop_info.name = stop_name;
			stop_info.coordinates = stop_coordinate;
			ctlg.AddBusStop(stop_info);			
		}
	}
}


void jReader::JsonReadInfo::FillStopDistances(infocatalogueclass::TransportCatalogue& ctlg){
	const json::Array& array = BusReq().AsArray();
	for (auto& request_stops : array) {
		const auto& request_stops_map = request_stops.AsMap();
		const auto& type = request_stops_map.at("type").AsString();
		if (type == "Stop") {
			auto [stop_name, coordinates, stop_distances] = FillStop(request_stops_map);
			for (auto& [to_name, dist] : stop_distances) {
				auto from = ctlg.FindBusStop(stop_name);
				auto to = ctlg.FindBusStop(to_name);
				ctlg.SetStopDistance(from, to, dist);
			}
		}
	}
}

std::tuple<std::string, geo::Coordinates, std::map<std::string, int>> jReader::JsonReadInfo::FillStop(const json::Dict& request_map) const {
	std::string stop_name = request_map.at("name").AsString();
	geo::Coordinates coordinates = { request_map.at("latitude").AsDouble(), request_map.at("longitude").AsDouble() };
	std::map<std::string, int> stop_distances;
	auto& distances = request_map.at("road_distances").AsMap();
	for (auto& [stop_name, dist] : distances) {
		stop_distances.emplace(stop_name, dist.AsInt());
	}
	return std::make_tuple(stop_name, coordinates, stop_distances);
}

