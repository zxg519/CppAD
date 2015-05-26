/* $Id$ */
/* --------------------------------------------------------------------------
CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-15 Bradley M. Bell

CppAD is distributed under multiple licenses. This distribution is under
the terms of the
	Eclipse Public License Version 1.0.

A copy of this license is included in the COPYING file of this distribution.
Please visit http://www.coin-or.org/CppAD/ for information on other licenses.
-------------------------------------------------------------------------- */

/*
$begin zdouble.cpp$$
$spell
	zdouble
$$

$section zdouble: Example and Test$$

$code
$verbatim%example/zdouble.cpp%0%// BEGIN C++%// END C++%1%$$
$$

$end
*/
// BEGIN C++
# include <cppad/cppad.hpp>

namespace {
	template <class Base> bool test(bool is_double)
	{	bool ok = true;
		Base eps = 10. * std::numeric_limits<double>::epsilon();

		typedef CppAD::AD<Base>   a1type;
		typedef CppAD::AD<a1type> a2type;

		// value during taping
		CPPAD_TESTVECTOR(Base) x(2);
		x[0] = 0.0;
		x[1] = 0.0;

		// declare independent variable
		CPPAD_TESTVECTOR(a2type) a2x(x.size());
		for (size_t j = 0; j < a2x.size(); j++)
			a2x[j] = a2type( a1type(x[j]) );
		Independent(a2x);

		// zero and one as a2type values
		a2type a2zero = a2type(0.0);
		a2type a2one  = a2type(1.0);

		// h(x) = x[0] / x[1] if x[1] > x[0] else 1.0
		a2type h_x = CondExpGt(a2x[1], a2x[0], a2x[0] / a2x[1], a2one);

		// f(x) = h(x) if x[0] > 0.0 else 0.0
		//      = x[0] / x[1] if x[1] > x[0]  and x[0] > 0.0
		//      = 1.0         if x[0] >= x[1] and x[0] > 0.0
		//      = 0.0         if x[0] <= 0.0
		a2type f_x = CondExpGt(a2x[0], a2zero, h_x, a2one);

		// define the function f(x)
		CPPAD_TESTVECTOR(a2type) a2y(1);
		a2y[0] = f_x;
		CppAD::ADFun<a1type> af1;
		af1.Dependent(a2x, a2y);

		// Define function g(x) = gradient of f(x)
		CPPAD_TESTVECTOR(a1type) a1x(x.size()), a1z(1), a1w(1);
		for (size_t j = 0; j < a1x.size(); j++)
			a1x[j] = a1type(x[j]);
		a1w[0] = a1type(1.0);
		Independent(a1x);
		af1.Forward(0, a1x);
		if( is_double )
		{	// if Base is double, this would generate an assert
			af1.check_for_nan(false);
		}
		a1z = af1.Reverse(1, a1w);
		CppAD::ADFun<Base> g;
		if( is_double )
		{	// if Base is double, this would generate an assert
				g.check_for_nan(false);
		}
		g.Dependent(a1x, a1z);

		// check result for a case where f(x) = 0.0;
		CPPAD_TESTVECTOR(Base) z(2);
		x[0] = 0.0;
		x[1] = 0.0;
		z    = g.Forward(0, x);
		if( is_double )
			ok &= CppAD::isnan(z[1]);
		else
		{	ok &= z[0] == 0.0;
			ok &= z[1] == 0.0;
		}

		// check result for a case where f(x) = 1.0;
		x[0] = 1.0;
		x[1] = 0.5;
		z    = g.Forward(0, x);
		ok &= z[0] == 0.0;
		ok &= z[1] == 0.0;

		// check result for a case where f(x) = x[0] / x[1];
		x[0] = 1.0;
		x[1] = 2.0;
		z    = g.Forward(0, x);
		ok &= CppAD::NearEqual(z[0], 1.0/x[1], eps, eps);
		ok &= CppAD::NearEqual(z[1], - x[0]/(x[1]*x[1]), eps, eps);

		// check that nan works
		ok &= CppAD::isnan( CppAD::nan( Base(0.0) ) );

		return ok;
	}
}

bool zdouble(void)
{	bool ok = true;
	using CppAD::AD;
	using CppAD::NearEqual;
	using CppAD::zdouble;
	//
	bool is_double = false;
	ok &= test<zdouble>(is_double);
	//
	is_double = true;
	ok &= test<double>(is_double);
	//
	return ok;
}

// END C++
