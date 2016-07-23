#ifndef INTERSECTION
#define INTERSECTION
#include <queue>
#include "Vehicle.h"
#include <iostream>
#include <string>
using namespace std;
//parent function to roundabout and trafficlight
class intersection {
protected:
	 int Ncars, Scars, Ecars, Wcars;
	 unsigned long tick;
	 int emergencyCount;
	 bool show;
	 unsigned long totalWait = 0;
	 queue <Car*> Nline;
	 queue <Car*> Sline;
	 queue <Car*> Eline;
	 queue <Car*> Wline;
	 set_of_cars garage;//holds all citizens and their proper vehicles
public:
	//sets initial data
	void set_cars( int N, int S, int E, int W, bool show) {
		Ncars = N;
		Scars = S;
		Ecars = E;
		Wcars = W;
		this->show = show;
	}

	//output intersection statistics
	virtual void outputdata() = 0;
	//move cars within intersection
	virtual void moveCarsOut() =0;
	//move cars from the front of each line into intersections if possible
	virtual void moveCarsIn() = 0;

	//adds cars to each of the four streets as well as takes care of emergency vehicle movement
	void addCars() {
		//CARS ENTER FROM NORTH
		if (random(Ncars)) {
			Car *enteringCar = &garage.getNewCar();//new car
			enteringCar->set_road("north");
			//emergency vehicles are not added to queue, they stop traffic for needed time and then leave
			if (enteringCar->get_type() == "ambulance" || enteringCar->get_type() == "firetruck" || enteringCar->get_type() == "police car") {
				emergencyCount = enteringCar->get_time_through();
				enteringCar->set_start(tick);//set time that emergency vehicle enters
				enteringCar->set_end(tick + emergencyCount);//now set time to end after the required time has gone by
				totalWait += enteringCar->get_wait();
				if(show)
					enteringCar->print_data();
			}
			else {
				enteringCar->set_start(tick);
				Nline.push(enteringCar);

			}
		}
		//CARS ENTER FROM SOUTH
		if (random(Scars)) {
			Car* enteringCar = &garage.getNewCar();//new car
			enteringCar->set_road("south");

			 //emergency vehicles are not added to queue, they stop traffic for needed time and then leave
			if (enteringCar->get_type() == "ambulance" || enteringCar->get_type() == "firetruck" || enteringCar->get_type() == "police car") {
				emergencyCount = enteringCar->get_time_through();
				enteringCar->set_start(tick);//set time that emergency vehicle enters
				enteringCar->set_end(tick + emergencyCount);//now set time to end after the required time has gone by
				totalWait += enteringCar->get_wait();
				if (show)
					enteringCar->print_data();
			}
			else {
				enteringCar->set_start(tick);
				Sline.push(enteringCar);
			}
		}

		//CARS ENTER FROM EAST
		if (random(Ecars)) {
			Car* enteringCar = &garage.getNewCar();//new car
			enteringCar->set_road("east");

			//emergency vehicles are not added to queue, they stop traffic for needed time and then leave
			if (enteringCar->get_type() == "ambulance" || enteringCar->get_type() == "firetruck" || enteringCar->get_type() == "police car") {
				emergencyCount = enteringCar->get_time_through();
				enteringCar->set_start(tick);//set time that emergency vehicle enters
				enteringCar->set_end(tick + emergencyCount);//now set time to end after the required time has gone by
				totalWait += enteringCar->get_wait();
				if (show)
					enteringCar->print_data();
			}
			else {
				enteringCar->set_start(tick);
				Eline.push(enteringCar);
			}
		}

		//CARS ENTER FROM WEST
		if (random(Wcars)) {
			Car* enteringCar = &garage.getNewCar();//new car
			enteringCar->set_road("west");

			 //emergency vehicles are not added to queue, they stop traffic for needed time and then leave
			if (enteringCar->get_type() == "ambulance" || enteringCar->get_type() == "firetruck" || enteringCar->get_type() == "police car") {
				emergencyCount = enteringCar->get_time_through();
				enteringCar->set_start(tick);//set time that emergency vehicle enters
				enteringCar->set_end(tick + emergencyCount);//now set time to end after the required time has gone by
				totalWait += enteringCar->get_wait();
				if (show)
					enteringCar->print_data();
			}
			else {
				enteringCar->set_start(tick);
				Wline.push(enteringCar);
			}
		}
	}

	//runs simulation for 4 simulated hours
	void run(){
		tick = 0;
		while (tick < 100) {//loop for every 14400 seconds to make 4 hours
			addCars();//add any cars that need to enter the queues
			moveCarsOut();//move cars that are already in intersection
			if (emergencyCount == 0)//if no emergency vehicle at intersection
				moveCarsIn();//move cars that can into intersection
			else
			{
				emergencyCount--; //"move" ambulance through intersection
			}
			++tick;
		}
		}
	virtual int rate() = 0;//returns value of effiecency
	
};

#endif