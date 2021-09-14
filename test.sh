#!/bin/zsh
EXUTABLE="/Users/mgena/CLionProjects/nm-otool/cmake-build-debug/nm_otool"
FILES="/sbin/* /bin/*"
rm a b
touch a
touch b
for f in /Users/mgena/.brew/bin/* /usr/local/bin/* /usr/bin/* /bin/* /usr/sbin/* /sbin/* /usr/local/munki; do
  echo $f >>a
  echo $f >>b
  $EXUTABLE $f >>a 2>/dev/null
  nm $f >>b 2>/dev/null
done
  diff a b > diff_file
#  rm a b
