#ifndef __TESTUTILS_H__
#define __TESTUTILS_H__

#define ASSERT_TO_STRING_EQ(obj, str) \
    do { \
        ostringstream ss;   \
        ss << obj; \\
        ASSERT_EQ(ss.str(), str); \\
    } while (0)\

#endif /* end of include guard: __TESTUTILS_H__ */
