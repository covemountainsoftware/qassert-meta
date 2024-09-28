#include "qassert-meta.h"
#include <stddef.h>
#include <string.h>

typedef struct {
    const char * module;
    int id;
    QAssertMetaDescription description;
} InternalMeta;

static InternalMeta m_internal[];  //actual data at bottom of this file.
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
    while (m_internal[i].module != NULL)
    {
        if (m_internal[i].id == id)
        {
            if (0 == strcmp(module, m_internal[i].module))
            {
                found = true;
                *output = m_internal[i].description;
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

static const char * const QPC_URL_QACTIVE_POST =
        "https://www.state-machine.com/qpc/struct_q_active.html#a1a81b9fd06d9c0aa5dea32d194f0552b";
static const char * const QPC_URL_QACTIVE_POST_LIFO =
        "https://www.state-machine.com/qpc/struct_q_active.html#a3a129f47e6d0c75c11a8902f8137f007";



/**
 * Collection of QP/QF related asserts.
 *
 * These are currently the opinion of Matthew Eshleman only
 * and are not necessarily the official description
 * of any particular QASSERT.
 */
static InternalMeta m_internal[] = {
    {
        "qf_actq", 102,
        {
            "The event being posted is either null, invalid, or corrupt.",
            "This typically means the event pointer was improperly retained\n"
            "after the event was returned to its event pool,\n"
            "i.e. used after the event was garbage collected.",
            QPC_URL_QACTIVE_POST
        }
    },
    {
        "qf_actq", 190,
        {
            "Target active object's queue is full.",
            "If posting an event to an active object using QF_NO_MARGIN, and the target queue is full,\n"
            "this assert will occur. The target AO might be overloaded OR a higher priority AO might\n"
            "be preventing this AO from executing.\n"
            "Note: 2024 online documentation refers to this as qf_actq:110",
            QPC_URL_QACTIVE_POST
        }
    },
    {
        "qf_actq", 202,
        {
            "The event being LIFO posted is either null, invalid, or corrupt.",
            "This typically means the event pointer was improperly retained\n"
            "after the event was returned to its event pool,\n"
            "i.e. used after the event was garbage collected.",
            QPC_URL_QACTIVE_POST_LIFO
        }
    },
    {
        "qf_actq", 201,
        {
            "The target active object's queue is full.",
            "If LIFO posting an event to an active object, and the target queue is full,\n"
            "this assert will occur. The target AO might be overloaded OR a higher priority AO might\n"
            "be preventing this AO from executing.",
            QPC_URL_QACTIVE_POST_LIFO
        }
    },
    {
        "qf_actq", 310,
        {
            "The final event was removed from the queue, yet internal data indicate a fault.",
            "Possible data corruption.",
            NULL
        }
    },
    {
        "qf_actq", 400,
        {
            "Returns the minimum of free queue entries of a target active object, using the priority as the key.",
            "Most likely, a currently unused priority was queried.",
            "https://www.state-machine.com/qpc/class_q_f.html#a29692c0dcab731199b5beb5847484ab7"
        }
    },
    //List terminating structure, keep last.
    {
        NULL, -1, {NULL, NULL, NULL}
    }
};