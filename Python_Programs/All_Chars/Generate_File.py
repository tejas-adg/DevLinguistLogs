import os
f = open(os.path.join(os.path.abspath(os.path.join(__file__, '..')), 'num_and_char.txt'), 'w', encoding = 'utf_8')
for num in range(0x1000):
	f.write(f'{num:04d}:0x{num:03x}:{num:012b}:{num:1c}')
	f.write('\n')
f.close()
