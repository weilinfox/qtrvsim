# 构建和部署模拟器的 WebAssembly 版本

## 起步阶段

WASM 版本是由 GitHub actions 自动构建的。构建结果文件可以在 `Actions`/`<detail of build you want to use>` 的 `Artifacts`
部分找到文件 `target-wasm-Linux-qtx.xx.x`。下载这个文件并跳到部署章节。详细的构建流程可以在 `.github/workflows/cmake.yml`
找到。

## 起步阶段 2

安装 `emsdk` 和 `aqt` （详细内容见下）。

使用项目根目录中准备好的辅助 make 工具。

```shell
make wasm # build
make wasm-clean # clean wasm build
make wasm-clean-deap # also clean cached external libraries - when changing compile settings, of when it just does not work ;)
make wasm-install-qt # install appropriate qt for wasm using aqt
```

这些命令的行为已在 `.dev-config.local.mk` 中根据本地系统进行了定制。该文件以模板形式提供，进一步的更改将被忽略。

## 依赖

- WASM compiler (Emscripten/EMSDK)
- WASM compiled Qt
- bash compatible shell (not fish, unfortunately)

步骤：

- 安装 `emsdk` 工具包。仅安装 Emscripten 编译器可能可行，但我不建议这样做。
- 选择工具包的版本并运行 `emsdk activate <version>`。只要所有组件都是与兼容版本一起编译的，您可以自由选择版本。Qt5 分发版本是
  使用版本 `1.39.8` 构建的。一些发行版提供了像 `qt5-wasm` 这样的软件包。必须使用相同的工具链编译项目，否则可能无法链接。
- 根据 activate 命令的输出建议，引用工具包。
- 下载或编译 Qt 为 wasm 。通常的做法是将其存储在 `/opt/` 。我使用了一个非官方的 Qt 下载器 [`aqtinstall`](https://pypi.org/project/aqtinstall/).
  - `python -m aqt install 5.12.2 linux desktop wasm_32 --outputdir "/opt/qt"`

## 构建

- 进入构建目录（我使用 `build/wasm` ）并运行（根据需要替换路径并使用您喜欢的构建系统）：
  ```shell
  emcmake cmake ../..
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_PREFIX_PATH=/opt/qt/5.13.1/wasm_32/ 
        -DCMAKE_FIND_ROOT_PATH=/opt/qt/5.13.1/wasm_32/ -Wno-dev -G Ninja
  ```
- 将生成的 `.js` 和 `.wasm` 文件以及 `data/wasm` 中的所有内容到 `target/wasm` 。其中包含加载器脚本、图标和其他支持文件。

## 部署

- 将 `target/wasm` 中的文件移动到 Web 狐务器。完工。
- 备注：由于 CORS 的缘故， Web 狐务器必须使用。

## 技巧

### Fish and co.

如果你希望使用不兼容 bash 的 shell ，运行 bash ，引用文件，然后以 bash 的环境运行 shell 。
