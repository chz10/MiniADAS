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

## Day 2 - Core Data Structures

目标：

- 实现 `BBox`；
- 实现 `ObjectInfo`；
- 实现 `FrameData`；
- 实现 `MatchResult`；
- 更新 `main.cpp` 验证核心结构可以正常包含和使用。

完成情况：

- [x] 添加 `include/core/BBox.hpp`；
- [x] 添加 `include/core/ObjectInfo.hpp`；
- [x] 添加 `include/core/FrameData.hpp`；
- [x] 添加 `include/core/MatchResult.hpp`；
- [x] 更新 README 当前版本；
- [x] CMake 构建通过；
- [x] 提交中文 commit 并推送 GitHub。

验证命令：

```bash
cmake --build build
./build/mini_adas_eval
```

## Day 3 - BBox Geometry and IoU

目标：

- 完善 `BBox` 的几何计算能力；
- 实现无交集、非法框、完全重合、部分重叠场景的 IoU 计算；
- 在 `main.cpp` 中加入临时断言验证，后续迁移到 GoogleTest。

完成情况：

- [x] 实现 `BBox::intersectionArea`；
- [x] 实现 `BBox::unionArea`；
- [x] 实现 `BBox::iou`；
- [x] 验证宽度、高度、面积、合法性判断；
- [x] 验证完全重合、无交集、非法框、部分重叠 IoU；
- [x] 更新 README 当前版本；
- [x] CMake 构建通过；
- [x] 提交中文 commit 并推送 GitHub。

验证命令：

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/mini_adas_eval
```

## Day 4 - GT CSV Parser

目标：

- 实现 `GTParser`；
- 支持读取 GT CSV 文件；
- 将合法行转换为 `ObjectInfo`；
- 按 `frame_id` 聚合为 `FrameData`；
- 跳过非法行并统计解析数量。

完成情况：

- [x] 添加 `include/parser/GTParser.hpp`；
- [x] 添加 `src/parser/GTParser.cpp`；
- [x] 添加 `data/gt/sample_gt.csv`；
- [x] 支持 header 和空行跳过；
- [x] 支持字段数量、类型转换、非法 bbox 容错；
- [x] 更新 README 当前版本和版本记录；
- [x] CMake 构建通过；
- [x] 提交中文 commit 并推送 GitHub。

验证命令：

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/mini_adas_eval
```
