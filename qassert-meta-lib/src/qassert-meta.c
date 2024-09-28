#include "qassert-meta.h"
#include <stddef.h>

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
    bool found = false;
    //TODO: search internal for matching module/id pair

    if ((!found) && (m_unknown_callback != NULL))
    {
        found = m_unknown_callback(module, id, output);
    }

    return found;
}
