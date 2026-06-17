# Design Notes

## 数据流

```text
GT CSV + Detection CSV + Image/Video
  -> Parser
  -> FrameData
  -> ObjectMatcher
  -> Evaluator
  -> CSV Report + Visualization
```

## 模块规划

- `core`：`BBox`、`ObjectInfo`、`FrameData`、`MatchResult` 等基础模型；
- `parser`：GT 与 Detection CSV 解析；
- `matcher`：IoU、类别、置信度匹配策略；
- `evaluator`：文件级和批量统计；
- `visualizer`：OpenCV 可视化；
- `utils`：配置、日志、通用工具。

## 首期约束

- 第一版固定 CSV 格式；
- 第一版使用贪心匹配；
- OpenCV 失败不阻塞核心评测；
- 多线程结果由主线程统一汇总写出。
