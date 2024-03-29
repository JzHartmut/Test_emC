#REM: invoked either from root of Test_emC or from current dir,
#REM but should work from point root of Test_emC
if test -f ../../../src/version_Test_emC.txt; then cd ../../..; fi
pwd
echo java -jar tools/vishiaBase.jar src/test/testScripts/evalTests.jzTc.sh                                                                                         
java -jar tools/vishiaBase.jar src/test/testScripts/evalTests.jzTc.sh                                                                                         

cat build/eval.txt

read -n1 -r -p "Press any key to continue..."



exit 0  ##the rest of the file is the JZtxtcmd script                                      
                                                                   
==JZtxtcmd==

##include ../ZmakeGcc/test_Selection.jztsh;  ##tables are their
include test_tables.jztc;

currdir=<:><&scriptdir>/../../..<.>;                             

main() {
  call eval1();
}

sub eval1() {
  
  ##for(lineTestSrc: tabTestSrc) {
    String nameFnames = <:>build/evalTest_TestEvMsg.txt<.>; 
    Openfile fname = nameFnames;                                            
    Stringjar problems;
    Stringjar evalTxt;
    Stringjar h1;
    Stringjar h2;
    Stringjar h3;
    Stringjar h4;
    for(lineStr: tabStr) {
      for(lineThCxt: tabThCxt) {             ##build header line with 1 char
        for(lineExc: tabExc) {                                  
          ##for(lineCpp: tabCpp) {
             h1 += lineStr.sh; h2 += lineThCxt.sh; h3 += lineExc.sh; 
    } } } ##}
    for(line: tabStr) {
      h1 += <:>  <&line.sh>:<&line.name><.>;  ##add legend
    }
    for(line: tabThCxt) {
      h2 += <:>  <&line.sh>:<&line.name><.>;
    }
    for(line: tabExc) {
      h3 += <:>  <&line.sh>:<&line.name><.>;
    }
    ##for(line: tabCpp) {
    ##  h4 += <:>  <&line.sh>:<&line.name><.>;
    ##}
    evalTxt += <:><&h1><:n><.>;                  ##write column header
    evalTxt += <:><&h2><:n><.>;
    evalTxt += <:><&h3><:n><.>;
    evalTxt += <:><&h4><:n><.>;
    ##
    for(lineCpp: tabCpp) {
      <+out>iterate through <&lineCpp.name> ...<.+n>
      for(lineTestSrc: tabTestSrc) {             ##iterate through all possible test cases                            
        <+out> - <&lineTestSrc.name> ...<.+n>
        for(lineRefl: tabRefl) {                 ##as lines                 
          List testNames;
          for(lineStr: tabStr) {
            for(lineThCxt: tabThCxt) {             ##build the file name of the test case
              for(lineExc: tabExc) {                                  
                String testName = <:>test_<&lineRefl.name>_<&lineStr.name>_<&lineCpp.name>_<&lineThCxt.name>_<&lineExc.name>_<&lineTestSrc.name><.>;
                testNames += testName;             ##add the file names to the list, it is all test names in the row for all columns
          } } }                                   ##the evaluation routine checks the files of content. 
          <+fname><&testNames><:n>---------------------------<.+n>
          String line = java org.vishia.testutil.EvalTestoutfiles.evalFiles(
                            testNames, File:"build/result", problems);
          evalTxt += <:><&line> - <&lineRefl.name> - <&lineTestSrc.name> - <&lineCpp.name><:n><.>;
    } } }
    fname.close();
    evalTxt += problems;
    java org.vishia.util.FileFunctions.writeFile(evalTxt, File:"build/eval.txt");
    onerror {
      <:>error evalFiles <&error><:n><.>
    }
}

