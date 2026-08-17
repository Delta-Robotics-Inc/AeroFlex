#!/usr/bin/env python3
"""Check that every relative markdown link in the repo points at a real file.

Run from anywhere: python3 scripts/check_links.py
Exits non-zero if any relative link target is missing. External URLs,
mailto:, and in-page anchors are not checked.
"""
import os
import re
import sys
import urllib.parse

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SKIP_DIRS = {".git", ".github", "node_modules"}
LINK_RE = re.compile(r"\]\(([^)\s]+)\)")

broken = []
for root, dirs, files in os.walk(REPO):
    dirs[:] = [d for d in dirs if d not in SKIP_DIRS]
    for name in files:
        if not name.lower().endswith(".md"):
            continue
        path = os.path.join(root, name)
        with open(path, encoding="utf-8", errors="replace") as fh:
            text = fh.read()
        for match in LINK_RE.finditer(text):
            url = match.group(1)
            # Skip external links, mailto:, and in-page anchors
            if url.startswith(("http://", "https://", "mailto:", "#")):
                continue
            # Normalize: remove fragment and query parameters (e.g., ?raw=1)
            target = urllib.parse.unquote(url.split("#")[0].split("?", 1)[0])
            if not target:
                continue
            # If the link begins with a slash, treat it as repo-root-relative
            if target.startswith("/"):
                resolved = os.path.normpath(os.path.join(REPO, target.lstrip("/")))
            else:
                resolved = os.path.normpath(os.path.join(os.path.dirname(path), target))
            if not os.path.exists(resolved):
                line = text[: match.start()].count("\n") + 1
                broken.append((os.path.relpath(path, REPO), line, url))

if broken:
    print(f"{len(broken)} broken relative link(s):")
    for relpath, line, url in broken:
        print(f"  {relpath}:{line}  ->  {url}")
    sys.exit(1)
print("All relative links OK.")
