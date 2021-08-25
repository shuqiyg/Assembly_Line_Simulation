// Name: Shuqi Yang
// Seneca Student ID: 132162207
// Seneca email: syang136@myseneca.ca
// Date of completion: July 15, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <algorithm>
#include <numeric>
#include <functional>
#include "LineManager.h"
#include "Workstation.h"
#include "Utilities.h"
#include "Station.h"

namespace sdds {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		Utilities util;
		std::string str, wrk_st_string, next_wrk_st_string;
		std::ifstream ifobj(file);
		if (!ifobj) throw std::string("No such file...");
		while (!ifobj.eof()) {
			size_t next_pos = 0;
			bool more = true;
			std::getline(ifobj, str);
			wrk_st_string = util.extractToken(str, next_pos, more);
			if (!more) {
				next_wrk_st_string = "\0";
			}
			else {
				next_wrk_st_string = util.extractToken(str, next_pos, more);
			};
			auto station = std::find_if(stations.begin(), stations.end(), [&](Workstation* wkst_ptr) {return wkst_ptr->getItemName() == wrk_st_string; });
			if (station != stations.end()) {
				activeLine.push_back(*station);
			}
			else {
				throw std::string("Current Station not found..");
			}
			if (next_wrk_st_string == "") {
				activeLine.back()->setNextStation();
			}
			else {
				auto nxt_station = std::find_if(stations.begin(), stations.end(), [&](Workstation* wkst_ptr) {  return next_wrk_st_string == wkst_ptr->Station::getItemName(); });
				if (nxt_station != stations.end()) {
					activeLine.back()->setNextStation(*nxt_station);
				}
				else {
					throw std::string("Next Station not found...");
				}
			}
		}
		ifobj.close();
		m_firstStation = activeLine.front();
		m_cntCustomerOrder = pending.size();
	}
	void LineManager::linkStations() {
		for (size_t i = 1; i < activeLine.size(); i++) {	
			activeLine[i] = activeLine[i - 1]->getNextStation();	
		}
		/*Workstation* st = m_firstStation;
		size_t i = 0;
		do {
			activeLine[i++] = st;
			st = st->getNextStation();
		} while (st);
		*/
	}
	bool LineManager::run(std::ostream& os) {
		static size_t count{};
		os << "Line Manager Iteration: " << ++count << std::endl;
		if (!pending.empty()) {
			*(m_firstStation) += std::move(pending.front());
			pending.pop_front();
		}
		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* ptr_wkst) { ptr_wkst->fill(os); });
		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* ptr_wkst) {
			ptr_wkst->attempToMoveOrder(); });
		return m_cntCustomerOrder == (completed.size() + incomplete.size());
	}
	void LineManager::display(std::ostream& os) const {
		std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* wkst) { return wkst->display(os); });
	}
}