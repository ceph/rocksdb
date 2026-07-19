//  Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.
#pragma once

#include <cstdint>
#include <memory>

#include "db/log_format.h"
#include "rocksdb/compression_type.h"
#include "rocksdb/env.h"
#include "rocksdb/io_status.h"
#include "rocksdb/slice.h"
#include "rocksdb/status.h"
#include "util/compression.h"

namespace ROCKSDB_NAMESPACE {

class WritableFileWriter;

namespace log {

/**
 * Writer is a general purpose log stream writer. It provides an append-only
 * abstraction for writing data. The details of the how the data is written is
 * handled by the WritableFile sub-class implementation.
 *
 * File format:
 *
 * File is broken down into variable sized records. The format of each record
 * is described below.
 *       +-----+-------------+--+----+----------+------+-- ... ----+
 * File  | r0  |        r1   |P | r2 |    r3    |  r4  |           |
 *       +-----+-------------+--+----+----------+------+-- ... ----+
 *       <--- kBlockSize ------>|<-- kBlockSize ------>|
 *  rn = variable size records
 *  P = Padding
 *
 * Data is written out in kBlockSize chunks. If next record does not fit
 * into the space left, the leftover space will be padded with \0.
 *
 * Legacy record format:
 *
 * +---------+-----------+-----------+--- ... ---+
 * |CRC (4B) | Size (2B) | Type (1B) | Payload   |
 * +---------+-----------+-----------+--- ... ---+
 *
 * CRC = 32bit hash computed over the record type and payload using CRC
 * Size = Length of the payload data
 * Type = Type of record
 *        (kZeroType, kFullType, kFirstType, kLastType, kMiddleType )
 *        The type is used to group a bunch of records together to represent
 *        blocks that are larger than kBlockSize
 * Payload = Byte stream as long as specified by the payload size
 *
 * Recyclable record format:
 *
 * +---------+-----------+-----------+----------------+--- ... ---+
 * |CRC (4B) | Size (2B) | Type (1B) | Log number (4B)| Payload   |
 * +---------+-----------+-----------+----------------+--- ... ---+
 *
 * Same as above, with the addition of
 * Log number = 32bit log file number, so that we can distinguish between
 * records written by the most recent log writer vs a previous one.
 */
class Writer {
 public:
  // Create a writer that will append data to "*dest".
  // "*dest" must be initially empty.
  // "*dest" must remain live while this Writer is in use.
  explicit Writer(std::unique_ptr<WritableFileWriter>&& dest,
                  uint64_t log_number, bool recycle_log_files,
                  bool manual_flush = false,
                  CompressionType compressionType = kNoCompression);
  // No copying allowed
  Writer(const Writer&) = delete;
  void operator=(const Writer&) = delete;

  ~Writer();

  // 4K alignment size
  static constexpr size_t kAlignSize = 4096;

  // Helper function to align size to 4K boundary
  static size_t AlignTo4K(size_t size) {
    return (size + kAlignSize - 1) & ~(kAlignSize - 1);
  }

  bool Is4KAligned(size_t size) {
      // 如果size与(4096-1)按位与的结果为0，则说明size是4K对齐的
      return (size & (kAlignSize - 1)) == 0;
  }

  IOStatus AddRecord(const Slice& slice,
                     Env::IOPriority rate_limiter_priority = Env::IO_TOTAL);
  IOStatus AddCompressionTypeRecord();

  WritableFileWriter* file() { return dest_.get(); }
  const WritableFileWriter* file() const { return dest_.get(); }

  uint64_t get_log_number() const { return log_number_; }

  IOStatus WriteBuffer();

  IOStatus Close();

  bool BufferIsEmpty();

  bool need_pad(RecordType type) {
    return type == kFullType || type == kLastType;
  }

  bool is_aligned_type(RecordType type) {
    return type == kFirstType || type == kMiddleType;
  }

 private:
  std::unique_ptr<WritableFileWriter> dest_;
  size_t block_offset_;  // Current offset in block
  uint64_t log_number_;
  bool recycle_log_files_;

  // crc32c values for all supported record types.  These are
  // pre-computed to reduce the overhead of computing the crc of the
  // record type stored in the header.
  uint32_t type_crc_[kMaxRecordType + 1];

  IOStatus EmitPhysicalRecord(
      RecordType type, const char* ptr, size_t length,
      Env::IOPriority rate_limiter_priority = Env::IO_TOTAL);

  // If true, it does not flush after each write. Instead it relies on the upper
  // layer to manually does the flush by calling ::WriteBuffer()
  bool manual_flush_;

  // Compression Type
  CompressionType compression_type_;
  StreamingCompress* compress_;
  // Reusable compressed output buffer
  std::unique_ptr<char[]> compressed_buffer_;
};

}  // namespace log
}  // namespace ROCKSDB_NAMESPACE
