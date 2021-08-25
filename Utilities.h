// Name: Shuqi Yang
// Seneca Student ID: 132162207
// Seneca email: syang136@myseneca.ca
// Date of completion: July 10, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef UTILITIES_H_
#define UTILITIES_H_
namespace sdds {
	constexpr size_t M_DEFAULT_WIDTH{ 1 };
	class Utilities {
		static char m_delimiter;
		size_t m_widthField{ M_DEFAULT_WIDTH };
	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		static void setDelimiter(char newDelimiter);
		static char getDelimiter();
	};
}

#endif // !UTILITIES_H_

