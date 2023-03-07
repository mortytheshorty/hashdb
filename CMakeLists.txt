cmake_minimum_required(VERSION "3.22.1")

set(src_path "src")
set(include_path "include" "src")
project("hashdb" VERSION 0.0.1 DESCRIPTION "hashmap using quadratic probing algorithm")

add_library(hashdb SHARED ${src_path}/misc.c ${src_path}/hashdb.c ${src_path}/hashdb_internal.c)

target_include_directories(hashdb PUBLIC "./include")
target_include_directories(hashdb PRIVATE "./src")
target_compile_options(hashdb PRIVATE "-Wall" "-ggdb" "-fPIC")

add_executable(hashdb_test ${src_path}/test/hashdb_test.c)
target_include_directories(hashdb_test PUBLIC "./include")
target_include_directories(hashdb_test PRIVATE "./src")

target_link_libraries(hashdb_test hashdb)