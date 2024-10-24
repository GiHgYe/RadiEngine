#pragma once
#include "..\ReCore\include\renderer\camera.h"

class Camera;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeCameraOperator{
    public:
        static const char* getClassName(){ return "Camera";}
        static void* constructorWithJson(const Json& json_context){
            Camera* ret_instance= new Camera;
            Serializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::Write(*(Camera*)instance);
        }
        // base class
        static int getCameraBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(Component,static_cast<Camera*>(instance));
            }
            return count;
        }
        // fields
        

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_Camera(){
        

        
        
        
        ClassFunctionTuple* class_function_tuple_Camera=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeCameraOperator::getCameraBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeCameraOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeCameraOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("Camera", class_function_tuple_Camera);
    }
namespace TypeWrappersRegister{
    void Camera()
    {
        TypeWrapperRegister_Camera();
    }
}//namespace TypeWrappersRegister

}//namespace Reflection


