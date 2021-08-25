// Name: Shuqi Yang
// Seneca Student ID: 132162207
// Seneca email: syang136@myseneca.ca
// Date of completion: July 16, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef CUSTOMERORDER_H_
#define CUSTOMERORDER_H_
#include "Station.h"

namespace sdds {
	class CustomerOrder {
		struct Item {
			std::string m_itemName;
			size_t m_serialNumber{ 0 };
			bool m_isFilled{ false };
			Item(const std::string& src) : m_itemName(src) {};
		};
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstItem{};
		static size_t m_widthField;
	public:
		CustomerOrder();
		CustomerOrder(const std::string&);
		CustomerOrder(const CustomerOrder&);
		CustomerOrder& operator=(const CustomerOrder&) = delete;
		CustomerOrder(CustomerOrder&&) noexcept;
		CustomerOrder& operator=(CustomerOrder&&) noexcept;
		~CustomerOrder();
		bool isFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}
#endif
