#ifndef FLAG_ACTIVATED
#define FLAG_ACTIVATED 1
#endif

#ifndef FLAG_DEACTIVATED
#define FLAG_DEACTIVATED 0
#endif

#ifndef RUN_UNIT_TESTS
#define RUN_UNIT_TESTS FLAG_DEACTIVATED /* Change it to control unit testing */
#endif /* RUN_UNIT_TESTS */

#ifdef RUN_UNIT_TESTS
#if RUN_UNIT_TESTS == FLAG_ACTIVATED
    #include "DataContainerTest.h"
    #define UNIT_TESTING() {\
        runDataContainerTests();\
    }
#else
    #define UNIT_TESTING() {}
#endif
#endif