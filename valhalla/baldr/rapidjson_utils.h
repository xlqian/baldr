/*
 * rapidjson_utils.h
 *
 *  Created on: 3 Feb 2017
 *      Author: xiaolong
 */

#ifndef VALHALLA_BALDR_RAPIDJSON_UTILS_H_
#define VALHALLA_BALDR_RAPIDJSON_UTILS_H_

#include <rapidjson/document.h>
#include <rapidjson/pointer.h>

namespace valhalla {


template<typename T>
inline boost::optional<T> GetOptionalFromRapidJson(const rapidjson::Value& v, const char* source){
  auto* ptr= rapidjson::Pointer{source}.Get(v);
  if(! ptr || ! ptr->Is<T>()) {
    return {};
  }
  return ptr->Get<T>();
}

template<typename T>
inline boost::optional<T> GetOptionalFromRapidJson(rapidjson::Value& v, const char* source){
  auto* ptr= rapidjson::Pointer{source}.Get(v);
  if(! ptr || ! ptr->Is<T>()) {
    return {};
  }
  return ptr->Get<T>();
}

}



#endif /* VALHALLA_BALDR_RAPIDJSON_UTILS_H_ */
