export LLVM_PROFILE_FILE="blockstmts.prof"
../ac blockstmts.a -a blockstmts.3ac 2> blockstmts.err
export LLVM_PROFILE_FILE="callexp.prof"
../ac callexp.a -a callexp.3ac 2> callexp.err
export LLVM_PROFILE_FILE="console.prof"
../ac console.a -a console.3ac 2> console.err
export LLVM_PROFILE_FILE="globals.prof"
../ac globals.a -a globals.3ac 2> globals.err
export LLVM_PROFILE_FILE="math_and_logic.prof"
../ac math_and_logic.a -a math_and_logic.3ac 2> math_and_logic.err
export LLVM_PROFILE_FILE="multiplereturns.prof"
../ac multiplereturns.a -a multiplereturns.3ac 2> multiplereturns.err
export LLVM_PROFILE_FILE="randomreliant.prof"
../ac randomreliant.a -a randomreliant.3ac 2> randomreliant.err

llvm-profdata-14 merge -sparse *.prof -o merge.profdata 
llvm-cov-14 show ../ac -instr-profile=merge.profdata >& profile.report