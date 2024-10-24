#include <chrono>
#include <iostream>
#include "meta_parser/parser/parser.h"

int main() {
	auto start_time = std::chrono::system_clock::now();

	bool is_show_error = true;

	MetaParser parser(
		"../../",								    // 搜索目录
		"../../MetaGenerate/source_include_file.h",		// 收集需要生成Meta文件的头文件
		"../../MetaGenerate;"								// Meta生成位置
			"../../ReCore/include;"						// 工作目录
			"../../Dependencies/json11/include;"
			"../../Dependencies/assimp/include;"
			"../../Dependencies/GLFW/include;"
			"../../Dependencies/lua/include;"
			"../../Dependencies/mustache/include;"
			"../../Dependencies/glad/include;"
			"../../Dependencies/freetype/include;"
			"../../Dependencies/spdlog/include;"
		,
		"*",
		is_show_error
	);

	parser.Parse();
	parser.GenerateFiles();

	auto duration_time = std::chrono::system_clock::now() - start_time;

	std::cout << "Completed in " << std::chrono::duration_cast<std::chrono::milliseconds>(duration_time).count() << "ms" << std::endl;

	return 0;
}