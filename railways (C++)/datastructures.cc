// Datastructures.cc
//

#include "datastructures.hh"

#include <random>

#include <cmath>

#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>
#include <queue>

/**
 * @brief Datastructures::Datastructures Constructor function for the class
 */
Datastructures::Datastructures()
{
    stations_= {};
}

/**
 * @brief Datastructures::~Datastructures Destruction function for the class
 */
Datastructures::~Datastructures()
{
    stations_.clear();
    regions_.clear();
    station_keys_.clear();
    region_keys_.clear();
    names_.clear();
}

/**
 * @brief Datastructures::station_count Returns the value of stations
 * @return int size of the stations map
 */
unsigned int Datastructures::station_count()
{
    return stations_.size();
}

/**
 * @brief Datastructures::clear_all Clears all structures in class
 */
void Datastructures::clear_all()
{
    stations_.clear();
    regions_.clear();
    station_keys_.clear();
    region_keys_.clear();
    names_.clear();
    distances_.clear();

}

/**
 * @brief Datastructures::all_stations Returns all station ids
 * @return a vector of all stationids
 */
std::vector<StationID> Datastructures::all_stations()
{
    if (keys_accurate == true) {
        return station_keys_;
    } else {
        station_keys_.clear();
        for (std::pair<StationID, Station> elem : stations_) {
            station_keys_.push_back(elem.first);
        }
        distances_accurate = true;
        return station_keys_;
    }

}

/**
 * @brief Datastructures::add_station Adds a new station
 * @param id of the station
 * @param name of the station
 * @param xy includes station coordinates
 * @return bool value whether adding was succesfull
 */
bool Datastructures::add_station(StationID id, const Name& name, Coord xy)
{
    if (stations_.find(id) == stations_.end()) {
        Station stat_1 = {id, name, xy, sqrt(pow(xy.x,2)+pow(xy.y,2))};
        stations_.insert({id, stat_1});
        names_.insert({name, id});
        station_keys_.push_back(id);
        distances_.push_back(stat_1);
        sorted = false;
        sorted_coord = false;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Datastructures::get_station_name Gets a name of the station
 * @param id of the station
 * @return Name value of the station
 */
Name Datastructures::get_station_name(StationID id)
{
    auto it = stations_.find(id);

    if (it == stations_.end()) {
        return NO_NAME;
    } else {
        return it->second.name_;
    }

}

/**
 * @brief Datastructures::get_station_coordinates Gets a coordinates of the station
 * @param id of the station
 * @return Coord value of the coordinates
 */
Coord Datastructures::get_station_coordinates(StationID id)
{
    auto it = stations_.find(id);

    if (it == stations_.end()) {
        return NO_COORD;
    } else {
        return it->second.coord_;
    }

}

/**
 * @brief Datastructures::stations_alphabetically Returns a alphabetically ordered vector of all stations
 * @return a vector of stations
 */
std::vector<StationID> Datastructures::stations_alphabetically()
{
    std::vector<StationID> order_ids;

    for (auto const& [key, value] : names_) {
        order_ids.push_back(value);
    }


    return order_ids;
}

/**
 * @brief Datastructures::stations_distance_increasing Returns a vector ordered in increasing distance
 * @return a vector of stations
 */
std::vector<StationID> Datastructures::stations_distance_increasing()
{

    std::vector<StationID> increasing;

    if (distances_accurate == false) {
        distances_.clear();
        for (std::pair<StationID, Station> elem : stations_) {
            distances_.push_back(elem.second);
        }
        distances_accurate = true;
    }

    if (sorted == false) {
        std::sort(distances_.begin(), distances_.end(),
                  [] (Station a, Station b) {
            if (a.distance_ == b.distance_) {
                return a.coord_.y < b.coord_.y;
            } else {
                return a.distance_ < b.distance_;
            }
        });
        sorted = true;
        sorted_coord = false;
    }

    for (auto it = distances_.begin(); it != distances_.end(); ++it) {
        increasing.push_back(it->id_);
    }

    return increasing;

}

/**
 * @brief Datastructures::find_station_with_coord Finds a station with given coordinates
 * @param xy includes coordinate values
 * @return StationID of the wanted station
 */
StationID Datastructures::find_station_with_coord(Coord xy)
{

    auto it = std::find_if(stations_.begin(), stations_.end(),
                           [xy](const std::pair<StationID, Station>& x) {
        if (x.second.coord_.x == xy.x && x.second.coord_.y == xy.y) {
            return true;
        } else {
            return false;
        }
    });

    if (it != stations_.end()) {
        return it->second.id_;
    }

    return NO_STATION;
}

/**
 * @brief Datastructures::change_station_coord Changes the coordinates of the station
 * @param id of the station
 * @param newcoord includes new coordinates
 * @return bool value whether the change was succesfull
 */
bool Datastructures::change_station_coord(StationID id, Coord newcoord)
{
    auto it = stations_.find(id);

    if (it == stations_.end()) {
        return false;
    } else {
        it->second.coord_ = newcoord;
        it->second.distance_ = sqrt(pow(newcoord.x,2)+pow(newcoord.y,2));

        if (distances_accurate == false) {
            distances_.clear();
            for (std::pair<StationID, Station> elem : stations_) {
                distances_.push_back(elem.second);
            }
            distances_accurate = true;
        }

        auto it1 = std::find_if(distances_.begin(), distances_.end(), [id](Station x){return x.id_ == id;});

        it1->distance_ = sqrt(pow(newcoord.x,2)+pow(newcoord.y,2));

        sorted = false;
        sorted_coord = false;
        return true;

    }
}

/**
 * @brief Datastructures::add_departure Adds a new departure for station
 * @param stationid is id of the station
 * @param trainid is id of the depature train
 * @param time when departure is happening
 * @return bool value whether adding is succesfull
 */
bool Datastructures::add_departure(StationID stationid, TrainID trainid, Time time)
{
    auto it = stations_.find(stationid);

    if (it == stations_.end()) {
        return false;
    } else {

        for (auto it1 = it->second.departures_.begin(); it1 != it->second.departures_.end(); ++it1) {
            if ((it1->id_ == trainid)&&(it1->time_ == time)) {
                    return false;
            }
        }

        const Departure dep_1 = {time, trainid};
        it->second.departures_.push_back(dep_1);
        return true;
        }

}

/**
 * @brief Datastructures::remove_departure Removes departure from station
 * @param stationid indentifies the station
 * @param trainid identifies the train
 * @param time of the departure
 * @return bool value whether removal was succesfull
 */
bool Datastructures::remove_departure(StationID stationid, TrainID trainid, Time time)
{
    auto it = stations_.find(stationid);

    if (it == stations_.end()) {
        return false;
    } else {

        for (auto it1 = it->second.departures_.begin(); it1 != it->second.departures_.end(); ++it1) {
            if ((it1->id_ == trainid)&&(it1->time_ == time)) {
                it->second.departures_.erase(it1);
                return true;
            }
        }
        return false;
    }
}

/**
 * @brief Datastructures::station_departures_after List the departures after given time
 * @param stationid identifies the station
 * @param time after which the departures are given
 * @return a vector of departures with time and trainid
 */
std::vector<std::pair<Time, TrainID>> Datastructures::station_departures_after(StationID stationid, Time time)
{
    std::vector<std::pair<Time, TrainID>> return_vals;
    auto it = stations_.find(stationid);

    if (it == stations_.end()) {
        return_vals.push_back({NO_TIME, NO_TRAIN});
    } else {

        std::sort(it->second.departures_.begin(), it->second.departures_.end(),
                  [] (Departure a, Departure b) {
            if (a.time_ == b.time_) {
                return a.id_ < b.id_;
            } else {
                return a.time_ == b.time_;
            }
        });

        for (auto it1 = it->second.departures_.begin(); it1 != it->second.departures_.end(); ++it1) {
            if (it1->time_ >= time) {
                std::pair<Time, TrainID> info (it1->time_, it1->id_);

                return_vals.push_back(info);
            }
        }

    }
    return return_vals;
}

/**
 * @brief Datastructures::add_region Adds a region
 * @param id identifies the region
 * @param name of the region
 * @param coords include the coordinates of the region
 * @return bool value whether adding was succesfull
 */
bool Datastructures::add_region(RegionID id, const Name &name, std::vector<Coord> coords)
{
    if (regions_.find(id) == regions_.end()) {
        Region reg_1 = {id, name, coords};
        regions_.insert({id,reg_1});
        region_keys_.push_back(id);
        return true;
    } else {
        return false;
    }

}

/**
 * @brief Datastructures::all_regions Returns all regions
 * @return a vector of all RegionIDs
 */
std::vector<RegionID> Datastructures::all_regions()
{
    return region_keys_;
}

/**
 * @brief Datastructures::get_region_name Gets region name
 * @param id identifies the region
 * @return The name of the region
 */
Name Datastructures::get_region_name(RegionID id)
{
    auto it = regions_.find(id);

    if (it != regions_.end()) {
        return it->second.name;
    } else {
        return NO_NAME;
    }

}

/**
 * @brief Datastructures::get_region_coords Gets region coordinates
 * @param id identifies the region
 * @return a vector of region coordinates
 */
std::vector<Coord> Datastructures::get_region_coords(RegionID id)
{
    auto it = regions_.find(id);

    if (it != regions_.end()) {
        return it->second.coords;
    } else {
        std::vector<Coord> empty = {NO_COORD};
        return empty;
    }
}

/**
 * @brief Datastructures::add_subregion_to_region Adds a subregion to another region
 * @param id identifies the subregion
 * @param parentid identifies the bigger region
 * @return bool value whether the adding was succesfull
 */
bool Datastructures::add_subregion_to_region(RegionID id, RegionID parentid)
{
    auto it1 = regions_.find(id);
    auto it2 = regions_.find(parentid);

    if (it1 == regions_.end()) {
        return false;
    } else if (it2 == regions_.end()) {
        return false;
    } else if (it1->second.bigRegion != NO_REGION) {
        return false;
    } else {
        it1->second.bigRegion = it2->second.id;
        it2->second.subregions.push_back(&it1->second);
        Region parent = it2->second;


        return true;
    }
}

/**
 * @brief Datastructures::add_station_to_region Adds station to a region
 * @param id identifies the station
 * @param parentid identifies the region
 * @return bool value whether adding was succesfull
 */
bool Datastructures::add_station_to_region(StationID id, RegionID parentid)
{
    auto it = regions_.find(parentid);

    if (it != regions_.end()) {
        auto it1 = stations_.find(id);

        if (it1 == stations_.end()) {
            return false;
        } else {

            if (it1->second.mainRegion == NO_REGION) {
                it->second.stations.push_back(it1->second);
                it1->second.mainRegion = parentid;
                return true;
            } else {
                return false;
            }
        }

    } else {
        return false;
    }
}

/**
 * @brief Datastructures::station_in_regions Gives all the regions station is located in
 * @param id identifies the station
 * @return a vector of the regions
 */
std::vector<RegionID> Datastructures::station_in_regions(StationID id)
{
    std::vector<RegionID> ans = {};
    auto it = stations_.find(id);

    if (it == stations_.end()) {
        ans.push_back({NO_REGION});
        return ans;
    }

    RegionID parent = it->second.mainRegion;
    if (parent == NO_REGION) {
        return ans;
    }

    Region reg = regions_.find(it->second.mainRegion)->second;
    while (true) {
        ans.push_back(reg.id);

        if (reg.bigRegion != NO_REGION) {
            reg = regions_.find(reg.bigRegion)->second;
        } else {
            break;
        }
    }

    return ans;
}

/**
 * @brief Datastructures::all_subregions_of_region Returns all subregions of the region
 * @param id identifies the region
 * @return a vector of subregions
 */
std::vector<RegionID> Datastructures::all_subregions_of_region(RegionID id)
{
    auto it = regions_.find(id);
    std::vector<RegionID> ans = {};

    if (it == regions_.end()) {
        ans.push_back(NO_REGION);
        return ans;
    } else {
        Region* root = &it->second;
        std::stack<Region*> regStack;
        regStack.push(root);
        int count = 0;

        while (regStack.empty() == false) {
            Region* reg = regStack.top();
            regStack.pop();

            for (Region* i : reg->subregions) {
                regStack.push(i);
            }

            if (count == 0) {
                ++count;
            } else {
                ans.push_back(reg->id);
            }
        }


    }
    return ans;
}

/**
 * @brief Datastructures::stations_closest_to Gets the closest station to the given coordinates
 * @param xy includes the given coordinates
 * @return a vector of 3 closest stations
 */
std::vector<StationID> Datastructures::stations_closest_to(Coord xy)
{
    std::vector<StationID> ans = {};

    if (distances_accurate == false) {
        distances_.clear();
        for (std::pair<StationID, Station> elem : stations_) {
            distances_.push_back(elem.second);
        }
    }

    /*Station stat_1;
    Station stat_2;
    Station stat_3;

    double dist_1, dist_2, dist_3;
    dist_1 = dist_2 = dist_3 = INFINITY;

    for (Station x : distances_) {
        double dist = sqrt(pow((xy.x-stat_1.coord_.x),2)+pow((xy.y-stat_1.coord_.y),2));

        if (dist < dist_1) {
            stat_3 = stat_2;
            stat_2 = stat_1;
            stat_1 = x;

            dist_3 = dist_2;
            dist_2 = dist_1;
            dist_1 = dist;
        } else if (dist < dist_2) {
            stat_3 = stat_2;
            stat_2 = x;

            dist_3 = dist_2;
            dist_2 = dist_1;
        } else if (dist < dist_3) {
            stat_3 = x;

            dist_3 = dist;
        }
    }

    ans.push_back(stat_1.id_);
    ans.push_back(stat_2.id_);
    ans.push_back(stat_3.id_);*/

    std::sort(distances_.begin(), distances_.end(), [xy] (Station a, Station b) {
        a.dist_from_point_ = sqrt(pow((xy.x-a.coord_.x),2)+pow((xy.y-a.coord_.y),2));
        b.dist_from_point_ = sqrt(pow((xy.x-b.coord_.x),2)+pow((xy.y-b.coord_.y),2));
        return a.dist_from_point_ < b.dist_from_point_;
    });
    sorted = false;

    for (auto it = distances_.begin(); it != distances_.begin()+3; ++it) {
        ans.push_back(it->id_);
    }

    return ans;
}

/**
 * @brief Datastructures::remove_station Removes a station
 * @param id identifies the station
 * @return bool value whether removal succesfull
 */
bool Datastructures::remove_station(StationID id)
{
   auto it = stations_.find(id);
    if (it == stations_.end()) {
        return false;
    } else {

        // Deletoi ja merkkaa muutokset
        keys_accurate = false;

        distances_accurate = false;

        names_.erase(it->second.name_);
        stations_.erase(it->second.id_);

        return true;
    }
}

/**
 * @brief Datastructures::common_parent_of_regions Gets the common parent of 2 regions
 * @param id1 identifies first region
 * @param id2 identifies second region
 * @return RegionID of the common parent of given regions
 */
RegionID Datastructures::common_parent_of_regions(RegionID id1, RegionID id2)
{
    auto it1 = regions_.find(id1);
    auto it2 = regions_.find(id2);

    if (it1 == regions_.end() || it2 == regions_.end()) {
        return NO_REGION;
    } else {

        if (it1->second.bigRegion == NO_REGION || it2->second.bigRegion == NO_REGION) {
            return NO_REGION;
        } else {
            Region reg1 = regions_.find(it1->second.bigRegion)->second;
            Region reg2 = regions_.find(it2->second.bigRegion)->second;

            std::vector<RegionID> regs1 = {};
            std::unordered_set<RegionID> regs2 = {};

            while (true) {
                regs1.push_back(reg1.id);

                if (reg1.bigRegion != NO_REGION) {
                    reg1 = regions_.find(reg1.bigRegion)->second;
                } else {
                    break;
                }
            }

            while (true) {
                regs2.insert(reg2.id);

                if (reg2.bigRegion != NO_REGION) {
                    reg2 = regions_.find(reg2.bigRegion)->second;
                } else {
                    break;
                }
            }

            for (RegionID id : regs1) {
                if (regs2.count(id) != 0) {
                    return id;
                }
            }

            return NO_REGION;
        }
    }
}

/**
 * @brief Datastructures::add_train Adds a train and also departured
 * @param trainid The added train
 * @param stationtimes The departure times of the train from stops,
 * @return bool value whether successfull
 */
bool Datastructures::add_train(TrainID trainid, std::vector<std::pair<StationID, Time> > stationtimes)
{
    if (trains_.find(trainid) == trains_.end()) {

        for (auto it = stationtimes.begin(); it != stationtimes.end(); ++it) {
            if (stations_.find(it->first) == stations_.end()) {
                return false;
            }
        }

        std::vector<StationID> stops = {};
        std::unordered_set<StationID> all_stops = {};
        stops.push_back(stationtimes.at(0).first);
        all_stops.insert(stationtimes.at(0).first);
        auto it = stations_.find(stationtimes.at(0).first);
        it->second.trains.insert(trainid);

        for (auto it = stationtimes.begin(); it != stationtimes.end()-1; ++it) {

            Station& stat_1 = stations_.find(it->first)->second;
            Station& stat_2 = stations_.find((it+1)->first)->second;

            Distance dist = (int) sqrt(pow((stat_1.coord_.x-stat_2.coord_.x),2)+pow((stat_1.coord_.y-stat_2.coord_.y),2));
            Route rout_1 = {stat_2.id_, trainid, dist};

            stat_1.to_neighbours.insert({stat_2.id_, rout_1});
            stat_2.from_neighbours.push_back(stat_1.id_);

            stops.push_back(stat_2.id_);
            all_stops.insert(stat_2.id_);

            if (it != stationtimes.end()-2) {
                stat_2.trains.insert(trainid);
            }
        }

        Train trn = {trainid, stops, all_stops};
        trains_.insert({trainid, trn});


        return true;

    }
    return false;
}

/**
 * @brief Datastructures::next_stations_from gets next stations from given station
 * @param id given station
 * @return vector of the next stations
 */
std::vector<StationID> Datastructures::next_stations_from(StationID id)
{
    std::vector<StationID> stats;
    auto it = stations_.find(id);

    if (it == stations_.end()) {
        stats.push_back(NO_STATION);
    } else {

        if (it->second.to_neighbours.empty() == false) {

            for (auto elem : it->second.to_neighbours) {
                stats.push_back(elem.first);
            }
        }

    }

    return stats;
}

/**
 * @brief Datastructures::train_stations_from gets next train stations that train passes
 * @param stationid the given station
 * @param trainid the giventrain
 * @return vector of stations
 */
std::vector<StationID> Datastructures::train_stations_from(StationID stationid, TrainID trainid)
{
    std::vector<StationID> stats = {};
    auto it1 = stations_.find(stationid);
    auto it2 = trains_.find(trainid);

    if (it1 == stations_.end() || it2 == trains_.end()) {
        stats.push_back(NO_STATION);
        return stats;
    }

    if (it1->second.trains.count(trainid) == 0) {
        stats.push_back(NO_STATION);
        return stats;
    }

    bool found_stat = false;
    for (auto stat : it2->second.stops) {

        if (found_stat == true) {
            stats.push_back(stat);
        }

        if (stat == stationid) {
            found_stat = true;
        }
    }

    return stats;

}

/**
 * @brief Datastructures::clear_trains clears all trains from datastructures
 */
void Datastructures::clear_trains()
{
    for (auto stat : stations_) {
        auto it = stations_.find(stat.first);
        it->second.to_neighbours.clear();
        it->second.from_neighbours.clear();
        it->second.trains.clear();

    }

    trains_.clear();
}

/**
 * @brief Datastructures::route_any finds any route from given station to another
 * @param fromid the station where route starts
 * @param toid the station wghere route ends
 * @return vector of pairs that include stations and distances along the route
 */
std::vector<std::pair<StationID, Distance>> Datastructures::route_any(StationID fromid, StationID toid)
{
    std::vector<std::pair<StationID, Distance>> route = {};
    TrainID trnid = NO_TRAIN;
    auto it1 = stations_.find(fromid);
    auto it2 = stations_.find(toid);

    if (it1 == stations_.end()) {
        route.push_back({NO_STATION, NO_DISTANCE});
        return route;
    }

    if (it2 == stations_.end()) {
        route.push_back({NO_STATION, NO_DISTANCE});
        return route;
    }

    if (corr_colors_and_distances_ == false) {
        for (auto stat : stations_) {
            auto it = stations_.find(stat.first);
            it->second.Colour = "w";
            it->second.dist_from_another_stat = (int) INFINITY;
            it->second.stat_from = NO_STATION;

        }
    }

    corr_colors_and_distances_ = false;

    std::queue<StationID> Q = {};

    it1->second.Colour = "g";
    it1->second.dist_from_another_stat = 0;
    Q.push(it1->first);

    while (Q.empty() != true) {

        StationID u_id = Q.front();
        Q.pop();
        auto stat = stations_.find(u_id);

        for (auto x : stat->second.to_neighbours) {

            auto neigh_stat = stations_.find(x.first);

            if (neigh_stat->second.Colour == "w") {
                neigh_stat->second.Colour = "g";
                neigh_stat->second.dist_from_another_stat = stat->second.dist_from_another_stat + x.second.distance;
                neigh_stat->second.stat_from = stat->first;
                Q.push(x.first);

                if (x.first == toid) {

                    StationID id = toid;

                    while (id != fromid) {

                        auto it1 = stations_.find(id);
                        std::pair<StationID, Distance> values = {it1->first, it1->second.dist_from_another_stat};
                        route.push_back(values);
                        id = it1->second.stat_from;
                    }

                    route.push_back({fromid, 0});
                    std::reverse(route.begin(), route.end());


                    return route;


                }
            }
        }
        stat->second.Colour = "b";
    }

    return route;


}

/**
 * @brief Datastructures::route_least_stations get a route with least stations
 * @param fromid the start station
 * @param toid the end station
 * @return vector of stations and distances
 */
std::vector<std::pair<StationID, Distance>> Datastructures::route_least_stations(StationID fromid, StationID toid)
{
    std::vector<std::pair<StationID, Distance>> stats = route_any(fromid, toid);

    return stats;
}

/**
 * @brief Datastructures::route_with_cycle finds a route with cycle
 * @param fromid the start station
 * @return  vector of stations
 */
std::vector<StationID> Datastructures::route_with_cycle(StationID fromid)
{
    std::vector<StationID> answers = {};
    auto it = stations_.find(fromid);

    if (it == stations_.end()) {
        answers.push_back(NO_STATION);
        return answers;
    }

    if (corr_colors_and_distances_ == false) {
        for (auto stat : stations_) {
            auto it = stations_.find(stat.first);
            it->second.Colour = "w";
            it->second.dist_from_another_stat = (int) INFINITY;
            it->second.stat_from = NO_STATION;

        }
    }

    corr_colors_and_distances_ = false;

    std::stack<StationID> Q = {};

    Q.push(it->first);

    while (Q.empty() != true) {
        StationID id = Q.top();
        Q.pop();
        auto stat = stations_.find(id);

        if (stat->second.Colour == "w") {
            stat->second.Colour = "g";
            Q.push(stat->first);

            for (auto x : stat->second.to_neighbours) {
                auto neigh_stat = stations_.find(x.first);

                if (neigh_stat->second.Colour == "w") {

                    Q.push(neigh_stat->first);
                    neigh_stat->second.stat_from = stat->first;

                } else if (neigh_stat->second.Colour == "g") {
                    answers.push_back(neigh_stat->first);

                    StationID id = neigh_stat->first;
                    answers.push_back(stat->first);
                    id = stat->first;

                    while (id != fromid) {
                        auto it1 = stations_.find(id);
                        answers.push_back(it1->second.stat_from);
                        id = it1->second.stat_from;

                    }

                    std::reverse(answers.begin(), answers.end());

                }


            }
        } else {
            stat->second.Colour = "b";
        }
    }

    return answers;

}
