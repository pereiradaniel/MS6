#ifndef SDDS_CAR_H__
#define SDDS_CAR_H__
#include <iostream>
#include "Vehicle.h"
namespace sdds {
	class Car :
		public Vehicle {
		bool m_carWash;
	public:
		Car();
		Car(const char* licensePlate, const char* makeModel);
		Car(const Car&) = delete;
		void operator=(const Car&) = delete;
		std::istream& read(std::istream& istr = std::cin);
		std::ostream& write(std::ostream& ostr = std::cout)const;
	};
}
#endif