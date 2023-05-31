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



//infostruct::Stop fill::ParseStop(std::string& inf) {
//	infostruct::Stop stop;
//	std::string stop_name = inf.substr(1, inf.find_first_of(':') - inf.find_first_of(' ') - 1);
//
//	double latitude = std::stod(inf.substr(inf.find_first_of(':') + 2, inf.find_first_of(',') - 1));
//	double longitude;
//	inf.erase(0, inf.find_first_of(',') + 2);
//	if (inf.find_last_of(',') == inf.npos) {
//		longitude = std::stod(inf.substr(0, inf.npos - 1));
//		inf.clear();
//	}
//	else {
//		longitude = std::stod(inf.substr(0, inf.find_first_of(',')));
//		inf.erase(0, inf.find_first_of(',') + 2);
//	}
//	coordinate::Coordinates stop_coordinates = { latitude, longitude };
//
//	stop.name = stop_name;
//	stop.coordinates = stop_coordinates;
//
//	return stop;
//}

//void jReader::JsonReadInfo::PrintInfo() {
//	json::Array arr = BusReq().AsArray();
//	for (const auto& ar : arr) {
//		ar.AsMap().at("name").AsString();
//	}
//
//}




