//
// CSU33014 Annual Exam, May 2022
// Question 1
//

// Please examine version each of the following routines with names
// starting 'routine_'. Where the routine can be vectorized, please
// replace the corresponding 'vectorized' version using SSE vector
// intrinsics. Where it cannot be vectorized please explain why.

// To illustrate what you need to do, routine_0 contains a
// non-vectorized piece of code, and vectorized_0 shows a
// corresponding vectorized version of the same code.

// Note that to simplify testing, I have put a copy of the original
// non-vectorized code in the vectorized version of the code for
// routines 1 to 6. This allows you to easily see what the output of
// the program looks like when the original and vectorized version of
// the code produce equivalent output.

// Note the restrict qualifier in C indicates that "only the pointer
// itself or a value directly derived from it (such as pointer + 1)
// will be used to access the object to which it points".


#include <immintrin.h>
#include <stdio.h>

#include "csu33014-annual-q1-code.h"


/****************  routine 0 *******************/

// Here is an example routine that should be vectorized
void Q1_routine_0(float * restrict a, float * restrict b,
		    float * restrict c) {
  for (int i = 0; i < 1024; i++ ) {
    a[i] = b[i] * c[i];
  }
}

// here is a vectorized solution for the example above
void Q1_vectorized_0(float * restrict a, float * restrict b,
		    float * restrict c) {
  __m128 a4, b4, c4;
  
  for (int i = 0; i < 1024; i = i+4 ) {
    b4 = _mm_loadu_ps(&b[i]);
    c4 = _mm_loadu_ps(&c[i]);
    a4 = _mm_mul_ps(b4, c4);
    _mm_storeu_ps(&a[i], a4);
  }
}

/***************** routine 1 *********************/

// in the following, size can have any positive value
float Q1_routine_1(float * restrict a, float * restrict b, int size) {
  float product_a = 1.0;
  float product_b = 1.0;
  
  for ( int i = 0; i < size; i++ ) {
    // fprintf(stderr, "pa %f, ai %f, pb %f, bi %f\n", product_a, a[i], product_b, b[i]);
    product_a = product_a * a[i];
    product_b = product_b * b[i];
  }
  return product_a + product_b;
}

// in the following, size can have any positive value
float Q1_vectorized_1(float * restrict a, float * restrict b, int size) {
  float product_a = 1.0;
  float product_b = 1.0;
  
  for ( int i = 0; i < size; i++ ) {
    product_a = product_a * a[i];
    product_b = product_b * b[i];
  }
  return product_a + product_b;
}


/******************* routine 2 ***********************/

// in the following, size can have any positive value
void Q1_routine_2(float * restrict a, float * restrict b, int size) {
  for ( int i = 0; i < size; i++ ) {
    a[i] = (a[i] * 17.2) + (3.14159/b[i]);
  }
}

// in the following, size can have any positive value
void Q1_vectorized_2(float * restrict a, float * restrict b, int size) {
  for ( int i = 0; i < size; i++ ) {
    a[i] = (a[i] * 17.2) + (3.14159/b[i]);
  }
}



/******************** routine 3 ************************/

// in the following, size can have any positive value
void Q1_routine_3(float * restrict a, float * restrict b, int size) {
  for ( int i = 0; i < size; i++ ) {
    if ( a[i] > b[i] ) {
      a[i] = -a[i];
    }
  }
}

// in the following, size can have any positive value
void Q1_vectorized_3(float * restrict a, float * restrict b, int size) {
  for ( int i = 0; i < size; i++ ) {
    if ( a[i] > b[i] ) {
      a[i] = -a[i];
    }
  }
}


/********************* routine 4 ***********************/

void Q1_routine_4(float * restrict a, float * restrict b,
		       float * restrict c) {
  for ( int i = 0; i < 2048; i++  ) {
    if ( i == 0 ) {
       a[i] = b[i]*c[i];
    }
    else if ( i == 2047 ) {
       a[i] = b[i]*c[i];
    }
    else {
       a[i] = b[i-1]*c[i+1] + b[i]*c[i] + b[i+1]*c[i-1] ;
    }
  }
}

void Q1_vectorized_4(float * restrict a, float * restrict b,
		       float * restrict c) {
  for ( int i = 0; i < 2048; i++  ) {
    if ( i == 0 ) {
       a[i] = b[i]*c[i];
    }
    else if ( i == 2047 ) {
       a[i] = b[i]*c[i];
    }
    else {
       a[i] = b[i-1]*c[i+1] + b[i]*c[i] + b[i+1]*c[i-1] ;
    }
  }
}


/********************* routine 5 ***********************/

// in the following, size can have any positive value
void Q1_routine_5(float * restrict a, float * restrict b,
                  float * restrict c, int size) {
  for ( int i = 0; i < size; i++ ) {
    if ( a[i] > c[i] ) {
      float temp = a[i];
      a[i] = c[i];
      c[i] = temp;
    }
    if ( a[i] > b[i] ) {
      float temp = a[i];
      a[i] = b[i];
      b[i] = temp; 
    }
    if ( b[i] > c[i] ) {
      float temp = b[i];
      b[i] = c[i];
      c[i] = temp;
    }
  }
}

// in the following, size can have any positive value
void Q1_vectorized_5(float * restrict a, float * restrict b,
                     float * restrict c, int size) {
  for ( int i = 0; i < size; i++ ) {
    if ( a[i] > c[i] ) {
      float temp = a[i];
      a[i] = c[i];
      c[i] = temp;
    }
    if ( a[i] > b[i] ) {
      float temp = a[i];
      a[i] = b[i];
      b[i] = temp; 
    }
    if ( b[i] > c[i] ) {
      float temp = b[i];
      b[i] = c[i];
      c[i] = temp;
    }
  }
}
  

/********************* routine 6 ***********************/

// in the following size is a positive value that is a multiple of 3
float Q1_routine_6(float * restrict a, int size) {
  float x = 0.0;
  float y = 0.0;
  float z = 0.0;
  for ( int i = 0; i < size; i = i + 3 ) {
    x = x + a[i];
    y = y + a[i+1];
    z = z + a[i+2];
  }
  return x * y * z;
}

// in the following size is a positive value that is a multiple of 3
float Q1_vectorized_6(float * restrict a, int size) {
  float x = 0.0;
  float y = 0.0;
  float z = 0.0;
  for ( int i = 0; i < size; i = i + 3 ) {
    x = x + a[i];
    y = y + a[i+1];
    z = z + a[i+2];
  }
  return x * y * z;
}
