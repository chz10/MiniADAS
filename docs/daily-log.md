# Daily Log

## Day 1 - Project Initialization

目标：

- 创建 Git 仓库；
- 创建 CMake 工程；
- 创建 `include/`、`src/`、`tests/` 等目录；
- 保证空项目可编译运行。

完成情况：

- [x] 创建项目目录结构；
- [x] 添加 `CMakeLists.txt`；
- [x] 添加 `src/main.cpp`；
- [x] 添加默认 `config/config.json`；
- [x] 整理 14 天排期；
- [x] 初始化 Git 仓库并完成本地 Day 1 commit；
- [ ] 绑定 GitHub 远端并推送。

验证命令：

```bash
cmake -S . -B build
cmake --build build
./build/mini_adas_eval
```
