@echo off
cd \
@echo on
@REG Delete HKEY_CURRENT_USER\Software\Microsoft\VisualStudio\10.0\FileMRUList /va /f
@REG Delete HKEY_CURRENT_USER\Software\Microsoft\VisualStudio\10.0\ProjectMRUList /va /f
@REG Delete HKEY_CURRENT_USER\Software\Microsoft\VisualStudio\11.0\FileMRUList /va /f
@REG Delete HKEY_CURRENT_USER\Software\Microsoft\VisualStudio\11.0\ProjectMRUList /va /f
@echo off
pause