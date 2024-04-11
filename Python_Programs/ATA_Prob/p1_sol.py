
def classGrouping(levels:list, maxSpread:int) -> int :
    count = 0
    while len(levels) > 0:
        curr_level = levels.pop(0)
        groupable_levels = list(range(curr_level - maxSpread, ((curr_level + maxSpread) + 1)))
        for a_lvl in groupable_levels:
            if levels.count(a_lvl) > 1:
                for _ in range(levels.count(a_lvl)):
                    levels.remove(a_lvl)
            elif levels.count(a_lvl) == 1:
                levels.remove(a_lvl)
        count += 1
    return count

def classGrouping(levels:list, maxSpread:int) -> int :
    levels.sort()
    curr_pos = 0
    count = 0
    while curr_pos < 1:
        curr_pos += 1
    if levels[curr_pos] in range(levels[curr_pos] - maxSpread, ((levels[curr_pos] + maxSpread) + 1)):
        curr_pos += 1
    else:
        count += 1

print(classGrouping([4, 1, 2, 5, 3], 0))
