#ifndef STDERR_CAPTURE_HPP
#define STDERR_CAPTURE_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <gtest/gtest.h>

class StderrCaptureTest : public ::testing::Test {
    protected:
        void SetUp() override {
            this->stderrBuffer = std::cerr.rdbuf();
            std::cerr.rdbuf(this->capturedStderr.rdbuf());
        }

        void TearDown() override {
            std::cerr.rdbuf(this->stderrBuffer);
        }

        void TestBody() override {
            std::cerr.rdbuf(this->capturedStderr.rdbuf());
        }

        std::streambuf *stderrBuffer;
        std::stringstream capturedStderr;
    
    public:
        void reset() {
            this->capturedStderr.str("");
        }

        std::string get() {
            return this->capturedStderr.str();
        }

        void capture() {
            std::cerr.rdbuf(this->capturedStderr.rdbuf());
        }
};

#endif /* !STDERR_CAPTURE_HPP */
