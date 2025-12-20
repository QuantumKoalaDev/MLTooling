#include <MLToolingCapi.h>

#include <stdio.h>
#include <assert.h>

#define ASSERT_STATUS_OK(testName, status, msg) \
	do { if (assert_status_ok(testName, status, msg)) goto cleanup; } while(0)

#define ASSERT_EQ_INT(testName, actual, expected, msg) \
	do { if(assert_eq_int(testName, actual, expected, msg)) goto cleanup; } while(0)

int assert_status_ok(const char* testName, mlt_status status, const char* msg) {
	if (status != MLT_OK) {
		fprintf(stderr, "%s: Assertion failed: %s (status=%d)\n", testName, msg, status);
		return 1;
	}

	return 0;
}

int assert_eq_int(const char* testName, int actual, int expected, const char* msg) {
	if (actual != expected) {
		fprintf(stderr, "%s: Assertion failed: %s (expected %d, got %d)\n",
			testName, msg, expected, actual);
		return 1;
	}
	return 0;
}

void test_creation_and_shape() {
	const char* testName = "test_creation_and_shape";

	Mat* mat = NULL;

	mlt_status creationStatus = mlt_ct_mat_create_with_val(2, 2, 0.f, &mat);
	ASSERT_STATUS_OK(testName, creationStatus, "Matrix creation failed");

	unsigned long matRows;
	mlt_status shapeRowStatus = mlt_ct_mat_get_shape_rows(mat, &matRows);
	ASSERT_STATUS_OK(testName, creationStatus, "Getting matrix row count failed");
	ASSERT_EQ_INT(testName, matRows, 2, "Wrong row count");

cleanup:
	if (mat)
		mlt_ct_mat_destroy(mat);
}

//void test_creation_and_shape()
//{
//	Mat* mat = NULL;
//
//	mlt_status creationStatus = mlt_ct_mat_create_with_val(2, 2, 0.f, &mat);
//	assert(creationStatus == MLT_OK);
//	assert(mat != NULL);
//
//	unsigned long matRows;
//	unsigned long matCols;
//	mlt_status shapeRowStatus = mlt_mat_get_shape_rows(mat, &matRows);
//	mlt_status shapeColStatus = mlt_mat_get_shape_cols(mat, &matCols);
//	assert(shapeRowStatus == MLT_OK && shapeColStatus == MLT_OK);
//	assert(matRows == 2 && matCols == 2);
//
//	mlt_ct_mat_destroy(mat);
//
//	printf("test_creation_and_shape passed!\n");
//}



int main(void) {
	test_creation_and_shape();
	//trainModel();
	return 0;
}