#include "CppUTest/TestHarness.h"
#include "qassert-meta.h"

TEST_GROUP(qassert_meta_lib_tests) {
    void setup() final
    {
    }
    void teardown() final
    {
    }
};

TEST(qassert_meta_lib_tests, can_compile)
{
}

TEST(qassert_meta_lib_tests, basic_description_returns_false_if_unknown_qassert)
{
    QAssertMetaDescription description;
    CHECK_FALSE(QAssertMetaGetDescription("gobble", 123456, &description));
}