
#include "request_handler.h"

std::optional<domain::Bus> RequestHandler::GetBusStat(const std::string_view& bus_name) const
{
	return std::optional<domain::Bus>();
}

const std::unordered_set<domain::Bus>* RequestHandler::GetBusesByStop(const std::string_view& stop_name) const
{
	return nullptr;
}
