cmake_minimum_required(VERSION 3.30)
project(3_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(3_1 main.cpp
        feed_parser.h
        market_snapshot.h
        order_manager.h)
