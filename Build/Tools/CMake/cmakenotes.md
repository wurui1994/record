glut32.dll被cmake搜索到会和其他的冲突

## 使用cmake将文件打包为7z格式:
```sh
cmake -E tar "cf" "package.7z" --format=7zip -- "package_dir_or_file"
cmake -E tar "cf" "package.7z" --format=7zip -- "package_dir/"
```

ref:https://github.com/Microsoft/vcpkg/blob/master/toolsrc/src/vcpkg/export.cpp
```cpp
static fs::path do_archive_export(const VcpkgPaths& paths,
                                    const fs::path& raw_exported_dir,
                                    const fs::path& output_dir,
                                    const ArchiveFormat& format);
```
