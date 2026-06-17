# MiniADAS-CPP

基于 C++17 的 ADAS 感知目标离线评测与可视化系统。

本项目计划在 14 天内完成一个可放入 GitHub 和简历展示的 C++ 工程项目：读取 GT 真值与 Detection 检测结果，通过 IoU、类别、置信度等规则完成目标匹配，输出 TP、FP、FN、Precision、Recall 等指标，并逐步加入 CSV 导出、OpenCV 可视化、批量处理、多线程、配置、日志和单元测试。

## 当前版本

`v0.1` 基础工程版。

已完成：

- CMake 工程初始化；
- 基础目录结构；
- `main.cpp` 可编译运行；
- 默认配置文件；
- 14 天排期文档。

## 构建方式

```bash
cmake -S . -B build
cmake --build build
./build/mini_adas_eval
```

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

## 每日节奏

每天按照 `docs/schedule.md` 的交付物推进，并在当天结束前完成一次 Git 提交与 GitHub 推送。
