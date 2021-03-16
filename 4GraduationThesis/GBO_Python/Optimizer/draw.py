import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


def drawPloterro(convergence_curve_list, name_list):
    '''绘制迭代-误差图'''
    plt.figure(figsize=(10, 6))

    color = ['r', 'y', 'g', 'b']
    for i in range(len(convergence_curve_list)):
        cc = convergence_curve_list[i]
        x = [i for i in range(len(cc))]
        plt.plot(x, cc, color[i], linewidth=1.5,
                 markersize=5, label=name_list[i])

    plt.xlabel(u'Iter', fontsize=18)
    plt.ylabel(u'Best score', fontsize=18)
    plt.xticks(fontsize=18)
    plt.yticks(fontsize=18)
    plt.xlim(0, )
    plt.legend()
    plt.grid(True)
    plt.show()


def drawPopScatter3D(pop_x, lb, ub, fobj):
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
    plt.ion()
    plt.pause(0.2)
    plt.close()
    # plt.show()


def drawPopScatter2D(pop_x, lb, ub, fobj):
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
    plt.ion()
    plt.pause(0.2)
    plt.close()
    # plt.show()


def drawFunction3D(lb, ub, fobj):
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
    plt.show()
