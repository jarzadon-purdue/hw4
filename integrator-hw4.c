// ***
// *** You MUST modify this file
// ***
#include <stdio.h>
#include <stdbool.h>
#include "hw4.h"

// must enclose the function by #ifdef TEST_INTEGRATE and #endif
#ifdef TEST_INTEGRATE
void integrate(Integration * intrg)
{
  double interval_size;
  int step;
  double sum = 0.0;
  double height1;
  double height2;
  
  interval_size = ((*intrg).upperlimit - (*intrg).lowerlimit) / (*intrg).intervals;

  for (step = 0; step < (*intrg).intervals; step++) {
    height1 = (*intrg).func((*intrg).lowerlimit + (step * interval_size));
    height2 = (*intrg).func((*intrg).lowerlimit + ((step + 1) * interval_size));
    sum += interval_size * ((height1 + height2) / 2.0);
  }

  (*intrg).answer = sum;

  // integrate the function stored in intrg's func
  // store the result in intrg's answer
  
}
#endif // TEST_INTEGRATE

// must enclose the function by #ifdef RUN_INTEGRATE and #endif
#ifdef RUN_INTEGRATE
bool  runIntegrate(char * infilename, char * outfilename)
// return true if it can successfully open and read the input 
// and open and write the output
// return false when encountering any problem
{
  // open the input file name for reading
  FILE *fptr_in;
  FILE *fptr_out;
  Integration intrg;

  fptr_in = fopen(infilename, "r");

  // if fopen fails, return false

  if (fptr_in == NULL) {
    return false;
  }

  // read one double from the input file and store it in 
  // intrg's lowerlimit
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false

  if (fscanf(fptr_in, "%lf", &intrg.lowerlimit) != 1) {
    fclose(fptr_in);
    return false;
  }

  // read one double from the input file and store it in 
  // intrg's upperlimit
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false

  if (fscanf(fptr_in, "%lf", &intrg.upperlimit) != 1) {
    fclose(fptr_in);
    return false;
  }

  // read one int from the input file and store it in 
  // intrg's intervals
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false

  if (fscanf(fptr_in, "%d", &intrg.intervals) != 1) {
    fclose(fptr_in);
    return false;
  }

  // close the input file
  
  fclose(fptr_in);

  // open the output file for writing
  // if fopen fails, return false

  fptr_out = fopen(outfilename, "w");
  if (fptr_out == NULL) {
    return false;
  }

  // create an array of funcptr called funcs with five elements:
  // func1, func2, ..., func5

  funcptr funcs[5] = {func1, func2, func3, func4, func5};


  // go through the elements in funcs 
  // for each element, call integrate for that function
  // write the result (stored in intrg's answer to 
  // the output file. each answer occupies one line (add "\n")
  // use fprintf

  for (int i = 0; i < 5; i++) {
    intrg.func = funcs[i];   // Assign the current function to the struct
    integrate(&intrg);       // Calculate the integral

    // check the return value of fprintf. 
    // If it is less one one, close the output
    // file and return false
    if (fprintf(fptr_out, "%lf\n", intrg.answer) < 1) {
      fclose(fptr_out);
      return false;
    }
  }

  // after going through all functions in funcs
  // close the output file

  fclose(fptr_out);

  // if the function reaches here, return true

  return true;
}
#endif // RUN_INTEGRATE
