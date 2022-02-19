#!/usr/bin/env python3

import argparse
import ctypes.util
import distutils.ccompiler
import os
import platform
import sys
import tempfile


# adapted from https://github.com/tree-sitter/py-tree-sitter
def build(repositories, output_path="libjava-tree-sitter", arch=None, verbose=False):
    output_path = f"{output_path}.{'dylib' if platform.system() == 'Darwin' else 'so'}"
    here = os.path.dirname(os.path.realpath(__file__))
    env = f"CFLAGS='-arch {arch}' LDFLAGS='-arch {arch}'" if arch else ""
    os.system(
        f"make -C {os.path.join(here, 'tree-sitter')} clean {'&> /dev/null' if not verbose else ''}"
    )
    os.system(
        f"{env} make -C {os.path.join(here, 'tree-sitter')} {'&> /dev/null' if not verbose else ''}"
    )

    cpp = False
    source_paths = [
        os.path.join(here, "lib", "ai_serenade_treesitter_TreeSitter.cc"),
        os.path.join(here, "lib", "ai_serenade_treesitter_Languages.cc"),
    ]

    compiler = distutils.ccompiler.new_compiler()
    for repository in repositories:
        src_path = os.path.join(repository, "src")
        source_paths.append(os.path.join(src_path, "parser.c"))
        scanner_c = os.path.join(src_path, "scanner.c")
        scanner_cc = os.path.join(src_path, "scanner.cc")
        if os.path.exists(scanner_cc):
            cpp = True
            source_paths.append(scanner_cc)
        elif os.path.exists(scanner_c):
            source_paths.append(scanner_c)

        compiler.define_macro(
            f"TS_LANGUAGE_{os.path.split(repository.rstrip('/'))[1].split('tree-sitter-')[-1].replace('-', '_').upper()}",
            "1",
        )

    source_mtimes = [os.path.getmtime(__file__)] + [
        os.path.getmtime(path) for path in source_paths
    ]

    if cpp:
        if ctypes.util.find_library("stdc++"):
            compiler.add_library("stdc++")
        elif ctypes.util.find_library("c++"):
            compiler.add_library("c++")

    output_mtime = os.path.getmtime(output_path) if os.path.exists(output_path) else 0
    if max(source_mtimes) <= output_mtime:
        return False

    with tempfile.TemporaryDirectory(suffix="tree_sitter_language") as out_dir:
        object_paths = []
        for source_path in source_paths:
            flags = ["-O3"]

            if platform.system() == "Linux":
                flags.append("-fPIC")

            if source_path.endswith(".c"):
                flags.append("-std=c99")

            if arch:
                flags += ["-arch", arch]

            include_dirs = [
                os.path.dirname(source_path),
                os.path.join(here, "tree-sitter", "lib", "include"),
                os.path.join(os.environ["JAVA_HOME"], "include"),
            ]

            if platform.system() == "Linux":
                include_dirs.append(
                    os.path.join(os.environ["JAVA_HOME"], "include", "linux")
                )
            elif platform.system() == "Darwin":
                include_dirs.append(
                    os.path.join(os.environ["JAVA_HOME"], "include", "darwin")
                )

            object_paths.append(
                compiler.compile(
                    [source_path],
                    output_dir=out_dir,
                    include_dirs=include_dirs,
                    extra_preargs=flags,
                )[0]
            )

        extra_preargs = []
        if platform.system() == "Darwin":
            extra_preargs.append("-dynamiclib")

        if arch:
            extra_preargs += ["-arch", arch]

        compiler.link_shared_object(
            object_paths,
            output_path,
            extra_preargs=extra_preargs,
            extra_postargs=[os.path.join(here, "tree-sitter", "libtree-sitter.a")],
            library_dirs=[os.path.join(here, "tree-sitter")],
        )

    return True


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Build a tree-sitter library")
    parser.add_argument(
        "-a",
        "--arch",
        help="Architecture to build for",
    )
    parser.add_argument(
        "-o", "--output", default="libjava-tree-sitter", help="Output file name"
    )
    parser.add_argument(
        "-v", "--verbose", action="store_true", help="Print verbose output"
    )
    parser.add_argument(
        "repositories",
        nargs="+",
        help="tree-sitter repositories to include in build",
    )

    args = parser.parse_args()
    distutils.log.set_verbosity(int(args.verbose))
    build(args.repositories, args.output, args.arch, args.verbose)
