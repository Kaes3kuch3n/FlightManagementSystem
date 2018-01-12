#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fms.h"

Airline *airlines[3];
Airport *airports[7];
FlightRoute *flightRoutes[15];

void CreateAirlines() {
    FlightRoute *lufthansaRoutes[5] = {flightRoutes[0], flightRoutes[1], flightRoutes[2], flightRoutes[3], flightRoutes[4]};
    FlightRoute *eurowingsRoutes[5] = {flightRoutes[10], flightRoutes[11], flightRoutes[12], flightRoutes[13], flightRoutes[14]};
    FlightRoute *tuiflyRoutes[5] = {flightRoutes[5], flightRoutes[6], flightRoutes[7], flightRoutes[8], flightRoutes[9]};

    airlines[0] = CreateAirline("Lufthansa", "A380", "D-AIMA", lufthansaRoutes);
    airlines[1] = CreateAirline("EuroWings", "A320", "D-AIAB", eurowingsRoutes);
    airlines[2] = CreateAirline("TUIfly", "B747", "D-ABCD", tuiflyRoutes);
}

void CreateAirports() {
    airports[0] = CreateAirport("HAM", "EDDH", 53.630278, 9.988333);
    airports[1] = CreateAirport("TXL", "EDDT", 52.559686, 13.287711);
    airports[2] = CreateAirport("DUS", "EDDL", 51.280925, 6.757311);
    airports[3] = CreateAirport("CGN", "EDDK", 50.865917, 7.142744);
    airports[4] = CreateAirport("FRA", "EDDF", 50.033333, 8.570556);
    airports[5] = CreateAirport("STR", "EDDS", 48.689878, 9.221964);
    airports[6] = CreateAirport("MUC", "EDDM", 48.353783, 11.786086);
}

void CreateFlightRoutes()  {
    // Lufthansa
    flightRoutes[0] = CreateFlightRoute(airlines[0], "LH 2147", airports[6], airports[0], 11, 30, 14, 30);
    flightRoutes[1] = CreateFlightRoute(flightRoutes[0]->airline, "LH 2148", flightRoutes[0]->to, airports[4], 15, 30, 16, 30);
    flightRoutes[2] = CreateFlightRoute(flightRoutes[0]->airline, "LH 2149", flightRoutes[1]->to, airports[6], 18, 30, 20, 30);
    flightRoutes[3] = CreateFlightRoute(flightRoutes[0]->airline, "LH 2148", flightRoutes[2]->to, airports[0], 20, 30, 22, 00);
    flightRoutes[4] = CreateFlightRoute(flightRoutes[0]->airline, "LH 2149", flightRoutes[3]->to, airports[6], 22, 30, 23, 30);

    // TUIfly
    flightRoutes[5] = CreateFlightRoute(airlines[2], "X3 2174", airports[0], airports[5], 8, 00, 10, 00);
    flightRoutes[6] = CreateFlightRoute(flightRoutes[5]->airline, flightRoutes[5]->flightNr, flightRoutes[5]->to, airports[1], 10, 15, 13, 00);
    flightRoutes[7] = CreateFlightRoute(flightRoutes[5]->airline, flightRoutes[5]->flightNr, flightRoutes[6]->to, airports[4], 13, 10, 15, 00);
    flightRoutes[8] = CreateFlightRoute(flightRoutes[5]->airline, flightRoutes[5]->flightNr, flightRoutes[7]->to, airports[0], 15, 12, 17, 00);
    flightRoutes[9] = CreateFlightRoute(flightRoutes[5]->airline, flightRoutes[5]->flightNr, flightRoutes[8]->to, airports[4], 22, 00, 24, 00);

    //EuroWings
    flightRoutes[10] = CreateFlightRoute(airlines[1], "EW 5953", airports[6], airports[2], 3, 00, 4, 15);
    flightRoutes[11] = CreateFlightRoute(flightRoutes[10]->airline, flightRoutes[10]->flightNr, flightRoutes[10]->to, airports[1], 8, 00, 10, 00);
    flightRoutes[12] = CreateFlightRoute(flightRoutes[10]->airline, flightRoutes[10]->flightNr, flightRoutes[11]->to, airports[3], 10, 12, 13, 15);
    flightRoutes[13] = CreateFlightRoute(flightRoutes[10]->airline, flightRoutes[10]->flightNr, flightRoutes[12]->to, airports[6], 18, 00, 20, 30);
    flightRoutes[14] = CreateFlightRoute(flightRoutes[10]->airline, flightRoutes[10]->flightNr, flightRoutes[13]->to, airports[2], 21, 45, 23, 30);
}

void PrintFlightRoutes() {
    printf("   Airline| Flug Nr.| von|nach|Abflug|Ankunft|  Flugzeug\n");
    printf("----------|---------|----|----|------|-------|----------\n");

    for (int i = 0; i < 15; ++i) {
        FlightRoute *flightRoute = flightRoutes[i];
        printf("%10s|%9s|%4s|%4s|%3i:%02i|%4i:%02i|%10s\n", flightRoute->airline->name, flightRoute->flightNr, flightRoute->from->iataCode, flightRoute->to->iataCode,
               flightRoute->departureTimeH, flightRoute->departureTimeM, flightRoute->arrivalTimeH, flightRoute->arrivalTimeM, flightRoute->airline->registration);
    }
}

void PrintFlightTimes(char registration[7]) {
    printf("   Airline| Flug Nr.| von|nach|  Flugzeit\n");
    printf("----------|---------|----|----|----------\n");

    int totalFlightHours = 0;
    int totalFlightMins = 0;
    FlightRoute *flightRoute;

    for (int i = 0; i < 15; ++i) {
        if (flightRoutes[i]->airline->registration == registration) {
            flightRoute = flightRoutes[i];
            int flightHours = flightRoute->arrivalTimeH - flightRoute->departureTimeH;
            int flightMinutes;
            if (flightRoute->departureTimeM > 0) {
                flightMinutes = 60 - flightRoute->departureTimeM + flightRoute->arrivalTimeM;
                if (flightMinutes >= 60)
                    flightMinutes = flightMinutes - 60;
                else
                    flightHours--;
            } else flightMinutes = flightRoute->arrivalTimeM;
            printf("%10s|%9s|%4s|%4s|%7i:%02i\n", flightRoute->airline->name, flightRoute->flightNr, flightRoute->from->iataCode, flightRoute->to->iataCode, flightHours, flightMinutes);

            totalFlightHours += flightHours;

            if (totalFlightMins + flightMinutes >= 60) {
                totalFlightMins = totalFlightMins + flightMinutes - 60;
                totalFlightHours++;
            } else totalFlightMins += flightMinutes;
        }
    }
    printf("Gesamtflugzeit für %s %s ist %i Stunden und %i Minuten.\n", flightRoute->airline->name, flightRoute->airline->registration, totalFlightHours, totalFlightMins);
}

double sindeg(double x) {
    return sin(x * M_PI / 180.0);
}

double cosdeg(double x) {
    return cos(x * M_PI / 180.0);
}

double CalculateDistance(double lat1, double lat2, double lon1, double lon2) {
    return 6378.388 * acos(sindeg(lat1) * sindeg(lat2) + cosdeg(lat1) * cosdeg(lat2) * cosdeg(lon2 - lon1));
}

void PrintFlightDistances(char registration[7]) {
    printf("   Airline| Flug Nr.| von|nach|Entfernung\n");
    printf("----------|---------|----|----|----------\n");

    double totalDistance = 0;
    FlightRoute *flightRoute;

    for (int i = 0; i < 15; ++i) {
        if (flightRoutes[i]->airline->registration == registration) {
            flightRoute = flightRoutes[i];
            double distance = CalculateDistance(flightRoute->from->lat, flightRoute->to->lat, flightRoute->from->lon, flightRoute->to->lon);
            printf("%10s|%9s|%4s|%4s|%10.2f\n", flightRoute->airline->name, flightRoute->flightNr, flightRoute->from->iataCode, flightRoute->to->iataCode, distance);

            totalDistance += distance;
        }
    }
    printf("Gesamtstrecke für %s %s ist %.2f km.\n", flightRoute->airline->name, flightRoute->airline->registration, totalDistance);
}

void CleanUp() {
    for (int i = 0; i < 3; ++i) {
        free(airlines[i]);
    }

    for (int i = 0; i < 7; ++i) {
        free(airports[i]);
    }

    for (int i = 0; i < 15; ++i) {
        free(flightRoutes[i]);
    }
}

int main() {
    CreateAirlines();
    CreateAirports();
    CreateFlightRoutes();

    PrintFlightRoutes();
    printf("\n");
    PrintFlightTimes(airlines[0]->registration);
    printf("\n");
    PrintFlightTimes(airlines[1]->registration);
    printf("\n");
    PrintFlightTimes(airlines[2]->registration);
    printf("\n");
    PrintFlightDistances(airlines[0]->registration);
    printf("\n");
    PrintFlightDistances(airlines[1]->registration);
    printf("\n");
    PrintFlightDistances(airlines[2]->registration);

    CleanUp();

    return 0;
}