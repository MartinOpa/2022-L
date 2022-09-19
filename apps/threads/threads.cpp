#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/param.h>
#include <pthread.h>

#define TYPE int

struct thread_argument
{
    int id;
    int from, length;
    TYPE *data;
    TYPE max;
};

TYPE search_max( int left, int length, TYPE *array )
{
    TYPE max_elem = array[ left ];
    for ( int i = 1; i < length; i++ )
        if ( max_elem < array[ left + i ] )
            max_elem = array[ left + i ];
    return max_elem;
}

void *thread( void *void_arg )
{
    thread_argument *ptr_data = ( thread_argument * ) void_arg;

    ptr_data->max = search_max( ptr_data->from, ptr_data->length, ptr_data->data );

    return NULL;
}

int timeval_to_ms( timeval *start, timeval *end )
{
    timeval res;
    timersub( end, start, &res );
    return 1000 * res.tv_sec + res.tv_usec / 1000;
}

int compare( const void* a, const void* b)
{
     int int_a = * ( (int*) a );
     int int_b = * ( (int*) b );

     if ( int_a == int_b ) return 0;
     else if ( int_a < int_b ) return -1;
     else return 1;
}

int merge( int *test_array, int *a, int *b, int length1, int length2, int *test_merged )
{
    for ( int i = 0; i < length1; i++ )
    {
        test_merged[i] = a[i];
    }
    for ( int i = 0; i < length1 + length2; i++)
    {
        test_merged[ i + length1 ] = b[i];
    }

    return NULL;
}

int main( int argc, char **argv )
{
    int test_length = 10;
    int array_length = atoi( argv[ 1 ] );

    if ( array_length > 7000 )
    {
        array_length = array_length - 2500;
    }

    TYPE *test_array = new TYPE [ test_length ];
    TYPE *test_array1 = new TYPE [ test_length / 2 ];
    TYPE *test_array2 = new TYPE [ test_length - ( test_length / 2 ) ];
    TYPE *array = new TYPE [ array_length ];
    TYPE *array1 = new TYPE [ array_length / 2];
    TYPE *array2 = new TYPE [ array_length - ( array_length / 2 )];

    srand( ( int ) time( NULL ) );

    //test

    printf("10 random test numbers\n");
    for ( int i = 0; i < test_length ; i++ )
    {
        test_array[ i ] = rand() % ( test_length * 10 );
        printf("number %d: %d \n", i+1 , test_array[ i ]);
    }

    qsort( test_array, test_length, sizeof(int), compare );

    printf("\n");

    int test_max = 0;

    for ( int i = 0; i < test_length; i++ )
    {
        printf("number %d: %d \n", i+1 , test_array[ i ]);
    }

    for ( int i = 0; i < test_length; i++)
    {
        if ( test_max < test_array[ i ])
        {
            test_max = test_array[ i ];
        }
    }

    printf("\nMaximum test number: %d \n", test_max);

    //"normal"

    for ( int i = 0; i < array_length; i++ )
    {
        array[ i ] = rand() % ( array_length * 10 );
    }

    timeval start, end;

    printf("\nNormal array sorting\n");

    gettimeofday( &start, NULL );

    qsort( array, array_length, sizeof(int), compare );

    TYPE MAX = search_max( 0, array_length, array );

    gettimeofday( &end, NULL );

    printf("Maximum number: %d \n", MAX);
    printf("Search time: %d [ms]\n\n", timeval_to_ms( &start, &end));

    // 2 threads

    printf("10 random test numbers\n");
    for ( int i = 0; i < test_length; i++ )
    {
        test_array[ i ] = rand() % ( test_length * 10 );
        printf("number %d: %d \n", i+1 , test_array[ i ]);
    }

    for ( int i = 0; i < test_length; i++ )
    {
        test_array1[ i ] = test_array[ i ]; 
    }

    for ( int i = 0; i < test_length; i++ )
    {
        test_array2[ i ] = test_array[ i + ( test_length / 2 ) ]; 
    }

    pthread_t testpt1, testpt2;
    thread_argument testta1, testta2;

    testta1.id = 1;
    testta1.from = 0;
    testta1.length = test_length / 2;
    testta1.data = test_array1;

    testta2.id = 2;
    testta2.from = 0;
    testta2.length = test_length - testta1.length;
    testta2.data = test_array2;

    printf("\n2 threads test sorting\n");

    pthread_create( &testpt1, NULL, thread, &testta1 );
    pthread_create( &testpt2, NULL, thread, &testta2 );

    pthread_join( testpt1, NULL );
    pthread_join( testpt2, NULL );

    qsort( test_array1, ( test_length / 2 ), sizeof(int), compare );
    qsort( test_array2, (test_length - ( test_length / 2 )), sizeof(int), compare );

    printf( "Thread 1:\n");
    for ( int i = 0; i < (test_length / 2); i++ )
    {
        printf( "Number %d: %d", i+1, test_array1[ i ]);
        if ( i < ((test_length / 2 ) -1 ) )
        {
            printf(", ");
        }
    }
    printf( "\nThread 2:\n");
    for ( int i = (test_length / 2); i < test_length; i++ )
    {
        printf( "Number %d: %d", i+1, test_array2[ i - ( test_length / 2 )]);
        if ( i < test_length -1 )
        {
            printf(", ");
        }
    }

    printf("\n2 threads test maximum: %d\n", MAX( testta1.max, testta2.max));

    int* test_merged = (int*)malloc(test_length*sizeof(int));
    
    merge( test_array, test_array1, test_array2, (test_length / 2), ( test_length - ( test_length / 2 ) ), test_merged );

    qsort( test_merged, test_length, sizeof(int), compare );

    printf("Merged numbers:\n");
    for ( int i = 0; i < test_length; i++)
    {
        printf("Number %d: %d\n", i+1, test_merged[i]);
    }

    printf("\n2 threads sorting\n");
    for ( int i = 0; i < array_length; i++ )
    {
        array[ i ] = rand() % ( array_length * 10 );
    }
    
    for ( int i = 0; i < array_length; i++ )
    {
        array1[ i ] = array[ i ]; 
    }

    for ( int i = 0; i < array_length; i++ )
    {
        array2[ i ] = array[ i + ( array_length / 2 ) ]; 
    }

    pthread_t pt1, pt2;
    thread_argument ta1, ta2;

    ta1.id = 1;
    ta1.from = 0;
    ta1.length = array_length / 2;
    ta1.data = array1;

    ta2.id = 2;
    ta2.from = 0;
    ta2.length = array_length - ta1.length;
    ta2.data = array2;

    gettimeofday( &start, NULL );

    pthread_create( &pt1, NULL, thread, &ta1 );
    pthread_create( &pt2, NULL, thread, &ta2 );

    pthread_join( pt1, NULL );
    pthread_join( pt2, NULL );

    qsort( array1, ( array_length / 2 ), sizeof(int), compare );
    qsort( array2, ( array_length - ( array_length / 2 )), sizeof(int), compare );

    int* merged = (int*)malloc(1+array_length*sizeof(int));

    merge( array, array1, array2, (array_length / 2), ( array_length - ( array_length / 2 ) ), merged );

    qsort( merged, array_length, sizeof(int), compare );

    gettimeofday( &end, NULL );

    printf("1st thread maximum: %d\n2nd thread maximum: %d\n", ta1.max, ta2.max);
    printf("2 threads maximum: %d\n", MAX( ta1.max, ta2.max));
    printf("Search time: %d [ms]\n", timeval_to_ms( &start, &end));

    free(test_merged);
    free(merged);
}