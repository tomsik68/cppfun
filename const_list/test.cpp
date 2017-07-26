#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "const_list2.hpp"

SCENARIO( "const_list" ) {
    const_list<int> l;
    GIVEN( "empty list" ) {
        THEN( "empty returns true" ) {
            REQUIRE( l.empty() );
        }
        THEN( "size is 0" ) {
            REQUIRE( l.size() == 0 );
        }
        GIVEN( "another empty list" ) {
            const_list<int> m;
            THEN( "lists are equal" ) {
                REQUIRE( l == m );
                REQUIRE( m == l );
            }
        }
        GIVEN( "empty list of other type" ) {
            const_list<char> m;
            THEN( "lists differ" ) {
                REQUIRE( l != m );
                REQUIRE( m != l );
            }
        }
        THEN( "begin == end" ) {
            REQUIRE( l.begin() == l.end() );
        }
    }
}
