#include <stdio.h>

int main()
{
	int res, op, first = 1;
	char delim;
	while ( scanf( "%d%c", &op, &delim ) == 2 ) {
		if ( first ) {
			res = op;
			first = 0;
		} else if ( op == 0 ) {
			return 0;
		} else {
			res /= op;
		}
		if ( delim == '\n' ) {
			printf( "%d\n", res );
			first = 1;
		}
	}
	return 0;
}
