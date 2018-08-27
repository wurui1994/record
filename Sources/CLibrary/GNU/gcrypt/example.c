//libgcrypt使用举例1，计算输入字符串的sha-1值：
#include <gcrypt.h>
#include <stdio.h>
#include <stdlib.h>

// compile with:
//
// gcc sha1.c -lstdc++ -lgcrypt -lgpg-error -I/local/include -L/local/lib -o sha1
//
//
// Example run:
//
// thomas@t40$ ./sha1 foo
// 0beec7b5ea3f0fdbc95d0dd47f3c5bc275da8a33
// thomas@t40$ echo -n foo | sha1sum
// 0beec7b5ea3f0fdbc95d0dd47f3c5bc275da8a33 -

int main(int argc, char **argv)
{
	/* Test for arg string */
	if ( argc < 2 ) {
		fprintf( stderr, "Usage: %s <string>\n", argv[0] );
		exit( 1 );
	}

	/* Length of message to encrypt */
	int msg_len = strlen( argv[1] );

	/* Length of resulting sha1 hash - gcry_md_get_algo_dlen
	* returns digest lenght for an algo */
	int hash_len = gcry_md_get_algo_dlen( GCRY_MD_SHA1 );

	/* output sha1 hash - this will be binary data */
	unsigned char hash[ hash_len ];

	/* output sha1 hash - converted to hex representation
	* 2 hex digits for every byte + 1 for trailing \0 */
	char *out = (char *) malloc( sizeof(char) * ((hash_len*2)+1) );
	char *p = out;

	/* calculate the SHA1 digest. This is a bit of a shortcut function
	* most gcrypt operations require the creation of a handle, etc. */
	gcry_md_hash_buffer( GCRY_MD_SHA1, hash, argv[1], msg_len );

	/* Convert each byte to its 2 digit ascii
	* hex representation and place in out */
	int i;
	for ( i = 0; i < hash_len; i++, p += 2 ) {
		snprintf ( p, 3, "%02x", hash[i] );
	}

	printf( "%s\n", out );
	free( out );
}