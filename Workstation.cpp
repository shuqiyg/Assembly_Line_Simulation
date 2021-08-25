// Name: Shuqi Yang
// Seneca Student ID: 132162207
// Seneca email: syang136@myseneca.ca
// Date of completion: July 15, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <deque>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "Station.h"
#include "CustomerOrder.h"
#include "Workstation.h"


namespace sdds {
	std::deque<sdds::CustomerOrder> pending{};
	std::deque<sdds::CustomerOrder> completed{};
	std::deque<sdds::CustomerOrder> incomplete{};
	Workstation::Workstation(const std::string& str) : Station(str){}
	void Workstation::fill(std::ostream& os) {
		if (!m_orders.empty()) m_orders.front().fillItem(*this, os);
	}
	bool Workstation::attempToMoveOrder() {
		if (!m_orders.empty()) {
			if (m_orders.front().isItemFilled(this->getItemName()) || this->getQuantity() == 0) {
				if (m_pNextStation == nullptr) {
					if (m_orders.front().isFilled())
					{
						completed.push_back(std::move(m_orders.front()));
					}
					else {
						incomplete.push_back(std::move(m_orders.front()));
					}
					m_orders.pop_front();
				}else {
					(*m_pNextStation) += std::move(m_orders.front());
					m_orders.pop_front();
				}	
			}
			return true;
		}
		return false;
	}
	void Workstation::setNextStation(Workstation* station) {
		m_pNextStation = station;
	}
	Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	}
	void Workstation::display(std::ostream& os) const {
		os << this->getItemName() << " --> ";
		if (m_pNextStation == nullptr) {
			os << "End of Line" << std::endl;
		}
		else {
			os << m_pNextStation->getItemName() << std::endl;
		}
	}
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(std::move(newOrder));
		return *this;
	}
}