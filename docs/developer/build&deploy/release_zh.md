# 发布流程

- 检查根目录中 `CMakeLists.txt` 的版本
- 更新 debian changelog
- 确保 CMake 配置了 `-DDEV_MODE=true` 以启用打包工具。若没有传入这个选项， CMake 将不会尝试执行任何需要外部工具的操
  作
- 运行 `make open_build_service_bundle`
- 部署 `<build_dir>/target/pkg` 中的内容到 Open Build Service （和 Launchpad）

## Debian changelog

Debian changelog 具有非常严格（甚至有点奇怪的）格式要求。 Bash 脚本 `extras/packaging/add-to-changelog.sh <version>`
会在 changelog 中生成一个新的条目并在 `$EDITOR` 中打开它。！小心！地编辑它，格式是脆弱的。在那之后，更改被提交， git
 tag 也将被更新。

### TODO

- 拒绝，这是否应使用 CMake 替代
- 从 CMake 中获取版本

## `open_build_service_bundle` 目标

在配置时，与包相关的文件会从 CMake 获取最新的信息（变量以 `PACKAGE_` 为前缀）并复制到
`<executable output directory>`/`pkg` 目录。这个目标将源代码打包成 `tar.xz` 文件并更新包文件中的哈希值。

### 使用 GitHub Actions (CI) 生成

在 GitHub 仓库页面上，转到 Actions 选项卡，并在左侧菜单中选择 Release 。

![](./media/obs-ci-step-1.png)

点击 `run workflow` 并选择一个分支。

![](./media/obs-ci-step-2.png)

一旦工作流程完成，包将在 artifacts 部分找到，将这个包上传到 OBS 。

![](./media/obs-ci-step-3.png)

### TODO

- 对包进行签名

## Open Build Service

部署文件到 OBS 最简单的方式就是使用 `osc` 命令行工具。

- 配置凭据，首次运行 `osc` 它会指导你进行
- 下载这个仓库

```shell
osc co home:jdupak qtrvsim
```

- 复制文件到 `home:jdupak`/`qtrvsim`.
- 添加文件以追踪（在 `qtrvsim` 目录中）：

```shell
osc addremove *
```

- 提交变更并 push

```shell
osc commit
```

- 如果有什么出错了，删除目录并从头开始

