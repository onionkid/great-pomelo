#include "foo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Automated.h"
#include "pomeloUT.h"

int main(int argc, char* argv[])
{

	if (CUE_SUCCESS != CU_initialize_registry())
	      return CU_get_error();


	AddTests();
	CU_set_output_filename("GreatPomeloUT");
	CU_list_tests_to_file();
	CU_automated_run_tests();
	CU_cleanup_registry();

  return 0;
}
