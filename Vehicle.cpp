#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <sstream>
#include "Vehicle.h"
#include "Utils.h"
using namespace std;
namespace sdds {
	Vehicle::Vehicle() : ReadWritable(), m_licensePlate{}, m_makeModel(nullptr), m_parkingSpot(0) {
		setEmpty();
	}

	Vehicle::Vehicle(const char* licensePlate, const char* makeModel) : ReadWritable(), m_licensePlate{}, m_makeModel(nullptr), m_parkingSpot(0) {
		if (licensePlate != nullptr && licensePlate[0] != '\0' && strlen(licensePlate) <= 8 && makeModel != nullptr && strlen(makeModel) >= 2) {
			strcpy(m_licensePlate, licensePlate);
			m_makeModel = new char[strlen(makeModel) + 1];
			strcpy(m_makeModel, makeModel);
		}
		else {
			setEmpty();
		}
	}

	Vehicle::~Vehicle() {
		delete[] m_makeModel;
	}

	bool Vehicle::isEmpty() const {
		return m_makeModel == nullptr;
	}

	void Vehicle::setEmpty() {
		delete[] m_makeModel;
		m_makeModel = nullptr;
		m_licensePlate[0] = 0;
		m_parkingSpot = -1;
	}

	int Vehicle::getParkingSpot() const {
		return m_parkingSpot;
	}

	void Vehicle::setParkingSpot(int value) {
		if (value < 0) {
			setEmpty();
		}
		else {
			m_parkingSpot = value;
		}
	}

	const char* Vehicle::getLicensePlate() const {
		return m_licensePlate;
	}

	const char* Vehicle::getMakeModel() const {
		return m_makeModel;
	}

	void Vehicle::setMakeModel(const char* value) {
		if (value != nullptr) {
			delete[] m_makeModel;
			m_makeModel = new char[strlen(value) + 1];
			strcpy(m_makeModel, value);
		}
		else {
			setEmpty();
		}
	}

	bool Vehicle::operator==(const char* licensePlate) const {
		bool result = false;
		if (!isEmpty() && licensePlate != nullptr && licensePlate[0] != '\0' && strlen(licensePlate) <= MAX_PLATE_CHARS) {
			char temp[MAX_PLATE_CHARS + 1];
			// temp = new char[MAX_PLATE_CHARS + 1];
			strcpy(temp, licensePlate);
			// Utils::toUpper(temp);
			if (strcmp(temp, licensePlate) == 0) {
				result = true;
			}
		}
		return result;
	}

	bool Vehicle::operator==(const Vehicle& V) const {
		return operator==(V.m_licensePlate);
	}

	istream& Vehicle::read(istream& istr) {
		if (isCsv()) {
			char t_parkingSpot[9];
			istr.get(t_parkingSpot, 9, ',');
			istr.ignore(2000, ',');

			char t_licensePlate[9];
			istr.get(t_licensePlate, 9, ',');
			istr.ignore(2000, ',');

			char t_makeModel[61];
			istr.get(t_makeModel, 61, ',');
			istr.ignore(2000, ',');

			m_parkingSpot = stoi(t_parkingSpot);
			strcpy(m_licensePlate, t_licensePlate);
			if (m_licensePlate[0] != '\0') {
				Utils::toUpper(m_licensePlate);
			}
			setMakeModel(t_makeModel);
		}
		else if (!isCsv()) {
			cout << "Enter Licence Plate Number: ";
			char t_licensePlate[9];
			Utils::read(t_licensePlate, MAX_PLATE_CHARS, "Invalid Licence Plate, try again: ", istr);
			strcpy(m_licensePlate, t_licensePlate);
			Utils::toUpper(m_licensePlate);

			cout << "Enter Make and Model: ";
			char t_makeModel[MAX_MAKE_MODEL_CHARS + 1];
			Utils::read(t_makeModel, MIN_MAKE_MODEL_CHARS, MAX_MAKE_MODEL_CHARS, "Invalid Make and model, try again: ", istr);
			setMakeModel(t_makeModel);

			m_parkingSpot = 0;
		}
		return istr;
	}

	ostream& Vehicle::write(ostream& ostr) const {
		if (!this->isEmpty()) {
			if (isCsv()) {
				ostr << m_parkingSpot << "," << m_licensePlate << "," << m_makeModel << ",";
			}
			else {
				ostr << "Parking Spot Number: ";
				if (m_parkingSpot == 0) {
					ostr << "N/A";
				}
				else {
					ostr << m_parkingSpot;
				}
				ostr << endl;
				ostr << "Licence Plate: " << m_licensePlate << endl;
				ostr << "Make and Model: " << m_makeModel << endl;
			}
		}
		else {
			ostr << "Invalid Vehicle Object" << endl;
		}
		return ostr;
	}
}
