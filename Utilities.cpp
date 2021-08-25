// Name: Shuqi Yang
// Seneca Student ID: 132162207
// Seneca email: syang136@myseneca.ca
// Date of completion: July 10, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include "Utilities.h"

namespace sdds {
	char Utilities::m_delimiter{};
	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		std::string token{};
		size_t delimiter_pos = str.find(m_delimiter, next_pos);
		if (next_pos == delimiter_pos) {
			more = false; throw "exception";
		}
		if (delimiter_pos == std::string::npos) {
			token = str.substr(next_pos, str.find(char(0), next_pos));
			more = false;
		}
		else {
			token = str.substr(next_pos, delimiter_pos - next_pos);
			next_pos = delimiter_pos + 1;
			more = true;
		}
		if (m_widthField < token.length()) {
			m_widthField = token.length();
		}	
		return token;	
	}
	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter() {
		return m_delimiter;
	}
}