#pragma once

#include <gmp.h>
#include <gmpxx.h>

#include <iostream>
#include <vector>

typedef std::vector<mpz_class> mpz_vector;
typedef std::vector<int> int_vector;

//overload the << operator to print a vector
template<typename T> std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
    out << "[";

    size_t last = v.size() - 1;
    for(size_t i = 0; i < v.size(); ++i) {
        out << v[i];

		if (i != last) {
            out << ", ";
		}
    }

    out << "]";

	fflush(stdout);

    return out;
}

long get_time_ms();
