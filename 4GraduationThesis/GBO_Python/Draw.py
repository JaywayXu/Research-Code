import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


class Draw:
    def __init__(self, isShow=True, isSavefig=False, isClose=True):
        self.isShow = isShow
        self.isSavefig = isSavefig
        self.isClose = isClose

    def drawPloterro(self, convergence_curve_list, name_list, title, y_lim=None):
        '''绘制迭代-误差图'''
        plt.figure(figsize=(10, 6))

        color = ['r', 'y', 'g', 'b']
        for i in range(len(convergence_curve_list)):
            cc = convergence_curve_list[i]
            x = [i for i in range(len(cc))]
            plt.plot(x, cc, color[i], linewidth=1.5,
                     markersize=5, label=name_list[i])

        plt.xlabel('Iter')
        plt.ylabel('Best score')
        plt.xlim(0, )
        plt.ylim(0, y_lim)
        plt.legend()
        plt.title(title)

        if self.isSavefig:
            plt.savefig("./Ploterro_Figure/Ploterro_"+title+".png")
        if self.isShow:
            plt.show()

    def drawPopScatter3D(self, pop_x, lb, ub, fobj):
        '''绘制3D种群分布图(2-dim)'''
        # fobj
        figure = plt.figure()
        axes = Axes3D(figure)
        step = 0.2
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

        if self.isShow:
            plt.show()
        else:
            plt.ion()
            plt.pause(0.2)
            plt.close()

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

    def drawFunction3D(self, lb, ub, fobj):
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

        if self.isShow:
            plt.show()
