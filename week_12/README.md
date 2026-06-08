# MCP 工具：代码质量分析器（实验提交版）

## 1. 实验要求对应

根据课件“课后实验”要求：使用 Model Context Protocol（MCP）SDK 构建一个自定义 MCP 工具，并接入一个 LLM Host（如 WorkBuddy / Claude Code / Cursor）。

本项目实现了一个 **MCP Server**：`code_analyzer_server.py`，对外暴露 3 个 Tools：

- `analyze_file(file_path, metrics="all")`：分析单文件（行数、函数/类结构、复杂度、imports）
- `scan_directory(directory_path, extensions=..., max_files=2000)`：扫描目录内代码文件概览
- `compare_files(file_a, file_b)`：对比两个文件结构差异

## 2. 安装依赖

**要求 Python >= 3.10**

```bash
pip install "mcp[cli]"
```

（建议在 venv/uv 环境中安装。macOS 系统自带 Python 3.9 无法安装，可使用 Anaconda Python 3.12：`/opt/anaconda3/bin/pip install "mcp[cli]"`）

## 3. 本地运行（用于自测）

```bash
# 使用 Python 3.10+（如 Anaconda Python）
/opt/anaconda3/bin/python3.12 code_analyzer_server.py
```

一般情况下不需要手动运行；Host 会按配置自动启动该子进程并通过 stdio 通信。

## 4. 接入 Host（示例配置）

同目录提供 `mcp.json` 示例：

1. 把 `mcp.json` 放到你的 Host 约定的位置（或在 Host 的 MCP 配置界面中粘贴其内容）
   - WorkBuddy: `~/.workbuddy/mcp.json`
   - Claude Code: `~/.claude/mcp.json` 或项目根目录 `.mcp.json`
   - Cursor: 在 Cursor Settings → MCP 中添加
2. 将 `command` 改为你机器上的 Python 3.10+ 路径，`args` 中的路径改为 `code_analyzer_server.py` 的绝对路径
3. 重启/刷新 Host，应该能看到 `code-analyzer` 工具组

## 5. 使用示例（给 LLM 的自然语言提示）

- “帮我分析这个文件的复杂度和 imports：/path/to/app.py”
- “扫描这个项目目录有哪些主要语言文件：/path/to/repo”
- “对比这两个文件结构差异：/path/a.py 和 /path/b.py”

