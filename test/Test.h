#include "XNet.h"
#include "Plugins/AllowingConnections.h"
#include "Plugins/Ordering.h"
#include "Plugins/Reliability.h"
#include "Plugins/Sequencing.h"
#include "Plugins/SimulateLag.h"
#include "Plugins/Splitting.h"

#include <stdio.h>
#include <stdlib.h>

#define ASSERT(cond, message) if (!(cond)) { fprintf(stdout, "Test failed: %s\n\t%s\n\t%s: line %d\n", (message), __PRETTY_FUNCTION__, __FILE__, __LINE__); abort(); }
#define ASSERT_TRUE(cond, message) ASSERT((cond), (message))
#define ASSERT_FALSE(cond, message) ASSERT(!(cond), message)
#define ASSERT_EQUAL(a, b, message) ASSERT((a) == (b), message)
#define ASSERT_NOT_EQUAL(a, b, message) ASSERT((a) != (b), message)
#define ASSERT_GREATER(a, b, message) ASSERT((a) > (b), message)
#define ASSERT_LESS(a, b, message) ASSERT((a) < (b), message)
#define ASSERT_GREATER_EQUAL(a, b, message) ASSERT((a) >= (b), message)
#define ASSERT_LESS_EQUAL(a, b, message) ASSERT((a) <= (b), message)
#define ASSERT_NULL(a, message) ASSERT((a) == NULL, message)
#define ASSERT_NOT_NULL(a, message) ASSERT((a) != NULL, message)
#define ASSERT_UNREACHABLE(message) ASSERT(0, message)
