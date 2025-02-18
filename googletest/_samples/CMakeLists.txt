cmake_minimum_required(VERSION 3.13)
project(SampleProject LANGUAGES CXX)

# 소스 및 헤더 파일 설정
set(SAMPLE_SOURCES
    src/Cat.cc
    src/CatFood.cc
)

set(SAMPLE_HEADERS
    includes/Cat.h
    includes/CatFood.h
)

# 실행 파일 대신 정적 라이브러리 생성
add_library(sample_lib STATIC ${SAMPLE_SOURCES} ${SAMPLE_HEADERS})

# 헤더 포함 경로 추가
target_include_directories(sample_lib PUBLIC includes)

# Google Test와 Google Mock 포함 경로 추가
find_package(GTest REQUIRED)
target_include_directories(sample_lib PUBLIC ${GTEST_INCLUDE_DIRS})

# Google Test + Google Mock을 사용한 테스트 추가
enable_testing()

add_executable(sample_test tests/CatTest.cc)

# Google Mock 헤더 경로 추가
target_include_directories(sample_test PUBLIC ${GTEST_INCLUDE_DIRS})

# Google Mock 라이브러리 포함
target_link_libraries(sample_test sample_lib GTest::GTest GTest::Main GTest::gmock GTest::gmock_main)

# 테스트 등록
add_test(NAME SampleTest COMMAND sample_test)
