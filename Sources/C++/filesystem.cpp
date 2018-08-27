// g++ pwd.cpp -lstdc++fs
#ifdef WIN32
#define _CRT_SECURE_NO_WARNINGS 1
#endif
#include <iostream>
#include <fstream>
#include <chrono>
#include <experimental/filesystem>

using namespace std::experimental::filesystem::v1;

namespace fs = std::experimental::filesystem;

void demo_perms(fs::perms p)
{
	std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
		<< ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
		<< ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
		<< ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
		<< ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
		<< ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
		<< ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
		<< ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
		<< ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
		<< '\n';
}

int main(int argc, char*argv[])
{
	std::cout << "Current path is " << current_path() << '\n';
	std::cout << "Free space is " << space("/").capacity / (1 << 30) << '\n';
	std::cout << std::boolalpha << exists(path(argv[0])) << std::endl;
	std::cout << "File size is " << file_size(path(argv[0])) << std::endl;
	demo_perms(fs::status(argv[0]).permissions());

	fs::path p = fs::path("..") / ".." / "..";
	std::cout << "Current path is " << fs::current_path() << '\n'
		<< "Canonical path for " << p << " is " << fs::canonical(p) << '\n';

	fs::path p2 = argv[0];
	std::cout << "Current path is " << fs::current_path() << '\n'
		<< "Absolute path for " << p2.filename() << " is " << fs::absolute(p2) << '\n'
		<< "System complete path for " << p2.filename() << " is " << fs::system_complete(p2) << '\n';

	std::cout << "The current path " << p2 << " decomposes into:\n"
		<< "root name " << p2.root_name() << '\n'
		<< "root directory " << p2.root_directory() << '\n'
		<< "relative path " << p2.relative_path() << '\n'
		<< "root path " << p2.root_path() << '\n'
		<< "path stem " << p2.stem() << '\n'
		<< "Extension is " << p2.extension() << '\n'
		<< "parent path " << p2.parent_path() << '\n';

	std::cout << "List parent path:" << std::endl;
	for (fs::directory_entry const& p : fs::directory_iterator(p2.parent_path()))
		std::cout << p << '\n';

	fs::create_directories("sandbox/dir/subdir");
	std::ofstream("sandbox/file1.txt").put('a');
	fs::copy("sandbox/file1.txt", "sandbox/file2.txt"); // 复制文件
	fs::copy("sandbox/dir", "sandbox/dir2"); // 复制目录（非递归）
											 // sandbox 保有 2 个文件及 2 个目录，其中之一拥有子目录
											 // sandbox/file1.txt
											 // sandbox/file2.txt
											 // sandbox/dir2
											 // sandbox/dir
											 //    sandbox/dir/subdir
											 //fs::copy("sandbox", "sandbox/copy", fs::copy_options::recursive);
											 //error:recursive copy 
											 //It's OK.
	fs::copy("sandbox", "copy", fs::copy_options::recursive);
	fs::rename("copy", "sandbox/copy");
	std::cout << "Recursive List Directory:" << std::endl;
	for (auto& p : fs::recursive_directory_iterator("sandbox"))
		std::cout << p << '\n';
	// sandbox/copy 保有上述文件和子目录的副本
	fs::remove_all("sandbox");

	//setlocale(LC_ALL, "");
	auto ftime = fs::last_write_time(argv[0]);

	std::time_t cftime = decltype(ftime)::clock::to_time_t(ftime); // 假定 system_clock
																   //std::cout << "File write time is " << std::asctime(std::localtime(&cftime)) << '\n';
	std::cout << "File write time is " << std::ctime(&cftime) << '\n';
}