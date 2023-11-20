# Git guidelines

## Commit conventions

- Label your commits. Each commit should be prefixed with the jira code
followed by a comprehensive commit message. For example:
```
TU-1: Implemented collision detection between wall and cannonball
```

Include `WIP` if the jira ticket is not done. Eg.
```
TU-1: WIP - Implemented function stub for collision detection between wall and cannonball
```

- **ALWAYS** create a new branch for every task. Name the branches properly and replace
the spaces with `-`.

An example on how to create a branch would be:
```
git checkout -b TU1-main-menu-dev
git add .
git commit -m 'created new branch for main menu dev'
git push --set-upstream TU1-main-menu-dev
```

Always create a new branch before making changes to the code.

Never push directly to master branch. This may result in merge conflicts.


# Setup/git guide

```
git clone https://github.com/jspoh/tank_u.git
```

Update local branch with remote branch:
```
git checkout <branch-name>
git pull
```

If you are sharing a branch with someone else, always run `git pull` before
making any changes.