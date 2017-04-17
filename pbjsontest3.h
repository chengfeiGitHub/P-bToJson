#pragma once
#include <iostream>
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include "hxzq/pb_to_json_string.h"

void ChooseMessageToJson(std::string& pb2jsonstring, const ::google::protobuf::Message& msg, std::set<uint>& needs, bool Enum_2_Str);
void GetRepeatedJson(std::string& pb2jsonstring, const ::google::protobuf::Message& msg, const google::protobuf::FieldDescriptor *field, const ::google::protobuf::Reflection *reflection, bool Enum_2_Str);
int AppendTmpString1(std::string& pb2jsonstring,std::string& tmp_string, int judge);
int AppendTmpString2(std::string& pb2jsonstring,std::string& tmp_string, int judge);



