#include "XNet.h"
#include "Plugins/AllowingConnections.h"
#include "Plugins/Ordering.h"
#include "Plugins/Reliability.h"
#include "Plugins/Sequencing.h"
#include "Plugins/SimulateLag.h"
#include "Plugins/Splitting.h"
#include "System/SocketProvider.h"
#include "System/LocalOnly.h"

#include <iostream>
#include <stdlib.h>

#define ASSERT(cond, message) if (!(cond)) { std::cerr << "Test failed: " << message << "\n\t" << __PRETTY_FUNCTION__ << "\n\t" << __FILE__ << ": line " << __LINE__ << std::endl; exit(1); }
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
