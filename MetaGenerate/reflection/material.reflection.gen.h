#pragma once
#include "..\ReCore\include\renderer\material.h"

class Material;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeMaterialOperator{
    public:
        static const char* getClassName(){ return "Material";}
        static void* constructorWithJson(const Json& json_context){
            Material* ret_instance= new Material;
            Serializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::Write(*(Material*)instance);
        }
        // base class
        static int getMaterialBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(Component,static_cast<Material*>(instance));
            }
            return count;
        }
        // fields
        

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_Material(){
        

        
        
        
        ClassFunctionTuple* class_function_tuple_Material=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeMaterialOperator::getMaterialBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeMaterialOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeMaterialOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("Material", class_function_tuple_Material);
    }
namespace TypeWrappersRegister{
    void Material()
    {
        TypeWrapperRegister_Material();
    }
}//namespace TypeWrappersRegister

}//namespace Reflection


