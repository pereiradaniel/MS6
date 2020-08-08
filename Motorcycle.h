#ifndef SDDS_MOTORCYCLE_H__
#define SDDS_MOTORCYCLE_H__
#include <iostream>
#include "Vehicle.h"
namespace sdds {
	class Motorcycle :
		public Vehicle {
		bool m_hasSideCar;
	public:
		Motorcycle();
		Motorcycle(const char* licensePlate, const char* makeModel);
		Motorcycle(const Motorcycle&) = delete;
		void operator=(const Motorcycle&) = delete;
		std::istream& read(std::istream& istr = std::cin);
		std::ostream& write(std::ostream& ostr = std::cout)const;
	};
}
#endif