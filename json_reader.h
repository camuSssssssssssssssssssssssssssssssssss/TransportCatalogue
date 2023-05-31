#pragma once
#include "json.h"
#include "geo.h"
#include "transport_catalogue.h"
#include "map_render.h"
#include "domain.h"

namespace jReader {
	class JsonReadInfo {
	public:
		
		JsonReadInfo(json::Document input) : input_(input) {}
		
		json::Node BusReq() const;
		json::Node StopReq() const;

		void ParseInfo(infocatalogueclass::TransportCatalogue& ctlg);
		void FillStopDistances(infocatalogueclass::TransportCatalogue& ctlg);
		std::tuple<std::string, geo::Coordinates, std::map<std::string, int>> FillStop(const json::Dict& request_map) const;

	private:
		json::Document input_;
	};

	

}
