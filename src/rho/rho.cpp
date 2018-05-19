#include <cstdbool>
#include <map>

#include <gmp.h>
#include <gmpxx.h>

#include <rho.hpp>
#include <utils.hpp>

mpz_vector rho(mpz_class n) {
	if(mpz_probab_prime_p(n.get_mpz_t(), 15) != 0) {
		return mpz_vector(0);
	}

	mpz_vector factors(0);

	rho_recursive(n, &factors);

	std::sort(factors.begin(), factors.end());

	return factors;
}

void rho_recursive(mpz_class n, mpz_vector *factors) {
	if(mpz_probab_prime_p(n.get_mpz_t(), 15) != 0) {
		return;
	}

	mpz_vector factor_pair = single_pair_rho(n);
	factors->erase(std::remove(factors->begin(), factors->end(), n), factors->end());

	for(mpz_class factor : factor_pair) {
		factors->push_back(factor);
		rho_recursive(factor, factors);
	}
}

mpz_vector single_pair_rho(mpz_class n) {
	mpz_class x(2);
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
