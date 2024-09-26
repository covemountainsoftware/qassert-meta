#ifndef QASSERT_META_QASSERT_META_H
#define QASSERT_META_QASSERT_META_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int id;
    const char * module;
    const char * description;
} QAssertMetaDescription;

/**
 * Get a basic description of a Q_ASSERT based on the module and id.
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
