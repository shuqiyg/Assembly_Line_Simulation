// Name: Shuqi Yang
// Seneca Student ID: 132162207
// Seneca email: syang136@myseneca.ca
// Date of completion: July 10, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <string>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace sdds {
	size_t Station::m_widthField{};
	size_t Station::id_generator{};
	Station::Station(const std::string& str) {
		stat_id = ++id_generator;
		Utilities util;
		size_t next_pos = 0;
		bool more = true;
		item_name = util.extractToken(str, next_pos, more);
		serial_num = std::stoi(util.extractToken(str, next_pos, more));
		quantity = std::stoi(util.extractToken(str, next_pos, more));
		m_widthField = m_widthField > util.getFieldWidth() ? m_widthField : util.getFieldWidth();
		stat_desc = util.extractToken(str, next_pos, more);
	}
	const std::string& Station::getItemName() const {
		return item_name;
	}
	size_t Station::getNextSerialNumber() {
		return serial_num++;
	}
	size_t Station::getQuantity() const{
		return quantity;
	}
	void Station::updateQuantity() {
		if (quantity > 0) quantity--;
	}
	void Station::display(std::ostream& os, bool full) const {
		os << "[" << std::setfill('0') << std::setw(3) << std::right << stat_id <<  std::setfill(' ') << "] Item: " <<  std::setw(m_widthField) << std::left << item_name << " [" << std::setw(6) << std::setfill('0') << std::right << serial_num << "]" << std::setfill(' ');
		if (full) {
			os << " Quantity: " << std::left << std::setw(m_widthField)  << quantity << " Description: " << stat_desc;
		}
		os << std::endl;
	}
}