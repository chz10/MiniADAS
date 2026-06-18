# MiniADAS-CPP

基于 C++17 的 ADAS 感知目标离线评测与可视化系统。

本项目为 C++ 工程项目，可用于 ADAS 感知结果离线评测：读取 GT 真值与 Detection 检测结果，通过 IoU、类别、置信度等规则完成目标匹配，输出 TP、FP、FN、Precision、Recall 等指标，并逐步加入 CSV 导出、OpenCV 可视化、批量处理、多线程、配置、日志和单元测试。

## 当前版本

`v0.4` GT 文件解析版。

已完成：

- CMake 工程初始化；
- 基础目录结构；
- `main.cpp` 可编译运行；
- 默认配置文件；
- 14 天排期文档；
- `BBox`、`ObjectInfo`、`FrameData`、`MatchResult` 核心数据结构；
- `BBox` 面积、合法性、交集面积、并集面积、IoU 计算；
- GT CSV 文件解析、非法行跳过、按帧组织目标数据。

## 版本记录

### v0.4 - GT 文件解析版

- 新增 `GTParser`，支持读取 GT CSV 文件；
- 将合法 GT 数据转换为 `ObjectInfo`；
- 按 `frame_id` 聚合为 `FrameData`；
- 跳过字段数量错误、类型转换失败、非法目标框等异常行；
- 添加 `data/gt/sample_gt.csv` 作为解析验证样例。

### v0.3 - IoU 基础算法版

- 完善 `BBox` 几何计算能力；
- 新增交集面积、并集面积、IoU 计算；
- 覆盖完全重合、部分重叠、无交集、非法框等基础场景；
- 在 `main.cpp` 中加入临时断言验证，为后续 GoogleTest 测试做准备。

### v0.2 - 核心数据结构版

- 新增 `BBox`，用于描述 2D 目标框；
- 新增 `ObjectInfo`，用于描述单个目标的帧号、ID、类别、置信度、距离和框信息；
- 新增 `FrameData`，用于按帧组织目标列表；
- 新增 `MatchResult`，用于描述 TP、FP、FN、ClassError 等匹配结果。

### v0.1 - 基础工程版

- 初始化 CMake 工程；
- 创建 `include/`、`src/`、`tests/`、`config/`、`data/`、`docs/` 等基础目录；
- 添加可运行的 `main.cpp`；
- 添加默认配置文件和项目排期文档；
- 完成本地 Git 初始化与 GitHub 仓库绑定。

## 构建方式

```bash
cmake -S . -B build
cmake --build build
./build/mini_adas_eval
```

## VS Code 调试

项目已提供 `.vscode/launch.json` 和 `.vscode/tasks.json`。在 VS Code 中选择 `Debug MiniADAS`，按 `F5` 即可先执行 CMake Debug 构建，再启动 `build/mini_adas_eval` 调试。

## 目录结构

```text
MiniADAS-CPP/
├── CMakeLists.txt
├── README.md
├── config/
├── data/
├── docs/
├── include/
├── output/
├── scripts/
├── src/
└── tests/
```
