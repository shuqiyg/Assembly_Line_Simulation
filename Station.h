// Name: Shuqi Yang
// Seneca Student ID: 132162207
// Seneca email: syang136@myseneca.ca
// Date of completion: July 10, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef STATION_H_
#define STATION_H_
namespace sdds {
	class Station {
		static size_t m_widthField;
		static size_t id_generator;
		size_t stat_id{};
		std::string item_name{};
		std::string stat_desc{};
		unsigned int serial_num{};
		unsigned int quantity{};
	public:
		Station(const std::string&);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;	
	};
}
#endif // !STATION_H_

