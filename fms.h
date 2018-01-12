//
// Created by Luis Hankel on 12.01.18.
//

typedef struct Airport {
    char icaoCode[5];
    char iataCode[4];
    double lat;
    double lon;
} Airport;

typedef struct FlightRoute FlightRoute;

typedef struct Airline {
    char name[10];
    char aircraft[5];
    char registration[7];
    FlightRoute *routes[5];
} Airline;

struct FlightRoute {
    Airline *airline;
    char flightNr[8];
    Airport *from;
    Airport *to;
    int departureTimeH;
    int departureTimeM;
    int arrivalTimeH;
    int arrivalTimeM;
};

Airport *CreateAirport(char iataCode[4], char icaoCode[5], double lat, double lon);

Airline *CreateAirline(char name[10], char aircraft[5], char registration[7], FlightRoute *routes[5]);

FlightRoute *CreateFlightRoute(Airline *airline, char flightNr[8],  Airport *from, Airport *to, int departureTimeH, int departureTimeM, int arrivalTimeH, int arrivalTimeM);