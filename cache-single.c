
#include <stdlib.h>
#include <stdio.h>

unsigned long long
fib( unsigned long const n )
{
    static unsigned long long cache[ MAX ] = { 0, 1 };
    static unsigned int cache_top = 1;

    if ( n > cache_top ) {
        cache[ n ] = fib( n - 2 ) + fib( n - 1 );
        cache_top = n;
    }

    return cache[ n ];
}

int
main( int const argc,
      char const * const * const argv )
{
    if ( argc != 2 ) {
        fprintf( stderr, "Usage: %s <n>\n", argv[ 0 ] );
        return 1;
    }

    unsigned long const calc = strtoul( argv[ 1 ], NULL, 10 );
    if ( calc > MAX ) {
        fprintf( stderr, "Can only calculate up to %d.\n", MAX );
        return 1;
    }

    printf( "fib(%lu) = %llu\n", calc, fib( calc ) );
}

