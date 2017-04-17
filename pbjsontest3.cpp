#include <iostream>
#include <google/protobuf/descriptor.h>  
#include <google/protobuf/message.h>  
#include <set>
#include <string>
#include "pbjsontest3.h"

// #include "hxzq/pb_to_json_string.h"
  
using namespace ::google::protobuf; 

void ChooseMessageToJson(std::string& pb2jsonstring, const ::google::protobuf::Message& msg, std::set<uint>& needs, bool Enum_2_Str)  
{  
    const Descriptor* descriptor = msg.GetDescriptor();  
    const Reflection* reflection = msg.GetReflection();  
  
    const uint count = descriptor->field_count();
    uint i,judge = 0;   //judge用来判断当前当前获取的field字符串是否是第一个不为空字段值，如果是，则直接append，
                        //如果不是第一个，则先append一个“，”逗号，与前一个字段进行分割。

    std::set<uint> need;
    if (needs.empty())  //如果needs为空，表示需要将所有的字段转换为json，此时将message中所有可能的字段号insert集合need中
    {   
        for(i=0; i<count ; ++i)
        {
            need.insert(i+1);        
        }
    }
    else{               //need不为空，仅需要转换几个特定的field，直接将needs复制为need

        need.swap(needs);
    }
    i=0;
    std::string tmp_string;
    pb2jsonstring.append("{");
    for (auto it = need.begin(); it != need.end(); ++i, ++it) 
    {  
        const FieldDescriptor* goal_field = descriptor->FindFieldByNumber(*it);  
        if(nullptr==goal_field)
            continue; 
        if (goal_field->is_repeated())  
        {  
            if (reflection->FieldSize(msg, goal_field) > 0)  
            { 
                tmp_string.clear();
                tmp_string.append("\"").append(goal_field->name()).append("\":");
                tmp_string .append("[");
                GetRepeatedJson(tmp_string, msg, goal_field, reflection, Enum_2_Str); 
                tmp_string.append("]"); 
                judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 

                //  
                // tmp_string.clear();
                // GetRepeatedJson(tmp_string, msg, goal_field, reflection, Enum_2_Str);             
                // if ( judge!=0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append(",").append("\"").append(goal_field->name()).append("\":").append("[");
                //     pb2jsonstring.append(tmp_string);
                // }
                // else if(judge==0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append("\"").append(goal_field->name()).append("\":").append("[");
                //     pb2jsonstring.append(tmp_string);
                //     // GetRepeatedJson(pb2jsonstring, msg, goal_field, reflection, Enum_2_Str);
                //     judge=1;
                // }
                // pb2jsonstring.append("]");
                //
            }
            continue;  
        }

        if (!reflection->HasField(msg, goal_field))  
        {  
            continue;  
        }         
        
        switch (goal_field->type())  
        {  
        case FieldDescriptor::TYPE_MESSAGE:  
            {  
                const Message& tmp_msg = reflection->GetMessage(msg, goal_field);  
                if (0 != tmp_msg.ByteSize())  
                {  
                    tmp_string.clear();
                    std::set<uint> NEED;
                    tmp_string.append("\"").append(goal_field->name()).append("\":");
                    ChooseMessageToJson(tmp_string,tmp_msg, NEED, Enum_2_Str);
                    judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);


                    //                    
                    // std::set<uint> NEED;
                    // tmp_string.clear();
                    // ChooseMessageToJson(tmp_string,tmp_msg, NEED, Enum_2_Str);
                    // if ( judge!=0 && tmp_string.length()!=0)
                    // {
                    //     pb2jsonstring.append(",").append("\"").append(goal_field->name()).append("\":");
                    //     pb2jsonstring.append(tmp_string);
                                                
                    // }
                    // else if(judge==0 && tmp_string.length()!=0)
                    // {
                    //     pb2jsonstring.append("\"").append(goal_field->name()).append("\":");
                    //     pb2jsonstring.append(tmp_string);
                    //     judge=1;
                    // }
                    //

                }  
            }  
            break;  
            
        case FieldDescriptor::TYPE_INT32: 
			{
                tmp_string.clear();
                tmp_string.append("\"").append(goal_field->name()).append("\":");
                tmp_string.append(std::to_string(reflection->GetInt32(msg, goal_field))); 
                judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 


                //
                // tmp_string.clear();
                // tmp_string.append(std::to_string(reflection->GetInt32(msg, goal_field)));
                // if ( judge!=0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append(",").append("\"").append(goal_field->name()).append("\":");
                //     pb2jsonstring.append(tmp_string);   
                // }
                // else if(judge==0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append("\"").append(goal_field->name()).append("\":");
                //     pb2jsonstring.append(tmp_string); 
                //     judge=1;
                // }

                //        

            }
            break;  

        case FieldDescriptor::TYPE_UINT32:
	        {  
	            tmp_string.clear();
	            tmp_string.append("\"").append(goal_field->name()).append("\":");
                tmp_string.append(std::to_string(reflection->GetUInt32(msg, goal_field)));  
                judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);  

                //
                
                // tmp_string.clear();
                // tmp_string.append(std::to_string(reflection->GetUInt32(msg, goal_field)));
                // if ( judge!=0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append(",").append("\"").append(goal_field->name()).append("\":");
                //     pb2jsonstring.append(tmp_string);   
                // }
                // else if(judge==0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append("\"").append(goal_field->name()).append("\":");
                //     pb2jsonstring.append(tmp_string); 
                //     judge=1;
                // }

                //        
       
	         }
            break;  

        case FieldDescriptor::TYPE_INT64:  
            {  
                tmp_string.clear();
	            tmp_string.append("\"").append(goal_field->name()).append("\":");         
                tmp_string.append(std::to_string(reflection->GetInt64(msg, goal_field)));
                judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);

                //
                // tmp_string.clear();
                // tmp_string.append(std::to_string(reflection->GetInt64(msg, goal_field)));
                // if ( judge!=0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append(",").append("\"").append(goal_field->name()).append("\":");
                //     pb2jsonstring.append(tmp_string);   
                // }
                // else if(judge==0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append("\"").append(goal_field->name()).append("\":");
                //     pb2jsonstring.append(tmp_string); 
                //     judge=1;
                // }

                //        

 
	         } 
            break;  
        case FieldDescriptor::TYPE_UINT64:  
             {  
	            tmp_string.clear();                
                tmp_string.append("\"").append(goal_field->name()).append("\":");      
                tmp_string.append(std::to_string(reflection->GetUInt64(msg, goal_field)));
                judge = AppendTmpString1(pb2jsonstring,tmp_string,judge); 

                // //
                // tmp_string.clear();
                // tmp_string.append(std::to_string(reflection->GetUInt64(msg, goal_field)));
                // if ( judge!=0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append(",").append("\"").append(goal_field->name()).append("\":");
                //     pb2jsonstring.append(tmp_string);   
                // }
                // else if(judge==0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append("\"").append(goal_field->name()).append("\":");
                //     pb2jsonstring.append(tmp_string); 
                //     judge=1;
                // }
                //        

	         } 
            break;  
        case FieldDescriptor::TYPE_STRING:  
        case FieldDescriptor::TYPE_BYTES:  
            {  
                tmp_string.clear();
                tmp_string.append("\"").append(goal_field->name()).append("\":").append("\"");
                tmp_string.append(reflection->GetString(msg, goal_field)).append("\"");
                judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);

                // //
                // tmp_string.clear();
                // tmp_string.append(reflection->GetString(msg, goal_field));
                // if ( judge!=0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append(",").append("\"").append(goal_field->name()).append("\":").append("\"");
                //     pb2jsonstring.append(tmp_string).append("\"");   
                // }
                // else if(judge==0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append("\"").append(goal_field->name()).append("\":").append("\"");
                //     pb2jsonstring.append(tmp_string).append("\""); 
                //     judge=1;
                // }
                // //
            }  
            break; 
        case FieldDescriptor::TYPE_DOUBLE:
            {
                // std::cout<<"double"<<reflection->GetDouble(msg, goal_field)<<std::endl;
                tmp_string.clear();
                tmp_string.append("\"").append(goal_field->name()).append("\":");
                tmp_string.append(std::to_string(reflection->GetDouble(msg, goal_field)));
                judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);

                //
                
                // tmp_string.clear();
                // tmp_string.append(std::to_string(reflection->GetDouble(msg, goal_field)));


                // if ( judge!=0 && tmp_string.length()!=0)
                // {

                //     pb2jsonstring.append(",").append("\"").append(goal_field->name()).append("\":");
                //     pb2jsonstring.append(tmp_string); 
                //     // std::cout<<"double:"<<pb2jsonstring<<std::endl;  
                // }
                // else if(judge==0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append("\"").append(goal_field->name()).append("\":");
                //     pb2jsonstring.append(tmp_string); 
                //     judge=1;
                // }


                //                 
            } 
            break;
        case FieldDescriptor::TYPE_ENUM:
            {
                tmp_string.clear();
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
                    // pb2jsonstring.append(std::to_string(reflection->GetEnum(msg, goal_field)));
                }

                judge = AppendTmpString1(pb2jsonstring,tmp_string,judge);

                //

                // if ( judge!=0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append(",").append(tmp_string);
                // }
                // else if(judge==0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append(tmp_string);
                //     judge = 1;
                // }
                //
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
  
void GetRepeatedJson(std::string& pb2jsonstring, const ::google::protobuf::Message& msg, const google::protobuf::FieldDescriptor *goal_field, const ::google::protobuf::Reflection *reflection, bool Enum_2_Str)  
{  
   std::set<uint> NEED;
    if (NULL == goal_field || NULL == reflection)  
    {  
        ChooseMessageToJson(pb2jsonstring, msg, NEED, Enum_2_Str);        
    }
    std::string tmp_string;
    int judge=0;
    for (int i = 0; i < reflection->FieldSize(msg, goal_field); ++i)  
    {      
        tmp_string.clear();
        switch (goal_field->type())                 
        {  
        case FieldDescriptor::TYPE_MESSAGE:  
            {  
                const Message& tmp_msg = reflection->GetRepeatedMessage(msg, goal_field, i);
                if (0 != tmp_msg.ByteSize())  
                {                    
                    tmp_string.clear();
                    ChooseMessageToJson(tmp_string, tmp_msg, NEED, Enum_2_Str); 
                    judge = AppendTmpString2(pb2jsonstring,tmp_string,judge);

                    //
                    // tmp_string.clear();
                    // ChooseMessageToJson(tmp_string, tmp_msg, NEED, Enum_2_Str); 
                    // if( judge!=0 && tmp_string.length()!=0)
                    // {
                    //     pb2jsonstring.append(",").append(tmp_string);
                                              
                    // }
                    // else if( judge==0 && tmp_string.length()!=0)
                    // {
                    //      pb2jsonstring.append(tmp_string);
                    //     judge= 1;
                    // }
                    //
                }

            }  
            break;  
        case FieldDescriptor::TYPE_INT32: 
        	{        		
                tmp_string.clear();
                tmp_string.append(std::to_string(reflection->GetInt32(msg, goal_field)));
                judge = AppendTmpString2(pb2jsonstring,tmp_string,judge);

                //
                // tmp_string.clear();
                // tmp_string.append(std::to_string(reflection->GetInt32(msg, goal_field)));
                // if( judge!=0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append(",").append(tmp_string);                    
                // }
                // else if( judge==0 && tmp_string.length()!=0)
                // {                    
                //     pb2jsonstring.append(tmp_string);
                //     judge = 1;
                // }
                //


        	} 
            
            break;  
        case FieldDescriptor::TYPE_UINT32:
    		{               
                tmp_string.clear();
                tmp_string.append(std::to_string(reflection->GetUInt32(msg, goal_field)));
                judge = AppendTmpString2(pb2jsonstring,tmp_string,judge);

                //
                // tmp_string.clear();
                // tmp_string.append(std::to_string(reflection->GetUInt32(msg, goal_field)));
                // if( judge!=0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append(",").append(tmp_string);                    
                // }
                // else if( judge==0 && tmp_string.length()!=0)
                // {                    
                //     pb2jsonstring.append(tmp_string);
                //     judge = 1;
                // }
                //
             } 
          
            break;  
        case FieldDescriptor::TYPE_INT64:  
            {  
                tmp_string.clear();
                tmp_string.append(std::to_string(reflection->GetInt64(msg, goal_field)));
                judge = AppendTmpString2(pb2jsonstring,tmp_string,judge);

                //
                // tmp_string.clear();
                // tmp_string.append(std::to_string(reflection->GetInt64(msg, goal_field)));
                // if( judge!=0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append(",").append(tmp_string);                    
                // }
                // else if( judge==0 && tmp_string.length()!=0)
                // {                    
                //     pb2jsonstring.append(tmp_string);
                //     judge = 1;
                // }
                // //
            }  
            break;  
        case FieldDescriptor::TYPE_UINT64:  
            {  
                tmp_string.clear();
                tmp_string.append(std::to_string(reflection->GetUInt64(msg, goal_field)));
                judge = AppendTmpString2(pb2jsonstring,tmp_string,judge);

                //
                // tmp_string.clear();
                // tmp_string.append(std::to_string(reflection->GetUInt64(msg, goal_field)));
                // if( judge!=0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append(",").append(tmp_string);                    
                // }
                // else if( judge==0 && tmp_string.length()!=0)
                // {                    
                //     pb2jsonstring.append(tmp_string);
                //     judge = 1;
                // }
                //
            }  
            break;  
        case FieldDescriptor::TYPE_STRING:  
        case FieldDescriptor::TYPE_BYTES: 
        	{
		        tmp_string.clear();
                tmp_string.append("\"").append(reflection->GetString(msg, goal_field)).append("\"");
                judge = AppendTmpString2(pb2jsonstring,tmp_string,judge);

                //
                // tmp_string.clear();
                // tmp_string.append(reflection->GetString(msg, goal_field));
                // if( judge!=0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append(",").append(tmp_string);                    
                // }
                // else if( judge==0 && tmp_string.length()!=0)
                // {                    
                //     pb2jsonstring.append(tmp_string);
                //     judge = 1;
                // }
                //
        	}
            break; 
        case FieldDescriptor::TYPE_DOUBLE:  
	        {
                tmp_string.clear();
                tmp_string.append(std::to_string(reflection->GetDouble(msg, goal_field)));
                judge = AppendTmpString2(pb2jsonstring,tmp_string,judge);

               //
                // tmp_string.clear();
                // tmp_string.append(std::to_string(reflection->GetDouble(msg, goal_field)));
                // if( judge!=0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append(",").append(tmp_string);                    
                // }
                // else if( judge==0 && tmp_string.length()!=0)
                // {                    
                //     pb2jsonstring.append(tmp_string);
                //     judge = 1;
                // }
                //
	        }           
            break; 
        case FieldDescriptor::TYPE_ENUM:
		    {
		       tmp_string.clear();
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

                judge = AppendTmpString2(pb2jsonstring,tmp_string,judge);

                //
                // if( judge!=0 && tmp_string.length()!=0)
                // {
                //     pb2jsonstring.append(",").append(tmp_string);
                    
                // }
                // else if( judge==0 && tmp_string.length()!=0)
                // {                    
                //     pb2jsonstring.append(tmp_string);
                //     judge = 1;
                // }
                //
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

