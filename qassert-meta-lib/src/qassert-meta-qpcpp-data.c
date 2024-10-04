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
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_hsm.html#a99dac28e8f65cab700d04a222f1b8283"
        }
    },
    {
        "qep_hsm", 210,
        {
            "QHsm init failure in the initial transition.",
            "The custom initial transition failed to transition to a state,\n."
            "i.e. use Q_TRAN(...) in the HSM's initial state.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_hsm.html#a99dac28e8f65cab700d04a222f1b8283"
        }
    },
    {
        "qep_hsm", 220,
        {
            "QHsm init failure in the initial transition, could not reach initial destination state.",
            "The HSM state nesting may be too deep or is malformed in some manner.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_hsm.html#a99dac28e8f65cab700d04a222f1b8283"
        }
    },
    {
        "qep_hsm", 290,
        {
            "QHsm init failure in the initial transition, could not reach initial destination state.",
            "The HSM state nesting may be too deep or is malformed in some manner.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_hsm.html#a99dac28e8f65cab700d04a222f1b8283"
        }
    },
    {
        "qf_defer", 210,
        {
            "The recalled deferred event must meet reference counter expectations.",
            "Stomping on memory?",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_active.html#aaf2f07ad05792379e23c7329dec942ce"
        }
    },
    {
        "qf_dyn", 200,
        {
            "Call to poolInit(...) exceeds the configured maximum.",
            "See QF_MAX_EPOOL. But do you really need more pools?",
            "https://www.state-machine.com/qpcpp/namespace_q_p_1_1_q_f.html#aad40f4b1c3935ccc0cd4e5b2c29fb03a"
        }
    },
    {
        "qf_dyn", 201,
        {
            "Each pool initialized by poolInit(...) must be initialized in increasing event size.",
            "Check the size of parameters used to initialize the pools and ensure they are\n"
            "sized as expected and in increasing size.",
            "https://www.state-machine.com/qpcpp/namespace_q_p_1_1_q_f.html#aad40f4b1c3935ccc0cd4e5b2c29fb03a"
        }
    },
    {
        "qf_dyn", 400,
        {
            "Call to getPoolMin(...) with invalid pool number.",
            "Typo? Bad code? Forgot to initialize the pool?",
            "https://www.state-machine.com/qpcpp/namespace_q_p_1_1_q_f.html#a473757a0a71f054aa9099b44504854f9"
        }
    },
    {
        "qf_dyn", 300,
        {
            "Attempting to allocate an event that is larger than any available pool.",
            "Probably need to increase the event size of the largest event pool.",
            "https://www.state-machine.com/qpcpp/namespace_q_p_1_1_q_f.html#ad9814e971340598df159c6b96d66abd9"
        }
    },
    {
        "qf_dyn", 320,
        {
            "Event allocation failed with QF_NO_MARGIN.",
            "There is likely an event leak or excessive deferral of events.",
            "https://www.state-machine.com/qpcpp/namespace_q_p_1_1_q_f.html#ad9814e971340598df159c6b96d66abd9"
        }
    },
    {
        "qf_dyn", 402,
        {
            "Event verification within garbage collection failed.",
            "Check for memory corruption or stale event pointer being reused incorrectly.",
            "https://www.state-machine.com/qpcpp/namespace_q_p_1_1_q_f.html#a2164a5f2abdeab74383e7997efb664eb"
        }
    },
    {
        "qf_dyn", 410,
        {
            "Within event garbage collection, an event's pool number was invalid.",
            "Check for memory corruption of event related data.",
            "https://www.state-machine.com/qpcpp/namespace_q_p_1_1_q_f.html#a2164a5f2abdeab74383e7997efb664eb"
        }
    },
    {
        "qf_dyn", 502,
        {
            "While creating a new reference, an event failed verification.",
            "Check for memory corruption or stale event pointer being reused incorrectly.",
            "https://www.state-machine.com/qpcpp/namespace_q_p_1_1_q_f.html#a134309505e31a0385cee389c257ca14b"
        }
    },
    {
        "qf_dyn", 500,
        {
            "While creating a new reference, an event failed pool verification.",
            "Check for memory corruption or stale event pointer being reused incorrectly.",
            "https://www.state-machine.com/qpcpp/namespace_q_p_1_1_q_f.html#a134309505e31a0385cee389c257ca14b"
        }
    },
    {
        "qf_dyn", 602,
        {
            "While deleting an event reference, an event failed verification.",
            "Check for memory corruption or stale event pointer being reused incorrectly.",
            "https://www.state-machine.com/qpcpp/namespace_q_p_1_1_q_f.html#a0a9e31bee94666ea1afd7de011635581"
        }
    },
    {
        "qf_mem", 100,
        {
            "QMPool init(...) parameters failed validation.",
            "Check the pool size and ensure that at least one free block will fit,\n"
            "otherwise, see the documentation at the URL.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_m_pool.html#a3855d7fe97b37dcc6c5349f74d439510"
        }
    },
    {
        "qf_mem", 110,
        {
            "QMPool init(...) parameters failed validation.",
            "The desired pool size must allow for at least one rounded up block.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_m_pool.html#a3855d7fe97b37dcc6c5349f74d439510"
        }
    },
    {
        "qf_mem", 300,
        {
            "QMPool get(...) internal integrity check failure.",
            "Check for memory corruption related to objects allocated from or near this pool.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_m_pool.html#a02568db54760dcbe5f5a1f776e2fd84e"
        }
    },
    {
        "qf_mem", 302,
        {
            "QMPool get(...) internal integrity check failure.",
            "Check for memory corruption related to objects allocated from or near this pool.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_m_pool.html#a02568db54760dcbe5f5a1f776e2fd84e"
        }
    },
    {
        "qf_mem", 320,
        {
            "QMPool get(...) internal integrity check failure upon becoming empty.",
            "Check for memory corruption related to objects allocated from or near this pool.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_m_pool.html#a02568db54760dcbe5f5a1f776e2fd84e"
        }
    },
    {
        "qf_mem", 330,
        {
            "QMPool get(...) internal integrity check failure when not empty.",
            "Check for memory corruption related to objects allocated from or near this pool.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_m_pool.html#a02568db54760dcbe5f5a1f776e2fd84e"
        }
    },
    {
        "qf_mem", 200,
        {
            "QMPool put(...) failed internal integrity check.",
            "Check for memory corruption related to objects allocated from or near this pool.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_m_pool.html#a9079ba142857550fc09162fe06ae2f7e"
        }
    },
    {
        "qf_ps", 200,
        {
            "Attempt to publish an event with a signal outside the configured pub/sub signal range.",
            "Is this an event that would normally be posted directly or needs to be added to the\n"
            "master publish/subscribe signal enum?",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_active.html#a55fef775cd0233ebd8ff5abb0f99fa01"
        }
    },
    {
        "qf_ps", 202,
        {
            "publish(...) failed an internal integrity check.",
            "Likely memory corruption.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_active.html#a55fef775cd0233ebd8ff5abb0f99fa01"
        }
    },
    {
        "qf_ps", 210,
        {
            "publish(...) failed an internal integrity check, where the AO\n"
            "found was (somehow) not registered with the framework.",
            "Likely memory corruption.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_active.html#a55fef775cd0233ebd8ff5abb0f99fa01"
        }
    },
    {
        "qf_ps", 220,
        {
            "publish(...) failed an internal integrity check, where a subsequent AO\n"
            "found was (somehow) not registered with the framework.",
            "Likely memory corruption.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_active.html#a55fef775cd0233ebd8ff5abb0f99fa01"
        }
    },
    {
        "qf_ps", 290,
        {
            "publish(...) failed an internal integrity check.",
            "Likely memory corruption.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_active.html#a55fef775cd0233ebd8ff5abb0f99fa01"
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
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_active.html#a1201ddb18d9abe54e9022f2a4d42bc4e"
        }
    },
    {
        "qf_ps", 302,
        {
            "subscribe(...) failed an internal integrity check.",
            "Likely memory corruption.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_active.html#a1201ddb18d9abe54e9022f2a4d42bc4e"
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
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_active.html#a4f4a0f57a0cae664e2ecfbe90b0a9025"
        }
    },
    {
        "qf_ps", 402,
        {
            "unsubscribe(...) failed an internal integrity check.",
            "Likely memory corruption.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_active.html#a4f4a0f57a0cae664e2ecfbe90b0a9025"
        }
    },
    {
        "qf_ps", 500,
        {
            "unsubscribeAll(...) failed one or more of multiple input and state checks.",
            "Specifically:\n"
            "  - The AO priority must be within the configured range.\n"
            "  - The AO must be registered with the framework.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_active.html#aeb6fd6d13c372928ad322c8225bd1a3d"
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
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_active.html#a3bf368efba3bebb423783df51b1028fc"
        }
    },
    {
        "qf_qact", 190,
        {
            "QActive register(...) failed one or more post-condition checks.",
            "Specifically:\n"
            "  - The preceding preemption threshold must not exceed this AO's preemption threshold.\n"
            "  - The preemption threshold must not exceed the next preemption threshold.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_active.html#a3bf368efba3bebb423783df51b1028fc"
        }
    },
    {
        "qf_qact", 200,
        {
            "QActive unregister(...) failed one or more input argument checks.",
            "Specifically:\n"
            "  - The AO priority must be within the configured range.\n"
            "  - The priority must have been already registered.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_active.html#a0a79b34cf47b63c0fea891a44381525b"
        }
    },
    {
        "qf_qeq", 200,
        {
            "QEQueue post(...), the provided event pointer is null.",
            "Thou shalt not follow the null pointer!",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_e_queue.html#ab5593a2e0442ecd25d66604a61a9321d"
        }
    },
    {
        "qf_qeq", 210,
        {
            "QEQueue post(...), the queue is full and margin is QF_NO_MARGIN.",
            "Double check priorities and thread behavior. A thread is generating too many events or\n"
            "the thread servicing this queue is too slow, is being starved by a higher priority thread\n"
            "or needs a deeper queue.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_e_queue.html#ab5593a2e0442ecd25d66604a61a9321d"
        }
    },
    {
        "qf_qeq", 300,
        {
            "QEQueue postLIFO(...), the target queue is full.",
            "Double check priorities and thread behavior. A thread is generating too many events or\n"
            "the thread servicing this queue is too slow, is being starved by a higher priority thread\n"
            "or needs a deeper queue.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_e_queue.html#af4ed5c7df0c0d4c1c407330b3c76c184"
        }
    },
    {
        "qf_qeq", 410,
        {
            "QEQueue get(...), an internal integrity check failed.",
            "Possible memory corruption?",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_e_queue.html#a6bf4f3735c83a43f383073342373893c"
        }
    },
    {
        "qf_time", 300,
        {
            "QTimeEvt ctor(...), invalid input parameter.",
            "'sig' must not be zero and 'tickRate' must be within the configured range.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_time_evt.html#a57d07b6ec85c3cd7db506f38a83717bb"
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
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_time_evt.html#a2256c1d035a2d2afa024ed9fd1bb1598"
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
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_time_evt.html#a665683d9bcf94a1de9250dd052bc4ed8"
        }
    },
    {
        "qf_time", 100,
        {
            "QTimeEvt tick(...), internal integrity failure.",
            "Invalid 'tickRate' parameter. The function calling tick(...) should be examined.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_time_evt.html#a0cd7ce23dfa22c2806ab397d9e963cdb"
        }
    },
    {
        "qf_time", 110,
        {
            "QTimeEvt tick(...), internal integrity failure.",
            "An internal variable was unexpectedly null. Memory corruption?",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_time_evt.html#a0cd7ce23dfa22c2806ab397d9e963cdb"
        }
    },
    {
        "qf_time", 112,
        {
            "QTimeEvt tick(...), internal integrity failure.",
            "A timer is firing, but the event to be posted is invalid.\n"
            "Confirm that the event provided to the timer is valid, otherwise seek\n"
            "out sources of memory corruption.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_time_evt.html#a0cd7ce23dfa22c2806ab397d9e963cdb"
        }
    },
    {
        "qf_time", 190,
        {
            "QTimeEvt tick(...), internal timer loop limit hit.",
            "There might be too many timers active in the system. Otherwise, seek\n"
            "out sources of memory corruption.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_time_evt.html#a0cd7ce23dfa22c2806ab397d9e963cdb"
        }
    },
    {
        "qf_time", 800,
        {
            "QTimeEvt noActive(...), input parameter failed sanity check.",
            "The tickRate param must be within the configured range.",
            "https://www.state-machine.com/qpcpp/class_q_p_1_1_q_time_evt.html#a8e554bafd8078c56be8a6a5c40ad86f5"
        }
    },
    //List terminating structure, keep last.
    {
        NULL, -1, {NULL, NULL, NULL}
    }
};