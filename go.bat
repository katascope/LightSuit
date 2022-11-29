REM f:\ffmpeg\bin\ffmpeg -r 1/5 -start_number 0 -i C:\myimages\img%03d.png -c:v libx264 -r 30 -pix_fmt yuv420p out.mp4
REM ffmpeg -r 1/5 -i img%03d.png -c:v libx264 -vf fps=25 -pix_fmt yuv420p out.mp4

REM f:\ffmpeg\bin\ffmpeg -r 1 -start_number 1 -i Render-XorY-%04d.png -c:v libx264 -vf fps=25 -pix_fmt yuv420p XorY.mp4


REM  f:\ffmpeg\bin\ffmpeg -r 5 -start_number 0 -i arena_img%02d.png -c:v libx264 -vf fps=25 -pix_fmt yuv420p Arena.mp4
REM ffmpeg -i input.mp4 -filter_complex "[0]reverse[r];[0][r]concat,loop=1:300,setpts=N/25/TB" output.mp4

f:\ffmpeg\bin\ffmpeg -r 25 -start_number 0 -i arena_anim%03d.png -c:v libx264 -vf fps=25 -pix_fmt yuv420p Arena.mp4
f:\ffmpeg\bin\ffmpeg -r 25 -start_number 0 -i nexus_anim%03d.png -filter_complex "[0]reverse[r];[0][r]concat,loop=1:150,setpts=N/25/TB" -c:v libx264 -pix_fmt yuv420p Nexus.mp4



f:\ffmpeg\bin\ffmpeg -i "H:\MusicLibrary\Definition FX\11-Space Time Disco.mp3" -lavfi showspectrumpic=s=2022x256:color=4:scale=lin disco.png



length_in_seconds = 202.24

hor_pixels = length_in_seconds*10 = 2022

649 /10 = 64.9




f:\ffmpeg\bin\ffmpeg -r 30 -start_number 0 -i viz_anim%04d.png -i "H:\MusicLibrary\Definition FX\11-Space Time Disco.mp3" -c:v libx264 -pix_fmt yuv420p Viz.mp4

f:\ffmpeg\bin\ffmpeg -r 30 -start_number 0 -i lhtest1_anim%04d.png -i "g:\rendered\layne1.mp3" -c:v libx264 -pix_fmt yuv420p lhtest1.mp4
f:\ffmpeg\bin\ffmpeg -r 30 -start_number 0 -i lhtest2_anim%04d.png -i "g:\rendered\layne1.mp3" -c:v libx264 -pix_fmt yuv420p lhtest2.mp4
f:\ffmpeg\bin\ffmpeg -r 30 -start_number 0 -i lhtest3_anim%04d.png -i "g:\rendered\layne1.mp3" -c:v libx264 -pix_fmt yuv420p lhtest3.mp4
f:\ffmpeg\bin\ffmpeg -r 30 -start_number 0 -i lhtest4_anim%04d.png -i "g:\rendered\layne1.mp3" -c:v libx264 -pix_fmt yuv420p lhtest4.mp4


f:\ffmpeg\bin\ffmpeg -r 30 -start_number 0 -i lhtest4_anim%04d.png -i "g:\rendered\layne1.mp3" -c:v libx264rgb -crf 18 -preset veryslow -pix_fmt yuv420p lhtest4_high.mp4
f:\ffmpeg\bin\ffmpeg -r 30 -start_number 0 -i lhtest4_anim%04d.png -i "g:\rendered\layne1.mp3" -c:v libx264rgb -crf 18 -preset veryslow -pix_fmt yuv420p -frames:v 1000 lhtest4_high.mp4


f:\ffmpeg\bin\ffmpeg -r 30 -start_number 0 -i hanmarb1_anim%04d.png -i "g:\rendered\hanmarb1.mp3" -c:v libx264rgb -crf 18 -preset veryslow -pix_fmt yuv420p -frames:v 2160 hanmarb1_high2.mp4