#!/bin/bash

# git fetch origin
# git pull origin main
# git checkout -b feature/nueva-caracteristica
# git add <archivo>
# git commit -m "Descripción clara del cambio"
# git diff
# git fetch origin
# git rebase origin/main  # o git merge origin/main
# git push origin feature/nueva-caracteristica
# git rebase -i HEAD~<número_de_commits>
# git branch -d feature/nueva-caracteristica
# git push origin --delete feature/nueva-caracteristica


# git ls-remote git@github.com:MaycolZx/ForAllMyProject.git refs/heads/master
# git archive --remote=git@github.com:MaycolZx/ForAllMyProject.git
# git archive --remote=git@github.com:MaycolZx/ForAllMyProject.git --format=tar master | tar -tvf -
# git clone --depth 1 --branch master git@github.com:MaycolZx/ForAllMyProject.git

# git clone git@github.com:MaycolZx/ForAllMyProject.git ./OtherGit/
cd ./OtherGit/
git fetch master
git pull origin master

find ./OtherGit/ -type f \( -name "*.cpp" -o -name "*.h" \)

