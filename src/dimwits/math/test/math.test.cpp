#define CATCH_CONFIG_MAIN

#include <iostream>

#include "dimwits.hpp"
#include "catch.hpp"

using namespace dimwits;

SCENARIO("log test"){
  std::vector<double> values
  { 1E-42, 1E-39, 1E-36, 1E-33, 1E-30,
      1E-27, 1E-24, 1E-21, 1E-18, 1E-15,
      1E-12, 1E-9, 1E-6, 1E-3, 1E-2, 1E-1,
      1E0, 1E1, 1E2, 1E3, 1E4, 1E5, 1E6,
      1E7, 1E8, 1E9, 1E10, 1E11, 1E12, 1E15,
      1E18, 1E21, 1E24, 1E27, 1E30, 1E33,
      1E36, 1E39, 1E42 };
  for ( auto value : values ) {
    std::cout << value << std::endl;
    std::cout << std::abs( ( std::log(value) - math::Log::evaluate(value) ) / ( (std::log(value) == 0.0) ? 1.0 : std::log(value) ) ) << std::endl;
    REQUIRE( std::abs( ( std::log(value) - math::Log::evaluate(value) )
		       / ( (std::log(value) == 0.0) ? 1.0 : std::log(value) ) )
	     < 1E-15 );
  }
}