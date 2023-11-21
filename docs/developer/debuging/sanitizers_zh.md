# 运行时检查器

## 在项目中使用检查器

所有 debug 构建默认使用地址和未定义的运行时检查器进行构建。若要禁用他们（强烈
不建议），使用 none 选项运行 cmake 。

```shell
cmake -DSANITIZERS=none
```

要以其他选项运行检查器，向命令传入冒号分隔的列表。

```shell
cmake -DSANITIZERS=memory,undefined
```

备注：一些检查器不能一起使用，比如 address 和 memory 。

### 检查器调试信息和 Clang

如果您将检查器和 clang 一起使用，且看不到文件和行号，请确保 `llvm-symbolizer` 已
经被安装，若这依然无法解决问题，添加 `ASAN_SYMBOLIZER_PATH=` 环境变量，将其指向
你检查器二进制的路径。在大部分时候，在 `PATH` 中包含该路径就足够了。

