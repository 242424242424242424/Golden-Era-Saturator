@echo off
echo Installing GoldenEraSaturator VST3...
set VST3_PATH="C:\Program Files\Common Files\VST3"
if not exist %VST3_PATH% mkdir %VST3_PATH%
xcopy /E /I "VST3\GoldenEraSaturator.vst3" %VST3_PATH%\GoldenEraSaturator.vst3
echo Installation complete!
pause
