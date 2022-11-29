REM f:\ffmpeg\bin\ffmpeg -i "H:\MusicLibrary\Definition FX\11-Space Time Disco.mp3" -lavfi showspectrumpic=s=2022x512:mode=separate:color=4:scale=lin:stop=8000 disco.png
REM f:\ffmpeg\bin\ffmpeg -i "H:\MusicLibrary\Definition FX\11-Space Time Disco.mp3" -filter_complex "[0:a]showspectrum=mode=separate:color=intensity:scale=cbrt:s=640x518[ss];" disco2.png
REM f:\ffmpeg\bin\ffmpeg -i "H:\MusicLibrary\Definition FX\11-Space Time Disco.mp3" -filter_complex "[0:a]avectorscope=s=640x518,pad=1280:720[vs]; [0:a]showspectrum=mode=separate:color=intensity:scale=cbrt:s=640x518[ss]; [0:a]showwaves=s=1280x202:mode=line[sw]; [vs][ss]overlay=w[bg]; [bg][sw]overlay=0:H-h,drawtext=fontfile=/usr/share/fonts/TTF/Vera.ttf:fontcolor=white:x=10:y=10:text='\"Song Title\" by Artist'[out]" -map "[out]" -map 0:a -c:v libx264 -preset fast -crf 18 -c:a copy output.mkv

f:\ffmpeg\bin\ffmpeg -i "H:\MusicLibrary\Definition FX\11-Space Time Disco.mp3" -lavfi showspectrumpic=s=6066x256:color=4:scale=lin:stop=8000 disco.png
f:\ffmpeg\bin\ffmpeg -i disco.png -vf  "crop=6066:256:141:64" discoCrop.png

f:\ffmpeg\bin\ffmpeg -i "H:\MusicLibrary\Plastikman\Musik\07 Marbles.m4a" -lavfi showspectrumpic=s=27720x512:color=4:scale=lin:stop=8000 marbles.png
f:\ffmpeg\bin\ffmpeg -i marbles.png -vf  "crop=27720:512:141:63" marblesCrop.png

f:\ffmpeg\bin\ffmpeg -i "H:\MusicLibrary\The Prodigy\Fat of the Land\01 Smack My Bitch Up.m4a" -lavfi showspectrumpic=s=16260x512:color=4:scale=lin:stop=8000 smack.png
f:\ffmpeg\bin\ffmpeg -i smack.png -vf  "crop=16260:512:141:64" smackCrop.png

REM f:\ffmpeg\bin\ffmpeg -i "H:\MusicLibrary\Definition FX\11-Space Time Disco.mp3" -filter_complex "[0:a]avectorscope=s=640x518,pad=1280:720[vs]; [0:a]showspectrum=mode=separate:color=intensity:scale=cbrt:s=640x518[ss]; [0:a]showwaves=s=1280x202:mode=line[sw]; [vs][ss]overlay=w[bg]; [bg][sw]overlay=0:H-h,drawtext=fontfile=/usr/share/fonts/TTF/Vera.ttf:fontcolor=white:x=10:y=10:text='\"Song Title\" by Artist'[out]" -map "[out]" -map 0:a -c:v libx264 -preset fast -crf 18 -c:a copy output.mkv

f:\ffmpeg\bin\ffmpeg -i "Layne1.mp3" -lavfi showspectrumpic=s=2100x256:color=4:scale=lin:stop=8000 layne1.png
f:\ffmpeg\bin\ffmpeg -i layne1.png -vf  "crop=2100:256:141:64" layne1Crop.png




f:\ffmpeg\bin\ffmpeg -i "g:\rendered\hanmarb1.mp3" -lavfi showspectrumpic=s=2160x512:color=4:scale=lin:stop=8000 hanmarb1.png
f:\ffmpeg\bin\ffmpeg -i hanmarb1.png -vf  "crop=2160:512:141:63" hanmarb1.png


f:\ffmpeg\bin\ffmpeg -i "g:\rendered\game.m4a" -lavfi showspectrumpic=s=6150x512:color=4:scale=lin:stop=8000 game.png
f:\ffmpeg\bin\ffmpeg -i game.png -vf  "crop=6150:512:141:63" game_crop.png



f:\ffmpeg\bin\ffmpeg -i "g:\rendered\game.m4a" -lavfi showspectrumpic=s=20500x512:color=4:scale=lin:stop=8000 gameHd.png
f:\ffmpeg\bin\ffmpeg -i "g:\rendered\game.m4a" -lavfi showspectrumpic=s=2050x512:color=4:scale=lin:stop=8000 gameLd.png
f:\ffmpeg\bin\ffmpeg -i game.png -vf  "crop=20500:512:141:63" gameHd_crop.png


f:\ffmpeg\bin\ffmpeg -i "TronGame.m4a" -lavfi showspectrumpic=s=1300x512:color=4:scale=lin:stop=8000 TronGame.png
f:\ffmpeg\bin\ffmpeg -i TronGame.png -vf  "crop=1300:512:141:64" TronGameCropped.png

f:\ffmpeg\bin\ffmpeg -i "TronGame.m4a" -lavfi showspectrumpic=s=13000x512:color=4:scale=lin:stop=8000 TronGameHD.png
f:\ffmpeg\bin\ffmpeg -i TronGame.png -vf  "crop=13000:512:141:64" TronGameCroppedHD.png

f:\ffmpeg\bin\ffmpeg -i "TronGame.m4a" -lavfi showspectrumpic=s=13000x512:scale=lin:stop=8000 TronGameHD2.png