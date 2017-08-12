#!/usr/bin/env bash

find . > before;
g++ --coverage $1;

while read line;
do
	echo "Running: $line";
	bash -c "$line";
done < $2;

lcov -c -d . -o info --rc lcov_branch_coverage=1; 
lcov -r info "*/usr/include*" > finalinfo;
genhtml finalinfo -o report;
open report/index.html;
diff before <(find .) | grep -i "^>.*$" | grep -vi "report" | cut -d " " -f 2- | xargs -n 1 rm -r;
rm before;
