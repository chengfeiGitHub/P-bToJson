#pragma once
#include <iostream>
#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>

void ChooseSomeFieldsToJson(std::string& pb2jsonstring, const ::google::protobuf::Message& msg, std::vector<uint>& needs, bool Enum_2_Str, bool Showzero);
//Enum_2_Str:　ture显示枚举名，false:显示枚举值；　Showzero: ture显示值为０的fields，false,不显示值为０的fields。
void GetRepeatedJson(std::string& pb2jsonstring, const ::google::protobuf::Message& msg, const google::protobuf::FieldDescriptor *field, const ::google::protobuf::Reflection *reflection, bool Enum_2_Str,bool Showzero);
void NeedEmptyToJson(std::string& pb2jsonstring, const ::google::protobuf::Message& msg, bool Enum_2_Str, bool Showzero);
void NeedNotEmptyToJson(std::string& pb2jsonstring, const ::google::protobuf::Message& msg, std::vector<uint>& needs, bool Enum_2_Str, bool Showzero);
int AppendTmpString1(std::string& pb2jsonstring,std::string& tmp_string, int judge);
int AppendTmpString2(std::string& pb2jsonstring,std::string& tmp_string, int judge);


