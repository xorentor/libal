#include <pthread.h>
#include <malloc.h>

#include "libal.h"

static int allocated = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

inline int albytes()
{
	return allocated;
}

inline void alfree( void *p )
{
	int *r;
	r = p;
	if( --r == NULL )
		return;
        pthread_mutex_lock( &mutex );
		allocated -= *r;
	pthread_mutex_unlock( &mutex );
	free( (void *)r );
}

inline void *almalloc( const int size ) {
	int *r;
	if( size <  1 )
		return NULL;
	r = malloc( size + sizeof( int ) );	
	if( r == NULL )
		return NULL;
	*r = size + sizeof( int );
        pthread_mutex_lock( &mutex );
       		allocated += *r;
	pthread_mutex_unlock( &mutex );
	return (void *)++r;
}
