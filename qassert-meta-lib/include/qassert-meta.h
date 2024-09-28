#ifndef QASSERT_META_QASSERT_META_H
#define QASSERT_META_QASSERT_META_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const char * short_description;
    const char * tips;
    const char * url;
} QAssertMetaDescription;

/**
 * Initialize the QAssertMeta module.
 */
void QAssertMetaInit(void);

typedef bool (*UnknownQAssertCallback)(const char * module, int id, QAssertMetaDescription* output);
/**
 * Register a callback to be executed if a GetDescription if called
 * and the module/id pair is found to be unknown.
 * @param callback:  the callback the module will record
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
