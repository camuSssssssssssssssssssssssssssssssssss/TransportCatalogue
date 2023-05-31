#pragma once
#include "json.h"
#include "transport_catalogue.h"
#include "map_renderer.h"
#include "domain.h"


namespace jReader {
	class JsonReadInfo {
	public:

		JsonReadInfo(json::Document input) : input_(input) {}

		json::Node BusReq() const;
		json::Node StopReq() const;

		void ParseInfo(infocatalogueclass::TransportCatalogue& ctlg);

	private:
		json::Document input_;
	};

}
