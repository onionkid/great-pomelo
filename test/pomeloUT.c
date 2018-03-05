
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#include "Automated.h"
#include "pomeloUT.h"
#include "foo.h"

/* Suite initialization/cleanup functions */
static int suite_success_init(void) { return 0; }
static int suite_success_clean(void) { return 0; }

/*static int suite_failure_init(void) { return 1;}
static int suite_failure_clean(void) { return 1; }

static void testSuccess1(void) { CU_ASSERT(1); }
static void testSuccess2(void) { CU_ASSERT(2); }
static void testSuccess3(void) { CU_ASSERT(3); }

static void testSuiteFailure1(void) { CU_ASSERT(0); }
static void testSuiteFailure2(void) { CU_ASSERT(2); }

static void testFailure1(void) { CU_ASSERT(0); }
static void testFailure2(void) { CU_ASSERT(0); }
static void testFailure3(void) { CU_ASSERT(0); }
*/

/** TEST FOO**/
static void testFoo(void)
{
	CU_ASSERT_EQUAL(0,dosomethingfoo(0));
	CU_ASSERT_EQUAL(1,dosomethingfoo(1));
	CU_ASSERT_EQUAL(1,dosomethingfoo(2));
	CU_ASSERT_EQUAL(1,dosomethingfoo(3));

	CU_ASSERT_NOT_EQUAL(1,dosomethingfoo(0));

}

static void testFoo2(void)
{
	CU_ASSERT_NOT_EQUAL(1,dosomethingfoo(0));
	CU_ASSERT_NOT_EQUAL(0,dosomethingfoo(1));
	CU_ASSERT_NOT_EQUAL(0,dosomethingfoo(2));
	CU_ASSERT_NOT_EQUAL(0,dosomethingfoo(3));

	CU_ASSERT_NOT_EQUAL(0,dosomethingfoo(0));

}

////test foo
static CU_TestInfo tests_foo[] ={
		{"testFoo",testFoo},
		{"testFoo2",testFoo2},
		CU_TEST_INFO_NULL,
};


static CU_SuiteInfo suites[] = {
  { "suite_test_foo",  suite_success_init, suite_success_clean, NULL, NULL, tests_foo},
	CU_SUITE_INFO_NULL,
};

void AddTests(void)
{
  assert(NULL != CU_get_registry());
  assert(!CU_is_test_running());

	/* Register suites. */
	if (CU_register_suites(suites) != CUE_SUCCESS) {
		fprintf(stderr, "suite registration failed - %s\n",
			CU_get_error_msg());
		exit(EXIT_FAILURE);
	}
}

void print_example_results(void)
{
  fprintf(stdout, "\n\nExpected Test Results:"
                  "\n\n  Error Handling  Type      # Run   # Pass   # Fail"
                  "\n\n  ignore errors   suites%9u%9u%9u"
                    "\n                  tests %9u%9u%9u"
                    "\n                  asserts%8u%9u%9u"
                  "\n\n  stop on error   suites%9u%9u%9u"
                    "\n                  tests %9u%9u%9u"
                    "\n                  asserts%8u%9u%9u\n\n",
                  14, 14, 3,
                  31, 10, 21,
                  89, 47, 42,
                  4, 4, 1,
                  12, 9, 3,
                  12, 9, 3);
}
