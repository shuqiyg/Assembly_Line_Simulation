// Name: Shuqi Yang
// Seneca Student ID: 132162207
// Seneca email: syang136@myseneca.ca
// Date of completion: July 15, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef WORKSTATION_H_
#define WORKSTATION_H_
#include <deque>
#include "CustomerOrder.h"

namespace sdds {
	extern std::deque<sdds::CustomerOrder> pending;
	extern std::deque<sdds::CustomerOrder> completed;
	extern std::deque<sdds::CustomerOrder> incomplete;
	class Workstation : public Station {
		std::deque<CustomerOrder> m_orders{};
		Workstation* m_pNextStation{};
	public:
		Workstation(const std::string&);
		Workstation(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation& operator=(Workstation&&) = delete;
		void fill(std::ostream&);
		bool attempToMoveOrder();
		void setNextStation(Workstation* station = nullptr);
		Workstation* getNextStation() const;
		void display(std::ostream&) const;
		Workstation& operator += (CustomerOrder&&);
	};
}
#endif
