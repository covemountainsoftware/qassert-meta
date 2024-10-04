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

#include "qassert-meta-private.h"
#include <stddef.h>

/**
 * Collection of QP/QF related asserts.
 *
 * These are currently the opinion of Matthew Eshleman only
 * and are not necessarily the official description
 * of any particular QASSERT.
 */
QAssertMetaInternalItem m_qassert_meta_items[] = {
    {
        "qf_actq", 102,
        {
            "QActive post(...), the event being posted is either null, invalid, or corrupt.",
            "This typically means the event pointer was improperly retained\n"
            "after the event was returned to its event pool,\n"
            "i.e. used after the event was garbage collected.",
            "https://www.state-machine.com/qpc/struct_q_active.html#a1a81b9fd06d9c0aa5dea32d194f0552b"
        }
    },
    {
        "qf_actq", 190,
        {
            "QActive post(...), the target active object's queue is full.",
            "If posting an event to an active object using QF_NO_MARGIN, and the target queue is full,\n"
            "this assert will occur. The target AO might be overloaded OR a higher priority AO might\n"
            "be preventing this AO from executing.\n"
            "Note: 2024 online documentation refers to this as qf_actq:110",
            "https://www.state-machine.com/qpc/struct_q_active.html#a1a81b9fd06d9c0aa5dea32d194f0552b"
        }
    },
    {
        "qf_actq", 202,
        {
            "QActive postLIFO(...), the event being posted is either null, invalid, or corrupt.",
            "This typically means the event pointer was improperly retained\n"
            "after the event was returned to its event pool,\n"
            "i.e. used after the event was garbage collected.",
            "https://www.state-machine.com/qpc/struct_q_active.html#a3a129f47e6d0c75c11a8902f8137f007"
        }
    },
    {
        "qf_actq", 201,
        {
            "QActive postLIFO(...), the target active object's queue is full.",
            "If LIFO posting an event to an active object, and the target queue is full,\n"
            "this assert will occur. The target AO might be overloaded OR a higher priority AO might\n"
            "be preventing this AO from executing.",
            "https://www.state-machine.com/qpc/struct_q_active.html#a3a129f47e6d0c75c11a8902f8137f007"
        }
    },
    {
        "qf_actq", 310,
        {
            "QActive get(...), an internal integrity check has failed.",
            "Possible data corruption.",
            NULL
        }
    },
    {
        "qf_actq", 400,
        {
            "QF getQueueMin, an error related to the selected priority input parameter.",
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
            "Call to poolInit(...) exceeds the configured maximum.",
            "See QF_MAX_EPOOL. But do you really need more pools?",
            "https://www.state-machine.com/qpc/class_q_f.html#a1c4fc5636c2bc2e9d47e958aac05b8e1"
        }
    },
    {
        "qf_dyn", 201,
        {
            "Each pool initialized by poolInit(...) must be initialized in increasing event size.",
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
            "QPPool init(...) parameters failed validation.",
            "Check the pool size and ensure that at least one free block will fit,\n"
            "otherwise, see the documentation at the URL.",
            "https://www.state-machine.com/qpc/struct_q_m_pool.html#a477cb6d8f27af8db6cf6a155b331d996"
        }
    },
    {
        "qf_mem", 110,
        {
            "QPPool init(...) parameters failed validation.",
            "The desired pool size must allow for at least one rounded up block.",
            "https://www.state-machine.com/qpc/struct_q_m_pool.html#a477cb6d8f27af8db6cf6a155b331d996"
        }
    },
    {
        "qf_mem", 300,
        {
            "QMPool get(...) internal integrity check failure.",
            "Check for memory corruption related to objects allocated from or near this pool.",
            "https://www.state-machine.com/qpc/struct_q_m_pool.html#a312e8c7ec9a9a751578248f3ef3847ff"
        }
    },
    {
        "qf_mem", 302,
        {
            "QMPool get(...) internal integrity check failure.",
            "Check for memory corruption related to objects allocated from or near this pool.",
            "https://www.state-machine.com/qpc/struct_q_m_pool.html#a312e8c7ec9a9a751578248f3ef3847ff"
        }
    },
    {
        "qf_mem", 320,
        {
            "QMPool get(...) internal integrity check failure upon becoming empty.",
            "Check for memory corruption related to objects allocated from or near this pool.",
            "https://www.state-machine.com/qpc/struct_q_m_pool.html#a312e8c7ec9a9a751578248f3ef3847ff"
        }
    },
    {
        "qf_mem", 330,
        {
            "QMPool get(...) internal integrity check failure when not empty.",
            "Check for memory corruption related to objects allocated from or near this pool.",
            "https://www.state-machine.com/qpc/struct_q_m_pool.html#a312e8c7ec9a9a751578248f3ef3847ff"
        }
    },
    {
        "qf_mem", 200,
        {
            "QMPool put(...) failed internal integrity check.",
            "Check for memory corruption related to objects allocated from or near this pool.",
            "https://www.state-machine.com/qpc/struct_q_m_pool.html#a2fc0921a76c70b107e9f495a37c02681"
        }
    },
    {
        "qf_ps", 200,
        {
            "Attempt to publish an event with a signal outside the configured pub/sub signal range.",
            "Is this an event that would normally be posted directly or needs to be added to the\n"
            "master publish/subscribe signal enum?",
            "https://www.state-machine.com/qpc/struct_q_active.html#a892d39d181cc0f0b053669d6b7c5b4bb"
        }
    },
    {
        "qf_ps", 202,
        {
            "publish(...) failed an internal integrity check.",
            "Likely memory corruption.",
            "https://www.state-machine.com/qpc/struct_q_active.html#a892d39d181cc0f0b053669d6b7c5b4bb"
        }
    },
    {
        "qf_ps", 210,
        {
            "publish(...) failed an internal integrity check, where the AO\n"
            "found was (somehow) not registered with the framework.",
            "Likely memory corruption.",
            "https://www.state-machine.com/qpc/struct_q_active.html#a892d39d181cc0f0b053669d6b7c5b4bb"
        }
    },
    {
        "qf_ps", 220,
        {
            "publish(...) failed an internal integrity check, where a subsequent AO\n"
            "found was (somehow) not registered with the framework.",
            "Likely memory corruption.",
            "https://www.state-machine.com/qpc/struct_q_active.html#a892d39d181cc0f0b053669d6b7c5b4bb"
        }
    },
    {
        "qf_ps", 290,
        {
            "publish(...) failed an internal integrity check.",
            "Likely memory corruption.",
            "https://www.state-machine.com/qpc/struct_q_active.html#a892d39d181cc0f0b053669d6b7c5b4bb"
        }
    },
    {
        "qf_ps", 300,
        {
            "subscribe(...) failed one or more of multiple input and state checks.",
            "Specifically:\n"
            "  - The signal being subscribed to must be within the configured pub/sub signal range.\n"
            "  - The subscriber AO priority must be within the configured range.\n"
            "  - The AO must be registered with the framework.",
            "https://www.state-machine.com/qpc/struct_q_active.html#ae2510a52f1185e2561fa78323983c04d"
        }
    },
    {
        "qf_ps", 302,
        {
            "subscribe(...) failed an internal integrity check.",
            "Likely memory corruption.",
            "https://www.state-machine.com/qpc/struct_q_active.html#ae2510a52f1185e2561fa78323983c04d"
        }
    },
    {
        "qf_ps", 400,
        {
            "unsubscribe(...) failed one or more of multiple input and state checks.",
                "Specifically:\n"
                "  - The signal being unsubscribed must be within the configured pub/sub signal range.\n"
                "  - The AO priority must be within the configured range.\n"
                "  - The AO must be registered with the framework.",
            "https://www.state-machine.com/qpc/struct_q_active.html#a0cf08b1345a60cb4cd2d580f448f819d"
        }
    },
    {
        "qf_ps", 402,
        {
            "unsubscribe(...) failed an internal integrity check.",
            "Likely memory corruption.",
            "https://www.state-machine.com/qpc/struct_q_active.html#a0cf08b1345a60cb4cd2d580f448f819d"
        }
    },
    {
        "qf_ps", 500,
        {
            "unsubscribeAll(...) failed one or more of multiple input and state checks.",
            "Specifically:\n"
            "  - The AO priority must be within the configured range.\n"
            "  - The AO must be registered with the framework.",
            "https://www.state-machine.com/qpc/struct_q_active.html#aec64ea18ec1909aa5ce20ca1c154bea4"
        }
    },
    {
        "qf_qact", 100,
        {
            "QActive register(...) failed one or more of input argument checks.",
            "Specifically:\n"
            "  - The AO priority must be within the configured range.\n"
            "  - The AO priority must not be in use already.\n"
            "  - The AO priority must not exceed the preemption threshold.",
            "https://www.state-machine.com/qpc/struct_q_active.html#abe6de335bea204db67cbd96fbb988f2b"
        }
    },
    {
        "qf_qact", 190,
        {
            "QActive register(...) failed one or more post-condition checks.",
            "Specifically:\n"
            "  - The preceding preemption threshold must not exceed this AO's preemption threshold.\n"
            "  - The preemption threshold must not exceed the next preemption threshold.",
            "https://www.state-machine.com/qpc/struct_q_active.html#abe6de335bea204db67cbd96fbb988f2b"
        }
    },
    {
        "qf_qact", 200,
        {
            "QActive unregister(...) failed one or more input argument checks.",
            "Specifically:\n"
            "  - The AO priority must be within the configured range.\n"
            "  - The priority must have been already registered.",
            "https://www.state-machine.com/qpc/struct_q_active.html#a16aba45c83211a8edc065662345e8a8e"
        }
    },
    {
        "qf_qeq", 200,
        {
            "QEQueue post(...), the provided event pointer is null.",
            "Thou shalt not follow the null pointer!",
            "https://www.state-machine.com/qpc/struct_q_e_queue.html#aef79dbd59331c61ec1591f7ca43b1280"
        }
    },
    {
        "qf_qeq", 210,
        {
            "QEQueue post(...), the queue is full and margin is QF_NO_MARGIN.",
            "Double check priorities and thread behavior. A thread is generating too many events or\n"
            "the thread servicing this queue is too slow, is being starved by a higher priority thread\n"
            "or needs a deeper queue.",
            "https://www.state-machine.com/qpc/struct_q_e_queue.html#aef79dbd59331c61ec1591f7ca43b1280"
        }
    },
    {
        "qf_qeq", 300,
        {
            "QEQueue postLIFO(...), the target queue is full.",
            "Double check priorities and thread behavior. A thread is generating too many events or\n"
            "the thread servicing this queue is too slow, is being starved by a higher priority thread\n"
            "or needs a deeper queue.",
            "https://www.state-machine.com/qpc/struct_q_e_queue.html#ab0c7a67307992567ffea4caf891a832a"
        }
    },
    {
        "qf_qeq", 410,
        {
            "QEQueue get(...), an internal integrity check failed.",
            "Possible memory corruption?",
            "https://www.state-machine.com/qpc/struct_q_e_queue.html#a55ae04e6f994d5016577ed4b342a8fbd"
        }
    },
    {
        "qf_time", 300,
        {
            "QTimeEvt ctor(...), invalid input parameter.",
            "'sig' must not be zero and 'tickRate' must be within the configured range.",
            "https://www.state-machine.com/qpc/struct_q_time_evt.html#a04b021eb5cf81f1d1700b9ce0afa37a9"
        }
    },
    {
        "qf_time", 400,
        {
            "QTimeEvt arm(...), invalid input parameter.",
            "  The host AO must not be null.\n"
            "  The time event must not be armed already.\n"
            "  Ticks must not be zero.\n"
            "  The signal value must be valid.",
            "https://www.state-machine.com/qpc/struct_q_time_evt.html#a9bbcb00315fb8bb8641003b2b2d07ce4"
        }
    },
    {
        "qf_time", 600,
        {
            "QTimeEvt rearm(...), invalid input parameter.",
            "  The host AO must not be null.\n"
            "  The time event must not be armed already.\n"
            "  Ticks must not be zero.\n"
            "  The signal value must be valid.",
            "https://www.state-machine.com/qpc/struct_q_time_evt.html#a3a5734e32caac22b89766a4b90a1679b"
        }
    },
    {
        "qf_time", 100,
        {
            "QTimeEvt tick(...), internal integrity failure.",
            "Invalid 'tickRate' parameter. The function calling tick(...) should be examined.",
            "https://www.state-machine.com/qpc/struct_q_time_evt.html#a4110381e712227678890d112edc28cf9"
        }
    },
    {
        "qf_time", 110,
        {
            "QTimeEvt tick(...), internal integrity failure.",
            "An internal variable was unexpectedly null. Memory corruption?",
            "https://www.state-machine.com/qpc/struct_q_time_evt.html#a4110381e712227678890d112edc28cf9"
        }
    },
    {
        "qf_time", 112,
        {
            "QTimeEvt tick(...), internal integrity failure.",
            "A timer is firing, but the event to be posted is invalid.\n"
            "Confirm that the event provided to the timer is valid, otherwise seek\n"
            "out sources of memory corruption.",
            "https://www.state-machine.com/qpc/struct_q_time_evt.html#a4110381e712227678890d112edc28cf9"
        }
    },
    {
        "qf_time", 190,
        {
            "QTimeEvt tick(...), internal timer loop limit hit.",
            "There might be too many timers active in the system. Otherwise, seek\n"
            "out sources of memory corruption.",
            "https://www.state-machine.com/qpc/struct_q_time_evt.html#a4110381e712227678890d112edc28cf9"
        }
    },
    {
        "qf_time", 800,
        {
            "QTimeEvt noActive(...), input parameter failed sanity check.",
            "The tickRate param must be within the configured range.",
            "https://www.state-machine.com/qpc/struct_q_time_evt.html#a1c6b4144dd26a56d3c65a18bc3a9e640"
        }
    },
    //List terminating structure, keep last.
    {
        NULL, -1, {NULL, NULL, NULL}
    }
};