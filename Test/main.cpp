#include <iostream>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include "model/model_loader.h"
#pragma comment(lib, "yaml-cpp.lib")
#pragma comment(lib, "assimp-vc143-mt.lib")
#pragma comment(lib, "glfw3.lib")
#include <glad.h>
#include <glfw3.h>
#include <reflection/all_reflection.h>
#include "math/math_headers.h"

using namespace std;

////Mesh�ļ�ͷ
//struct MeshFileHead {
//    char type_[4];
//    unsigned short vertex_num_;//�������
//    unsigned short vertex_index_num_;//��������
//};
//
////����Mesh�ļ�
//static void ExportMesh(string save_path) {
//    ofstream output_file_stream(save_path, ios::out | ios::binary);
//
//    MeshFileHead mesh_file_head;
//    mesh_file_head.type_[0] = 'm';
//    mesh_file_head.type_[1] = 'e';
//    mesh_file_head.type_[2] = 's';
//    mesh_file_head.type_[3] = 'h';
//    mesh_file_head.vertex_num_ = kVertexRemoveDumplicateVector.size();
//    mesh_file_head.vertex_index_num_ = kVertexIndexVector.size();
//    //д���ļ�ͷ
//    output_file_stream.write((char*)&mesh_file_head, sizeof(mesh_file_head));
//    //д�붥������
//    output_file_stream.write((char*)&kVertexRemoveDumplicateVector[0], kVertexRemoveDumplicateVector.size() * sizeof(Vertex));
//    //д����������
//    output_file_stream.write((char*)&kVertexIndexVector[0], kVertexIndexVector.size() * sizeof(unsigned short));
//    output_file_stream.close();
//}

GLFWwindow* window;
void init_opengl()
{
    glfwSetErrorCallback([](int error, const char* description) { fprintf(stderr, "GLFW Error %d: %s\n", error, description); });

    if (!glfwInit())
        throw std::runtime_error("Failed to init GLFW window");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(960, 640, "SandBox", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glfwSwapInterval(1);
    glViewport(0, 0, 960, 640);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* windowint, int width, int height) { glViewport(0, 0, width, height); });
}


int main()
{
    // ModelFileLoader loader{ "C:\\Users\\asus\\Desktop\\RenderCode\\GIRnder\\models\\bunny.obj" };
    //init_opengl();
    //ConvertImageFile("C:\\Users\\asus\\Desktop\\RenderCode\\GIRnder\\models\\floor\\checker.png", "../checker.cpt");
    
    
    Quaternion q = Quaternion::GetQuaternionFromEulerAngle({60, 70, 80});

    cout << q.GetPitch(false).ValueDegrees() << " " << q.GetYaw(false).ValueDegrees() << " " << q.GetRoll(false).ValueDegrees();

    return 0;
}

//static int OpenCv2()
//{
//	cv::VideoCapture capture;
//	capture.open(0);
//
//	cv::Mat frame;
//	while (true)
//	{
//		capture >> frame;
//		imshow("�������ͷ", frame);
//		if (cv::waitKey(30) >= 0)
//			break;
//	}
//	return 0;
//}
//
//static int pyRuntime() 
//{
//	// F:\\anaconda3\\envs\\torch_gpu
//	// I:\\Program Files\\Python-3.9.19_src\\Python-3.9.19\\PCbuild\\amd64
//	Py_SetPythonHome(L"F:\\anaconda3\\envs\\torch_gpu"); 
//	Py_Initialize();
//	if (!Py_IsInitialized())
//	{
//		printf("��ʼ��ʧ�ܣ�");
//		return -1;
//	}
//	else {
//		PyRun_SimpleString("import sys");
//		PyRun_SimpleString("sys.path.append('./')");
//		PyRun_SimpleString("print(sys.path)");
//		PyRun_SimpleString("print(__name__)");
//		PyObject* pModule = NULL;	//��������
//		PyObject* pFunc = NULL;		// ��������
//		pModule = PyImport_ImportModule("py"); // load py file
//		if (pModule == NULL)
//		{
//			std::cout << "û�ҵ���Python�ļ�" << std::endl;
//			return -1;
//		}
//		else {
//			pFunc = PyObject_GetAttrString(pModule, "add");		//������Ҫ���õĺ�����
//			PyObject* args = Py_BuildValue("(ii)", 28, 103);	//��python����������ֵ
//			PyObject* pRet = PyObject_CallObject(pFunc, args);	//���ú���
//			int res = 0;
//			PyArg_Parse(pRet, "i", &res);				//ת����������
//			std::cout << "res:" << res << std::endl;	//������
//		}
//		Py_Finalize();	//����Py_Finalize�������Py_Initialize���Ӧ�ġ�
//	}
//	return 1;
//}
