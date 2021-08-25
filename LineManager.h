// Name: Shuqi Yang
// Seneca Student ID: 132162207
// Seneca email: syang136@myseneca.ca
// Date of completion: July 15, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef LINEMANAGER_H_
#define LINEMANAGER_H_
#include "Workstation.h"
namespace sdds {
	class LineManager {
		std::vector<Workstation*> activeLine{};
		size_t m_cntCustomerOrder{};
		Workstation* m_firstStation{};
	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void linkStations();
		bool run(std::ostream&);
		void display(std::ostream&) const;
	};
}
#endif
