# 回溯法解决迷宫问题
# 1为通路，0为障碍
from tabnanny import check

maze = [
    [1, 0, 1, 1, 1, 1],
    [1, 0, 1, 0, 0, 1],
    [1, 1, 1, 1, 0, 1],
    [0, 0, 0, 1, 0, 1],
    [0, 0, 0, 1, 1, 1],
]


class Pos:

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def set_pos(self, x, y):
        self.x = x
        self.y = y


class Tracker:
    def __init__(self):
        self.trace = []

    def add_trace(self, pos: Pos):
        self.trace.append((pos.x, pos.y))

    def pop_pos(self):
        self.trace.pop()


def check_pos(pos: Pos):
    if pos.x < 0 or pos.y < 0:
        return False
    if pos.x >= maze.__len__() or pos.y >= maze[0].__len__():
        return False
    if maze[pos.x][pos.y] == 0:
        return False
    return True


class Pointer:
    def __init__(self):
        self.__now_pos = Pos(0, 0)  # 将 __now_pos 改为 now_pos，以便于访问
        self.tracker = Tracker()

    def go_up(self):
        self.__now_pos.set_pos(self.__now_pos.x, self.__now_pos.y + 1)  # 使用 self.now_pos 访问

    def go_down(self):
        self.__now_pos.set_pos(self.__now_pos.x, self.__now_pos.y - 1)

    def go_left(self):
        self.__now_pos.set_pos(self.__now_pos.x - 1, self.__now_pos.y)

    def go_right(self):
        self.__now_pos.set_pos(self.__now_pos.x + 1, self.__now_pos.y)

    def try_go_up(self):
        return Pos(self.__now_pos.x, self.__now_pos.y + 1)

    def try_go_down(self):
        return Pos(self.__now_pos.x, self.__now_pos.y - 1)

    def try_go_left(self):
        return Pos(self.__now_pos.x - 1, self.__now_pos.y)

    def try_go_right(self):
        return Pos(self.__now_pos.x + 1, self.__now_pos.y)

    def valid(self):
        if self.__now_pos.x == maze.__len__() - 1 and self.__now_pos.y == maze[0].__len__() - 1:
            print(self.tracker.trace)
            return True
        maze[self.__now_pos.x][self.__now_pos.y] = 0
        # 只有四周为1的时候才能走
        # 尝试向上走
        if check_pos(self.try_go_up()):
            self.go_up()
            self.tracker.add_trace(self.__now_pos)
            self.valid()
        # 尝试向下走
        if check_pos(self.try_go_down()):
            self.go_down()
            self.tracker.add_trace(self.__now_pos)
            self.valid()
        # 尝试向左走
        if check_pos(self.try_go_left()):
            self.go_left()
            self.tracker.add_trace(self.__now_pos)
            self.valid()
        # 尝试向右走
        if check_pos(self.try_go_right()):
            self.go_right()
            self.tracker.add_trace(self.__now_pos)
            self.valid()
        self.tracker.pop_pos()
        return False


if __name__ == '__main__':
    print('Loaded')
    pointer = Pointer()
    pointer.valid()
    print('Finished')
