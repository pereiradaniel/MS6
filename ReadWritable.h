#define _CRT_SECURE_NO_WARNINGS
#ifndef SDDS_READWRITABLE_H__
#define SDDS_READWRITABLE_H__
#include <iostream>
namespace sdds {
	class ReadWritable {
	private:
		bool	m_csvIO;
	public:
		ReadWritable();
		bool isCsv() const;
		void setCsv(bool value);
		virtual std::istream& read(std::istream& istr = std::cin) = 0;
		virtual std::ostream& write(std::ostream& ostr = std::cout) const = 0;
		virtual ~ReadWritable();
	};
	std::ostream& operator<<(std::ostream& ostr, const ReadWritable& rw);
	std::istream& operator>>(std::istream& istr, ReadWritable& rw);
}
#endif