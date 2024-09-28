#include "CppUTest/TestHarness.h"
#include "qassert-meta.h"

TEST_GROUP(qassert_meta_lib_tests) {
    void setup() final
    {
        QAssertMetaInit();
    }

    void teardown() final
    {
    }
};

TEST(qassert_meta_lib_tests, can_compile)
{
}

TEST(qassert_meta_lib_tests, description_returns_false_if_unknown_qassert)
{
    QAssertMetaDescription description;
    CHECK_FALSE(QAssertMetaGetDescription("gobble", 123456, &description));
}

TEST(qassert_meta_lib_tests, description_returns_false_if_output_param_is_null)
{
    CHECK_FALSE(QAssertMetaGetDescription("qf_actq", 102, nullptr));
}

TEST(qassert_meta_lib_tests, can_register_callback_for_unknown_asserts)
{
    constexpr const char * TEST_UNKNOWN_MODULE = "gobble";
    constexpr int TEST_UNKNOWN_ID = 123456;
    static const char * callbackModule = nullptr;
    static int callbackId = -1;
    QAssertMetaDescription description;
    auto testCallback = [](const char * module, int id, QAssertMetaDescription* output){
        (void)output;
        callbackModule = module;
        callbackId = id;
        return false;
    };

    QAssertMetaRegisterUnknownCallback(testCallback);
    bool ok = QAssertMetaGetDescription(
            TEST_UNKNOWN_MODULE, TEST_UNKNOWN_ID, &description);

    CHECK_FALSE(ok);
    STRCMP_EQUAL(TEST_UNKNOWN_MODULE, callbackModule);
    CHECK_EQUAL(TEST_UNKNOWN_ID, callbackId);
}

TEST(qassert_meta_lib_tests, unknown_callback_if_true_then_returns_true_and_output_reflects_callback_changes)
{
    constexpr const char * TEST_EXTENDED_MODULE = "extended";
    constexpr int TEST_EXTENDED_ID = 1;
    constexpr const char * SHORT_DESC = "This is short";
    constexpr const char * TIPS = "Here are some tips";
    QAssertMetaDescription description;
    auto testCallback = [](const char * module, int id, QAssertMetaDescription* output){
        (void)module;
        (void)id;
        output->brief = SHORT_DESC;
        output->tips = TIPS;
        output->url = nullptr;
        return true;
    };

    QAssertMetaRegisterUnknownCallback(testCallback);
    bool ok = QAssertMetaGetDescription(
            TEST_EXTENDED_MODULE, TEST_EXTENDED_ID, &description);

    CHECK_TRUE(ok);
    STRCMP_EQUAL(SHORT_DESC, description.brief);
    STRCMP_EQUAL(TIPS, description.tips);
    CHECK_EQUAL(nullptr, description.url);
}

TEST(qassert_meta_lib_tests, if_qassert_is_known_returns_true_and_description_is_filled)
{
    QAssertMetaDescription description = {nullptr, nullptr, nullptr};
    CHECK_TRUE(QAssertMetaGetDescription("qf_actq", 110, &description));

    CHECK_TRUE(description.url != nullptr);
    CHECK_TRUE(description.tips != nullptr);
    CHECK_TRUE(description.brief != nullptr);
}
