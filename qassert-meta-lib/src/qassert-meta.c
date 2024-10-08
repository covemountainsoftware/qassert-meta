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

#include "qassert-meta.h"
#include "qassert-meta-private.h"
#include <stddef.h>
#include <string.h>

static UnknownQAssertCallback m_unknown_callback = NULL;

void QAssertMetaInit(void)
{
    m_unknown_callback = NULL;
}

void QAssertMetaRegisterUnknownCallback(UnknownQAssertCallback callback)
{
    m_unknown_callback = callback;
}

bool QAssertMetaGetDescription(const char * module, int id, QAssertMetaDescription* output)
{
    if ((NULL == output) || (NULL == module))
    {
        return false;
    }

    bool found = false;

    //TODO: search internal for matching module/id pair
    int i = 0;
    while (m_qassert_meta_items[i].module != NULL)
    {
        if (m_qassert_meta_items[i].id == id)
        {
            if (0 == strcmp(module, m_qassert_meta_items[i].module))
            {
                found = true;
                *output = m_qassert_meta_items[i].description;
                break;
            }
        }
        ++i;
    }

    if ((!found) && (m_unknown_callback != NULL))
    {
        found = m_unknown_callback(module, id, output);
    }

    return found;
}
