cmake_minimum_required(VERSION 3.10)

project(hash LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(test_list test_list.c hash.c linkedlist.c)
add_executable(test_hash test_hash.c hash.c linkedlist.c)
add_executable(test_large_hash_shallow_copy test_large_hash_shallow_copy.c hash.c linkedlist.c)
add_executable(test_large_hash_deep_copy test_large_hash_deep_copy.c hash.c linkedlist.c)
add_executable(time_hash time_hash.c hash.c linkedlist.c)
