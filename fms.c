//
// Created by Luis Hankel on 12.01.18.
//

#include <stdlib.h>
#include <memory.h>
#include <printf.h>
#include "fms.h"

Airport *CreateAirport(char iataCode[4], char icaoCode[5], double lat, double lon) {
    Airport *airport;
    airport = malloc(sizeof(Airport));

    strcpy(airport->iataCode, iataCode);
    strcpy(airport->icaoCode, icaoCode);
    airport->lat = lat;
    airport->lon = lon;

    return airport;
}

Airline *CreateAirline(char name[10], char aircraft[5], char registration[7], FlightRoute *routes[5]) {
    Airline *airline;
    airline = malloc(sizeof(Airline));

    strcpy(airline->name, name);
    strcpy(airline->aircraft, aircraft);
    strcpy(airline->registration, registration);
    for (int i = 0; i < 5; ++i) {
        airline->routes[i] = routes[i];
    }

    return airline;
}

FlightRoute *CreateFlightRoute(Airline *airline, char flightNr[8],  Airport *from, Airport *to, int departureTimeH, int departureTimeM, int arrivalTimeH, int arrivalTimeM) {
    FlightRoute *flightRoute;
    flightRoute = malloc(sizeof(FlightRoute));

    flightRoute->airline = airline;
    strcpy(flightRoute->flightNr, flightNr);
    flightRoute->from = from;
    flightRoute->to = to;
    flightRoute->departureTimeH = departureTimeH;
    flightRoute->departureTimeM = departureTimeM;
    flightRoute->arrivalTimeH = arrivalTimeH;
    flightRoute->arrivalTimeM = arrivalTimeM;

    return flightRoute;
}