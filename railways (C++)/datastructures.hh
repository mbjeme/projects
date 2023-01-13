// Datastructures.hh
//
// Student name:
// Student email:
// Student number:

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <map>
#include <set>
#include <unordered_set>
#include <iterator>
#include <vector>
#include <algorithm>
#include <math.h>


// Types for IDs
using StationID = std::string;
using TrainID = std::string;
using RegionID = unsigned long long int;
using Name = std::string;
using Time = unsigned short int;

// Return values for cases where required thing was not found
StationID const NO_STATION = "---";
TrainID const NO_TRAIN = "---";
RegionID const NO_REGION = -1;
Name const NO_NAME = "!NO_NAME!";
Time const NO_TIME = 9999;

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();


// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};


// This is the class you are supposed to implement

struct Departure {
    Time time_;
    TrainID id_;
};

struct Route {
    StationID to_station;
    TrainID trnid;
    Distance distance;
};

struct Station {
    StationID id_;
    Name name_;
    Coord coord_;
    double distance_;
    double dist_from_point_ = 0;
    std::vector<Departure> departures_ = {};
    RegionID mainRegion = NO_REGION;
    std::vector<RegionID> regions_of_station_ = {};

    std::unordered_map<StationID, Route> to_neighbours = {};
    std::vector<StationID> from_neighbours = {};
    std::unordered_set<TrainID> trains = {};

    std::string Colour = "w";
    Distance dist_from_another_stat = (int) INFINITY;
    StationID stat_from = NO_STATION;


};

struct Region {
    RegionID id;
    Name name;
    std::vector<Coord> coords;
    std::vector<Station> stations = {};

    std::vector<Region*> subregions = {};
    RegionID bigRegion = NO_REGION;
};

struct Train {
    TrainID trn_id;
    std::vector<StationID> stops;
    std::unordered_set<StationID> all_stops;
};



class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    //
    // Old assignment 1 operations
    //
    // Estimate of performance: O(1)
    // Short rationale for estimate: The function returns
    //simply the size of the vector including stations.
    unsigned int station_count();

    // Estimate of performance: O(n^4)
    // Short rationale for estimate: Clear is a linear function repeated to
    // many structures.
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: The function does return all the n values of
    // the vector
    std::vector<StationID> all_stations();

    // Estimate of performance: O(n)
    // Short rationale for estimate: The insertion in unordered map is in worst
    // case linear but average is costant and there is two insertions to unordered map.
    bool add_station(StationID id, Name const& name, Coord xy);

    // Estimate of performance: O(1)
    // Short rationale for estimate: The find function is constant as
    // well as ifs and returns as nothing is copied from anywhere, just returned.
    Name get_station_name(StationID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Similarly to the get_station_name, the find is
    // constant and other rows do include just constant operations.
    Coord get_station_coordinates(StationID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: The loop goes through the entire unordered map and
    // copies values of StationIDs from each element.
    std::vector<StationID> stations_alphabetically();

    // Estimate of performance: O(n)
    // Short rationale for estimate: The loop assures that
    // function is linear. Sort is completed just when the vector is not in order.
    std::vector<StationID> stations_distance_increasing();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Goes through the stations and finds the wanted
    // station. In worst case goes through all of them.
    StationID find_station_with_coord(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The find_if std function is linear so
    // the function is linear due to other rows being constant.
    bool change_station_coord(StationID id, Coord newcoord);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Goes through possibly the all elements in departures
    // vector.
    bool add_departure(StationID stationid, TrainID trainid, Time time);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Goes through the loop and possibly all elements.
    bool remove_departure(StationID stationid, TrainID trainid, Time time);

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate: The sort is nlogn and the loop in the end assures that the
    // performance is what it is.
    std::vector<std::pair<Time, TrainID>> station_departures_after(StationID stationid, Time time);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: The insertion to unorderedmap is O(n) and other values are
    // constant.
    bool add_region(RegionID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Returns just the value of the vector, not copying any
    // new values to another vector.
    std::vector<RegionID> all_regions();

    // Estimate of performance: O(1)
    // Short rationale for estimate: The find and other rows are all constant and due to this
    // the whole function is constant.
    Name get_region_name(RegionID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: The function includes only constant time operations and due
    // to this the function is constant.
    std::vector<Coord> get_region_coords(RegionID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Value is constant if pushback operation is constant.
    // Otherwise it is O(n).
    bool add_subregion_to_region(RegionID id, RegionID parentid);

    // Estimate of performance: O(1)
    // Short rationale for estimate: If pushback is constant, the function is constant time aswell.
    bool add_station_to_region(StationID id, RegionID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: As the operations in the function are mainly constant
    // but the loop makes the function linear.
    std::vector<RegionID> station_in_regions(StationID id);

    // Non-compulsory operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: In the worst case the function goes through every
    // region.
    std::vector<RegionID> all_subregions_of_region(RegionID id);

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate: The sort happens if the vector is not in order. Otherwise
    // complexity is from the loop where we get the return ids in a vector.
    std::vector<StationID> stations_closest_to(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The function finds the iterators to element in vectors
    // and erases them. All could be in worst case linear.
    bool remove_station(StationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: In worst case, goes through all the regions.
    RegionID common_parent_of_regions(RegionID id1, RegionID id2);


    //
    // New assignment 2 operations
    //

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate: The function goes through a loop when adding the departures and routes.
    bool add_train(TrainID trainid, std::vector<std::pair<StationID, Time>> stationtimes);

    // Estimate of performance: O(n)
    // Short rationale for estimate: If the station has next stations, it goes through a loop to get them.
    std::vector<StationID> next_stations_from(StationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: There is a loop to get the trains stations between stations and in worst case
    // it is linear
    std::vector<StationID> train_stations_from(StationID stationid, TrainID trainid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Removes the trains from data structures.
    void clear_trains();

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate: The BFS is O(n) and the function also creates the vector.
    std::vector<std::pair<StationID, Distance>> route_any(StationID fromid, StationID toid);

    // Non-compulsory operations

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate: Uses the function from route_any to find the answer so same estimate
    std::vector<std::pair<StationID, Distance>> route_least_stations(StationID fromid, StationID toid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: The DFS in O(n) and the function does not contain extra loops outside the
    // function
    std::vector<StationID> route_with_cycle(StationID fromid);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Not done and due to this is constant
    std::vector<std::pair<StationID, Distance>> route_shortest_distance(StationID fromid, StationID toid);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Not done and due to this is constant
    std::vector<std::pair<StationID, Time>> route_earliest_arrival(StationID fromid, StationID toid, Time starttime);

private:
    std::unordered_map<StationID, Station> stations_;
    std::vector<StationID> station_keys_;
    std::map<Name, StationID> names_;
    std::vector<Station> distances_;
    bool sorted = false;
    bool sorted_coord = false;
    bool keys_accurate = true;
    bool distances_accurate = true;

    std::unordered_map<RegionID, Region> regions_;
    std::vector<RegionID> region_keys_;

    std::unordered_map<TrainID, Train> trains_;
    bool corr_colors_and_distances_ = true;
};

#endif // DATASTRUCTURES_HH
