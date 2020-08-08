#include <iostream>
#include "Car.h"
#include "Vehicle.h"
#include "Utils.h"
using namespace std;
namespace sdds {
	Car::Car() : Vehicle(), m_carWash(false) {}

	Car::Car(const char* licensePlate, const char* makeModel) : Vehicle(licensePlate, makeModel), m_carWash(false) {}

	std::istream& Car::read(std::istream& istr) {
		if (!isCsv()) {
			// if car is not in csv mode, print a message "EOLCar information entryEOL"
			cout << endl << "Car information entry" << endl;
			// call read(istr) function from the base class (Vehicle)
			Vehicle::read(istr);
			// print a message "Carwash while parked? (Y)es/(N)o: "
			cout << "Carwash while parked? (Y)es/(N)o: ";
			// call function yes() from Utils and save the result in m_carWash
			m_carWash = Utils::yes(istr);
		}
		else {
			// if car in CSV mode
			Vehicle::read(istr);
			// extract from istr to m_carWash
			istr >> m_carWash;
			// ignore the rest of the input line:  istr.ignore(100, '\n')
			istr.ignore(1000, '\n');
		}
		return istr;
	}

	std::ostream& Car::write(std::ostream& ostr) const {
		// print messages according to MS5 documentation
		if (isEmpty()) {
			ostr << "Invalid Car Object" << endl;
		}
		else {
			if (isCsv()) {
				ostr << "C,";
			}
			else {
				ostr << "Vehicle type: Car" << endl;
			}

			Vehicle::write(ostr);
			if (isCsv()) {
				ostr << m_carWash << endl;
			}
			else {
				if (m_carWash == true) {
					ostr << "With Carwash" << endl;
				}
				else {
					ostr << "Without Carwash" << endl;
				}
			}
		}
		return ostr;
	}
}