
include(FetchContent)

set(GOOGLETEST_COMMIT e2239ee6043f73722e7aa812a459f54a28552929)

FetchContent_Declare(
    googletest
    URL "https://github.com/google/googletest/archive/${GOOGLETEST_COMMIT}.zip"
)

if (WIN32)
  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif ()

FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
#add_executable(example example.cpp)
#target_link_libraries(example gtest_main)
#add_test(NAME example_test COMMAND example)
