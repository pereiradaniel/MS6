#ifndef SDDS_PARKING_H__
#define SDDS_PARKING_H__
#include "Menu.h"

namespace sdds {
	const int	MAX_LOT_SIZE = 100;
	class Parking {
	private:
		char* m_datafile;				// may be nullptr -> Parking in empty state
		Menu	m_parkingMenu;
		Menu	m_vehicleMenu;
	private:
		bool	isEmpty() const;
		void	setEmpty();
		void	parkingStatus() const;	// message->****** Seneca Valet Parking ******
		void	parkVehicle();
		void	returnVehicle();		// message->Returning Vehicle
		void	listParkedVehicles();	// message->Listing Parked Vehicles
		bool	closeParking();			// message->Closing Parking
		bool	exitParkingApp();
		bool	load();
		void	save();
	public:
		Parking(const char* datafile);
		Parking(const Parking&) = delete;
		void operator=(const Parking&) = delete;
		int run();
		~Parking();
	};
}
#endif