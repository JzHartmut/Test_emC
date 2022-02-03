CP="tools/vishiaGui.jar;tools/vishiaBase.jar;tools/org.eclipse.swt.win32.win32.x86_64.jar"                                                    
JAVAW=java
SCRIPT=$PWD/$0
cd ../../..
echo dir=
pwd
##call the GUI. This file %0 is used as argument for SimSelector. It contains all control after the JZtxtcmd label
echo $JAVAW -cp $CP org.vishia.jztxtcmd.JZtxtcmd $SCRIPT
$JAVAW -cp $CP org.vishia.jztxtcmd.JZtxtcmd $SCRIPT
exit                          

==JZtxtcmd==

include test_tables.jztc;

currdir = <:><&scriptdir>/../../..<.>;

String actionScript = "evalSelScripts.jzTc";


String guicfg = 
  <:>
  @primaryWindow, 3-2,1+5: Text("Selector from evaluation results emC Test");
  
  @3+50,1+118: OutputBox(name=evalText, action="selectResult");
  @56-3,1+30: InputTextline(%t:"Inputfile (d&drop)", name=inputfile, dropFiles="dropInfile");
  @56-3,32+6: Button(readInp, "read", action="readInp");
  @56-3,40+6: Button(showInfo, "show", action="showInfo");
  @56-3,50+9: Button(openErr, "openErr", action="openErr");
  @56-3,60+9: Button(openDef, "openDef", action="openDef");
  @56-3,70+9: Button(openOut, "openOut", action="openOut");
  @60-3,1+118: Show(%t:"Testcase", name=testcase);
  @63-3,1+118: Show(%t:"Testcase-2", name=testcase2);
  <.>;
  
Obj gralActions = java new org.vishia.gral.ifc.GralActionJztc(jztc, out, console);
gralActions.setScript(File: <:><&scriptdir>/evalSelector.sh<.>);
  
Obj window=java org.vishia.gral.cfg.GralCfgWindow.createWindow("@20+80, 20+120=evalSel", "Selector from evaluation results emC Test", "C", guicfg, null, console);

##text = window.getWidget("outTexts");

Map evalTables =
{ Obj l1 = tabRefl;
  Obj l2 = tabTestSrc;
  Obj l3 = tabCpp;
  Obj c1 = tabExc;     ##first sequence
  Obj c2 = tabThCxt;   ##greater sequence
  Obj c3 = tabStr;
};


Num colm_1 = evalTables.c1.size();
Num colm_2 = colm_1 * evalTables.c2.size() ;
Num line_1 = evalTables.l1.size();
Num line_2 = line_1 * evalTables.l2.size();


main(){
  Obj wdgFname = window.getWidget("inputfile");
  wdgFname.setText("build/eval.txt");
  Obj wdgEvalText = window.getWidget("evalText");
  wdgEvalText.setTextStyle("bk", "m", 11);  ##color, font, size
  ## initalize the script variables with values from the included script here,
  ##because the other script is not visible in the script part.
  ##jztc.scriptVariables().colm_1 = tabExc.size();
  <+>output...tabExc: <&colm_1><.+n>
  
  while(!window.isGraphicDisposed()) {
    jztc.sleep(1000);
  }
}


sub showInfo(Obj widget) {
##  Obj wdgFname = window.getWidget("inputfile");
##  Num cursor = wdgFname.getCursorPos();
##  <+out>sel-result <&cursor> <.+n>
  call showTestcase();

}

##
##called on keypressed of testcase text box.
##
sub selectResult(Obj widget) {
  Obj wdgTestcase = window.getWidget("testcase");
  wdgTestcase.setFocus();   ##force focus lost for the evalText widget 
  call showTestcase();      ##to get the current cursor.
}


sub readInp(Obj widget) {  ##Note: name widget nececessary to detect it as actionScript
  Obj wdgFname = window.getWidget("inputfile");
  String fnameEval = wdgFname.getText();
  <+out>fnameEval:<&fnameEval><.+n>
  String sEval = java org.vishia.util.FileFunctions.readFile(File:&fnameEval);
  Obj wdgEvalText = window.getWidget("evalText");
  wdgEvalText.setText(sEval);  
  wdgEvalText.setFocus();
}


sub showTestcase() {

  Obj wdgResultBox : org.vishia.gral.base.GralWidget = window.getWidget("evalText");
  wdgResultBox.setFocus();
  jztc.sleep(50);
  Num line = wdgResultBox.getCursorLine() -4;
  Num colm = wdgResultBox.getCursorCol();
  if(line <0){ line = 0; }
  
  Num colm3 = colm/colm_2;
  Num colm2a = colm - colm3 * colm_2;
  Num colm2 = colm2a/colm_1;
  Num colm1 = colm2a - colm2 * colm_1;
  Num line3 = line/line_2;
  Num line2a = line - line3 * line_2;
  Num line2 = line2a/line_1;
  Num line1 = line2a - line2 * line_1;

  <+out>sel-result colm_1/2 = <&colm_1>/<&colm_2> <&line_1>/<&line_2> || <&line> : <&colm> || <&colm3> <&colm2> <&colm1> || <&line3> <&line2> <&line1><.+n>
  String testcase = <:><&evalTables.l1.get(line1).name>_<&evalTables.c3.get(colm3).name>_<&evalTables.l3.get(line3).name>_<&evalTables.c2.get(colm2).name>_<&evalTables.c1.get(colm1).name>_<&evalTables.l2.get(line2).name><.>;
  Obj wdgTestcase = window.getWidget("testcase");
  wdgTestcase.setText(testcase);   ##current text
  String return.testcase = testcase;
  onerror {
    <+out><&error><.+n>
  }
}


sub openErr(Obj widget) {
  Map testcase;
  testcase = call showTestcase();
  <+out><&testcase.testcase><.+n>
  cmd cmd.exe /C ed++.bat <:>build\result\test_<&testcase.testcase>.cc_err<.> ; 
  ##cmd cmd.exe /C start cmd.exe /K ed++.bat <:>build\result\test_<&testcase.testcase>.err<.> ; 
  onerror {
    <+out><&error><.+n>
  }
}



sub openDef(Obj widget) {
  Map testcase;
  testcase = call showTestcase();
  <+out><&testcase.testcase><.+n>
  cmd cmd.exe /C ed++.bat <:>build\result\test_<&testcase.testcase>.err<.> ; 

  onerror {
    <+out><&error><.+n>
  }
}



sub openOut(Obj widget) {
  Map testcase;
  testcase = call showTestcase();
  <+out><&testcase.testcase><.+n>
  cmd cmd.exe /C ed++.bat <:>build\result\test_<&testcase.testcase>.out<.> ; 
  <+out><&testcase.testcase><.+n> 

  onerror {
    <+out><&error><.+n>
  }
}





