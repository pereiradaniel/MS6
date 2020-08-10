#ifndef SDDS_PARKING_H__
#define SDDS_PARKING_H__
#include "Menu.h"
#include "Vehicle.h"

namespace sdds {
	const int	MAX_LOT_SIZE = 100;
	const int	MIN_LOT_SIZE = 10;
	class Parking {
	private:
		char*	m_datafile;
		Menu	m_parkingMenu;
		Menu	m_vehicleMenu;
		int		m_lotSize;
		int		m_Vcnt;
		Vehicle* m_parkingSpots[MAX_LOT_SIZE];
	private:
		bool	isEmpty() const;
		void	setEmpty();
		void	parkingStatus() const;
		void	parkVehicle();
		void	returnVehicle();
		void	listParkedVehicles();
		bool	closeParking();
		bool	exitParkingApp();
		bool	load();
		void	save();
	public:
		Parking(const char* datafile, int noOfSpots);
		Parking(const Parking&) = delete;
		void operator=(const Parking&) = delete;
		int run();
		~Parking();
	};
}
#endif