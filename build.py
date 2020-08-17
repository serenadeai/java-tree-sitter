#!/usr/bin/env python3

import ctypes.util
import distutils.ccompiler
import os
import platform
import sys
import tempfile


# adapted from https://github.com/tree-sitter/py-tree-sitter
def build(repo_paths, output_path="libjava-tree-sitter.so"):
    os.system("make -C tree-sitter > /dev/null")
    output_mtime = os.path.getmtime(output_path) if os.path.exists(output_path) else 0

    if not repo_paths:
        raise ValueError("Must provide at least one language folder")

    cpp = False
    source_paths = ["lib/ai_serenade_treesitter_TreeSitterJNI.cc"]
    for repo_path in repo_paths:
        src_path = os.path.join(repo_path, "src")
        source_paths.append(os.path.join(src_path, "parser.c"))
        scanner_c = os.path.join(src_path, "scanner.c")
        scanner_cc = os.path.join(src_path, "scanner.cc")
        if os.path.exists(scanner_cc):
            cpp = True
            source_paths.append(scanner_cc)
        elif os.path.exists(scanner_c):
            source_paths.append(scanner_c)

    source_mtimes = [os.path.getmtime(__file__)] + [
        os.path.getmtime(path_) for path_ in source_paths
    ]

    compiler = distutils.ccompiler.new_compiler()
    if cpp:
        if ctypes.util.find_library("c++"):
            compiler.add_library("c++")
        elif ctypes.util.find_library("stdc++"):
            compiler.add_library("stdc++")

    if max(source_mtimes) <= output_mtime:
        return False

    with tempfile.TemporaryDirectory(suffix="tree_sitter_language") as out_dir:
        object_paths = []
        for source_path in source_paths:
            flags = ["-O3"]

            if platform.system() != "Windows":
                flags.append("-fPIC")

            if source_path.endswith(".c"):
                flags.append("-std=c99")

            object_paths.append(
                compiler.compile(
                    [source_path],
                    output_dir=out_dir,
                    include_dirs=[
                        os.path.dirname(source_path),
                        "tree-sitter/lib/include",
                        f"{os.environ['JAVA_HOME']}/include",
                        f"{os.environ['JAVA_HOME']}/include/linux",
                    ],
                    extra_preargs=flags,
                )[0]
            )

        compiler.link_shared_object(
            object_paths,
            output_path,
            extra_postargs=["tree-sitter/libtree-sitter.a"],
            library_dirs=["./tree-sitter"],
        )

    return True


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: build.py ./tree-sitter-python ./tree-sitter-javascript")
        sys.exit(1)

    distutils.log.set_verbosity(1)
    build(sys.argv[1:])
