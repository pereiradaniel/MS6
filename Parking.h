#ifndef SDDS_PARKING_H__
#define SDDS_PARKING_H__
#include "Menu.h"
#include "Vehicle.h"

namespace sdds {
	const int	MAX_LOT_SIZE = 100;
	class Parking {
	private:
		char*	m_datafile;						// may be nullptr -> Parking in empty state
		Menu	m_parkingMenu;
		Menu	m_vehicleMenu;
		int		m_lotSize;						// new	- number of spots
		int		m_Vcnt;							// new	- number of parked vehicles
		Vehicle* m_parkingSpots[MAX_LOT_SIZE];	// new	- Parking Spots.
	private:
		bool	isEmpty() const;				// no changes
		void	setEmpty();						// no changes
		void	parkingStatus() const;			// modify - modified but not tested
		void	parkVehicle();					// modify - modified but not tested x
		void	returnVehicle();				// modify - modified but not tested x
		void	listParkedVehicles();			// modify - modified but not tested x
		bool	closeParking();					// modify - modified but not tested x
		bool	exitParkingApp();				// no changes
		bool	load();							// modify x
		void	save();							// modify x
		//bool moveToParkingSpot(Vehicle* V);		// new
		//void endOfDay();						// new
		//int findVehicle(const char* licPlate);	// new
		//Vehicle* getVehicle() const;			// new
	public:
		Parking(const char* datafile, int noOfSpots);	// modified - changed but not tested x
		Parking(const Parking&) = delete;
		void operator=(const Parking&) = delete;
		int run();										// no changes
		~Parking();										// modified - changed but not tested x
	};
}
#endif