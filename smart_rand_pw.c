#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * l(20)*14*l(9)*l(6) = 165.1144747
 *
 * 165 bit of entropie is more than enogh
 *
 */

static const size_t N_CHARS = 16;

/*
 * characters are selected based on unique shape,
 * confusion while reading should be minimal
 */

static const char *upper = "ACDFHJ";
static const char *lower = "abcdefghiknprstuvxyz";
static const char *number = "123456789";
static const char *punkt = ".";

static void
oneChar( const char *cset, size_t num )
{
	size_t n = strlen( cset );
	/* n is extremly small compared to the range of num, % is good enough */
	size_t idx = num % n;
	char ch = cset[ idx ];
	putchar( ch );
}

int
main()
{
	size_t rnd[ N_CHARS ];
	int fd = open( "/dev/urandom", O_CLOEXEC | O_RDONLY );
	if (read( fd, rnd, sizeof(rnd) ) != sizeof(rnd) )
		exit( 1 );
	close( fd );
	
	for (size_t i = 0; i < N_CHARS; ++i) {
		const char *cset = lower;
		if (i == 0)
			cset = upper;
		else if (i == 1)
			cset = number;
		if (i && i % 4 == 0)
			putchar( punkt[0] );
		oneChar( cset, rnd[i] );
	}
	putchar( '\n' );
	return 0;
}
