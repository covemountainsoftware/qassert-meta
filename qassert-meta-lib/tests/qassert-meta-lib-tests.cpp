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
    CHECK_TRUE(QAssertMetaGetDescription("qf_actq", 102, &description));

    CHECK_TRUE(description.url != nullptr);
    CHECK_TRUE(description.tips != nullptr);
    CHECK_TRUE(description.brief != nullptr);
}

TEST(qassert_meta_lib_tests, list_of_internal_qassert_supported)
{
    // Check (list) each internal module/id combo.
    // Not confirming the output descriptions.
    QAssertMetaDescription description = {nullptr, nullptr, nullptr};
    CHECK_TRUE(QAssertMetaGetDescription("qf_actq", 102, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_actq", 190, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_actq", 202, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_actq", 201, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_actq", 310, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_actq", 400, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qep_hsm", 200, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qep_hsm", 210, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qep_hsm", 220, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qep_hsm", 290, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_defer", 210, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_dyn", 200, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_dyn", 201, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_dyn", 400, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_dyn", 300, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_dyn", 320, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_dyn", 402, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_dyn", 410, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_dyn", 502, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_dyn", 602, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_mem", 100, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_mem", 110, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_mem", 300, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_mem", 302, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_mem", 320, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_mem", 330, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_mem", 200, &description));


}
