# Contributing to the AeroFlex Standard

Thanks for helping make pneumatic artificial muscles something anyone can
build and build on. Contributions of every kind are welcome: fixing doc
errors, reporting build results, adding research citations, and proposing
changes to the standard itself.

## Ways to contribute

| You want to | Do this |
|---|---|
| Fix a typo, broken link, or wrong value | Open a PR directly |
| Report an error or unsafe value in the docs | Open a "Doc or spec issue" |
| Share results from building a muscle | Open an issue with your data (pressure, force, stroke, materials) |
| Propose a change to the standard (interfaces, geometry, conventions) | Open a "Standard proposal" issue first, before writing the PR |

Spec changes affect everyone building against the standard, so proposals get
discussed in an issue before a PR. Doc fixes do not need an issue first.

## Working locally

This is a documentation repo; there is nothing to build. Two things keep it
healthy:

1. Use relative links for in-repo files so links survive branch renames.
2. Before opening a PR, run the link checker:

```bash
python3 scripts/check_links.py
```

CI runs the same check on every PR.

## Sign your commits (DCO)

We use the [Developer Certificate of Origin](https://developercertificate.org).
Add a `Signed-off-by` line to each commit by committing with `-s`:

```bash
git commit -s -m "docs: correct braid angle in design.md"
```

## Style

- Match the tone and structure of the surrounding docs.
- Cite sources for physical claims (papers, datasheets, or your own measured
  data with the setup described).
- State units explicitly and prefer both psi and kPa/MPa where practical.

## What to expect

This standard is maintained by a small team at Delta Robotics alongside
product work. We aim to respond to issues and PRs within a few days. Small,
focused PRs merge fastest.
