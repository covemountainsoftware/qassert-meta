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
            "QF_getQueueMin, an error related to the selected priority input parameter.",
            "Most likely, a currently unused priority was queried.",
            "https://www.state-machine.com/qpc/class_q_f.html#a29692c0dcab731199b5beb5847484ab7"
        }
    },
    {
        "qep_hsm", 200,
        {
            "QHsm init failure.",
            "A setup of the target HSM was not completed correctly,\n"
            "or the HSM's init was executed more than once.",
            "https://www.state-machine.com/qpc/struct_q_hsm.html#ae69df28aa99b6f9db31a0499e5a52622"
        }
    },
    {
        "qep_hsm", 210,
        {
            "QHsm init failure in the initial transition.",
            "The custom initial transition failed to transition to a state,\n."
            "i.e. use Q_TRAN(...) in the HSM's initial state.",
            "https://www.state-machine.com/qpc/struct_q_hsm.html#ae69df28aa99b6f9db31a0499e5a52622"
        }
    },
    {
        "qep_hsm", 220,
        {
            "QHsm init failure in the initial transition, could not reach initial destination state.",
            "The HSM state nesting may be too deep or is malformed in some manner.",
            "https://www.state-machine.com/qpc/struct_q_hsm.html#ae69df28aa99b6f9db31a0499e5a52622"
        }
    },
    {
        "qep_hsm", 290,
        {
            "QHsm init failure in the initial transition, could not reach initial destination state.",
            "The HSM state nesting may be too deep or is malformed in some manner.",
            "https://www.state-machine.com/qpc/struct_q_hsm.html#ae69df28aa99b6f9db31a0499e5a52622"
        }
    },
    {
        "qf_defer", 210,
        {
            "The recalled deferred event must meet reference counter expectations.",
            "Stomping on memory?",
            "https://www.state-machine.com/qpc/struct_q_active.html#a7a942dbe8981c0a6f85550a7dbb841be"
        }
    },
    {
        "qf_dyn", 200,
        {
            "Call to pollInit(...) exceeds the configured maximum.",
            "See QF_MAX_EPOOL. But do you really need more pools?",
            "https://www.state-machine.com/qpc/class_q_f.html#a1c4fc5636c2bc2e9d47e958aac05b8e1"
        }
    },
    {
        "qf_dyn", 201,
        {
            "Each pool initialized by pollInit(...) must be initialized in increasing event size.",
            "Check the size of parameters used to initialize the pools and ensure they are\n"
            "sized as expected and in increasing size.",
            "https://www.state-machine.com/qpc/class_q_f.html#a1c4fc5636c2bc2e9d47e958aac05b8e1"
        }
    },
    {
        "qf_dyn", 400,
        {
            "Call to getPoolMin(...) with invalid pool number.",
            "Typo? Bad code? Forgot to initialize the pool?",
            "https://www.state-machine.com/qpc/class_q_f.html#a92f6caf14f52d95b7d8bfc39d1656fe3"
        }
    },
    {
        "qf_dyn", 300,
        {
            "Attempting to allocate an event that is larger than any available pool.",
            "Probably need to increase the event size of the largest event pool.",
            "https://www.state-machine.com/qpc/class_q_f.html#ad3bc25ebbfc2c2c433f8762a77136366"
        }
    },
    {
        "qf_dyn", 320,
        {
            "Event allocation failed with QF_NO_MARGIN.",
            "There is likely an event leak or excessive deferral of events.",
            "https://www.state-machine.com/qpc/class_q_f.html#ad3bc25ebbfc2c2c433f8762a77136366"
        }
    },
    {
        "qf_dyn", 402,
        {
            "Event verification within garbage collection failed.",
            "Check for memory corruption or stale event pointer being reused incorrectly.",
            "https://www.state-machine.com/qpc/class_q_f.html#a7aa4e9d39b8af089405cb829e2cc5a24"
        }
    },
    {
        "qf_dyn", 410,
        {
            "Event's pool number was invalid.",
            "Check for memory corruption of event related data.",
            "https://www.state-machine.com/qpc/class_q_f.html#a7aa4e9d39b8af089405cb829e2cc5a24"
        }
    },
    {
        "qf_dyn", 502,
        {
            "While creating a new reference, an event failed verification.",
            "Check for memory corruption or stale event pointer being reused incorrectly.",
            "https://www.state-machine.com/qpc/class_q_f.html#aee4449d368362c7fc1d1ddc258027d53"
        }
    },
    {
        "qf_dyn", 602,
        {
            "While deleting an event reference, an event failed verification.",
            "Check for memory corruption or stale event pointer being reused incorrectly.",
            "https://www.state-machine.com/qpc/class_q_f.html#aebb373ddc448c4198e4247b6c6ff3e69"
        }
    },
    {
        "qf_mem", 100,
        {
            "QPPool_init(...) parameters failed validation.",
            "Check the pool size and ensure that at least one free block will fit,\n"
            "otherwise, see the documentation at the URL.",
            "https://www.state-machine.com/qpc/struct_q_m_pool.html#a477cb6d8f27af8db6cf6a155b331d996"
        }
    },
    {
        "qf_mem", 110,
        {
            "QPPool_init(...) parameters failed validation.",
            "The desired pool size must allow for at least one rounded up block.",
            "https://www.state-machine.com/qpc/struct_q_m_pool.html#a477cb6d8f27af8db6cf6a155b331d996"
        }
    },
    {
        "qf_mem", 300,
        {
            "QMPool_get(...) internal integrity check failure.",
            "Check for memory corruption related to objects allocated from or near this pool.",
            "https://www.state-machine.com/qpc/struct_q_m_pool.html#a312e8c7ec9a9a751578248f3ef3847ff"
        }
    },
    {
        "qf_mem", 302,
        {
            "QMPool_get(...) internal integrity check failure.",
            "Check for memory corruption related to objects allocated from or near this pool.",
            "https://www.state-machine.com/qpc/struct_q_m_pool.html#a312e8c7ec9a9a751578248f3ef3847ff"
        }
    },
    {
        "qf_mem", 320,
        {
            "QMPool_get(...) internal integrity check failure upon becoming empty.",
            "Check for memory corruption related to objects allocated from or near this pool.",
            "https://www.state-machine.com/qpc/struct_q_m_pool.html#a312e8c7ec9a9a751578248f3ef3847ff"
        }
    },
    {
        "qf_mem", 330,
        {
            "QMPool_get(...) internal integrity check failure when not empty.",
            "Check for memory corruption related to objects allocated from or near this pool.",
            "https://www.state-machine.com/qpc/struct_q_m_pool.html#a312e8c7ec9a9a751578248f3ef3847ff"
        }
    },
    {
        "qf_mem", 200,
        {
            "QMPool_put(...) failed internal integrity check.",
            "Check for memory corruption related to objects allocated from or near this pool.",
            "https://www.state-machine.com/qpc/struct_q_m_pool.html#a2fc0921a76c70b107e9f495a37c02681"
        }
    },
    //List terminating structure, keep last.
    {
        NULL, -1, {NULL, NULL, NULL}
    }
};