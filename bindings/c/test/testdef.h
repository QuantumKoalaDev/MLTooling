//
// Created by andi on 20.12.25.
//

#ifndef MLTOOLING_TESTDEF_H
#define MLTOOLING_TESTDEF_H

#include <Container/Mat.h>
#include <math.h>
#include <stdio.h>

#define ASSERT_STATUS_OK(testName, status, msg) \
do { if (assert_status_ok(testName, status, msg)) goto cleanup; } while(0)

#define ASSERT_EQ_INT(testName, actual, expected, msg) \
do { if(assert_eq_int(testName, actual, expected, msg)) goto cleanup; } while(0)

#define ASSERT_EQ_FLOAT(testName, actual, expected, msg) \
do { if(assert_eq_float(testName, actual, expected, msg)) goto cleanup; } while(0)

static inline int assert_status_ok(const char* testName, const mlt_status status, const char* msg) {
  if (status != MLT_OK) {
    fprintf(stderr, "%s: Assertion failed: %s (status=%d)\n", testName, msg, status);
    return 1;
  }

  return 0;
}

static inline int assert_eq_int(const char* testName, const int actual, const int expected, const char* msg) {
  const float epsilon = 0.00001f;
  if ( fabs(expected - actual) > epsilon) {
    fprintf(stderr, "%s: Assertion failed: %s (expected %d, got %d)\n",
            testName, msg, expected, actual);
    return 1;
  }
  return 0;
}

static inline int assert_eq_float(const char* testName, const float actual, const float expected, const char* msg) {
  if (actual != expected) {
    fprintf(stderr, "%s: Assertion failed: %s (expected %f, got %f)\n",
      testName, msg, expected, actual );
    return 1;
  }
  return 0;
}


#endif // MLTOOLING_TESTDEF_H
