
#include <stdlib.h>
#include <stdio.h>

unsigned long long
fib( unsigned long const n )
{
    return ( n <= 1 ) ? n
                      : fib( n - 1 ) + fib( n - 2 );
}

int
main( int const argc,
      char const * const * const argv )
{
    if ( argc != 2 ) {
        fprintf( stderr, "Usage: %s <n>\n", argv[ 0 ] );
        exit( 1 );
    }

    unsigned long const calc = strtoul( argv[ 1 ], NULL, 10 );
    if ( calc > MAX ) {
        fprintf( stderr, "Can only calculate up to %d.\n", MAX );
        return 1;
    }

    printf( "fib(%lu) = %lld\n", calc, fib( calc ) );
}

