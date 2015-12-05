/*!
 * Copyright 2014 by Contributors
 * \file io.h
 * \brief general stream interface for serialization, I/O
 * \author Tianqi Chen
 */

#ifndef XGBOOST_UTILS_IO_H_
#define XGBOOST_UTILS_IO_H_
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include "./utils.h"
#include "../sync/sync.h"

// =*=*=*=*=*

#define XGBOOST_USE_BOOST 1
#if XGBOOST_USE_BOOST
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp>
#endif

#define XGBOOST_SQUEEZE 1
// TODO: fp16 for small additional gain?
#if XGBOOST_SQUEEZE
#include "half.hpp" // must be in path
typedef int16_t xgboost_int_t;
typedef uint16_t xgboost_uint_t;
#define XGBOOST_HIGH_BIT 15
#else
typedef int32_t xgboost_int_t;
typedef uint32_t xgboost_uint_t;
#define XGBOOST_HIGH_BIT 31
#endif
// =*=*=*=*

namespace xgboost {
namespace utils {
// reuse the definitions of streams
typedef rabit::Stream IStream;
typedef rabit::utils::SeekStream ISeekStream;
typedef rabit::utils::MemoryFixSizeBuffer MemoryFixSizeBuffer;
typedef rabit::utils::MemoryBufferStream MemoryBufferStream;

/*! \brief implementation of file i/o stream */
class FileStream : public ISeekStream {
 public:
  explicit FileStream(std::FILE *fp) : fp(fp) {}
  FileStream(void) {
    this->fp = NULL;
  }
  virtual size_t Read(void *ptr, size_t size) {
    return std::fread(ptr, size, 1, fp);
  }
  virtual void Write(const void *ptr, size_t size) {
    std::fwrite(ptr, size, 1, fp);
  }
  virtual void Seek(size_t pos) {
    std::fseek(fp, static_cast<long>(pos), SEEK_SET); // NOLINT(*)
  }
  virtual size_t Tell(void) {
    return std::ftell(fp);
  }
  virtual bool AtEnd(void) const {
    return std::feof(fp) != 0;
  }
  inline void Close(void) {
    if (fp != NULL) {
      std::fclose(fp); fp = NULL;
    }
  }

 private:
  std::FILE *fp;
};
}  // namespace utils
}  // namespace xgboost
#include "./base64-inl.h"
#endif  // XGBOOST_UTILS_IO_H_
