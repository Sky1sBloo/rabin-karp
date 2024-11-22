add_executable(
    rabin-karp-unit-tests
    tests.cpp
)

target_link_libraries(rabin-karp-unit-tests PRIVATE rabin-karp-lib)
