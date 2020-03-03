//
// @author   liyan
// @contact  lyan_dut@outlook.com
//
#pragma once
#ifndef MYGENETICFORRCPSP_COMMON_H
#define MYGENETICFORRCPSP_COMMON_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

template<typename T>
using Vector = std::vector<T>;

using String = std::string;

using Time = int;

template<typename T>
std::ostream& operator<<(std::ostream &os, const Vector<T> &vec) {
	if (vec.empty()) {
		os << "[ ]";
		return os;
	}
	os << "[";
	for (int i = 0; i < vec.size() - 1; ++i) { os << vec[i] << " "; }
	os << vec[vec.size() - 1] << "]";
	return os;
}


#endif // !MYGENETICFORRCPSP_COMMON_H
