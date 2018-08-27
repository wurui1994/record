#include <stdio.h>
#include <string.h>
#define SWAP(t, a, b) do {t v=a; a=b; b=v;} while (0)
#define OP(o)   do { a[1].n = a[0].n o a[1].n; \
        sprintf(a[1].s, "(%s"#o"%s)", a[0].s, strcpy(t.s, a[1].s)); \
        if (dfs(n - 1, a + 1, r)) return 1; \
        a[1] = temp; } while (0)
typedef struct data {
    double n;
    char s[8 * 7]; // 长度看你需要而设定
} data;
data num[4], t;
 
int dfs( int n, data a[], double r ) {
    int i, j;
    if ( n == 1 )
        if ( a[0].n-r > 1e-8 || a[0].n-r < -1e-8 )
            return 0;
        else return 1;
    for ( i = 0; i < n; ++i ) {
        SWAP( data, a[i], a[0] );
        for ( j = 1; j < n; ++j ) {
            SWAP( data, a[j], a[1] );
            data temp = a[1];
            OP( + );
            OP( - );
            OP( * );
            if ( a[1].n > 1e-8 || a[1].n < -1e-8 )
                OP( / );
            SWAP( data, a[j], a[1] );
        }
        SWAP( data, a[i], a[0] );
    }
    return 0;
}
 
int main( void ) {
    int r = 24, i;
    for ( i = 0; i < 4; ++i ) {
        scanf( "%s", num[i].s );
        sscanf( num[i].s, "%lf", &num[i].n );
    }
    if ( dfs( 4, num, r ) )
        printf( "%s = %d\n", num[3].s, r );
    else
        printf( "No answer\n" );
    return 0;
}