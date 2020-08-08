#define _CRT_SECURE_NO_WARNINGS
#ifndef SDDS_VEHICLE_H__
#define SDDS_VEHICLE_H__
#include <iostream>
#include "ReadWritable.h"
namespace sdds {
	const int MAX_PLATE_CHARS = 8;
	const int MAX_MAKE_MODEL_CHARS = 60;
	const int MIN_MAKE_MODEL_CHARS = 2;
	class Vehicle : public ReadWritable {
	private:
		char	m_licensePlate[9];
		char* m_makeModel;
		int		m_parkingSpot;
	public:
		Vehicle();
		Vehicle(const char* licensePlate, const char* makeModel);
		Vehicle(const Vehicle&) = delete;
		void operator=(const Vehicle&) = delete;
		virtual ~Vehicle();
		void			setEmpty();
		bool			isEmpty()const;
		const char* getLicensePlate()const;
		const char* getMakeModel()const;
		void			setMakeModel(const char* value);
		int				getParkingSpot()const;
		void			setParkingSpot(int value);
		bool operator==(const char* licensePlate) const;
		bool operator==(const Vehicle& v) const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
	};
}
#endif