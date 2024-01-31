#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int totalF = 0;////////////////////////////

struct FlightInfo {
    string flight, departure, arrival, price;
};

string cheapest(int total, FlightInfo* flights) {

    string cheap;
    int count = total;
    double price = 0.00;

    price = stod(flights[0].price);
    cheap = "The cheapest flight is flight " + flights[0].flight + " from " + flights[0].departure + " to " + flights[0].arrival + " at $" +  flights[0].price;

    for (int i = 1; i < count; i++) {
        if(price > stod(flights[i].price)) {

            price = stod(flights[i].price);

            cheap = "The cheapest flight is flight " + flights[i].flight + " from " + flights[i].departure + " to " + flights[i].arrival + " at $" +  flights[i].price;
        }
    }

    return cheap;
}

string numFlightFlyLand (int total, const string& city, FlightInfo* flights) {

    int count = total, numFlights = 0;
    string numFlightsFL;

    for (int i = 0; i < count; i++) {
        if(flights[i].departure == city || flights[i].arrival == city) {
            //cout << flights[i].flight << endl;
            numFlights++;
        }
    }


    //cout << "num" << numFlights << endl;

    if (numFlights > 1) {
        numFlightsFL = "There are " + to_string(numFlights) + " flights arriving at or leaving from " + city;
    } else {
        numFlightsFL = "There is " + to_string(numFlights) + " flights arriving at or leaving from " + city;
    }


    return numFlightsFL;
}

string average (int total, const string& city, FlightInfo* flights) {

    int count = total, numF = 0;
    double cost = 0.00;
    string average;

    for (int i = 0; i < count; i++) {
        if(flights[i].departure == city) {

            numF++;
            cost += stod(flights[i].price);

            //cout << numF << "and" << to_string(cost) << endl;
        }
    }

    cost = cost / numF;

    if (cost > 0) {
        average = "The average price to leave " + city + " is $" + to_string(cost);
    } else {
        average = "There is no flight leaving " + city;
    }


    return average;
}

void selectionSort(FlightInfo* flights, int total) {

  /*  int i, j, minIn;
    string index, indexMin;*/

    int minIn = 0;
    //FlightInfo temp = (const FlightInfo &) new FlightInfo;

    for (int i = 0; i < total - 1; i++) {
        for (int j = i + 1; j < total; j++) {
            if(flights[j].flight < flights[minIn].flight) {
                minIn = j;
            }
            if (minIn != i) {
                //temp = flights[i];
                //cout << temp << endl;
            }
        }
    }


   /* for(i = 0; i < total - 1; i++) {
        minIn = i;
        indexMin = flightsSorted[i].flight;
        //cout << indexMin << "hi" << endl;

        for(j = i + 1; j < total; j++) {
            index = flightsSorted[j].flight;
          //  cout << "here" << endl;

            if(index < indexMin) {
                minIn = j;
                cout << "hi" << endl;
            }
           *//* if(minIn != i) {
                swap(flights[i].flight, flights[minIn].flight);
            }*//*
        }
        swap(flightsSorted[i], flightsSorted[minIn]);
    }

    for(int x = 0; x < total; x++) {
        cout << flightsSorted[x].flight << endl;
    }*/
}


FlightInfo* readFile (const string& filename) {

    int topBot = 0;
    totalF = 0;

    cout << filename<< endl;


    ifstream flightsFile;
      flightsFile.open(filename);

      if(!flightsFile.is_open()) {
          cerr << "Failed to open" << endl;
          return nullptr;
      }

      string line;
      while(!flightsFile.eof()) {
          getline(flightsFile, line);
          totalF++;
          //cout << count << "here1" << endl;
      }

      if(line.empty()) {
          totalF--;
          //cout << *count << "here1" << endl;

      }

      flightsFile.clear();
      flightsFile.seekg(0, ios::beg);

      //cout << *count << "here2" << endl;

      auto * flights = new FlightInfo[totalF]; // delete memory?
      string firstLast [10];

      for(int i = 0; i < totalF; i++) {
          getline(flightsFile, line);
          istringstream iss (line);
          getline(iss, flights[i].flight, ',');
          getline(iss, flights[i].departure, ',');
          getline(iss, flights[i].arrival, ',');
          getline(iss, flights[i].price, ',');

          if(i < 5) {
              firstLast[topBot] = "Flight " + flights[i].flight + " from " + flights[i].departure + " to " + flights[i].arrival + " costs $" + flights[i].price;
              topBot++;
          }

          if(i > totalF - 6){
              firstLast[topBot] = "Flight " + flights[i].flight + " from " + flights[i].departure + " to " + flights[i].arrival + " costs $" + flights[i].price;
              topBot++;
          }

      }

      cout << "The first 10 flights are:" << endl;

      for(int i = 0; i < 10; i++) {
          cout << firstLast[i] << endl;
          if (i == 4) {
              cout << "The last 10 flights are:" << endl;
          }
      }

      cout << endl << totalF << " flights loaded." << endl << endl;



      flightsFile.close();

      return flights;
}

int main() {

    string file = "flights_10.dat";

    FlightInfo* flights = readFile(file);

    cout << cheapest(totalF, flights) << endl;

    cout << numFlightFlyLand(totalF, "Chicago", flights) << endl;
    cout << numFlightFlyLand(totalF, "Taipei", flights) << endl;
    cout << numFlightFlyLand(totalF, "Washington", flights) << endl;
    cout << numFlightFlyLand(totalF, "Kingston", flights) << endl;

    cout << average(totalF, "Chicago", flights) << endl;
    cout << average(totalF, "Paris", flights) << endl;
    cout << average(totalF, "Kingston", flights) << endl;

    selectionSort(flights, totalF);


    return 0;
}
