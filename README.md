# MiniADAS-CPP

基于 C++17 的 ADAS 感知目标离线评测与可视化系统。

本项目为 C++ 工程项目，可用于 ADAS 感知结果离线评测：读取 GT 真值与 Detection 检测结果，通过 IoU、类别、置信度等规则完成目标匹配，输出 TP、FP、FN、Precision、Recall 等指标，并逐步加入 CSV 导出、OpenCV 可视化、批量处理、多线程、配置、日志和单元测试。

## 当前版本

`v0.3` IoU 基础算法版。

已完成：

- CMake 工程初始化；
- 基础目录结构；
- `main.cpp` 可编译运行；
- 默认配置文件；
- 14 天排期文档；
- `BBox`、`ObjectInfo`、`FrameData`、`MatchResult` 核心数据结构；
- `BBox` 面积、合法性、交集面积、并集面积、IoU 计算。

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
