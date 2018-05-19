#pragma once

#include <gmp.h>
#include <gmpxx.h>

#include <utils.hpp>

mpz_vector rho(mpz_class n);
void rho_recursive(mpz_class n, mpz_vector *factors);
mpz_vector single_pair_rho(mpz_class n);
void rho_poly(mpz_class *r, mpz_class x, mpz_class n);
