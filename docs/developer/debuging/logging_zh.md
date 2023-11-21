# Logging

项目使用 Qt 日志框架。 快速了解，请参阅[这个 KDAB 演示](https://www.kdab.com/wp-content/uploads/stories/slides/Day2/KaiKoehne_Qt%20Logging%20Framework%2016_9_0.pdf)。

添加下列代码片段以在 `cpp` 中启用日志记录

```c++
#include "common/logging.h"

LOG_CATEGORY("<project>.<file/class>");
```

这会在作用域中创建一个类别对象并启用对 `DEBUG` `LOG` `WARN` 和 `INFO` 日志宏的无缝使用。如果需要在头文件中使用日志记录，
请仅在局部范围内调用 `LOG_CATEGORY` 宏，以避免干扰源文件中的日志类别。

调试日志旨在提供详细的信息，应默认隐藏并仅在当前调试的类别中启用。调试日志在所有 `release` 版本中都将被移除。

## 使用日志

Qt 同时支持 C++ 流和类似 `printf` 的接口. **在这个项目中，应仅使用 `printf` 风格的日志。** 日志被视为文档的一部分，而流的
阅读过于困难。唯一的例外是与使用的库兼容（当前是 *svgscene*）。

若要打印任何 Qt 类型，使用 `qPrintable` 宏将其包装。

**示例：**

```
QT_LOGGING_CONF=/data/Dev/school/QtRvSim/qtlogging.ini;
```

```cpp
DEBUG("Link triggered (href: %s).", qPrintable(getTargetName()));
```

## 配置日志

要过滤显示的日志，请修改位于项目根目录的 `qtlogging.ini`  文件。如果未自动找到此配置，请使用 `QT_LOGGING_CONF` 环境变量。

**示例：**

```shell
QT_LOGGING_CONF=/data/Dev/school/QtRvSim/qtlogging.ini
```

**配置示例** （只从 `instruction.cpp` 显示 debug 日志）：

```ini
[Rules]
*.debug=false
machine.Instruction.debug=true
```
