#include <iostream>
#include "Plane.h"
#include "Runway.h"
#include "utility.h"
#include "Extended_queue.h"
#include "Random.h"

using namespace std;

void main_1();
void main_2();
void main_3();

void initialize(int &end_time, int &queue_limit,
                double &arrival_rate, double &departure_rate) {
   cout << "This program simulates an airport with only one runway." << endl
        << "One plane can land or depart in each unit of time." << endl;
   cout << "Up to what number of planes can be waiting to land "
        << "or take off at any time? " << flush;
   cin  >> queue_limit;

   cout << "How many units of time will the simulation run?" << flush;
   cin  >> end_time;

   bool acceptable;
   do {
      cout << "Expected number of arrivals per unit time?" << flush;
      cin  >> arrival_rate;
      cout << "Expected number of departures per unit time?" << flush;
      cin  >> departure_rate;
      if (arrival_rate < 0.0 || departure_rate < 0.0)
         cerr << "These rates must be nonnegative." << endl;
      else
         acceptable = true;

      if (acceptable && arrival_rate + departure_rate > 1.0)
         cerr << "Safety Warning: This airport will become saturated. " << endl;

   } while (!acceptable);
}


int main() {

   int choice;

   do {

      cout << "1. Run P1 version of Airport simulator" << endl;
      cout << "2. Run P2 version of Airport simulator" << endl;
      cout << "3. End the simulator" << endl;
      cout << "Your choice: " << endl;
      cin >> choice;

      switch (choice) {
         case 1: main_1(); break;
         case 2: main_2(); break;
         case 3: main_3(); break;
         case 4: cout << "Ending simulation" << endl; break;
         default: cout << "Invalid choice" << endl;
      }
   } while (choice != 4);

   return 0;
}

   void main_1() {

   int end_time;            //  time to run simulation
   int queue_limit;         //  size of Runway queues
   int flight_number = 0;

   double arrival_rate, departure_rate;

   initialize(end_time, queue_limit, arrival_rate, departure_rate);

   Random variable;
   Runway small_airport(queue_limit);

   for (int current_time = 0; current_time < end_time; current_time++) { //  loop over time intervals
      int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
      for (int i = 0; i < number_arrivals; i++) {
         Plane current_plane(flight_number++, current_time, arriving);
         if (small_airport.can_land(current_plane) != success)
            current_plane.refuse();
      }

      int number_departures= variable.poisson(departure_rate); //  current departure requests
      for (int j = 0; j < number_departures; j++) {
         Plane current_plane(flight_number++, current_time, departing);
         if (small_airport.can_depart(current_plane) != success)
            current_plane.refuse();
      }

      Plane moving_plane;
      switch (small_airport.activity(current_time, moving_plane)) {
        //  Let at most one Plane onto the Runway at current_time.
      case land:
         moving_plane.land(current_time);
         break;
      case takeoff:
         moving_plane.fly(current_time);
         break;
      case idle:
         run_idle(current_time);
      }
   }
   small_airport.shut_down(end_time);
}
   
void main_2() {

   int end_time;
   int queue_limit;
   int flight_number = 0;

   double arrival_rate, departure_rate;

   initialize(end_time, queue_limit, arrival_rate, departure_rate);

   Random variable;

   Runway landing_airplanes(queue_limit);
   Runway departing_airplanes(queue_limit);

   for (int current_time = 0; current_time < end_time; current_time++) {
      int number_arrivals = variable.poisson(arrival_rate);
      for (int i = 0; i < number_arrivals; i++) {
         Plane current_plane(flight_number++, current_time, arriving);
         if (landing_airplanes.can_land(current_plane) != success)
         current_plane.refuse();
      }

      int number_departures = variable.poisson(departure_rate);
      for (int j = 0; j < number_departures; j++) {
         Plane current_plane(flight_number++, current_time, departing);
         if (departing_airplanes.can_depart(current_plane) != success)
         current_plane.refuse();
      }

      Plane moving_plane;

      if (landing_airplanes.activity(current_time, moving_plane) == land) {
         moving_plane.land(current_time);
      } else {
         run_idle(current_time);
      }

      if (departing_airplanes.activity(current_time, moving_plane) == takeoff) {
         moving_plane.fly(current_time);
      } else {
         run_idle(current_time);
      }

   }
      landing_airplanes.shut_down(end_time);
      departing_airplanes.shut_down(end_time);

}

void main_3() {

   int end_time;
   int queue_limit;
   int flight_number = 0;



   double arrival_rate, departure_rate;

   initialize(end_time, queue_limit, arrival_rate, departure_rate);

   Random variable;

   Runway landing_airplanes(queue_limit);
   Runway departing_airplanes(queue_limit);

   int landing_queue = 0;
   int departing_queue = 0;


   for (int current_time = 0; current_time < end_time; current_time++) {
      int number_arrivals = variable.poisson(arrival_rate);
      for (int i = 0; i < number_arrivals; i++) {
         Plane current_plane(flight_number++, current_time, arriving);
         if (landing_airplanes.can_land(current_plane) != success) {
            landing_queue++;
         } else {
         current_plane.refuse();
         }
      }

      int number_departures = variable.poisson(departure_rate);
      for (int j = 0; j < number_departures; j++) {
         Plane current_plane(flight_number++, current_time, departing);
         if (departing_airplanes.can_depart(current_plane) != success) {
            departing_queue++;
         } else {
         current_plane.refuse();
         }
      }


   bool landing_full = (landing_queue == queue_limit);
   bool landing_empty = (landing_queue == 0);
   bool departing_empty = (departing_queue == 0);

      Plane moving_plane;
      bool busy = false;


   if (!busy) {
      run_idle(current_time);
   }
}
}