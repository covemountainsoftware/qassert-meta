// MIT License
//
// Copyright (c) 2024 Matthew Eshleman Consulting (covemountainsoftware.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
    CHECK_TRUE(QAssertMetaGetDescription("qf_dyn", 500, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_dyn", 502, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_dyn", 602, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_mem", 100, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_mem", 110, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_mem", 300, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_mem", 302, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_mem", 320, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_mem", 330, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_mem", 200, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_ps", 200, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_ps", 202, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_ps", 210, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_ps", 220, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_ps", 290, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_ps", 300, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_ps", 302, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_ps", 400, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_ps", 402, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_ps", 500, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_qact", 100, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_qact", 190, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_qact", 200, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_qeq", 200, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_qeq", 210, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_qeq", 300, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_qeq", 410, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_time", 300, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_time", 400, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_time", 600, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_time", 100, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_time", 110, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_time", 112, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_time", 190, &description));
    CHECK_TRUE(QAssertMetaGetDescription("qf_time", 800, &description));



}
