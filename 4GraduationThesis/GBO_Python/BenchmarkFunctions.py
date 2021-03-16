import numpy as np


class BenchmarkFunctions:
    def __init__(self, D=30):
        self.D = D
        self.size = 14
        self.switch = {
            1: self.f1,
            2: self.f2,
            3: self.f3,
            4: self.f4,
            5: self.f5,
            6: self.f6,
            7: self.f7,
            8: self.f8,
            9: self.f9,
            10: self.f10,
            11: self.f11,
            12: self.f12,
            13: self.f13,
            14: self.f14,
        }

    def get(self, fname):
        method = self.switch.get(fname)
        return method()

    def f1(self):
        lb = np.full((self.D), -100)
        ub = np.full((self.D), 100)
        fobj = f1_obj
        return [lb, ub, self.D, fobj]

    def f2(self):
        lb = np.full((self.D), -100)
        ub = np.full((self.D), 100)
        fobj = f2_obj
        return [lb, ub, self.D, fobj]

    def f3(self):
        lb = np.full((self.D), -100)
        ub = np.full((self.D), 100)
        fobj = f3_obj
        return [lb, ub, self.D, fobj]

    def f4(self):
        lb = np.full((self.D), -100)
        ub = np.full((self.D), 100)
        fobj = f4_obj
        return [lb, ub, self.D, fobj]

    def f5(self):
        lb = np.full((self.D), -100)
        ub = np.full((self.D), 100)
        fobj = f5_obj
        return [lb, ub, self.D, fobj]

    def f6(self):
        lb = np.full((self.D), -100)
        ub = np.full((self.D), 100)
        fobj = f6_obj
        return [lb, ub, self.D, fobj]

    def f7(self):
        lb = np.full((self.D), -100)
        ub = np.full((self.D), 100)
        fobj = f7_obj
        return [lb, ub, self.D, fobj]

    def f8(self):
        lb = np.full((self.D), -100)
        ub = np.full((self.D), 100)
        fobj = f8_obj
        return [lb, ub, self.D, fobj]

    def f9(self):
        lb = np.full((self.D), -100)
        ub = np.full((self.D), 100)
        fobj = f9_obj
        return [lb, ub, self.D, fobj]

    def f10(self):
        lb = np.full((self.D), -32.768)
        ub = np.full((self.D), 32.768)
        fobj = f10_obj
        return [lb, ub, self.D, fobj]

    def f11(self):
        lb = np.full((self.D), -100)
        ub = np.full((self.D), 100)
        fobj = f11_obj
        return [lb, ub, self.D, fobj]

    def f12(self):
        lb = np.full((self.D), -100)
        ub = np.full((self.D), 100)
        fobj = f12_obj
        return [lb, ub, self.D, fobj]

    def f13(self):
        lb = np.full((self.D), -100)
        ub = np.full((self.D), 100)
        fobj = f13_obj
        return [lb, ub, self.D, fobj]

    def f14(self):
        lb = np.full((self.D), -100)
        ub = np.full((self.D), 100)
        fobj = f14_obj
        return [lb, ub, self.D, fobj]


def f1_obj(x):
    '''f1: Bent Cigar (Unimodal)'''
    D = x.shape[0]
    z = np.power(x[0], 2) + pow(10, 6) * np.power(x[1:D], 2).sum()
    return z


def f2_obj(x):
    '''f2: Power (Unimodal)'''
    D = x.shape[0]
    f = np.zeros([D, 1])
    for i in range(D):
        f[i] = np.power(abs(x[i]), (i + 1))
    z = f.sum()
    return z


def f3_obj(x):
    '''f3: Zakharov (Unimodal)'''
    z = np.power(x, 2).sum() + pow((x.sum() * 0.5), 2) + pow(
        (x.sum() * 0.5), 4)
    return z


def f4_obj(x):
    '''f4: Rosenbrock (Unimodal)'''
    D = x.shape[0]
    ff = np.zeros([D - 1, 1])
    for i in range(D - 1):
        ff[i] = 100 * np.power((np.power(x[i], 2) - x[i + 1]), 2) + np.power(
            (x[i] - 1), 2)
    z = ff.sum()
    return z


def f5_obj(x):
    '''f5: Discus (Unimodal)'''
    D = x.shape[0]
    z = pow(10, 6) * np.power(x[0], 2) + np.power(x[1:D], 2).sum()
    return z


def f6_obj(x):
    '''f6: High Conditioned Elliptic Function (Unimodal)'''
    D = x.shape[0]
    f = np.zeros([D, 1])
    for i in range(D):
        f[i] = pow(pow(10, 6), (i - 1) / (D - 1)) * np.power(x[i], 2)
    z = f.sum()
    return z


def f7_obj(x):
    '''f7: Expanded Schaffer’s F6 (Multimodal)'''
    D = x.shape[0]
    f = np.zeros([D, 1])
    for i in range(D):
        if i == D - 1:
            f[i] = 0.5 + (
                pow(np.sin(np.sqrt(pow(x[i], 2) + pow(x[0], 2))), 2) -
                0.5) / pow(1 + 0.001 * (pow(x[i], 2) + pow(x[0], 2)), 2)
        else:
            f[i] = 0.5 + (
                pow(np.sin(np.sqrt(pow(x[i], 2) + pow(x[i + 1], 2))), 2) -
                0.5) / pow(1 + 0.001 * (pow(x[i], 2) + pow(x[i + 1], 2)), 2)
    z = f.sum()
    return z


def f8_obj(x):
    '''f8: Levy Function (Multimodal)'''
    D = x.shape[0]
    w = np.zeros([D, 1])
    f = np.zeros([D - 1, 1])
    for i in range(D - 1):
        w[i] = 1 + (x[i] - 1) / 4
        f[i] = pow((w[i] - 1), 2) * (1 + 10 * pow(np.sin(np.pi * w[i] + 1), 2))
    w[D - 1] = 1 + (x[D - 1] - 1) / 4
    z = pow(np.sin(np.pi*w[0]), 2) + f.sum() + \
        pow((w[D-1]-1), 2) * (1 + pow(np.sin(2*np.pi*w[D-1]), 2))
    return z


def f9_obj(x):
    '''f9: Modified Schwefel’s Function (Multimodal)'''
    D = x.shape[0]
    f = np.zeros([D, 1])
    for i in range(D):
        y = x[i] + 4.209687462275036e+002
        if abs(y) < 500:
            f[i] = y * np.sin(pow(abs(y), 0.5))
        elif y > 500:
            f[i] = (500 - y % 500) * np.sin(np.sqrt(abs(500 - y % 500))) - pow(
                (y - 500), 2) / (10000 * D)
        elif y < -500:
            f[i] = (abs(y) % 500 - 500) * np.sin(
                np.sqrt(abs(abs(y) % 500 - 500))) - pow(
                    (y + 500), 2) / (10000 * D)
    z = 418.9829 * D - f.sum()
    return z


def f10_obj(x):
    '''f10: Ackley (Multimodal)'''
    D = x.shape[0]
    z = -20 * np.exp(-0.2 * pow((1/D) * np.power(x, 2).sum(), 0.5)) - \
        np.exp((1/D) * np.cos(2*np.pi*x).sum()) + 20 + np.exp(1)
    return z


def f11_obj(x):
    '''f11: weierstrass (Multimodal)'''
    def w(x1, c1, c2):
        y = (c1 * np.cos(c2 * x1)).sum()
        return y

    D = x.shape[0]
    x = x + 0.5
    a = 0.5
    b = 3
    kmax = 20
    c1 = np.zeros([20])
    c2 = np.zeros([20])
    c1[0:kmax] = np.power(a, range(kmax))
    c2[0:kmax] = 2 * np.pi * np.power(b, range(kmax))
    f = 0
    c = -w(0.5, c1, c2)
    for i in range(D):
        f = f + w(x[i], c1, c2)
    z = f + c * D
    return z


def f12_obj(x):
    '''f12: HappyCat Function (Multimodal)'''
    D = x.shape[0]
    z = pow(abs(np.power(x, 2).sum() - D), 1/4) + \
        (0.5 * np.power(x, 2).sum() + x.sum()) / D + 0.5
    return z


def f13_obj(x):
    '''f13: HGBat Function (Multimodal)'''
    D = x.shape[0]
    z = pow(abs(pow(np.power(x, 2).sum(), 2) - pow(x.sum(), 2)),
            1 / 2) + (0.5 * np.power(x, 2).sum() + x.sum()) / D + 0.5
    return z


def f14_obj(x):
    '''f14: Alpine (Multimodal)'''
    z = sum(abs(x * np.sin(x) + 0.1 * x))
    return z
