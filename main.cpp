#include "json_reader.h"
#include "request_handler.h"

int main() {
    infocatalogue::TransportCatalogue catalogue;
    JSONReader json_doc(std::cin);

    json_doc.FillCatalogue(catalogue);

    const auto& stat_requests = json_doc.StatRequests();
    const auto& render_settings = json_doc.RenderSettings();
    const auto& renderer = json_doc.FillRenderSettings(render_settings);
    const auto& routing_settings = json_doc.FillRoutingSettings(json_doc.RoutingSettings());
    const transport_router::Router router = { routing_settings, catalogue };

    RequestHandler rh(catalogue, renderer, router);
    rh.ProcessRequests(stat_requests);
}
