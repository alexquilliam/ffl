#include <cstdbool>
#include <map>

#include <gmp.h>
#include <gmpxx.h>

#include <rho.hpp>
#include <utils.hpp>

mpz_vector rho(mpz_class n) {
	std::vector<std::pair<mpz_class, bool>> factors;
	std::vector<std::pair<mpz_class, bool>> tmp_factors;

	mpz_vector factor_pair = single_pair_rho(n);

	for(mpz_class raw_factor : factor_pair) {
		if(mpz_probab_prime_p(raw_factor.get_mpz_t(), 15) == 0) {
			factors.push_back(std::make_pair(raw_factor, false));
		}else {
			factors.push_back(std::make_pair(raw_factor, true));
		}
	}

	tmp_factors = factors;

	bool is_factored = false;
	while(!is_factored) {
		is_factored = true;

		for(size_t i = 0; i < tmp_factors.size(); i++) {
			std::pair<mpz_class, bool> factor = tmp_factors[i];

			if(factor.second == true) {
				continue;
			}else {
				is_factored = false;

				factor_pair = single_pair_rho(factor.first);

				factors.erase(factors.begin() + i);

				for(mpz_class raw_factor : factor_pair) {
					if(mpz_probab_prime_p(raw_factor.get_mpz_t(), 15) == 0) {
						factors.push_back(std::make_pair(raw_factor, false));
					}else {
						factors.push_back(std::make_pair(raw_factor, true));
					}
				}
			}
		}

		tmp_factors = factors;
	}

	mpz_vector raw_factors(factors.size());
	for(size_t i = 0; i < factors.size(); i++) {
		raw_factors[i] = factors[i].first;
	}

	std::sort(raw_factors.begin(), raw_factors.end());

	return raw_factors;
}

mpz_vector single_pair_rho(mpz_class n) {
	mpz_class x(3);
	mpz_class y(2);
	mpz_class d(1);

	mpz_vector factors(0);

	while(d == 1) {
		rho_poly(&x, x, n);
		rho_poly(&y, y, n);
		rho_poly(&y, y, n);

		mpz_class abs_difference(x - y);
		mpz_abs(abs_difference.get_mpz_t(), abs_difference.get_mpz_t());

		mpz_gcd(d.get_mpz_t(), abs_difference.get_mpz_t(), n.get_mpz_t());
	}

	if(d == 1) {
		return factors;
	}else {
		factors.push_back(d);
		factors.push_back(n / d);

		return factors;
	}

	return factors;
}

void rho_poly(mpz_class *r, mpz_class x, mpz_class n) {
	mpz_mod((*r).get_mpz_t(), mpz_class((x * x) + 1).get_mpz_t(), n.get_mpz_t());
}
