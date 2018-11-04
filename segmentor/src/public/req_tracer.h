#pragma once

#include "common.h"

namespace xforce { namespace nlu {

class ReqTracer {
 public: 
  inline ReqTracer();

  inline void Set(const std::string &key, bool val);
  inline void Set(const std::string &key, int val);
  inline void Set(const std::string &key, const char *val);
  inline void Set(const std::string &key, const std::string &val);

  inline void Add(const std::string &key, const std::string &val);

  inline void Clear();
  inline std::string GetReport() const;

  virtual ~ReqTracer();

  inline static ReqTracer& Get() { return *reqTracer_; }
  static void Tini();
 
 private:
  inline std::string ProcessStr_(const std::string &str); 

 private:
  time_t curMs_;
  xforce::JsonType *jsonType_;  

  static ReqTracer *reqTracer_;
};

ReqTracer::ReqTracer() {
  jsonType_ = new xforce::JsonType();
}

void ReqTracer::Set(const std::string &key, bool val) {
  (*jsonType_)[key] = val;
}

void ReqTracer::Set(const std::string &key, int val) {
  (*jsonType_)[key] = val;
}

void ReqTracer::Set(const std::string &key, const char *val) {
  (*jsonType_)[key] = val;
}

void ReqTracer::Set(const std::string &key, const std::string &val) {
  (*jsonType_)[key] = val;
}

void ReqTracer::Add(const std::string &key, const std::string &val) {
  (*jsonType_)[key].Append(val);
}

void ReqTracer::Clear() {
  curMs_ = xforce::Time::GetCurrentMsec(true);
}

std::string ReqTracer::GetReport() const {
  std::stringstream ostr;
  jsonType_->DumpJson(ostr);
  return ostr.str();
}

}}
