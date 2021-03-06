#define CATCH_CONFIG_MAIN

#include "dimwits.hpp"
#include "catch.hpp"

using namespace dimwits;

SCENARIO("quantity Type"){
  SECTION( "default construction functions" ){
    quantity::Type< Meter > length;
  }

  SECTION( "construction from value/primitive multiplication" ){
    /* using auto, types are lazily converted */
    auto kgm_ss = 1.0 * kilo(gram) * meter / second / second;
    auto trial = typename decltype(kgm_ss)::Units();
    auto reference = Kilo<Gram>() * Meter() / Second() / Second();
    REQUIRE( reference == trial );

    /* quantities can be eagerly converted by specifying a destination type */
    quantity::Type< Kilo<Newton> > n =
      1.0 * kilo(gram) * meter / second / second;
    REQUIRE( n.value == Approx(1.0E-3) );
  }

  SECTION( "unitless quantities are interoperable with scalar types" ){
    quantity::Type< Unitless > buckinghamPi = 5.0;
    double value = buckinghamPi;
    REQUIRE( buckinghamPi == value );
    
    quantity::Type< Unitless, int > integerBuckinghamPi = 5.0;
    REQUIRE( integerBuckinghamPi == 5 );
  }

  using MilesPerSecond = decltype( Mile()/Second() );
  constexpr Quantity< MilesPerSecond > fast = constant::lightSpeed;
}
