#include <iostream>
#include <google/protobuf/descriptor.h>  
#include <google/protobuf/message.h>  
#include <set>
#include <string>
#include "pbjsontest3.h"
  
using namespace ::google::protobuf; 

void ChooseSomeFieldsToJson(std::string& pb2jsonstring, const ::google::protobuf::Message& msg, std::vector<uint>& need, bool Enum_2_Str, bool Showzero)  
{

    const Descriptor* descriptor = msg.GetDescriptor();  
    const Reflection* reflection = msg.GetReflection(); 
    if (need.empty())  //如果needs为空，表示需要将所有的字段转换为json
    {    
        NeedEmptyToJson(pb2jsonstring, msg, Enum_2_Str, Showzero);
    }
    else 
    {
        NeedNotEmptyToJson(pb2jsonstring, msg, need, Enum_2_Str, Showzero);
    }
}
 
void NeedEmptyToJson(std::string& pb2jsonstring, const ::google::protobuf::Message& msg, bool Enum_2_Str, bool Showzero)
{
    const Descriptor* descriptor = msg.GetDescriptor();  
    const Reflection* reflection = msg.GetReflection(); 
    const uint count = descriptor->field_count();
    uint judge = 0;//ｊｕｄｇｅ用来判断是否在当前ｊｓｏｎ元素前加“，”用来分隔前后元素，如果ｊｕｄｇｅ＝＝０，则不加，如果ｊｕｇｄｇｅ＝＝１，则加“，”
    std::string tmp_string;
    std::int32_t v32=0;
    std::uint32_t vu32=0;
    std::int64_t v64=0;
    std::uint64_t vu64=0;
    double vd=0;
    std::string str;
    pb2jsonstring.append("{");
    for (int it = 0; it <count; ++it) 
    {         
        const FieldDescriptor* goal_field=descriptor->field(it);       
        if(nullptr==goal_field)  //不存在字段
        {
            continue;
        } 

        if (goal_field->is_repeated())  
        {  
            if (reflection->FieldSize(msg, goal_field) > 0)  
            { 
                tmp_string="";
                tmp_string.append("\"").append(goal_field->name()).append("\":");
                tmp_string .append("[");
                GetRepeatedJson(tmp_string, msg, goal_field, reflection, Enum_2_Str,Showzero); 
                tmp_string.append("]"); 
                judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);  
            }
            continue;  
        }
        switch (goal_field->type())  
        {  
        case FieldDescriptor::TYPE_MESSAGE:  
            {  
                const Message& tmp_msg = reflection->GetMessage(msg, goal_field);  
                if (0 != tmp_msg.ByteSize())  
                { 
                    tmp_string="";
                    tmp_string.append("\"").append(goal_field->name()).append("\":");
                    NeedEmptyToJson(tmp_string,tmp_msg, Enum_2_Str, Showzero);
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);
                }  
            }  
            break;  
            
        case FieldDescriptor::TYPE_INT32: 
            {
                v32=reflection->GetInt32(msg, goal_field);
                if(v32==0)
                {
                    if(Showzero)   //字段值为０，也需要进行打印
                    {                        
                        tmp_string="";
                        tmp_string.append("\"").append(goal_field->name()).append("\":");
                        tmp_string.append(std::to_string(v32)); 
                        judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                    }
                }
                else
                {
                    tmp_string="";
                    tmp_string.append("\"").append(goal_field->name()).append("\":");
                    tmp_string.append(std::to_string(v32));                     
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                } 
            }
            break;  

        case FieldDescriptor::TYPE_UINT32:
            {  
                vu32=reflection->GetUInt32(msg, goal_field);
                if(vu32==0)
                {
                    if(Showzero)
                    {
                        tmp_string="";
                        tmp_string.append("\"").append(goal_field->name()).append("\":");
                        tmp_string.append(std::to_string(vu32));  
                        judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                    }
                }
                else
                {
                    tmp_string="";
                    tmp_string.append("\"").append(goal_field->name()).append("\":");
                    tmp_string.append(std::to_string(vu32));
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                }       
             }
            break;  

        case FieldDescriptor::TYPE_INT64:  
            {  
                v64=reflection->GetInt64(msg, goal_field);
                if(v64==0)
                {
                    if(Showzero)
                    {
                        tmp_string="";
                        tmp_string.append("\"").append(goal_field->name()).append("\":");         
                        tmp_string.append(std::to_string(v64));
                        judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                    }
                }
                else
                {
                    tmp_string="";
                    tmp_string.append("\"").append(goal_field->name()).append("\":");
                    tmp_string.append(std::to_string(v64));         
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);  
                } 
            } 
            break;  
        case FieldDescriptor::TYPE_UINT64:  
             {  
                vu64=reflection->GetUInt64(msg, goal_field);
                if(vu64==0)
                {
                    if(Showzero)
                    {
                        tmp_string="";                
                        tmp_string.append("\"").append(goal_field->name()).append("\":");      
                        tmp_string.append(std::to_string(vu64));
                        judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                    }
                }
                else
                {
                    tmp_string="";                
                    tmp_string.append("\"").append(goal_field->name()).append("\":");      
                    tmp_string.append(std::to_string(vu64));
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                }
             } 
            break;  
        case FieldDescriptor::TYPE_STRING:  
        case FieldDescriptor::TYPE_BYTES:  
            {  
                
                str=reflection->GetString(msg, goal_field);
                if(str.empty())
                {
                    if(Showzero)
                    {
                        tmp_string="";
                        tmp_string.append("\"").append(goal_field->name()).append("\":");
                        tmp_string.append("\"").append(str).append("\"");
                        judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);
                    }
                }
                else
                {
                    tmp_string="";
                    tmp_string.append("\"").append(goal_field->name()).append("\":");
                    tmp_string.append("\"").append(str).append("\"");
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);

                }
            }  
            break; 
        case FieldDescriptor::TYPE_DOUBLE:
            {
                vd=reflection->GetDouble(msg, goal_field);
                if(vd==0)
                {
                    if(Showzero)
                    {
                        tmp_string="";
                        tmp_string.append("\"").append(goal_field->name()).append("\":");
                        tmp_string.append(std::to_string(vd));
                        judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);
                    }
                }
                else 
                {
                    tmp_string="";
                    tmp_string.append("\"").append(goal_field->name()).append("\":");
                    tmp_string.append(std::to_string(vd));
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);
                }          
            } 
            break;
        case FieldDescriptor::TYPE_BOOL:
            {
                tmp_string="";
                tmp_string.append("\"").append(goal_field->name()).append("\":");
                if (reflection->GetBool(msg, goal_field))
                    tmp_string.append("true");
                else 
                    tmp_string.append("false");
                judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);
              
            } 
            break;
        case FieldDescriptor::TYPE_ENUM:
            {
                tmp_string="";
                tmp_string.append("\"").append(goal_field->name()).append("\":");
                if (Enum_2_Str)
                {       
                    tmp_string.append("\"").append(reflection->GetEnum(msg,goal_field)->name()).append("\"");
                }
                else 
                {
                    static char enumstr[8];
                    memset(enumstr, 0, sizeof(enumstr)); 
                    snprintf(enumstr, sizeof(enumstr), "%d", reflection->GetEnum(msg,goal_field)->number());
                    tmp_string.append(enumstr);                    
                }
                judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);
            }
            break;
        default:  
            break;  
        }
    }
    pb2jsonstring.append("}");
}

void NeedNotEmptyToJson(std::string& pb2jsonstring, const ::google::protobuf::Message& msg, std::vector<uint>& needs, bool Enum_2_Str, bool Showzero)
{
    const Descriptor* descriptor = msg.GetDescriptor();  
    const Reflection* reflection = msg.GetReflection(); 
   
    uint judge = 0;
    std::string tmp_string;
    std::int32_t v32=0;
    std::uint32_t vu32=0;
    std::int64_t v64=0;
    std::uint64_t vu64=0;
    double vd=0;
    std::string str;

    pb2jsonstring.append("{");
   
    for (auto it=needs.begin(); it != needs.end(); ++it) 
    {         
        const FieldDescriptor* goal_field=descriptor->FindFieldByNumber(*it); 

        if(nullptr==goal_field)  //不存在字段
        {
            continue;
        } 

        if (goal_field->is_repeated())  
        {  
            if (reflection->FieldSize(msg, goal_field) > 0)  
            { 
                tmp_string="";
                tmp_string.append("\"").append(goal_field->name()).append("\":");
                tmp_string .append("[");
                GetRepeatedJson(tmp_string, msg, goal_field, reflection, Enum_2_Str,Showzero); 
                tmp_string.append("]"); 
                judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);  
            }
            continue;  
        }
        switch (goal_field->type())  
        {  
        case FieldDescriptor::TYPE_MESSAGE:  
            {  
                const Message& tmp_msg = reflection->GetMessage(msg, goal_field);  
                if (0 != tmp_msg.ByteSize())  
                { 
                    tmp_string="";
                    tmp_string.append("\"").append(goal_field->name()).append("\":");
                    NeedEmptyToJson(tmp_string,tmp_msg, Enum_2_Str, Showzero);
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);
                }  
            }  
            break;  
            
        case FieldDescriptor::TYPE_INT32: 
            {
                v32=reflection->GetInt32(msg, goal_field);
                if(v32==0)
                {
                    if(Showzero)   //字段值为０，也需要进行打印
                    {                        
                        tmp_string="";
                        tmp_string.append("\"").append(goal_field->name()).append("\":");
                        tmp_string.append(std::to_string(v32)); 
                        judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                    }
                }
                else
                {
                    tmp_string="";
                    tmp_string.append("\"").append(goal_field->name()).append("\":");
                    tmp_string.append(std::to_string(v32));                     
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                } 
            }
            break;  

        case FieldDescriptor::TYPE_UINT32:
            {  
                vu32=reflection->GetUInt32(msg, goal_field);
                if(vu32==0)
                {
                    if(Showzero)
                    {
                        tmp_string="";
                        tmp_string.append("\"").append(goal_field->name()).append("\":");
                        tmp_string.append(std::to_string(vu32));  
                        judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                    }
                }
                else
                {
                    tmp_string="";
                    tmp_string.append("\"").append(goal_field->name()).append("\":");
                    tmp_string.append(std::to_string(vu32));
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                }       
             }
            break;  

        case FieldDescriptor::TYPE_INT64:  
            {  
                v64=reflection->GetInt64(msg, goal_field);
                if(v64==0)
                {
                    if(Showzero)
                    {
                        tmp_string="";
                        tmp_string.append("\"").append(goal_field->name()).append("\":");         
                        tmp_string.append(std::to_string(v64));
                        judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                    }
                }
                else
                {
                    tmp_string="";
                    tmp_string.append("\"").append(goal_field->name()).append("\":");
                    tmp_string.append(std::to_string(v64));         
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);  
                } 
            } 
            break;  
        case FieldDescriptor::TYPE_UINT64:  
             {  
                vu64=reflection->GetUInt64(msg, goal_field);
                if(vu64==0)
                {
                    if(Showzero)
                    {
                        tmp_string="";                
                        tmp_string.append("\"").append(goal_field->name()).append("\":");      
                        tmp_string.append(std::to_string(vu64));
                        judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                    }
                }
                else
                {
                    tmp_string="";                
                    tmp_string.append("\"").append(goal_field->name()).append("\":");      
                    tmp_string.append(std::to_string(vu64));
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                }
             } 
            break;  
        case FieldDescriptor::TYPE_STRING:  
        case FieldDescriptor::TYPE_BYTES:  
            {  
                
                str=reflection->GetString(msg, goal_field);
                if(str.empty())
                {
                    if(Showzero)
                    {
                        tmp_string="";
                        tmp_string.append("\"").append(goal_field->name()).append("\":");
                        tmp_string.append("\"").append(str).append("\"");
                        judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);
                    }
                }
                else
                {
                    tmp_string="";
                    tmp_string.append("\"").append(goal_field->name()).append("\":");
                    tmp_string.append("\"").append(str).append("\"");
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);

                }
            }  
            break; 
        case FieldDescriptor::TYPE_DOUBLE:
            {
                vd=reflection->GetDouble(msg, goal_field);
                if(vd==0)
                {
                    if(Showzero)
                    {
                        tmp_string="";
                        tmp_string.append("\"").append(goal_field->name()).append("\":");
                        tmp_string.append(std::to_string(vd));
                        judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);
                    }
                }
                else 
                {
                    tmp_string="";
                    tmp_string.append("\"").append(goal_field->name()).append("\":");
                    tmp_string.append(std::to_string(vd));
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);
                }          
            } 
            break;
        case FieldDescriptor::TYPE_BOOL:
            {
                tmp_string="";
                tmp_string.append("\"").append(goal_field->name()).append("\":");
                if (reflection->GetBool(msg, goal_field))
                    tmp_string.append("true");
                else 
                    tmp_string.append("false");
                judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);
              
            } 
            break;
        case FieldDescriptor::TYPE_ENUM:
            {
                tmp_string="";
                tmp_string.append("\"").append(goal_field->name()).append("\":");
                if (Enum_2_Str)
                {       
                    tmp_string.append("\"").append(reflection->GetEnum(msg,goal_field)->name()).append("\"");
                }
                else 
                {
                    static char enumstr[8];
                    memset(enumstr, 0, sizeof(enumstr)); 
                    snprintf(enumstr, sizeof(enumstr), "%d", reflection->GetEnum(msg,goal_field)->number());
                    tmp_string.append(enumstr);                    
                }
                judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);
            }
            break;
        default:  
            break;  
        }
    }
    pb2jsonstring.append("}");
}

int AppendTmpString1(std::string &pb2jsonstring,std::string &tmp_string, int judge)
{
    if ( judge!=0 && tmp_string.length()!=0)
    {
        pb2jsonstring.append(",").append(tmp_string);
        return judge;
    }
    else if(judge==0 && tmp_string.length()!=0)
    {
        pb2jsonstring.append(tmp_string);
        return 1;
    }
    return judge;
} 
  
void GetRepeatedJson(std::string& pb2jsonstring, const ::google::protobuf::Message& msg, const google::protobuf::FieldDescriptor *goal_field, const ::google::protobuf::Reflection *reflection, bool Enum_2_Str,bool Showzero)  
{     
    std::string tmp_string;
    int judge=0;
    std::int32_t v32=0;
    std::uint32_t vu32=0;
    std::int64_t v64=0;
    std::uint64_t vu64=0;
    double vd=0;
    std::string str;
    for (int i = 0; i < reflection->FieldSize(msg, goal_field); ++i)  
    {      
        switch (goal_field->type())                 
        {  
        case FieldDescriptor::TYPE_MESSAGE:  
            {  
                const Message& tmp_msg = reflection->GetRepeatedMessage(msg, goal_field, i);
                if (0 != tmp_msg.ByteSize())  
                {                    
                    tmp_string="";
                    NeedEmptyToJson(tmp_string, tmp_msg, Enum_2_Str,Showzero); 
                    judge = AppendTmpString2(pb2jsonstring,tmp_string,judge);
                }
            }  
            break;  
        case FieldDescriptor::TYPE_INT32: 
            {               
                v32=reflection->GetRepeatedInt32(msg, goal_field,i);
                if(v32==0)
                {
                    if(Showzero)
                    {                        
                        tmp_string="";
                        tmp_string.append(std::to_string(v32)); 
                        judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                    }
                }
                else
                {
                    tmp_string="";
                    tmp_string.append(std::to_string(v32));            
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                } 
            } 
            
            break;  
        case FieldDescriptor::TYPE_UINT32:
            {               
                vu32=reflection->GetRepeatedUInt32(msg, goal_field,i);
                if(vu32==0)
                {
                    if(Showzero)
                    {
                        tmp_string="";
                        tmp_string.append(std::to_string(vu32));  
                        judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                    }
                }
                else
                {
                    tmp_string="";
                    tmp_string.append(std::to_string(vu32)); 
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                }       
             }          
            break;  
        case FieldDescriptor::TYPE_INT64:  
            {  
                v64=reflection->GetRepeatedInt64(msg, goal_field,i);
                if(v64==0)
                {
                    if(Showzero)
                    {
                        tmp_string="";      
                        tmp_string.append(std::to_string(v64));
                        judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                    }
                }
                else
                {
                    tmp_string="";
                    tmp_string.append(std::to_string(v64));         
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);  
                }
            }  
            break;  
        case FieldDescriptor::TYPE_UINT64:  
            {  
                vu64=reflection->GetRepeatedUInt64(msg, goal_field,i);
                if(vu64==0)
                {
                    if(Showzero)
                    {
                        tmp_string="";                      
                        tmp_string.append(std::to_string(vu64));
                        judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                    }
                }
                else
                {
                    tmp_string="";                    
                    tmp_string.append(std::to_string(vu64));
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 
                }

            }  
            break;  
        case FieldDescriptor::TYPE_STRING:  
        case FieldDescriptor::TYPE_BYTES: 
            {
                str="";
                str=reflection->GetRepeatedString(msg, goal_field,i);
                if(str.empty())
                {
                    if(Showzero)
                    {
                        tmp_string="";
                        tmp_string.append("\"").append(str).append("\"");
                        judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);
                    }
                }
                else
                {
                    tmp_string="";
                    tmp_string.append("\"").append(str).append("\"");
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);

                }
            }
            break; 
        case FieldDescriptor::TYPE_DOUBLE:  
            {
                vd=reflection->GetRepeatedDouble(msg, goal_field,i);
                if(vd==0)
                {
                    if(Showzero)
                    {
                        tmp_string="";
                        tmp_string.append(std::to_string(vd));
                        judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);
                    }
                }
                else 
                {
                    tmp_string="";
                    tmp_string.append(std::to_string(vd));
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);
                }

            }           
            break; 
         case FieldDescriptor::TYPE_BOOL:  
        {
            tmp_string="";
            if(reflection->GetRepeatedBool(msg, goal_field,i))
                tmp_string.append("true");
            else
                tmp_string.append("false");
            judge = AppendTmpString2(pb2jsonstring,tmp_string,judge);

        }           
        break; 
        case FieldDescriptor::TYPE_ENUM:
            {
               tmp_string="";
               if (Enum_2_Str)
                    {                       
                        tmp_string.append("\"").append(reflection->GetRepeatedEnum(msg,goal_field,i)->name()).append("\"");                
                    }
                else 
                    {
                        static char enumstr[8];
                        memset(enumstr, 0, sizeof(enumstr)); 
                        snprintf(enumstr, sizeof(enumstr), "%d", reflection->GetRepeatedEnum(msg,goal_field,i)->number());
                        tmp_string.append(enumstr);
                    }
                judge = AppendTmpString2(pb2jsonstring,tmp_string,judge);
            }       
            break;  
        default:  
            break;  
        }        
    }    
}  
int AppendTmpString2(std::string &pb2jsonstring,std::string &tmp_string, int judge)
{
    if( judge!=0 && tmp_string.length()!=0)
    {
        pb2jsonstring.append(",").append(tmp_string);
        return judge;
    }
    else if( judge==0 && tmp_string.length()!=0)
    {
        pb2jsonstring.append(tmp_string);
        return 1;
    }
    return judge;
}

