echo=off
setlocal

rem copy ..\..\Install\Doc\EULA.pdf

del *__or.html /s /q

set OPTIONS=-add -rec -exc=TODO.txt -exc=Diagrams.pptx -exc=AshDemo.cfg -exc=TB.bat -exc=Package.bat -exc=post.bat -exc=TestBed.Result -exc=FolderTestBed.cfg -exc=*.report -exc=.gitignore -exc=*.CoverageData -exc=*.zip -path=relative

del MS1553_driver_pkg.zip

rem create the release package zip
pkzip25 %OPTIONS% MS1553_driver_pkg.zip  *.*
