#include <iostream>
#include <cstring>
#include "Motorcycle.h"
#include "Utils.h"
using namespace std;
namespace sdds {
	Motorcycle::Motorcycle() : Vehicle(), m_hasSideCar(false) {}
	Motorcycle::Motorcycle(const char* licensePlate, const char* makeModel) : Vehicle(licensePlate, makeModel), m_hasSideCar(false) {}

	std::istream& Motorcycle::read(std::istream& istr) {
		if (!isCsv()) {
			// if car is not in csv mode, print a message "EOLMotorcycle information entryEOL"
			cout << endl << "Motorcycle information entry" << endl;
			// cal read(istr) function from the base class (Vehicle)
			Vehicle::read(istr);
			// print a message "Does the Motorcycle have a side car? (Y)es/(N)o: "
			cout << "Does the Motorcycle have a side car? (Y)es/(N)o: ";
			// call function yes() from Utils and save the result in m_hasSideCar
			m_hasSideCar = Utils::yes(istr);
		}
		else {
			// if motobike in CSV mode
			Vehicle::read(istr);
			// extract from istr to m_hasSideCar
			istr >> m_hasSideCar;
			// ignore the rest of the input line: istr.ignore(100, '\n')
			istr.ignore(1000, '\n');
		}
		return istr;
	}

	std::ostream& Motorcycle::write(std::ostream& ostr) const {
		// print messagaes according to MS5 documentation
		if (isEmpty()) {
			ostr << "Invalid Motorcycle Object" << endl;
		}
		else {
			if (isCsv()) {
				ostr << "M,";
			}
			else {
				ostr << "Vehicle type: Motorcycle" << endl;
			}

			Vehicle::write(ostr);
			if (isCsv()) {
				ostr << m_hasSideCar << endl;;
			}
			else {
				if (m_hasSideCar) {
					ostr << "With Sidecar" << endl;
				}
			}
		}
		return ostr;
	}
}