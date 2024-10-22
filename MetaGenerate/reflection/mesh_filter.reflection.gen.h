#pragma once
#include "..\ReCore\include\renderer\mesh_filter.h"

class MeshFilter;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeMeshFilterOperator{
    public:
        static const char* getClassName(){ return "MeshFilter";}
        static void* constructorWithJson(const Json& json_context){
            MeshFilter* ret_instance= new MeshFilter;
            Serializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::Write(*(MeshFilter*)instance);
        }
        // base class
        static int getMeshFilterBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(Component,static_cast<MeshFilter*>(instance));
            }
            return count;
        }
        // fields
        

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_MeshFilter(){
        

        
        
        
        ClassFunctionTuple* class_function_tuple_MeshFilter=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeMeshFilterOperator::getMeshFilterBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeMeshFilterOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeMeshFilterOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("MeshFilter", class_function_tuple_MeshFilter);
    }
namespace TypeWrappersRegister{
    void MeshFilter()
    {
        TypeWrapperRegister_MeshFilter();
    }
}//namespace TypeWrappersRegister

}//namespace Reflection


