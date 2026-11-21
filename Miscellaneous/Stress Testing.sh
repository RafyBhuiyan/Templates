#!/bin/bash
# AUST Simplexity Team Notebook, section "Grundy + Stress Test", pp. 2.
numLoop=${1:-100}
doComp=${2:-1}
if [ $doComp -eq 1 ]; then
    g++ -std=c++17 gen.cpp -o gen
    g++ -std=c++17 solution.cpp -o solution
    g++ -std=c++17 brute.cpp -o brute
fi
diff_found=0
for ((i=1;i<=numLoop;i++)); do
    echo "Test $i"
    ./gen > input.in
    ./solution < input.in > output.out
    ./brute < input.in > output2.out
    if ! diff -q output.out output2.out > /dev/null; then
        diff_found=1
        break
    fi
done
if [ $diff_found -eq 1 ]; then
    echo "A difference has been found!"
    echo "Input:"
    cat input.in
    echo
    echo "Output:"
    cat output.out
    echo
    echo "Expected:"
    cat output2.out
else
    echo "All tests passed :D"
fi
rm -f input.in output.out output2.out

# 1.create gen,solution,brute.cpp
# 2.go to the directory
# 3. nano stress.sh
# 4. ctrl+O (to save) -> ENTER -> ctrl+X (to escape)
# 5.chmod +x stress.sh
# 6../stress.sh #of_test 1
