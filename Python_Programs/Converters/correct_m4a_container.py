

import os


dirname = r"D:\tejas\Music"
for song_file in os.listdir(dirname):
    if song_file.split('.')[1] == 'm4a':
        new_name = song_file.split('.')[0] + "_Processed.m4a"
        print(f"{song_file} --> {new_name}")
        os.system(f"D:\\ffmpeg\\bin\\ffmpeg.exe -hide_banner -i {os.path.join(dirname, song_file)} {os.path.join(dirname, new_name)}")
        os.remove(os.path.join(dirname, song_file))