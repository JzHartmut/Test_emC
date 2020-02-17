if not exist T:\Msc15 mkdir T:\Msc15
if not exist T:\Msc15\StateM_Test mkdir T:\Msc15\StateM_Test
cd ..
rmdir /S/Q StateM_Test_Rdisk
mklink /J StateM_Test_Rdisk T:\Msc15\StateM_Test
copy StateM_Test\StateM_Test.vcxproj StateM_Test_Rdisk\StateM_Test.vcxproj
copy StateM_Test\StateM_Test.vcxproj StateM_Test_Rdisk\StateM_Test.vcxproj.filters
copy StateM_Test\StateM_Test.sln StateM_Test_Rdisk\StateM_Test.sln
pause


