import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from mpl_toolkits.axes_grid1.inset_locator import mark_inset


class Draw:
    def __init__(self, isShow=True, isClose=True):
        self.isShow = isShow
        self.isClose = isClose

    def drawPloterro(self, cc_list, name_list, title, isSave=False, figName=None, isDrawSub=True):
        '''绘制迭代-误差图'''
        fig, ax = plt.subplots(1, 1, figsize=(10, 6))
        if isDrawSub:
            axins = ax.inset_axes((0.65, 0.2, 0.25, 0.55))  # 局部放大图

        color = ['r', 'y', 'g', 'b']
        for i in range(len(cc_list)):
            cc = cc_list[i]
            x = [i for i in range(len(cc))]
            ax.plot(x, cc, color[i], linewidth=1.5,
                    markersize=5, label=name_list[i])
            if isDrawSub:
                axins.plot(x, cc, color[i], linewidth=1.5,
                           markersize=5, label=name_list[i])

        # 主图
        # y轴的显示范围
        ylim = None
        if len(name_list) >= 3:  # 画三条线以上
            y_ = np.array(cc_list)[:, 10]
            ylim = y_[np.argsort(y_)[1:3]].mean()
        # 设置
        ax.set_xlabel('Iter')
        ax.set_ylabel('Best score')
        ax.set_xlim(0, )
        # ax.set_ylim(0, ylim)
        ax.legend()
        ax.set_title(title)

        # 局部图
        if isDrawSub:
            # X轴的显示范围
            xlim_l = int(0.9 * len(cc))
            xlim_u = len(cc)
            if isDrawSub:
                axins.set_xlim(xlim_l, xlim_u)
            # y轴的显示范围
            y_xl = np.array(cc_list)[:, int(
                np.array([xlim_u, xlim_l]).mean())-1]
            y_xu = np.array(cc_list)[:, xlim_u-1]
            arg_y_xl = np.argsort(y_xl)
            if len(cc_list) > 3:
                ylim = y_xl[arg_y_xl[3]] * 1.2
                if y_xl[arg_y_xl[3]] > (y_xl[arg_y_xl[2]]*100):
                    ylim = y_xl[arg_y_xl[2]] * 1.2
                if y_xl[arg_y_xl[2]] > (y_xl[arg_y_xl[1]]*100):
                    ylim = y_xl[arg_y_xl[1]] * 1.2
                axins.set_ylim(y_xu.min()-ylim/10, ylim)
            # loc1 loc2: 坐标系的四个角
            # 1 (右上) 2 (左上) 3(左下) 4(右下)
            mark_inset(ax, axins, loc1=3, loc2=1, fc="none", ec='k', lw=1)

        if isSave:
            plt.savefig(figName)
            plt.close()
        if self.isShow:
            plt.show()

    def drawPopScatter3D(self, pop_x, lb, ub, fobj):
        '''绘制3D种群分布图(2-dim)'''
        # fobj
        figure = plt.figure()
        axes = Axes3D(figure)
        step = 2
        X = np.arange(lb[0], ub[0], step)
        Y = np.arange(lb[1], ub[1], step)
        X, Y = np.meshgrid(X, Y)
        Z = np.zeros(X.shape)
        for i in range(X.shape[0]):
            for j in range(X.shape[1]):
                Z[i, j] = fobj(np.array([X[i, j], Y[i, j]]))
        axes.plot_surface(X, Y, Z, cmap='rainbow', alpha=.3)

        # pop
        z = np.empty(pop_x.shape[0])
        for i in range(pop_x.shape[0]):
            z[i] = fobj(pop_x[i])
        z = z.T
        pop_t = pop_x.T
        x, y = pop_t[0], pop_t[1]
        axes.scatter(x, y, z, c='r', marker='.')

        plt.xlim(lb[0], ub[0])
        plt.ylim(lb[1], ub[1])
        plt.title(fobj.__doc__)

        if self.isClose:
            plt.ion()
            plt.pause(0.2)
            plt.close()
        else:
            plt.show()

    def drawPopScatter2D(self, pop_x, lb, ub, fobj):
        '''绘制2D种群分布图(2-dim)'''
        # fobj
        plt.figure()
        step = 1
        X = np.arange(lb[0], ub[0], step)
        Y = np.arange(lb[1], ub[1], step)
        X, Y = np.meshgrid(X, Y)
        Z = np.zeros(X.shape)
        for i in range(X.shape[0]):
            for j in range(X.shape[1]):
                Z[i, j] = fobj(np.array([X[i, j], Y[i, j]]))
        plt.contourf(X, Y, Z)
        plt.contour(X, Y, Z)

        # pop
        pop_t = pop_x.T
        x, y = pop_t[0], pop_t[1]
        plt.scatter(x, y, c='r', marker='.', zorder=2)

        plt.xlim(lb[0], ub[0])
        plt.ylim(lb[1], ub[1])
        plt.title(fobj.__doc__)

        if self.isClose:
            plt.ion()
            plt.pause(0.2)
            plt.close()
        else:
            plt.show()

    def drawFunction3D(self, lb, ub, fobj, isSave=False, figName=None):
        '''绘制函数3D图(2-dim)'''
        lb = lb[0]
        ub = ub[0]

        figure = plt.figure()
        axes = Axes3D(figure)
        X = np.arange(lb, ub, 1)
        Y = np.arange(lb, ub, 1)

        X, Y = np.meshgrid(X, Y)
        Z = np.zeros(X.shape)

        for i in range(X.shape[0]):
            for j in range(X.shape[1]):
                Z[i, j] = fobj(np.array([X[i, j], Y[i, j]]))
        axes.plot_surface(X, Y, Z, cmap='rainbow')
        print(fobj.__doc__)

        if isSave:
            plt.savefig(figName)
            plt.close()
        if self.isShow:
            plt.show()
