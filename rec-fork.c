

#define _POSIX_C_SOURCE 200902L

#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


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

    int fds[ 2 ];
    pipe( fds );

    pid_t const child_pid = fork();
    long fib_n2;
    switch ( child_pid ) {

        case -1: // error
            perror( "fork" );
            exit( 1 );

        case 0: // child
            close( fds[ 0 ] );
            fib_n2 = fib( calc - 2 );
            write( fds[ 1 ], &fib_n2, sizeof fib_n2 );
            close( fds[ 1 ] );
            break;

        default: // parent
            close( fds[ 1 ] );
            read( fds[ 0 ], &fib_n2, sizeof fib_n2 );
            waitpid( child_pid, NULL, 0 );
            printf( "fib(%lu) = %lld\n", calc, fib_n2 + fib( calc - 1 ) );
            close( fds[ 0 ] );
            break;

    }
}

