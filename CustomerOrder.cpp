// Name: Shuqi Yang
// Seneca Student ID: 132162207
// Seneca email: syang136@myseneca.ca
// Date of completion: July 16, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace sdds {
	size_t CustomerOrder::m_widthField{};
	CustomerOrder::CustomerOrder() {}
	CustomerOrder::CustomerOrder(const std::string& str) {
		Utilities util;
		size_t next_pos = 0;
		bool more = true;
		m_name = util.extractToken(str, next_pos, more);
		m_product = util.extractToken(str, next_pos, more);
		size_t items_start_pos = next_pos;
		while (more) {
			util.extractToken(str, items_start_pos, more);
			++m_cntItem;
		}
		m_lstItem = new Item* [m_cntItem];
		more = true;
		std::string temp;
		for (size_t i = 0; i < m_cntItem; i++) {
			std::stringstream ss(util.extractToken(str, next_pos, more));
			getline(ss, temp, '\r');  //windows files ends with crlf which is 2 characters comparing to 1 character in Linux
			m_lstItem[i] =  new Item(temp);
		}
		m_widthField = m_widthField > util.getFieldWidth() ? m_widthField : util.getFieldWidth();
	}
	CustomerOrder::CustomerOrder(const CustomerOrder& co) {
		throw std::string("An Error has occured...");
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& co) noexcept {
		*this = std::move(co);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& co) noexcept {
		if (this != &co) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_cntItem = co.m_cntItem;
			m_lstItem = new Item*[m_cntItem];
			for (size_t i = 0; i < m_cntItem; i++) {
				m_lstItem[i] = co.m_lstItem[i];
				co.m_lstItem[i] = nullptr;
			};
			delete[] co.m_lstItem;		
			co.m_lstItem = nullptr;
			m_name = co.m_name;
			m_product = co.m_product;	
			co.m_name = char(0);
			co.m_product = char(0);
			co.m_cntItem = 0u;
		}
		return *this;
	}
	CustomerOrder::~CustomerOrder() {
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
			m_lstItem[i] = nullptr;
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}
	bool CustomerOrder::isFilled() const {
		bool filled = true;
		for (size_t i = 0; i < m_cntItem && filled; i++) {
			filled = m_lstItem[i]->m_isFilled;
		}
		return filled;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		bool itemFilled = true;
		for (size_t i = 0; i < m_cntItem; i++) {
			if (m_lstItem[i]->m_itemName == itemName) {
				if (!m_lstItem[i]->m_isFilled) {
					return false;
				}
			}
		}
		return itemFilled;
	}
	void CustomerOrder::fillItem(Station& station, std::ostream& os) {
		for (size_t i = 0; i < m_cntItem; i++) {
			if (station.getItemName() == m_lstItem[i]->m_itemName) {
				if (station.getQuantity() > 0) {
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
				else {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
				}
			}
		}	
	}
	void CustomerOrder::display(std::ostream& os) const {
		os << m_name << " - " << m_product << std::endl;
		for (size_t i = 0; i < m_cntItem; i++) {
			os << "[" << std::setfill('0') << std::setw(6)  << m_lstItem[i]->m_serialNumber << "] " << std::setfill(' ') << std::left << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - " <<std::right << std::setw(0);
			if (m_lstItem[i]->m_isFilled) {
				os << "FILLED" << std::endl;
			}
			else {
				os << "TO BE FILLED" << std::endl;
			}
		};
	}
		
}