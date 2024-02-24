# todos tienen forma de L
part1 = [1,6,7,8]
part2 = [2,3,4,9]
part3 = [5,10,11,12]
part4 = [13,14,19,24]
part5 = [15,20,21,22]
part6 = [16,17,18,23]

parts = [part1, part2, part3, part4, part5, part6]

for i in range(6):
	with open(f'part{i+1}.txt', 'w') as f:
		for n in range(1, 25):
			if n not in parts[i]:
				f.write(f'map 25 {n} 0\n')