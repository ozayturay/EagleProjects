64tass -c -b 64IRQTransferSoftNewForC64Fast.65s -o 64IRQTransferSoftNewForC64Fast.65s.bin --labels 64IRQTransferSoftNewForC64Fast.txt
64tass -c -b IrqLoaderMenuNew.65s -o IrqLoaderMenuNew.65s.bin --labels IrqLoaderMenuNew.txt
petcat -w2 <IrqLoaderMenu.bas >IrqLoaderMenu.obj
copy /b IrqLoaderMenu.obj + IrqLoaderMenuNew.65s.bin menu.prg
REM bin2h menu.prg menu.h -cz -id=cartridgeData
bin2Ardh menu.prg menu.h data_len cartridgeData
copy avrincludehead.txt+menu.h head.tmp
copy head.tmp+avrincludefoot.txt  C:\Users\nejat\Documents\Arduino\IRQHack64\FlashLib.h
del head.tmp
CreateEpromLoader 64IRQTransferSoftNewForC64Fast.65s.bin 64IRQTransferSoftNewForC64FastLoader.bin
PAUSE