#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "ReadWritable.h"
namespace sdds {
    ReadWritable::ReadWritable() {
        m_csvIO = false;
    }

    bool ReadWritable::isCsv() const {
        return m_csvIO;
    }

    void ReadWritable::setCsv(bool value) {
        m_csvIO = value;
    }

    ReadWritable::~ReadWritable() {
    }

    std::ostream& operator<<(std::ostream& ostr, const ReadWritable& rw) {
        rw.write(ostr);
        return ostr;
    }

    std::istream& operator>>(std::istream& istr, ReadWritable& rw) {
        rw.read(istr);
        return istr;
    }
}
