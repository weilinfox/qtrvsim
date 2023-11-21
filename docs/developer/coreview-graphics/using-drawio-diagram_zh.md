# 使用 .drawio 图表

为了更容易操作， coreview 图表是使用图表工具 [diagrams.net](https://app.diagrams.net) ，以前叫 __draw.io__ ，创建的。
这足够在浏览器中使用，不过也有可安装的版本。

## 准备您的工作空间

在开始并打开图表之前，你需要在 `Extra`/`Plugins...` 菜单中启用一些插件。你会需要 `tags` 插件，选择它并重启 app 。

你会需要从 `Extras` 菜单中启用 `Tabs` 和 `Hidden Tabs` 。我还建议在 view 中启用 `Layers` 工具。

## 导出

现在你需要导出 3 个 SVG 文件。

在 `Tags` 窗口中，清空区域并点击 `Hide` ，所有东西都会消失。然后输出 `simple` 并点击 show 。它将只显示标记为 simple 的组
件。不要点击 `File`/`Export as...`/`SVG...` 。反选 `include a copy of diagram` 选项和 git export 。保存为 `simple.svg`
到 `device` 并移动到项目目录 (`src/gui/core`)。点击 hide 并为其他版本重复此步骤（当前是 `simple` 、 `pipeline` 和
 `forwarding` ）。

## 编辑

你可以从设备中或从 GitHub 载入图表。从设备载入是被推荐的，因为这样不会建立许多无用的提交。我使用的所有形状都在[我的 GitHub](https://github.com/jdupak/Diagrams.net-CPU-scheme-kit)
上。你可以从 `File`/`Open library from` 打开它。如果您需要写入访问权限，请建立 issue 。

编辑器本身相当直观，因此这里只介绍特殊功能和亮点：

- 在使用文本时，请确保已禁用格式化文本选项。它将使用 SVG 外部对象，这在大部分简单的渲染器和解释器不被支持。该选项位于
  右侧文本选项卡的中间位置。
- 如果需要确保某些元素在生成的 SVG 中位于其他元素内，你必须使用 `Custom element` 。否则 SVG 将被扁平化。目前，这就是
  缓存的工作方式。在样式选项卡中，您可以通过 `edit shape` 按钮查看它。确保选择的是元素而不是某个组。你可以在 `Arrange`
  /`Insert`/`Shape...` 中创建新的。该语言类似于 SVG 但是并不相同，可以在这里找到文档：
  [https://www.diagrams.net/doc/faq/shape-complex-create-edit](https://www.diagrams.net/doc/faq/shape-complex-create-edit) ，
  完整的语言参考在这里： [https://jgraph.github. io/mxgraph/docs/stencils.xsd](https://jgraph.github.io/mxgraph/docs/stencils.xsd)。
  这是缓存的代码：
  ```xml
    <shape name="cache" h="50" w="60" aspect="fixed" strokewidth="inherit">
      <background>
        <roundrect x="0" y="0" w="60" h="50" arcsize="2" />
      </background>
      <foreground>
        <fillstroke />
        <fontsize size="6" />
        <fontstyle style="1" />
        <fontfamily family="sans-serif" />
        <text str="Cache" x="30" y="10" align="center" />
        <text str="Hit:" x="5" y="25" align="left" />
        <text str="Miss:" x="5" y="34" align="left" />
        <text str="0" x="20" y="25" align="left" />
        <text str="0" x="25" y="34" align="left" />
      </foreground>
    </shape>
  ```
- 具有动态值的组件是在上下文菜单 (`CTRL+M`) 中的 `Edit data` 。示例（在这里使用 json ）：
  ```json
    {
      "component": "instruction-value",
      "source": "decode"
    }
  ```
  组件在 `src/gui/coreview/scene.cpp` 中处理，在 `src/gui/coreview/domponents` 中定义，数据绑定（源属性）在
  `src/gui/coreview/data.h` 中控制
  ![](./media/data.png).
- 在上下文菜单中的 `Edit link...` 选项，你可以创建超链接，双击这些链接可以打开 gui 的一些部分。使用 `src/gui/coreview/
  data.h` 中的表格连接 `CoreViewScene` 信号。为了控制给定元素以某种变体出现，你可以使用 gui 工具 `Edit data` 中的 `tags` ，
  它在 `Extras`/`Hidden tags...` 中
  ![](./media/tags.png).
