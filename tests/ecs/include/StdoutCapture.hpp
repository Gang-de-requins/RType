#ifndef STDOUT_CAPTURE_HPP
#define STDOUT_CAPTURE_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <gtest/gtest.h>

class StdoutCaptureTest : public ::testing::Test {
    protected:
        void SetUp() override {
            this->stdoutBuffer = std::cout.rdbuf();
            std::cout.rdbuf(this->capturedStdout.rdbuf());
        }

        void TearDown() override {
            std::cout.rdbuf(this->stdoutBuffer);
        }

        void TestBody() override {
            std::cout.rdbuf(this->capturedStdout.rdbuf());
        }

        std::streambuf *stdoutBuffer;
        std::stringstream capturedStdout;
    
    public:
        void reset() {
            this->capturedStdout.str("");
        }

        std::string get() {
            return this->capturedStdout.str();
        }

        void capture() {
            std::cout.rdbuf(this->capturedStdout.rdbuf());
        }
};

#endif /* !STDOUT_CAPTURE_HPP */
