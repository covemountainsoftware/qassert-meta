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
