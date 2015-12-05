// Copyright by Contributors
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define NOMINMAX
#include <cstring>
#include "./gbm.h"
#include "./gbtree-inl.hpp"
#include "./gblinear-inl.hpp"

namespace xgboost {
namespace gbm {
IGradBooster* CreateGradBooster(const char *name) {
  using namespace std;
  if (!strcmp("gbtree", name)) return new GBTree();
  if (!strcmp("gblinear", name)) return new GBLinear();
  utils::Error("unknown booster type: %s", name);
  return NULL;
}
}  // namespace gbm
}  // namespace xgboost

//BOOST_CLASS_EXPORT_IMPLEMENT(xgboost::gbm::GBTree);
//BOOST_CLASS_EXPORT_IMPLEMENT(xgboost::gbm::GBLinear);
