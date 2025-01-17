/**
 * vector
 * CS 341 - Fall 2023
 */
#include "vector.h"
#include <stdio.h>
#include <assert.h>

void print_vector(char *desc, vector *v)
{
    puts("*****************************");
    puts(desc);
    if (vector_size(v) != 0)
    {
        char **walk = (char **)vector_begin(v);
        char **end = (char **)vector_end(v);
        while (walk < end)
        {
            printf("v[%ld]: %s\n", walk - (char **)vector_begin(v), *walk);
            walk++;
        }
    }
    printf("size: %zu\n", vector_size(v));
    printf("capacity: %zu\n", vector_capacity(v));
    printf("vector.empty(): %d\n", vector_empty(v));
    puts("*****************************\n");
}

void print_int_vector(char *desc, vector *v)
{
    puts("*****************************");
    puts(desc);
    if (vector_size(v) != 0)
    {
        int **walk = (int **)vector_begin(v);
        int **end = (int **)vector_end(v);
        while (walk < end)
        {
            printf("v[%ld]: %d\n", walk - (int **)vector_begin(v), **walk);
            walk++;
        }
    }
    printf("size: %zu\n", vector_size(v));
    printf("capacity: %zu\n", vector_capacity(v));
    printf("vector.empty(): %d\n", vector_empty(v));
    puts("*****************************\n");
}

void run_test(char **arr, size_t n)
{

    vector *v = vector_create(NULL, NULL, NULL); // shallow
    print_vector("Empty vector", v);

    for (size_t i = 0; i < n; ++i)
        vector_push_back(v, arr[i]);
    print_vector("Vector after push_backs", v);

    vector_pop_back(v);
    print_vector("Vector after one pop_back", v);

    // Test iterators
    puts("*****************************");
    printf("Begin of vector: %s\n", *((char **)vector_begin(v)));
    printf("End of vector: %s\n", *((char **)vector_end(v) - 1));
    puts("*****************************\n");

    // Test: size & capacity, resize & reserve
    puts("*****************************");
    printf("Size of vector: %zu\n", vector_size(v));
    printf("Capacity of vector: %zu\n\n", vector_capacity(v));
    printf("Let's resize the vector w/: n = 12\n");
    vector_resize(v, 12);
    printf("Size of vector: %zu\n", vector_size(v));         // expected 12
    printf("Capacity of vector: %zu\n", vector_capacity(v)); // expected 16
    puts("*****************************\n\n");

    puts("*****************************");
    printf("Let's reserve vector: n = 50\n");
    vector_reserve(v, 50); // expected: capacity = 64, the first power of 2 >= 50
    printf("Size of vector: %zu\n", vector_size(v));
    printf("Capacity of vector: %zu\n", vector_capacity(v));
    puts("*****************************\n\n");

    puts("*****************************");
    printf("Let's reserve vector: n = 2; This should have no effect! \n");
    vector_reserve(v, 2);
    printf("Size of vector: %zu\n", vector_size(v));
    printf("Capacity of vector: %zu\n", vector_capacity(v));
    puts("*****************************\n");

    // Element access tests
    // at
    puts("*****************************");
    size_t p = 2;
    char *str = (char *)*vector_at(v, p);
    printf("I expect vector_at[%ld] to be: 3. It is %s. Hooray!\n", p, str);
    puts("*****************************\n");

    // set
    puts("*****************************");
    vector_set(v, p, "Changed");
    printf("I expect vector_at[%ld] to be: Changed. It is %s. Hooray!\n", p, (char *)*vector_at(v, p));
    puts("*****************************\n");

    // get
    puts("*****************************");
    char *obtained = (char *)vector_get(v, 1);
    printf("I expect vector_at[%ld] to be: 2. It is %s. Hooray!\n", (size_t)1, obtained);
    puts("*****************************\n");

    // front
    puts("*****************************");
    obtained = (char *)*vector_front(v);
    printf("I expect vector_front to be: 100. It is %s. Hooray!\n", obtained);
    puts("*****************************\n");

    // back
    puts("*****************************");
    puts("Let's first resize the vector back to 3 elements");
    vector_resize(v, 3);
    printf("vector_size(v): %ld\n", vector_size(v));
    obtained = (char *)*vector_back(v);
    printf("I expect vector_back to be: Changed. It is %s. Hooray!\n", obtained);
    puts("*****************************\n");

    // Test: insert & erase
    // insert
    print_vector("Before insertion", v);
    vector_insert(v, 1, "inserted");
    print_vector("After insertion", v);

    // erase
    print_vector("Before erase", v);
    vector_erase(v, 2);
    print_vector("After erase v[2] = 2", v);

    // Test: clear
    puts("*****************************");
    vector_clear(v);
    printf("I expect v.size() == 0, and I obtain: %ld. Hooray!\n", vector_size(v));
    puts("*****************************\n");

    // Test: destroy
    puts("*****************************");
    vector_destroy(v);
    // print_vector("Lets see some stats after `vector_destroy(v)`", v);
    puts("*****************************\n");
}

int **allocate_array_intptrs(size_t n)
{
    puts("*****************************");
    printf("Print int array: for n = %ld\n", n);
    int **arr = malloc(sizeof(int *) * n);
    for (size_t i = 0; i < n; ++i)
    {
        arr[i] = malloc(sizeof(int));
        *arr[i] = i;
        printf("%d ", *arr[i]);
    }
    puts("\n*****************************\n");
    return arr;
}

void run_test_2(int **arr, size_t n)
{

    vector *v = vector_create(int_copy_constructor, int_destructor, int_default_constructor); // deep
    print_vector("Empty vector", v);

    for (size_t i = 0; i < n; ++i)
        vector_push_back(v, arr[i]);
    print_int_vector("Vector after push_backs", v);

    vector_pop_back(v);
    print_int_vector("Vector after one pop_back", v);

    // Test iterators
    puts("*****************************");
    printf("Begin of vector: %d\n", **((int **)vector_begin(v)));
    printf("End of vector: %d\n", **((int **)vector_end(v) - 1));
    puts("*****************************\n");

    // // Test: size & capacity, resize & reserve
    puts("*****************************");
    printf("Size of vector: %zu\n", vector_size(v));
    printf("Capacity of vector: %zu\n\n", vector_capacity(v));
    printf("Let's resize the vector w/: n = 12\n");
    vector_resize(v, 12);
    printf("Size of vector: %zu\n", vector_size(v));         // expected 12
    printf("Capacity of vector: %zu\n", vector_capacity(v)); // expected 16
    puts("*****************************\n\n");

    puts("*****************************");
    printf("Let's reserve vector: n = 50\n");
    vector_reserve(v, 50); // expected: capacity = 64, the first power of 2 >= 50
    printf("Size of vector: %zu\n", vector_size(v));
    printf("Capacity of vector: %zu\n", vector_capacity(v));
    puts("*****************************\n\n");

    puts("*****************************");
    printf("Let's reserve vector: n = 2; This should have no effect! \n");
    vector_reserve(v, 2);
    printf("Size of vector: %zu\n", vector_size(v));
    printf("Capacity of vector: %zu\n", vector_capacity(v));
    puts("*****************************\n");

    // // Element access tests
    // // at
    puts("*****************************");
    size_t p = 2;
    int *ptr = (int *)*vector_at(v, p);
    printf("I expect vector_at[%ld] to be: 2. It is %d. Hooray!\n", p, *ptr);
    puts("*****************************\n");

    // // set
    puts("*****************************");
    int *elem = malloc(sizeof(int));
    *elem = 5;
    vector_set(v, p, elem);
    free(elem);

    printf("I expect vector_at[%ld] to be: 5. It is %d. Hooray!\n", p, *((int *)*vector_at(v, p)));
    puts("*****************************\n");

    // // get
    puts("*****************************");
    int *obtained = (int *)vector_get(v, 1);
    printf("I expect vector_at[%ld] to be: 1. It is %d. Hooray!\n", (size_t)1, *obtained);
    puts("*****************************\n");

    // // front
    puts("*****************************");
    obtained = (int *)*vector_front(v);
    printf("I expect vector_front to be: 0. It is %d. Hooray!\n", *obtained);
    puts("*****************************\n");

    // // back
    puts("*****************************");
    puts("Let's first resize the vector back to 3 elements");
    vector_resize(v, 3);
    printf("vector_size(v): %ld\n", vector_size(v));
    obtained = (int *)*vector_back(v);
    printf("I expect vector_back to be: 5. It is %d. Hooray!\n", *obtained);
    puts("*****************************\n");

    // // Test: insert & erase
    // insert
    print_int_vector("Before insertion", v);
    elem = (int *)malloc(sizeof(int));
    *elem = 100;
    vector_insert(v, 1, elem);
    free(elem);
    print_int_vector("After insertion", v);

    // //erase
    print_int_vector("Before erase", v);
    vector_erase(v, 2);
    print_int_vector("After erase v[2] = 1", v);

    // Edge case: insert at end
    print_int_vector("Before insert at end (push_back behavior)", v);
    elem = (int *) malloc(sizeof(int));
    *elem = 6;
    vector_insert(v, vector_size(v), elem);
    free(elem);
    print_int_vector("After insert at end (push_back behavior)", v);


    // // Test: clear
    puts("*****************************");
    vector_clear(v);
    printf("I expect v.size() == 0, and I obtain: %ld. Hooray!\n", vector_size(v));
    puts("*****************************\n");

    // // Test: destroy
    puts("*****************************");
    vector_destroy(v);
    v = NULL;
    // print_int_vector("Lets see some stats after `vector_destroy(v)`", v); // (!) comment this out, as assert in vector_size fails as v == NULL
    puts("*****************************\n");
}

int main(/* int argc, char *argv[] */)
{
    // Write your test cases here

    // T1 -> shallow copy of char* vector
    run_test((char *[]){"100", "2", "3", "4"}, 4);

    // T2 -> deep copy of int* vector
    size_t n = 4;
    int **arr = allocate_array_intptrs(n);
    run_test_2(arr, n);
    // Deallocate
    for (size_t i = 0; i < n; ++i)
    {
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);
    arr = NULL;
    assert(arr == NULL);

    return 0;
}
