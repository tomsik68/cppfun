#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "const_list.hpp"

SCENARIO( "const_list" ) {
    GIVEN( "empty list" ) {
        const_list<int> l;
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
        WHEN( "empty list is iterated" ) {
            size_t i = 0;
            l.for_each([&i](int) {
                ++i;
            });
            THEN( "it contains 0 items" ) {
                REQUIRE( i == 0 );
            }
        }
    }
    GIVEN( "list 0,1,2" ) {
        const_list<int, 0, 1, 2> l;
        THEN( "empty returns false" ) {
            REQUIRE_FALSE( l.empty() );
        }
        THEN( "size is 3" ) {
            REQUIRE( l.size() == 3 );
        }
        GIVEN( "an empty list" ) {
            const_list<int> m;
            THEN( "lists are not equal" ) {
                REQUIRE_FALSE( l == m );
                REQUIRE_FALSE( m == l );
            }
        }
        GIVEN( "the same list" ) {
            const_list<int, 0, 1, 2> m;
            THEN( "lists are equal" ) {
                REQUIRE( l == m );
                REQUIRE( m == l );
            }
        }
        WHEN( "sum is calculated" ) {
            int s = 0;
            l.for_each([&s](int i){
                s += i;
            });
            THEN( "sum is 3" ) {
                REQUIRE( s == 3 );
            }
        }
        WHEN( "sum is accumulated" ) {
            int s = l.accumulate([](int a, int b){ return a + b;}, 0);
            THEN( "sum is 3" ) {
                REQUIRE( s == 3 );
            }
        }
    }
    GIVEN( "list of true's" ) {
        const_list<bool, true, true, true> l;
        WHEN( "list is and'd" ) {
            bool r = l.accumulate([](bool a, bool b) { return a && b; }, true);
            THEN( "result is true" ) {
                REQUIRE( r );
            }
        }
    }
    GIVEN( "list of false's" ) {
        const_list<bool, false, false, false> l;
        WHEN( "list is or'd" ) {
            bool r = l.accumulate([](bool a, bool b) { return a || b; }, false);
            THEN( "result is false" ) {
                REQUIRE_FALSE( r );
            }
        }
    }
}
