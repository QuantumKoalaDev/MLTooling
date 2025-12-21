#include "testdef.h"
#include <MLToolingCapi.h>
#include <stdio.h>

void test_create_with_val_and_shape(void) {
    const char* testName = "test_create_with_val_and_shape";

    Mat* mat = NULL;

    mlt_status status = mlt_ct_mat_create_with_val(2, 3, 1.5f, &mat);
    ASSERT_STATUS_OK(testName, status, "Matrix creation with initial value failed");

    unsigned long rows = 0;
    unsigned long cols = 0;

    status = mlt_ct_mat_get_shape_rows(mat, &rows);
    ASSERT_STATUS_OK(testName, status, "Failed to get row count");
    ASSERT_EQ_INT(testName, rows, 2, "Row count mismatch");

    status = mlt_ct_mat_get_shape_cols(mat, &cols);
    ASSERT_STATUS_OK(testName, status, "Failed to get column count");
    ASSERT_EQ_INT(testName, cols, 3, "Column count mismatch");

    float value = 0.0f;
    status = mlt_ct_mat_get_item(1, 2, mat, &value);
    ASSERT_STATUS_OK(testName, status, "Failed to read matrix item");
    ASSERT_EQ_FLOAT(testName, value, 1.5f, "Initial value not applied correctly");

cleanup:
    if (mat)
        mlt_ct_mat_destroy(mat);
}

void test_create_from_flat_array(void) {
    const char* testName = "test_create_from_flat_array";

    const float data[] = { 1.f, 2.f, 3.f, 4.f };
    Mat* mat = NULL;

    mlt_status status = mlt_ct_mat_create_from_flat_array(2, 2, data, &mat);
    ASSERT_STATUS_OK(testName, status, "Matrix creation from flat array failed");

    float value = 0.0f;

    status = mlt_ct_mat_get_item(0, 0, mat, &value);
    ASSERT_STATUS_OK(testName, status, "Failed to read matrix item");
    ASSERT_EQ_FLOAT(testName, value, 1.f, "Flat array mapping incorrect");

    status = mlt_ct_mat_get_item(1, 1, mat, &value);
    ASSERT_STATUS_OK(testName, status, "Failed to read matrix item");
    ASSERT_EQ_FLOAT(testName, value, 4.f, "Flat array mapping incorrect");

cleanup:
    if (mat)
        mlt_ct_mat_destroy(mat);
}

void test_get_set_item(void) {
    const char* testName = "test_get_set_item";

    Mat* mat = NULL;

    mlt_status status = mlt_ct_mat_create_with_val(2, 2, 0.f, &mat);
    ASSERT_STATUS_OK(testName, status, "Matrix creation failed");

    float value = 0.0f;

    status = mlt_ct_mat_set_item(0, 1, 5.5f, mat);
    ASSERT_STATUS_OK(testName, status, "Failed to set matrix item");

    status = mlt_ct_mat_get_item(0, 1, mat, &value);
    ASSERT_STATUS_OK(testName, status, "Failed to get matrix item");
    ASSERT_EQ_FLOAT(testName, value, 5.5f, "Set value not stored correctly");

cleanup:
    if (mat)
        mlt_ct_mat_destroy(mat);
}

void test_copy_and_append_row(void) {
    const char* testName = "test_copy_and_append_row";

    const float data[] = { 1.f, 2.f, 3.f, 4.f };
    Mat* mat = NULL;

    mlt_status status = mlt_ct_mat_create_from_flat_array(2, 2, data, &mat);
    ASSERT_STATUS_OK(testName, status, "Matrix creation failed");

    float row[2] = { 0.f, 0.f };
    status = mlt_ct_mat_copy_row(1, mat, row);
    ASSERT_STATUS_OK(testName, status, "Failed to copy row");

    ASSERT_EQ_FLOAT(testName, row[0], 3.f, "Copied row content incorrect");
    ASSERT_EQ_FLOAT(testName, row[1], 4.f, "Copied row content incorrect");

    status = mlt_ct_mat_append_row(2, row, mat);
    ASSERT_STATUS_OK(testName, status, "Failed to append row");

    unsigned long rows = 0;
    status = mlt_ct_mat_get_shape_rows(mat, &rows);
    ASSERT_STATUS_OK(testName, status, "Failed to get row count after append");
    ASSERT_EQ_INT(testName, rows, 3, "Row count after append incorrect");

cleanup:
    if (mat)
        mlt_ct_mat_destroy(mat);
}

void test_add_matrix(void) {
    const char* testName = "test_add_matrix";

    const float aData[] = { 1.f, 2.f, 3.f, 4.f };
    const float bData[] = { 5.f, 6.f, 7.f, 8.f };

    Mat* a = NULL;
    Mat* b = NULL;
    Mat* result = NULL;

    mlt_status status = mlt_ct_mat_create_from_flat_array(2, 2, aData, &a);
    ASSERT_STATUS_OK(testName, status, "Matrix A creation failed");

    status = mlt_ct_mat_create_from_flat_array(2, 2, bData, &b);
    ASSERT_STATUS_OK(testName, status, "Matrix B creation failed");

    status = mlt_ct_mat_add(a, b, &result);
    ASSERT_STATUS_OK(testName, status, "Matrix addition failed");

    float value = 0.f;
    status = mlt_ct_mat_get_item(1, 1, result, &value);
    ASSERT_STATUS_OK(testName, status, "Failed to read result matrix");
    ASSERT_EQ_FLOAT(testName, value, 12.f, "Matrix addition result incorrect");

cleanup:
    if (a) mlt_ct_mat_destroy(a);
    if (b) mlt_ct_mat_destroy(b);
    if (result) mlt_ct_mat_destroy(result);
}

void test_add_matrix_in_place(void) {
    const char* testName = "test_add_matrix_in_place";

    const float aData[] = { 1.f, 1.f, 1.f, 1.f };
    const float bData[] = { 2.f, 2.f, 2.f, 2.f };

    Mat* a = NULL;
    Mat* b = NULL;

    mlt_status status = mlt_ct_mat_create_from_flat_array(2, 2, aData, &a);
    ASSERT_STATUS_OK(testName, status, "Matrix A creation failed");

    status = mlt_ct_mat_create_from_flat_array(2, 2, bData, &b);
    ASSERT_STATUS_OK(testName, status, "Matrix B creation failed");

    status = mlt_ct_mat_add_in_place(a, b);
    ASSERT_STATUS_OK(testName, status, "In-place matrix addition failed");

    float value = 0.f;
    status = mlt_ct_mat_get_item(0, 0, a, &value);
    ASSERT_STATUS_OK(testName, status, "Failed to read modified matrix");
    ASSERT_EQ_FLOAT(testName, value, 3.f, "In-place addition result incorrect");

cleanup:
    if (a) mlt_ct_mat_destroy(a);
    if (b) mlt_ct_mat_destroy(b);
}

void test_matrix_multiplication(void) {
    const char* testName = "test_matrix_multiplication";

    const float aData[] = { 1.f, 2.f, 3.f, 4.f };
    const float bData[] = { 5.f, 6.f, 7.f, 8.f };

    Mat* a = NULL;
    Mat* b = NULL;
    Mat* result = NULL;

    mlt_status status = mlt_ct_mat_create_from_flat_array(2, 2, aData, &a);
    ASSERT_STATUS_OK(testName, status, "Matrix A creation failed");

    status = mlt_ct_mat_create_from_flat_array(2, 2, bData, &b);
    ASSERT_STATUS_OK(testName, status, "Matrix B creation failed");

    status = mlt_ct_mat_mul(a, b, &result);
    ASSERT_STATUS_OK(testName, status, "Matrix multiplication failed");

    float value = 0.f;
    status = mlt_ct_mat_get_item(0, 0, result, &value);
    ASSERT_STATUS_OK(testName, status, "Failed to read multiplication result");
    ASSERT_EQ_FLOAT(testName, value, 19.f, "Matrix multiplication result incorrect");

cleanup:
    if (a) mlt_ct_mat_destroy(a);
    if (b) mlt_ct_mat_destroy(b);
    if (result) mlt_ct_mat_destroy(result);
}

int main(void) {
    test_create_with_val_and_shape();
    test_create_from_flat_array();
    test_get_set_item();
    test_copy_and_append_row();
    test_add_matrix();
    test_add_matrix_in_place();
    test_matrix_multiplication();

    printf("All tests completed.\n");
    return 0;
}
