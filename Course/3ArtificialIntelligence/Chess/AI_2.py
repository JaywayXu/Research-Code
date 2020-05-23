from enum import IntEnum
from random import randint
import time

AI_SEARCH_DEPTH = 4  #搜索层数
AI_LIMITED_MOVE_NUM = 8  #


class CHESS_TYPE(IntEnum):  #棋形类别枚举
    NONE = 0,  #无
    SLEEP_TWO = 1,  #眠2
    LIVE_TWO = 2,  #活2
    SLEEP_THREE = 3  #眠3
    LIVE_THREE = 4,  #活3
    CHONG_FOUR = 5,  #冲4
    LIVE_FOUR = 6,  #活4
    LIVE_FIVE = 7,  #活5


CHESS_TYPE_NUM = 8  #棋形类别数量

FIVE = CHESS_TYPE.LIVE_FIVE.value  #活5简写
FOUR, THREE, TWO = CHESS_TYPE.LIVE_FOUR.value, CHESS_TYPE.LIVE_THREE.value, CHESS_TYPE.LIVE_TWO.value  #活432简写
SFOUR, STHREE, STWO = CHESS_TYPE.CHONG_FOUR.value, CHESS_TYPE.SLEEP_THREE.value, CHESS_TYPE.SLEEP_TWO.value  #冲4、眠32简写

SCORE_MAX = 0x7fffffff  #最大值
SCORE_MIN = -1 * SCORE_MAX  #最小值
SCORE_FIVE, SCORE_FOUR, SCORE_SFOUR = 100000, 10000, 1000  #活5、活4、冲4分数
SCORE_THREE, SCORE_STHREE, SCORE_TWO, SCORE_STWO = 100, 10, 8, 2  #活3、眠3、活2、眠2分数


class ChessAI():  #五子棋AI类
    def __init__(self, chess_len):
        self.len = chess_len  #棋盘每行每列节点数
        # [横、竖、左对角线、右对角线]
        self.record = [[[0, 0, 0, 0] for x in range(self.len)]
                       for y in range(self.len)]  #棋盘上每个棋子的分数
        self.count = [[0 for x in range(CHESS_TYPE_NUM)]
                      for i in range(2)]  #自己和对手现在的局势记录

    def reset(self):
        ''''重置record、count'''
        for y in range(self.len):
            for x in range(self.len):
                for i in range(4):
                    self.record[y][x][i] = 0
        for i in range(len(self.count)):
            for j in range(len(self.count[0])):
                self.count[i][j] = 0

    def evaluatePointScore(self, board, x, y, mine, opponent):
        '''计算某个点的四种得分'''
        dir_offset = [(1, 0), (0, 1), (1, 1),
                      (1, -1)]  # direction from left to right
        for i in range(len(self.count)):
            for j in range(len(self.count[0])):
                self.count[i][j] = 0

        board[y][x] = mine
        self.evaluatePoint(board, x, y, mine, opponent, self.count[mine - 1])
        mine_count = self.count[mine - 1]
        board[y][x] = opponent
        self.evaluatePoint(board, x, y, opponent, mine,
                           self.count[opponent - 1])
        opponent_count = self.count[opponent - 1]
        board[y][x] = 0

        mscore = self.getPointScore(mine_count)
        oscore = self.getPointScore(opponent_count)

        return (mscore, oscore)

    def hasNeighbor(self, board, x, y, radius):
        '''检查邻居是否满了,未满返回True'''
        start_x, end_x = (x - radius), (x + radius)
        start_y, end_y = (y - radius), (y + radius)

        for i in range(start_y, end_y + 1):
            for j in range(start_x, end_x + 1):
                if i >= 0 and i < self.len and j >= 0 and j < self.len:
                    if board[i][j] != 0:
                        return True
        return False

    def genmove(self, board, turn):
        '''返回可能走的所有情况'''
        fives = []
        mfours, ofours = [], []
        msfours, osfours = [], []
        if turn == 1:
            mine = 1
            opponent = 2
        else:
            mine = 2
            opponent = 1

        moves = []
        radius = 1

        for y in range(self.len):
            for x in range(self.len):
                if board[y][x] == 0 and self.hasNeighbor(board, x, y, radius):
                    mscore, oscore = self.evaluatePointScore(
                        board, x, y, mine, opponent)
                    point = (max(mscore, oscore), x, y)

                    if mscore >= SCORE_FIVE or oscore >= SCORE_FIVE:
                        fives.append(point)
                    elif mscore >= SCORE_FOUR:
                        mfours.append(point)
                    elif oscore >= SCORE_FOUR:
                        ofours.append(point)
                    elif mscore >= SCORE_SFOUR:
                        msfours.append(point)
                    elif oscore >= SCORE_SFOUR:
                        osfours.append(point)

                    moves.append(point)

        if len(fives) > 0: return fives

        if len(mfours) > 0: return mfours

        if len(ofours) > 0:
            if len(msfours) == 0:
                return ofours
            else:
                return ofours + msfours

        moves.sort(reverse=True)

        # FIXME: decrease think time: only consider limited moves with higher scores
        if self.maxdepth > 2 and len(moves) > AI_LIMITED_MOVE_NUM:
            moves = moves[:AI_LIMITED_MOVE_NUM]
        return moves

    def __search(self, board, turn, depth, alpha=SCORE_MIN, beta=SCORE_MAX):
        '''递归搜索下棋点，Alpha-beta剪枝算法'''
        score = self.evaluate(board, turn)
        if depth <= 0 or abs(score) >= SCORE_FIVE:
            return score

        moves = self.genmove(board, turn)
        bestmove = None
        self.alpha += len(moves)

        # if there are no moves, just return the score
        if len(moves) == 0:
            return score

        for _, x, y in moves:
            board[y][x] = turn

            if turn == 1:
                op_turn = 2
            else:
                op_turn = 1

            score = -self.__search(board, op_turn, depth - 1, -beta, -alpha)

            board[y][x] = 0
            self.belta += 1

            # alpha/beta pruning
            if score > alpha:
                alpha = score
                bestmove = (x, y)
                if alpha >= beta:
                    break

        if depth == self.maxdepth and bestmove:
            self.bestmove = bestmove

        return alpha

    def search(self, board, turn, depth=4):
        '''搜索下棋点，返回分数和坐标'''
        self.maxdepth = depth
        self.bestmove = None
        score = self.__search(board, turn, depth)
        x, y = self.bestmove
        return score, x, y

    def findBestChess(self, board, turn):
        '''AI找下一个下棋点'''
        time1 = time.time()
        self.alpha = 0
        self.belta = 0
        score, x, y = self.search(board, turn, AI_SEARCH_DEPTH)
        time2 = time.time()
        print('time[%.2f] (%d, %d), score[%d] alpha[%d] belta[%d]' %
              ((time2 - time1), x, y, score, self.alpha, self.belta))
        return (x, y)

    def getPointScore(self, count):
        score = 0
        if count[FIVE] > 0:
            return SCORE_FIVE

        if count[FOUR] > 0:
            return SCORE_FOUR

        # FIXME: the score of one chong four and no live three should be low, set it to live three
        if count[SFOUR] > 1:
            score += count[SFOUR] * SCORE_SFOUR
        elif count[SFOUR] > 0 and count[THREE] > 0:
            score += count[SFOUR] * SCORE_SFOUR
        elif count[SFOUR] > 0:
            score += SCORE_THREE

        if count[THREE] > 1:
            score += 5 * SCORE_THREE
        elif count[THREE] > 0:
            score += SCORE_THREE

        if count[STHREE] > 0:
            score += count[STHREE] * SCORE_STHREE
        if count[TWO] > 0:
            score += count[TWO] * SCORE_TWO
        if count[STWO] > 0:
            score += count[STWO] * SCORE_STWO

        return score

    # calculate score, FIXME: May Be Improved
    def getScore(self, mine_count, opponent_count):
        mscore, oscore = 0, 0
        if mine_count[FIVE] > 0:
            return (SCORE_FIVE, 0)
        if opponent_count[FIVE] > 0:
            return (0, SCORE_FIVE)

        if mine_count[SFOUR] >= 2:
            mine_count[FOUR] += 1
        if opponent_count[SFOUR] >= 2:
            opponent_count[FOUR] += 1

        if mine_count[FOUR] > 0:
            return (9050, 0)
        if mine_count[SFOUR] > 0:
            return (9040, 0)

        if opponent_count[FOUR] > 0:
            return (0, 9030)
        if opponent_count[SFOUR] > 0 and opponent_count[THREE] > 0:
            return (0, 9020)

        if mine_count[THREE] > 0 and opponent_count[SFOUR] == 0:
            return (9010, 0)

        if (opponent_count[THREE] > 1 and mine_count[THREE] == 0
                and mine_count[STHREE] == 0):
            return (0, 9000)

        if opponent_count[SFOUR] > 0:
            oscore += 400

        if mine_count[THREE] > 1:
            mscore += 500
        elif mine_count[THREE] > 0:
            mscore += 100

        if opponent_count[THREE] > 1:
            oscore += 2000
        elif opponent_count[THREE] > 0:
            oscore += 400

        if mine_count[STHREE] > 0:
            mscore += mine_count[STHREE] * 10
        if opponent_count[STHREE] > 0:
            oscore += opponent_count[STHREE] * 10

        if mine_count[TWO] > 0:
            mscore += mine_count[TWO] * 6
        if opponent_count[TWO] > 0:
            oscore += opponent_count[TWO] * 6

        if mine_count[STWO] > 0:
            mscore += mine_count[STWO] * 2
        if opponent_count[STWO] > 0:
            oscore += opponent_count[STWO] * 2

        return (mscore, oscore)

    def evaluate(self, board, turn, checkWin=False):
        self.reset()

        if turn == 1:
            mine = 1
            opponent = 2
        else:
            mine = 2
            opponent = 1

        for y in range(self.len):
            for x in range(self.len):
                if board[y][x] == mine:
                    self.evaluatePoint(board, x, y, mine, opponent)
                elif board[y][x] == opponent:
                    self.evaluatePoint(board, x, y, opponent, mine)

        mine_count = self.count[mine - 1]
        opponent_count = self.count[opponent - 1]
        if checkWin:
            return mine_count[FIVE] > 0
        else:
            mscore, oscore = self.getScore(mine_count, opponent_count)
            return (mscore - oscore)

    def evaluatePoint(self, board, x, y, mine, opponent, count=None):
        dir_offset = [(1, 0), (0, 1), (1, 1),
                      (1, -1)]  # direction from left to right
        ignore_record = True
        if count is None:
            count = self.count[mine - 1]
            ignore_record = False
        for i in range(4):
            if self.record[y][x][i] == 0 or ignore_record:
                self.analysisLine(board, x, y, i, dir_offset[i], mine,
                                  opponent, count)

    # line is fixed len 9: XXXXMXXXX
    def getLine(self, board, x, y, dir_offset, mine, opponent):
        line = [0 for i in range(9)]

        tmp_x = x + (-5 * dir_offset[0])
        tmp_y = y + (-5 * dir_offset[1])
        for i in range(9):
            tmp_x += dir_offset[0]
            tmp_y += dir_offset[1]
            if (tmp_x < 0 or tmp_x >= self.len or tmp_y < 0
                    or tmp_y >= self.len):
                line[i] = opponent  # set out of range as opponent chess
            else:
                line[i] = board[tmp_y][tmp_x]

        return line

    def analysisLine(self, board, x, y, dir_index, dir, mine, opponent, count):
        # record line range[left, right] as analysized
        def setRecord(self, x, y, left, right, dir_index, dir_offset):
            tmp_x = x + (-5 + left) * dir_offset[0]
            tmp_y = y + (-5 + left) * dir_offset[1]
            for i in range(left, right + 1):
                tmp_x += dir_offset[0]
                tmp_y += dir_offset[1]
                self.record[tmp_y][tmp_x][dir_index] = 1

        empty = 0
        left_idx, right_idx = 4, 4

        line = self.getLine(board, x, y, dir, mine, opponent)

        while right_idx < 8:
            if line[right_idx + 1] != mine:
                break
            right_idx += 1
        while left_idx > 0:
            if line[left_idx - 1] != mine:
                break
            left_idx -= 1

        left_range, right_range = left_idx, right_idx
        while right_range < 8:
            if line[right_range + 1] == opponent:
                break
            right_range += 1
        while left_range > 0:
            if line[left_range - 1] == opponent:
                break
            left_range -= 1

        chess_range = right_range - left_range + 1
        if chess_range < 5:
            setRecord(self, x, y, left_range, right_range, dir_index, dir)
            return CHESS_TYPE.NONE

        setRecord(self, x, y, left_idx, right_idx, dir_index, dir)

        m_range = right_idx - left_idx + 1

        # M:mine chess, P:opponent chess or out of range, X: empty
        if m_range >= 5:
            count[FIVE] += 1

        # Live Four : XMMMMX
        # Chong Four : XMMMMP, PMMMMX
        if m_range == 4:
            left_empty = right_empty = False
            if line[left_idx - 1] == empty:
                left_empty = True
            if line[right_idx + 1] == empty:
                right_empty = True
            if left_empty and right_empty:
                count[FOUR] += 1
            elif left_empty or right_empty:
                count[SFOUR] += 1

        # Chong Four : MXMMM, MMMXM, the two types can both exist
        # Live Three : XMMMXX, XXMMMX
        # Sleep Three : PMMMX, XMMMP, PXMMMXP
        if m_range == 3:
            left_empty = right_empty = False
            left_four = right_four = False
            if line[left_idx - 1] == empty:
                if line[left_idx - 2] == mine:  # MXMMM
                    setRecord(self, x, y, left_idx - 2, left_idx - 1,
                              dir_index, dir)
                    count[SFOUR] += 1
                    left_four = True
                left_empty = True

            if line[right_idx + 1] == empty:
                if line[right_idx + 2] == mine:  # MMMXM
                    setRecord(self, x, y, right_idx + 1, right_idx + 2,
                              dir_index, dir)
                    count[SFOUR] += 1
                    right_four = True
                right_empty = True

            if left_four or right_four:
                pass
            elif left_empty and right_empty:
                if chess_range > 5:  # XMMMXX, XXMMMX
                    count[THREE] += 1
                else:  # PXMMMXP
                    count[STHREE] += 1
            elif left_empty or right_empty:  # PMMMX, XMMMP
                count[STHREE] += 1

        # Chong Four: MMXMM, only check right direction
        # Live Three: XMXMMX, XMMXMX the two types can both exist
        # Sleep Three: PMXMMX, XMXMMP, PMMXMX, XMMXMP
        # Live Two: XMMX
        # Sleep Two: PMMX, XMMP
        if m_range == 2:
            left_empty = right_empty = False
            left_three = right_three = False
            if line[left_idx - 1] == empty:
                if line[left_idx - 2] == mine:
                    setRecord(self, x, y, left_idx - 2, left_idx - 1,
                              dir_index, dir)
                    if line[left_idx - 3] == empty:
                        if line[right_idx + 1] == empty:  # XMXMMX
                            count[THREE] += 1
                        else:  # XMXMMP
                            count[STHREE] += 1
                        left_three = True
                    elif line[left_idx - 3] == opponent:  # PMXMMX
                        if line[right_idx + 1] == empty:
                            count[STHREE] += 1
                            left_three = True

                left_empty = True

            if line[right_idx + 1] == empty:
                if line[right_idx + 2] == mine:
                    if line[right_idx + 3] == mine:  # MMXMM
                        setRecord(self, x, y, right_idx + 1, right_idx + 2,
                                  dir_index, dir)
                        count[SFOUR] += 1
                        right_three = True
                    elif line[right_idx + 3] == empty:
                        #setRecord(self, x, y, right_idx+1, right_idx+2, dir_index, dir)
                        if left_empty:  # XMMXMX
                            count[THREE] += 1
                        else:  # PMMXMX
                            count[STHREE] += 1
                        right_three = True
                    elif left_empty:  # XMMXMP
                        count[STHREE] += 1
                        right_three = True

                right_empty = True

            if left_three or right_three:
                pass
            elif left_empty and right_empty:  # XMMX
                count[TWO] += 1
            elif left_empty or right_empty:  # PMMX, XMMP
                count[STWO] += 1

        # Live Two: XMXMX, XMXXMX only check right direction
        # Sleep Two: PMXMX, XMXMP
        if m_range == 1:
            left_empty = right_empty = False
            if line[left_idx - 1] == empty:
                if line[left_idx - 2] == mine:
                    if line[left_idx - 3] == empty:
                        if line[right_idx + 1] == opponent:  # XMXMP
                            count[STWO] += 1
                left_empty = True

            if line[right_idx + 1] == empty:
                if line[right_idx + 2] == mine:
                    if line[right_idx + 3] == empty:
                        if left_empty:  # XMXMX
                            #setRecord(self, x, y, left_idx, right_idx+2, dir_index, dir)
                            count[TWO] += 1
                        else:  # PMXMX
                            count[STWO] += 1
                elif line[right_idx + 2] == empty:
                    if line[right_idx +
                            3] == mine and line[right_idx +
                                                4] == empty:  # XMXXMX
                        count[TWO] += 1

        return CHESS_TYPE.NONE
