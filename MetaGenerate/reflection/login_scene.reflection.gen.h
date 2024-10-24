#pragma once
#include "..\SandBox\include\login_scene.h"

class LoginScene;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeLoginSceneOperator{
    public:
        static const char* getClassName(){ return "LoginScene";}
        static void* constructorWithJson(const Json& json_context){
            LoginScene* ret_instance= new LoginScene;
            Serializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::Write(*(LoginScene*)instance);
        }
        // base class
        static int getLoginSceneBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(Component,static_cast<LoginScene*>(instance));
            }
            return count;
        }
        // fields
        

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_LoginScene(){
        

        
        
        
        ClassFunctionTuple* class_function_tuple_LoginScene=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeLoginSceneOperator::getLoginSceneBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeLoginSceneOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeLoginSceneOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("LoginScene", class_function_tuple_LoginScene);
    }
namespace TypeWrappersRegister{
    void LoginScene()
    {
        TypeWrapperRegister_LoginScene();
    }
}//namespace TypeWrappersRegister

}//namespace Reflection


