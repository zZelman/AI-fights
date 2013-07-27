@ECHO off

AStyle.exe  --style=allman --indent=tab   --indent-cases --indent-namespaces --indent-labels --indent-preprocessor --max-instatement-indent=40 --pad-oper --pad-header --unpad-paren --align-pointer=type --align-reference=type --break-closing-brackets --add-brackets --close-templates --verbose --recursive *.cpp

AStyle.exe  --style=allman --indent=tab   --indent-cases --indent-namespaces --indent-labels --indent-preprocessor --max-instatement-indent=40 --pad-oper --pad-header --unpad-paren --align-pointer=type --align-reference=type --break-closing-brackets --add-brackets --close-templates --verbose --recursive *.c

AStyle.exe  --style=allman --indent=tab   --indent-cases --indent-namespaces --indent-labels --indent-preprocessor --max-instatement-indent=40 --pad-oper --pad-header --unpad-paren --align-pointer=type --align-reference=type --break-closing-brackets --add-brackets --close-templates --verbose --recursive *.h

AStyle.exe  --style=allman --indent=tab   --indent-cases --indent-namespaces --indent-labels --indent-preprocessor --max-instatement-indent=40 --pad-oper --pad-header --unpad-paren --align-pointer=type --align-reference=type --break-closing-brackets --add-brackets --close-templates --verbose --recursive *.java

echo Deleting Changed Files
del /s *.orig

pause