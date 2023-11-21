# 需要了解

**每个开发者都需要了解的关键信息。**

## Modal Windows, Dialogues, Message Boxes

在一个典型的、本地的 Qt 环境中，模态窗口在堆栈上分配并在打开时阻塞。为了管理模态窗口，Qt 启动第二个事件循环。然而，在
Web-Assembly 环境中，这在技术上是不可能的。*（这个问题可能在新的带有 "asyncify" 构建标志的 Qt 中解决，但在当前使用的
Qt 5.15.2 中不起作用）*

[Read more](http://qtandeverything.blogspot.com/2019/05/exec-on-qt-webassembly.html)

### 损坏的 API 调用

```cpp
QMessageBox msg;
msg.exec();
```

```cpp
QMessageBox::critical("Hello");
```

`.exec()` 方法和单行调用是典型的警告信号。

代码的一些部分使用了针对 Web-Assembly 的特殊代码（如 HTML 文件选择器），而本地部分可能使用阻塞解决方案。然而，在性能非
关键的部分（大多数对话框都属于此类部分），更倾向于使用统一的异步解决方案。

### 解决方法

模态窗口对象必须动态分配并使用异步方法 `open` 启动。对象的回应必须通过 `connect` 回调获得。

为了便于使用，在 `gui/helper/async_modal.h` 中准备了包装函数。

在打开之前，可以通过特殊回调 `msg->setAttribute(Qt::WA_DeleteOnClose)` 来实现释放，这个方法在 `async_modal.h` 中会自动
使用。

相关文档: [WA_DeleteOnClose](https://doc.qt.io/qt-5/qt.html#WidgetAttribute-enum)
, [QCloseEvent](https://doc.qt.io/qt-5/qcloseevent.html)
