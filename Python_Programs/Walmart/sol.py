

#colors = "wwbbww"


def removable(pos, c_lis, c):
    if ((pos == 0) or (pos == len(c_lis)) or (c_lis[pos] != c) or (pos == (len(c_lis) - 1))):
        return False
    else:
        return ((c_lis[pos - 1] == c) and (c_lis[pos] == c) and (c_lis[pos + 1] == c))

any_removable = lambda col_lis: any([removable(i, col_lis, col_lis[i]) for i in range(len(col_lis))])

def gameWinner(colors:str):
    colors_lis = list(colors)
    count = 0
    while True:
        if removable(colors.find('w' if ((count % 2) == 0) else 'b'), colors_lis, 'w' if ((count % 2) == 0) else 'b'):
            colors_lis.pop(colors.find('w' if ((count % 2) == 0) else 'b'))
            colors = ''.join(colors_lis)

print(gameWinner("wwwbbbbwww"))