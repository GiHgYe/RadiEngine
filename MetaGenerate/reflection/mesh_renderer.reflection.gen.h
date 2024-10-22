#pragma once
#include "..\ReCore\include\renderer\mesh_renderer.h"

class MeshRenderer;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeMeshRendererOperator{
    public:
        static const char* getClassName(){ return "MeshRenderer";}
        static void* constructorWithJson(const Json& json_context){
            MeshRenderer* ret_instance= new MeshRenderer;
            Serializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::Write(*(MeshRenderer*)instance);
        }
        // base class
        static int getMeshRendererBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(Component,static_cast<MeshRenderer*>(instance));
            }
            return count;
        }
        // fields
        

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_MeshRenderer(){
        

        
        
        
        ClassFunctionTuple* class_function_tuple_MeshRenderer=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeMeshRendererOperator::getMeshRendererBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeMeshRendererOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeMeshRendererOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("MeshRenderer", class_function_tuple_MeshRenderer);
    }
namespace TypeWrappersRegister{
    void MeshRenderer()
    {
        TypeWrapperRegister_MeshRenderer();
    }
}//namespace TypeWrappersRegister

}//namespace Reflection


