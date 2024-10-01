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

#ifndef QASSERT_META_QASSERT_META_H
#define QASSERT_META_QASSERT_META_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *   QASSERT Meta Description output structure.
 */
typedef struct {
    const char * brief; //short description of the QASSERT
    const char * tips;  //detailed tips regarding this QASSERT, if available.
    const char * url;   //a URL for more, if available.
} QAssertMetaDescription;

//typedef for a callback that may be used to extend this module
//to provide Meta for application or other QASSERT sources
typedef bool (*UnknownQAssertCallback)(const char * module, int id, QAssertMetaDescription* output);

/**
 * Initialize the QAssertMeta module.
 */
void QAssertMetaInit(void);

/**
 * Register a callback to be executed if GetDescription is called
 * and the module/id pair is found to be unknown.
 * @param callback:  the callback
 */
void QAssertMetaRegisterUnknownCallback(UnknownQAssertCallback callback);

/**
 * Get a description of a Q_ASSERT based on the module and id.
 * @param module:  The module string provided with the Q_ASSERT
 * @param id:      The id value provided with the Q_ASSERT
 * @param output:  a valid pointer. This structure will be filled in if the return is true.
 * @return:  true:  assert identified and description provided.  false, this assert was not found.
 */
bool QAssertMetaGetDescription(const char * module, int id, QAssertMetaDescription* output);

#ifdef __cplusplus
}
#endif

#endif //QASSERT_META_QASSERT_META_H
