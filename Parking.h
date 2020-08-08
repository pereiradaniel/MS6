#ifndef SDDS_PARKING_H__
#define SDDS_PARKING_H__
#include "Menu.h"
#include "Vehicle.h"

namespace sdds {
	const int	MAX_LOT_SIZE = 100;
	class Parking {
	private:
		char* m_datafile;				// may be nullptr -> Parking in empty state
		Menu	m_parkingMenu;
		Menu	m_vehicleMenu;
		int		m_litSize;
		int		m_Vcnt;
		Vehicle* m_parkingSpots[MAX_LOT_SIZE];
	private:
		bool	isEmpty() const;				// no changes
		void	setEmpty();						// no changes
		void	parkingStatus() const;			// modify
		void	parkVehicle();					// modify
		void	returnVehicle();				// modify
		void	listParkedVehicles();			// modify
		bool	closeParking();					// modify
		bool	exitParkingApp();				// no changes
		bool	load();							// modify
		void	save();							// modify
		bool moveToParkingSpot(Vehicle* V);		// new
		void endOfDay();						// new
		int findVehicle(const char* licPlate);	// new
		Vehicle* getVehicle() const;			// new
	public:
		Parking(const char* datafile, int lotSize);		// modified
		Parking(const Parking&) = delete;
		void operator=(const Parking&) = delete;
		int run();										// no changes
		~Parking();										// modified
	};
}
#endif