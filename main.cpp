#include "input_reader.h"
#include "stat_reader.h"

// main.cpp — точка входа.
int main() {
    TransportCatalogue catalogue;
    FillCatalogue(std::cin, catalogue);
    ProcessRequests(catalogue);
}








