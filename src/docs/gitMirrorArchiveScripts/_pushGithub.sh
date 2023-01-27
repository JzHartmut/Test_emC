echo HOME=$HOME
echo HOMEDRV=$HOMEDRV
echo HOMEDIR=$HOMEDIR

eval $(ssh-agent -s)
ssh-add ~/.ssh/github.key
## comment/uncomment TAGNEW and TAGDEL if necessary
##TAGNEW="2022-04-25"
##TAGTXT="MSP430Exmpl"
##TAGDEL=$TAGNEW
##TAGDEL="2021-07-01"
if test -v TAGDEL; then
  git tag -d $TAGDEL
  git tag
  #Note:   --tags :tag   means, remove the tag
  git push 'git@github.com:JzHartmut/src_emC' master --tags :$TAGDEL
fi
if test -v TAGNEW; then
  git tag -a $TAGNEW -m "$TAGTXT"
  echo ----------------
  git tag
fi  
git push 'git@github.com:JzHartmut/src_emC' master --tags

