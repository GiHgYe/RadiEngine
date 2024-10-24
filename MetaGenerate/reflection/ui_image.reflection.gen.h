#pragma once
#include "..\ReCore\include\ui\ui_image.h"

class UIImage;
namespace Reflection{
namespace TypeFieldReflectionOparator{
    class TypeUIImageOperator{
    public:
        static const char* getClassName(){ return "UIImage";}
        static void* constructorWithJson(const Json& json_context){
            UIImage* ret_instance= new UIImage;
            Serializer::Read(json_context, *ret_instance);
            return ret_instance;
        }
        static Json writeByName(void* instance){
            return Serializer::Write(*(UIImage*)instance);
        }
        // base class
        static int getUIImageBaseClassReflectionInstanceList(ReflectionInstance* &out_list, void* instance){
            int count = 1;
            out_list = new ReflectionInstance[count];
            for (int i=0;i<count;++i){
               out_list[i] = TypeMetaDef(Component,static_cast<UIImage*>(instance));
            }
            return count;
        }
        // fields
        

        // methods
        
    };
}//namespace TypeFieldReflectionOparator


    void TypeWrapperRegister_UIImage(){
        

        
        
        
        ClassFunctionTuple* class_function_tuple_UIImage=new ClassFunctionTuple(
            &TypeFieldReflectionOparator::TypeUIImageOperator::getUIImageBaseClassReflectionInstanceList,
            &TypeFieldReflectionOparator::TypeUIImageOperator::constructorWithJson,
            &TypeFieldReflectionOparator::TypeUIImageOperator::writeByName);
        REGISTER_BASE_CLASS_TO_MAP("UIImage", class_function_tuple_UIImage);
    }
namespace TypeWrappersRegister{
    void UiImage()
    {
        TypeWrapperRegister_UIImage();
    }
}//namespace TypeWrappersRegister

}//namespace Reflection


