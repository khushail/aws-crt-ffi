/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#include "aws/cal/hash.h"
#include "crt.h"

aws_crt_hash *aws_crt_sha1_new(void) {
    struct aws_allocator *allocator = aws_crt_default_allocator();
    return aws_sha1_new(allocator);
}

aws_crt_hash *aws_crt_sha256_new(void) {
    struct aws_allocator *allocator = aws_crt_default_allocator();
    return aws_sha256_new(allocator);
}

aws_crt_hash *aws_crt_md5_new(void) {
    struct aws_allocator *allocator = aws_crt_default_allocator();
    return aws_md5_new(allocator);
}

int aws_crt_hash_update(aws_crt_hash *hash, uint8_t *buffer, uint32_t buffer_size) {
    struct aws_byte_cursor buffer_cursor;
    AWS_ZERO_STRUCT(buffer_cursor);
    buffer_cursor.ptr = buffer;
    buffer_cursor.len = buffer_size;
    return aws_hash_update(hash, &buffer_cursor);
}

void aws_crt_hash_digest(aws_crt_hash *hash, size_t truncate_to, uint8_t *buffer) {

    struct aws_byte_buf digest_buf = aws_byte_buf_from_array(buffer, hash->digest_size);
    digest_buf.len = 0;
    aws_hash_finalize(hash, &digest_buf, truncate_to);
}

void aws_crt_hash_destroy(aws_crt_hash *hash) {
    aws_hash_destroy(hash);
}
