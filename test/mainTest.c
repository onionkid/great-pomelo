#include "foo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Automated.h"
#include "pomeloUT.h"

int main(int argc, char* argv[])
{
  CU_BOOL Run = CU_FALSE ;

  setvbuf(stdout, NULL, _IONBF, 0);

  if (argc > 1) {
    if (!strcmp("-i", argv[1])) {
      Run = CU_TRUE ;
      CU_set_error_action(CUEA_IGNORE);
    }
    else if (!strcmp("-f", argv[1])) {
      Run = CU_TRUE ;
      CU_set_error_action(CUEA_FAIL);
    }
    else if (!strcmp("-A", argv[1])) {
      Run = CU_TRUE ;
      CU_set_error_action(CUEA_ABORT);
    }
    else if (!strcmp("-e", argv[1])) {
      print_example_results();
    }
    else {
      printf("\nUsage:  AutomatedTest [option]\n\n"
               "        Options: -i  Run, ignoring framework errors [default].\n"
               "                 -f  Run, failing on framework error.\n"
               "                 -A  Run, aborting on framework error.\n"
               "                 -e  Print expected test results and exit.\n"
               "                 -h  Print this message.\n\n");
    }
  }
  else {
    Run = CU_TRUE;
    CU_set_error_action(CUEA_IGNORE);
  }

  if (CU_TRUE == Run) {
    if (CU_initialize_registry()) {
      printf("\nInitialization of Test Registry failed.");
    }
    else {
      AddTests();
      CU_set_output_filename("GreatPomeloUT");
      CU_list_tests_to_file();
      CU_automated_run_tests();
      CU_cleanup_registry();
    }
  }

  return 0;
}
