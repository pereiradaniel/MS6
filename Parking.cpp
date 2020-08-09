#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "Parking.h"
#include "Utils.h"
#include "Car.h"
#include "Motorcycle.h"
using namespace std;
namespace sdds {
	Parking::Parking(const char* datafile, int noOfSpots) :
		m_datafile(nullptr),
		m_parkingMenu("Parking Menu, select an action:"),
		m_vehicleMenu("Select type of the vehicle:", 1){
		// Set the value of m_lotSize to noOfSpots.
		// If the number is invalid (less than 10 or more than MAX_NUM_SPOTS)  then parking is set to an invalid empty state.
		if (noOfSpots < 10 || noOfSpots > MAX_LOT_SIZE) {
			setEmpty();
		}
		// if parameter datafile is good
		if (datafile != nullptr && datafile [0] != '\0') {
			// allocate memory and copy string
			m_datafile = new char[strlen(datafile) + 1];
			strcpy(m_datafile, datafile);
		}
		if (load()) {
			// add to parking menu 5 items (first page of WS documentation)
			// no numbers, dashes or spaces!
			m_parkingMenu.add("Park Vehicle");
			m_parkingMenu.add("Return Vehicle");
			m_parkingMenu.add("List Parked Vehicles");
			m_parkingMenu.add("Close Parking (End of day)");
			m_parkingMenu.add("Exit Program");

			// add to vehicle menu 3 items (first page of WS documentation)
			// no numbers, dashes or spaces!
			m_vehicleMenu.add("Car");
			m_vehicleMenu.add("Motorcycle");
			m_vehicleMenu.add("Cancel");
		}
		else {
			// message 'Error in data file'
			cout << "Error in data file" << endl;
			// set empty state
			m_datafile = nullptr;
		}
	}

	bool Parking::exitParkingApp() {
		// call confirmed() function from Utils module
		bool result = Utils::confirmed("terminate the program");
		// if it returns true, print 'Exiting program!' + EOL and return true
		if (result == true) {
			cout << "Exiting program!" << endl;
		}
		// otherwise return false
		return result;
	}

	void Parking::parkingStatus() const {
		// message + EOL
		cout << "****** Seneca Valet Parking ******" << endl;
		cout << "Available spots: ";
		cout << cout.setf(ios::left) << cout.width(4) << m_lotSize - m_Vcnt;
		cout << cout.setf(ios::right) << " *****" << endl;
	}

	void Parking::parkVehicle() {
		// run the vehicle menu save the user's choice
		
		// If no parking spots available, print "Parking is full" and exit
		// Otherwise display the submenu

		if (m_Vcnt == m_lotSize) {
			cout << "Parking is full";
		}
		else {
			int selection = 0;
			m_vehicleMenu.display();
			if (!isEmpty()) {
				cin >> selection;

				switch (selection) {
				case 1:
					cout << "Parking Car" << endl;
					// Dynamically create an instance of a car in a Vehicle pointer
					Vehicle* temp = new Car();
					// Set it NOT in CSV mode
					temp->setCsv(false);
					temp->read(cin);
					// After receiving the Vehicle information from the console:
					//	- Search through the Parking Spots array and find the first available (null) Parking Spot
					bool found = false;
					for (int i = 0; i < m_lotSize || found; i++) {
						if (m_parkingSpots[i] != nullptr) {
							//	- Set it to the Vehicle pointer and also
							m_parkingSpots[i] = temp;
							//	- It will set the Parking Spot member variable of the Vehicle to the spot number it was parkin in (index + 1) and prints
							temp->setParkingSpot(i + 1);
						}
					}
					//		"Parking ticket" endl
					cout << "Parking ticket" << endl;
					//	- And prints the vehicle
					temp->write(cout);
					break;
				case 2:
					cout << "Parking Motorcycle" << endl;
					// Dynamically create an instance of a motorcycle in a Vehicle pointer
					Vehicle* temp = new Motorcycle();
					// Set it NOT in CSV mode
					temp->setCsv(false);
					temp->read(cin);
					// After receiving the Vehicle information from the console:
					//	- Search through the Parking Spots array and find the first available (null) Parking Spot
					bool found = false;
					for (int i = 0; i < m_lotSize || found; i++) {
						if (m_parkingSpots[i] != nullptr) {
							//	- Set it to the Vehicle pointer and also
							m_parkingSpots[i] = temp;
							//	- It will set the Parking Spot member variable of the Vehicle to the spot number it was parkin in (index + 1) and prints
							temp->setParkingSpot(i + 1);
						}
					}
					//		"Parking ticket" endl
					cout << "Parking ticket" << endl;
					//	- And prints the vehicle
					temp->write(cout);
					break;
				case 3:
					cout << "Cancelled parking" << endl;
					break;
				}
			}
		}
		
	}
	
	void Parking::returnVehicle() {
		// message + EOL
		cout << "Returning Vehicle" << endl;

		// Prompt the user for the license plate of the Vehicle that is to be returned:
		cout << "Enter Licence Plate Number: ";
		// Receives the license plate value in a C-style character string between 1 to 8 chars.
		string plateNumber;
		cin >> plateNumber;

		while (plateNumber.length() < 1 || plateNumber.length() > 8) {
			//	- If the length of the license plate is less than 1 or more than 8:
			//		print "Invalid Licence Plate, try, again: "
			cout << "Invalid licence plate, try again: ";
			//		and receives the value again.
			cin >> plateNumber;
		}
		
		// Search through the parked Vehicles for a matching license plate.
		bool found = false;
		int index = 0;
		for (int i = 0; i < m_lotSize || found; i++) {
			if (m_parkingSpots[i]->getLicensePlate() == plateNumber) {
				found == true;
				index = i;
			}
		}

		if (!found) {
			// If not found:
			//	- print "License plate " and then the plate " Not found" ENDL
			cout << "Licence plate " + plateNumber + " Not found" << endl;
		}
		else {
			// - if found it will print "Returning: " and prints the Vehicle, then delete the
			//		Vehicle from the memory and set the Parking Spot element back to nullptr.
			cout << "Returning: ";
			m_parkingSpots[index]->write(std::cout);
			delete m_parkingSpots[index];
			m_parkingSpots[index] = nullptr;
		}
	}

	void Parking::listParkedVehicles() {
		// message + EOL
		cout << "Listing Parked Vehicles" << endl;
		for (int i = 0; i < m_lotSize; i++) {
			if (m_parkingSpots[i] != nullptr) {
				m_parkingSpots[i]->write(std::cout);
				cout << "--------------------------------------------------------------" << endl;
			}
		}
	}

	bool Parking::closeParking() {
		bool result;
		if (isEmpty()) {
			cout << "Closing Parking" << endl;
			result = true;
		}
		else {
			result = Utils::confirmed("Remove and tow all remaining Vehicles from the Parking", std::cin);
			if (result == true) {
				cout << "Closing Parking" << endl;
				for (int i = 0; i < m_lotSize; i++) {
					if (m_parkingSpots[i] != nullptr) {
						cout << "Towing request" << endl;
						cout << "*********************";
						m_parkingSpots[i]->write(std::cout);
						cout << endl;
						delete m_parkingSpots[i];
						m_parkingSpots[i] = nullptr;
					}
				}
			}
		}
		return result;
	}

	bool Parking::load() {
		bool result = false;
		bool goodState = false;
		bool same = false;
		Vehicle* vehicle = nullptr;
		
		char nullEnd = '\0';
		int number = 0;
		
		std::ifstream file("ParkingData.csv.bak");
		
		if (!isEmpty()) {
			result = true;
			
			if (file.fail()) file.clear();
			if (file.is_open()) file.close();

			file.open(m_datafile, ios::in);
			if (file) {

				do {
					vehicle = nullptr;
					nullEnd = '\0';
					file.get(nullEnd);
					file.ignore(8, ',');

					if (toupper(nullEnd) == 'C') {

						vehicle = new Car();
						goodState = true;

					}
					else if (toupper(nullEnd) == 'M') {
						vehicle = new Motorcycle();
						goodState = true;
					}

					if (goodState) {
						vehicle->setCsv(true);
						vehicle->read(file);
						if (vehicle != nullptr) {
							int n = vehicle->getParkingSpot();
							m_parkingSpots[(n - 1)] = vehicle;
							m_Vcnt++;
							result = true;
							vehicle = nullptr;
						}
						else {
							delete vehicle;
							vehicle = nullptr;
							result = false;
						}
					}
					goodState = false;
					number++;
				} while (number < m_lotSize && result == true);
			}
		}
		else {
			result = true;
		}
		for (int i = 0; i < m_lotSize && !same; i++) {
			if (vehicle != nullptr && *vehicle == *m_parkingSpots[i]) {
				same = true;
			}
		}
		if (!same && vehicle != nullptr) {
			delete vehicle;
			vehicle = nullptr;
		}
		file.close();
		return result;
	}

	Parking::~Parking() {
		save();
		setEmpty();
	}

	void Parking::save() {
		if (!isEmpty())
			cout << "Saving data into " << m_datafile << endl;
	}

	bool Parking::isEmpty() const {
		return m_datafile == nullptr;
	}

	void Parking::setEmpty() {
		delete[] m_datafile;
		m_datafile = nullptr;
		delete[] m_parkingSpots;
		// Set all parking spots to nullptr
		int parkingSize = end(m_parkingSpots) - begin(m_parkingSpots);
		for (int i = 0; i < parkingSize; i++) {
			m_parkingSpots[i] = nullptr;
		}
		
	}

	int Parking::run() {
		bool done = false;
		int selection = 0;
		while (!isEmpty() && !done) {
			// parking status mesage
			parkingStatus();
			// run parking menu save the result in selection variable
			m_parkingMenu.display();
			cin >> selection;
			// depending on selection:  part or return or list or clsoe or exit
			// when you call the last two save the result in done variable
			if (selection == 1) {
				parkVehicle();
			}
			else if (selection == 2) {
				returnVehicle();
			}
			else if (selection == 3) {
				listParkedVehicles();
			}
			else if (selection == 4) {
				done = closeParking();
				if (done) {
					break;
				}
			}
			else if (selection == 5) {
				done = exitParkingApp();
				if (done) {
					break;
				}
			}
		}
		return selection;
	}
}
