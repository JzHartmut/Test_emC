eval $(ssh-agent -s)
ssh-add ~/.ssh/github.key
git push --delete 'git@github.com:JzHartmut/src_emC' 2020-12-05
