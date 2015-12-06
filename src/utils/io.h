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

/*
 Some knowledge of boost serialization is required.  Since xgboost is largely header based,
 I have added all serialization calls as class members direclty in the header files:
 
 template<class Archive> void serialize(Archive & ar, const unsigned int version)
 
 So the user can instantiate any archives they want.  This also requires that the 
 classes are "exported" from a cpp file in the user's main project.  There are some
 subtleties within boost related to how this exporting is done (in particular 
 polymorphis classes).  The following is standard boost code (per docs) but is included 
 to give a funtional starting point for anyone who wants to use this feature.
 
 // Learner (IGradBooster):
 BOOST_SERIALIZATION_ASSUME_ABSTRACT(xgboost::gbm::IGradBooster);
 BOOST_CLASS_EXPORT_GUID(xgboost::gbm::IGradBooster, "IGradBooster");
 BOOST_CLASS_EXPORT_GUID(xgboost::gbm::GBLinear, "GBLinear")
 BOOST_CLASS_EXPORT_GUID(xgboost::gbm::GBTree, "GBTree")
 
 // Tree model:
 typedef xgboost::tree::RTreeNodeStat RTreeNodeStat;
 typedef xgboost::tree::TreeModel<bst_float, RTreeNodeStat> TreeModel;
 BOOST_SERIALIZATION_ASSUME_ABSTRACT(TreeModel);
 BOOST_CLASS_EXPORT_GUID(TreeModel, "TreeModel");
 BOOST_CLASS_EXPORT_GUID(xgboost::tree::RegTree, "RegTree");
 
 // Loss function:
 BOOST_SERIALIZATION_ASSUME_ABSTRACT(xgboost::learner::IObjFunction);
 BOOST_CLASS_EXPORT_GUID(xgboost::learner::IObjFunction, "IObjFunction");
 BOOST_CLASS_EXPORT_GUID(xgboost::learner::RegLossObj, "RegLossObj");

 */

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
