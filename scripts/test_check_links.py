#!/usr/bin/env python3
# Minimal functional test — runs the check_links script in a temporary repo layout.
import os
import subprocess
import tempfile
import textwrap
import sys

SCRIPT = os.path.join(os.path.dirname(__file__), "check_links.py")


def write(path, content):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w", encoding="utf-8") as fh:
        fh.write(content)


def run_test():
    with tempfile.TemporaryDirectory() as td:
        # Create a minimal repo layout
        repo_root = td
        docs_dir = os.path.join(repo_root, "docs", "test-rig-evidence")
        os.makedirs(docs_dir)
        # A real file that should be found
        real_zip = os.path.join(docs_dir, "aeroflex-test-rig-reference-photo-set-20260817.zip")
        with open(real_zip, "wb") as fh:
            fh.write(b"zip")
        # README with a ?raw=1 query on the local filename
        readme = os.path.join(docs_dir, "README.md")
        write(readme, textwrap.dedent("""
        For a one-click handoff, download
        [`aeroflex-test-rig-reference-photo-set-20260817.zip`](aeroflex-test-rig-reference-photo-set-20260817.zip?raw=1).
        """))
        # Run the check_links.py script with cwd set to repo root
        proc = subprocess.run([sys.executable, SCRIPT], cwd=repo_root, capture_output=True, text=True)
        print("stdout:", proc.stdout)
        print("stderr:", proc.stderr)
        return proc.returncode


if __name__ == "__main__":
    rc = run_test()
    if rc != 0:
        print("Test failed: check_links returned non-zero")
        sys.exit(rc)
    print("Test passed")
