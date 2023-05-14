#include "geo.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <deque>
#include <vector>

/*transport_catalogue.h, transport_catalogue.cpp — класс транспортного справочника;*/ 

struct Bus{                                     /*ИНФОРМАЦИЯ ОБ АВТОБУСЕ*/      
    std::string bus_name;                      //имя автобуса
    std::vector<std::string> stops;             //все имеющиеся остановки этого автобуса
    bool circular_route;                        //круговой маршрут yes or not.
};

struct Stop{                                    /*ИНФОРМАЦИЯ ОБ ОСТАНОВКЕ*/
    std::string stop_name;                      //имя остановки
    Coordinates coordinate_stop;                //координаты остановки
};

struct InfoRoute{                               /*ИНФОРМАЦИЯ О МАРШРУТЕ*/
    size_t stops_count;                         //количество остановок
    size_t stops_unique_count;                  //количество уникальных остановок
    double distance_route;                      //длина маршрута
};

class TransportCatalogue{
    public:
    
    void AddStop(const std::string& s_name, Coordinates& coordinate);                                           //добавить остановку
    void AddBus(const std::string& route_name, const std::vector<std::string>&st_name, bool circular_route);    //добавить автобус
    const Stop* FindStop(std::string& stop_name) const;                                                         //найти остановку
    const Bus* FindBus(std::string& b_name) const;                                                              //найти автобус
    const InfoRoute GetBusInfo(std::string& route_name);                                                        //найти информацию о маршруте автобуса
    size_t StopsUniqueCount(std::string& unique_bus_name);                                                      //уникальное количество остановок автобуса


    private:
    std::deque<Stop> all_bus_stop_;                                             //все остановки
    std::deque<Bus> all_bus_info_;                                              //информация о всех автобусах
    std::unordered_map<std::string_view, const Bus*>busname_to_bus_;            //поиск по нэйму автобуса информацию об автобусе
    std::unordered_map<std::string_view, const Stop*>stopname_to_stop_;         //поиск по нэйму остановки информацию об остановке
};