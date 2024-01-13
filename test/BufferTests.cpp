#include <gtest/gtest.h>

#include <Optibits/Buffer.hpp>
#include <cstring>
#include <filesystem>


class BufferTests : public testing::Test
{
};


TEST_F(BufferTests, from_existing_memory)
{
    // nullptr & non-zero size.
    ASSERT_THROW(Optibits::Buffer(nullptr, 5, nullptr), std::invalid_argument);
    
    // negative size
    std::uint8_t bytes[] = { 1, 2 ,3 ,4 };
    ASSERT_THROW(Optibits::Buffer(bytes, -5, nullptr), std::length_error);

    bool purged = false;

    auto purger = [&](void* ptr) {
        ASSERT_EQ(ptr, bytes);
        purged = true;
    };

    // Create an instance
    Optibits::Buffer tBuffer(bytes, sizeof bytes, purger);
    ASSERT_EQ(tBuffer.data(), bytes);
    ASSERT_EQ(tBuffer.size(), sizeof bytes);

    // Move to another Buffer
    // will call move constr so 
    Optibits::Buffer newBuffer = std::move(tBuffer);

    ASSERT_EQ(tBuffer.data(), nullptr);
    ASSERT_EQ(tBuffer.size(), 0);
    ASSERT_EQ(newBuffer.data(), bytes);
    ASSERT_EQ(newBuffer.size(), sizeof bytes);

    // Had no buffer at first so purger should not be called
    ASSERT_FALSE(purged);

    newBuffer = std::move(tBuffer);

    ASSERT_TRUE(purged);
}



TEST_F(BufferTests, from_size)
{
    ASSERT_THROW(Optibits::Buffer(-5), std::length_error);
    Optibits::Buffer buffer(600);
    ASSERT_EQ(buffer.size(), 600);

    // Assigning to self in no-op
    buffer = buffer;
    ASSERT_EQ(buffer.size(), 600);
    buffer = std::move(buffer);

    // Copying has to make another copy of mem
    Optibits::Buffer buffer2;
    buffer2 = buffer;
    ASSERT_EQ(buffer2.size(), 600);
    ASSERT_NE(buffer2.data(), buffer.data());
}