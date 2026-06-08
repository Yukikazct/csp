#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
MCP 工具：代码质量分析器（课程实验版）

提供 3 个 tools：
  1) analyze_file     分析单文件（行数 / 函数结构 / 复杂度 / imports）
  2) scan_directory   扫描目录内的代码文件概览
  3) compare_files    对比两个文件的结构差异

依赖：
  pip install "mcp[cli]"

运行：
  python code_analyzer_server.py

接入（示例）：
  见同目录 mcp.json
"""

from __future__ import annotations

import ast
import json
import os
import re
from pathlib import Path
from typing import Any, Optional

from mcp.server.fastmcp import FastMCP


mcp = FastMCP(
    "code-analyzer",
    instructions=(
        "代码质量分析工具：用于分析单个代码文件的行数统计、函数/类结构、"
        "简化圈复杂度估计、以及导入依赖；也支持扫描目录与对比两个文件。"
    ),
    # 让 Host 直接拿到 JSON（dict/list）而不是纯文本
    json_response=True,
)


# -----------------------------------------------------------------------------
# Tool 1：analyze_file
# -----------------------------------------------------------------------------
@mcp.tool(
    description=(
        "分析单个代码文件的质量指标。"
        "metrics 支持：lines, functions, complexity, imports；传 all 表示全部。"
    )
)
def analyze_file(file_path: str, metrics: str = "all") -> dict[str, Any]:
    path = Path(file_path)
    if not path.exists():
        return {"error": f"文件不存在：{file_path}"}
    if not path.is_file():
        return {"error": f"路径不是文件：{file_path}"}

    content = _read_text_file(path)
    if content is None:
        return {"error": f"无法读取/解码文件：{file_path}"}

    ext = path.suffix.lower()
    lines = content.splitlines()

    metric_list = (
        ["lines", "functions", "complexity", "imports"]
        if metrics.strip().lower() == "all"
        else [m.strip().lower() for m in metrics.split(",") if m.strip()]
    )
    valid = {"lines", "functions", "complexity", "imports"}
    requested = [m for m in metric_list if m in valid]

    result: dict[str, Any] = {
        "file": str(path.resolve()),
        "extension": ext,
        "size_bytes": path.stat().st_size,
        "metrics": requested,
    }

    if "lines" in requested:
        result["lines"] = _analyze_lines(lines)

    functions: list[dict[str, Any]] = []
    if "functions" in requested or "complexity" in requested:
        functions = _extract_functions(content, ext)

    if "functions" in requested:
        result["functions"] = functions

    if "complexity" in requested:
        func_only = [f for f in functions if f.get("kind") in ("function", "async_function")]
        for fn in func_only:
            fn["cyclomatic_complexity"] = _estimate_complexity(fn.get("body", ""))

        result["function_complexities"] = [
            {"name": f.get("name"), "line": f.get("line"), "complexity": f.get("cyclomatic_complexity")}
            for f in func_only
        ]
        total = sum(int(f.get("cyclomatic_complexity") or 0) for f in func_only)
        result["total_complexity"] = total
        result["avg_complexity"] = round(total / len(func_only), 2) if func_only else 0

    if "imports" in requested:
        result["imports"] = _extract_imports(content, ext)

    return result


# -----------------------------------------------------------------------------
# Tool 2：scan_directory
# -----------------------------------------------------------------------------
@mcp.tool(
    description=(
        "扫描指定目录，统计常见代码文件的基本信息（路径、大小、行数概览）。"
        "可通过 extensions 指定扩展名（逗号分隔），并用 max_files 限制扫描数量。"
    )
)
def scan_directory(
    directory_path: str,
    extensions: str = ".py,.js,.ts,.jsx,.tsx,.java,.cpp,.h,.hpp,.cs,.go,.rs,.rb,.php,.swift,.kt,.scala",
    max_files: int = 2000,
) -> dict[str, Any]:
    root = Path(directory_path)
    if not root.exists():
        return {"error": f"目录不存在：{directory_path}"}
    if not root.is_dir():
        return {"error": f"路径不是目录：{directory_path}"}

    ext_list = [
        e.strip().lower() if e.strip().startswith(".") else f".{e.strip().lower()}"
        for e in extensions.split(",")
        if e.strip()
    ]

    skip_dirs = {
        "node_modules",
        ".git",
        "__pycache__",
        ".venv",
        "venv",
        ".idea",
        ".vscode",
        "build",
        "dist",
        ".next",
        ".nuxt",
        "target",
        "bin",
        "obj",
        ".workbuddy",
    }
    skip_dirs_lower = {d.lower() for d in skip_dirs}

    files: list[dict[str, Any]] = []
    total_bytes = 0
    scanned = 0

    try:
        for current_root, dirs, filenames in os.walk(root):
            dirs[:] = [d for d in dirs if d.lower() not in skip_dirs_lower]

            for filename in filenames:
                if scanned >= max_files:
                    break
                ext = os.path.splitext(filename)[1].lower()
                if ext not in ext_list:
                    continue
                full_path = Path(current_root) / filename
                scanned += 1

                try:
                    size = full_path.stat().st_size
                    total_bytes += size

                    content = _read_text_file(full_path)
                    line_info = _analyze_lines(content.splitlines()) if content is not None else None

                    files.append(
                        {
                            "relative_path": str(full_path.relative_to(root)),
                            "extension": ext,
                            "size_bytes": size,
                            "size_kb": round(size / 1024, 1),
                            "lines": line_info,
                        }
                    )
                except (OSError, PermissionError):
                    continue
            if scanned >= max_files:
                break
    except PermissionError:
        return {"error": f"无权限访问目录：{directory_path}"}

    by_ext: dict[str, int] = {}
    for f in files:
        by_ext[f["extension"]] = by_ext.get(f["extension"], 0) + 1

    return {
        "directory": str(root.resolve()),
        "max_files": max_files,
        "scanned_files": scanned,
        "matched_files": len(files),
        "total_size_kb": round(total_bytes / 1024, 1),
        "by_extension": [
            {"extension": ext, "count": count}
            for ext, count in sorted(by_ext.items(), key=lambda x: -x[1])
        ],
        "files": sorted(files, key=lambda x: -x["size_bytes"]),
    }


# -----------------------------------------------------------------------------
# Tool 3：compare_files
# -----------------------------------------------------------------------------
@mcp.tool(
    description="对比两个代码文件的结构差异（行数、函数/类数量、imports 数量、体积等）。"
)
def compare_files(file_a: str, file_b: str) -> dict[str, Any]:
    info_a = _quick_file_info(file_a)
    info_b = _quick_file_info(file_b)
    if not info_a or not info_b:
        missing = []
        if not info_a:
            missing.append(file_a)
        if not info_b:
            missing.append(file_b)
        return {"error": f"以下文件无法读取：{'、'.join(missing)}"}

    diff = {
        "size_bytes": info_b["size_bytes"] - info_a["size_bytes"],
        "total_lines": info_b["total_lines"] - info_a["total_lines"],
        "code_lines": info_b["code_lines"] - info_a["code_lines"],
        "comment_lines": info_b["comment_lines"] - info_a["comment_lines"],
        "blank_lines": info_b["blank_lines"] - info_a["blank_lines"],
        "func_count": info_b["func_count"] - info_a["func_count"],
        "class_count": info_b["class_count"] - info_a["class_count"],
        "import_count": info_b["import_count"] - info_a["import_count"],
    }

    return {
        "file_a": info_a,
        "file_b": info_b,
        "difference": diff,
        "summary": (
            f"文件 A「{Path(file_a).name}」vs 文件 B「{Path(file_b).name}」："
            f"B 比 A {'大' if diff['size_bytes'] >= 0 else '小'} {abs(diff['size_bytes'])} 字节；"
            f"代码行 {'多' if diff['code_lines'] >= 0 else '少'} {abs(diff['code_lines'])}；"
            f"函数 {'多' if diff['func_count'] >= 0 else '少'} {abs(diff['func_count'])}；"
            f"类 {'多' if diff['class_count'] >= 0 else '少'} {abs(diff['class_count'])}"
        ),
    }


# -----------------------------------------------------------------------------
# Helpers
# -----------------------------------------------------------------------------
def _read_text_file(path: Path) -> Optional[str]:
    try:
        return path.read_text(encoding="utf-8")
    except UnicodeDecodeError:
        try:
            return path.read_text(encoding="gbk")
        except Exception:
            return None
    except Exception:
        return None


def _analyze_lines(lines: list[str]) -> dict[str, Any]:
    total = len(lines)
    code = 0
    comments = 0
    blank = 0

    for line in lines:
        s = line.strip()
        if not s:
            blank += 1
            continue

        # 仅做“行级”粗略判断（多行注释块不做完整语法分析）
        if s.startswith(("#", "//", "/*", "*", "--", "%")):
            comments += 1
        else:
            code += 1

    return {
        "total_lines": total,
        "code_lines": code,
        "comment_lines": comments,
        "blank_lines": blank,
        "comment_ratio": f"{round(comments / max(total, 1) * 100, 2)}%",
    }


def _extract_functions(content: str, ext: str) -> list[dict[str, Any]]:
    if ext == ".py":
        return _extract_python_functions(content)

    functions: list[dict[str, Any]] = []
    patterns = [
        (r"(?:function\s+)?(\w+)\s*\([^)]*\)\s*\{", "function"),  # JS
        (r"(?:def|fun|func|fn)\s+(\w+)\s*\(", "function"),  # 多语言
        (
            r"(?:public|private|protected)?\s*(?:static\s+)?(\w+)\s*\([^)]*\)\s*(?:throws\s+\w+)?\s*\{",
            "method",
        ),  # Java/C#
        (r"class\s+(\w+)", "class"),
    ]
    for pattern, kind in patterns:
        for match in re.finditer(pattern, content):
            line_no = content[: match.start()].count("\n") + 1
            start = max(0, match.start() - 80)
            snippet = content[start : match.end() + 200]
            functions.append(
                {
                    "name": match.group(1),
                    "line": line_no,
                    "kind": kind,
                    "body": snippet,
                }
            )
    return functions


def _extract_python_functions(content: str) -> list[dict[str, Any]]:
    functions: list[dict[str, Any]] = []
    try:
        tree = ast.parse(content)
        for node in ast.walk(tree):
            if isinstance(node, ast.FunctionDef):
                src = _get_node_source(content, node)
                functions.append(
                    {
                        "name": node.name,
                        "line": node.lineno,
                        "kind": "function",
                        "args_count": len(node.args.args),
                        "has_docstring": ast.get_docstring(node) is not None,
                        "body": src,
                    }
                )
            elif isinstance(node, ast.AsyncFunctionDef):
                src = _get_node_source(content, node)
                functions.append(
                    {
                        "name": node.name,
                        "line": node.lineno,
                        "kind": "async_function",
                        "args_count": len(node.args.args),
                        "has_docstring": ast.get_docstring(node) is not None,
                        "body": src,
                    }
                )
            elif isinstance(node, ast.ClassDef):
                functions.append(
                    {
                        "name": node.name,
                        "line": node.lineno,
                        "kind": "class",
                        "methods": sum(
                            1
                            for n in node.body
                            if isinstance(n, (ast.FunctionDef, ast.AsyncFunctionDef))
                        ),
                        "has_docstring": ast.get_docstring(node) is not None,
                    }
                )
    except SyntaxError:
        # 语法错误时回退到通用正则
        return _extract_functions(content, ext=".txt")

    return functions


def _get_node_source(content: str, node: Any) -> str:
    lines = content.splitlines()
    start = max(0, int(getattr(node, "lineno", 1)) - 1)
    end = int(getattr(node, "end_lineno", start + 1))
    end = min(len(lines), max(end, start + 1))
    return "\n".join(lines[start:end])


def _estimate_complexity(body: str) -> int:
    """
    估算圈复杂度（简化 McCabe）：
    基线 1 + 控制流/布尔分支关键词计数。
    """
    if not body:
        return 1
    complexity = 1
    keywords = [
        r"\bif\b",
        r"\belif\b",
        r"\bfor\b",
        r"\bwhile\b",
        r"\bcase\b",
        r"\bcatch\b",
        r"\bexcept\b",
        r"\bwhen\b",
        r"\band\b",
        r"\bor\b",
        r"&&",
        r"\|\|",
        r"\?",
    ]
    for kw in keywords:
        complexity += len(re.findall(kw, body))
    return complexity


def _extract_imports(content: str, ext: str) -> list[dict[str, Any]]:
    imports: list[dict[str, Any]] = []

    if ext == ".py":
        try:
            tree = ast.parse(content)
            for node in ast.walk(tree):
                if isinstance(node, ast.Import):
                    for alias in node.names:
                        imports.append(
                            {"type": "import", "source": alias.name, "alias": alias.asname}
                        )
                elif isinstance(node, ast.ImportFrom):
                    module = node.module or ""
                    for alias in node.names:
                        imports.append(
                            {
                                "type": "from_import",
                                "source": module,
                                "name": alias.name,
                                "alias": alias.asname,
                            }
                        )
        except SyntaxError:
            for match in re.finditer(r"^(?:import|from)\s+(.+)$", content, re.MULTILINE):
                imports.append({"type": "statement", "raw": match.group(0).strip()})
        return imports

    patterns = [
        (r"(?:import|require)\s+[\"']([^\"']+)[\"']", "import"),  # JS/TS
        (r"(?:from|using|include|import)\s+(\w+(?:\.\w+)*)", "import_statement"),
        (r"#include\s*[<\"]([^>\"]+)[>\"]", "include"),  # C/C++
    ]
    for pattern, kind in patterns:
        for match in re.finditer(pattern, content):
            imports.append({"type": kind, "value": match.group(1)})
    return imports


def _quick_file_info(file_path: str) -> Optional[dict[str, Any]]:
    path = Path(file_path)
    if not path.exists() or not path.is_file():
        return None

    content = _read_text_file(path)
    if content is None:
        return None

    ext = path.suffix.lower()
    lines = content.splitlines()
    line_info = _analyze_lines(lines)
    functions = _extract_functions(content, ext)
    imports = _extract_imports(content, ext)

    return {
        "file": str(path.resolve()),
        "extension": ext,
        "size_bytes": path.stat().st_size,
        "total_lines": line_info["total_lines"],
        "code_lines": line_info["code_lines"],
        "comment_lines": line_info["comment_lines"],
        "blank_lines": line_info["blank_lines"],
        "func_count": len([f for f in functions if f.get("kind") in ("function", "async_function")]),
        "class_count": len([f for f in functions if f.get("kind") == "class"]),
        "import_count": len(imports),
    }


if __name__ == "__main__":
    # Stdio transport by default (适配 Claude Code / WorkBuddy / Cursor 等 Host)
    mcp.run()

