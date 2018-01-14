# Contributing guidelines

#### Contents
* [General guidelines](#general-guidelines)
* [Pull requests](#pull-requests)
* [Code of Conduct](#code-of-conduct)

## General guidelines
* When contributing to this repository, please first inform or discuss the change(s) you wish to make via an issue. This helps in letting others know what you're working on.

* Before you push your changes to GitHub, make sure that your code compiles and runs without any errors or warnings.

## Pull requests
Follow the steps below when making changes to the project and to submit a PR:

1. [Fork](https://help.github.com/fork-a-repo/) the repo (once).

1. Clone your fork and configure the remote (once per clone):

   ```bash
   # Clone your fork of the repo into the current directory
   git clone https://github.com/<your-username>/BigInt.git

   # Navigate to the newly cloned directory
   cd BigInt

   # Assign the original repo to a remote called "upstream"
   git remote add upstream https://github.com/faheel/BigInt.git
   ```

1. If you cloned a while ago, get the latest changes from upstream:

   ```bash
   git checkout master
   git pull upstream master
   ```

1. Create a new branch (off the `master` branch) for the changes you're about to make:

   ```bash
   git checkout -b <branch-name>
   ```

1. Commit your changes in logical chunks. Use Git's [interactive rebase](https://help.github.com/articles/interactive-rebase)
   feature to tidy up your commits before making them public.

1. Locally merge (or rebase) the upstream development branch into your branch:

   ```bash
   git pull [--rebase] upstream master
   ```

1. Push your branch up to your fork:

   ```bash
   git push origin <branch-name>
   ```

1. [Open a pull request](https://help.github.com/articles/about-pull-requests/)
    with a clear title and description against the `master` branch.

## Code of Conduct
This project has a [Code of Conduct](CODE_OF_CONDUCT.md). Please follow it in
all your interactions with the project.
