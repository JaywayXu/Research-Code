import numpy as np


class BenchmarkFunctions:
    def __init__(self):
        self.D = 30
        self.switch = {
            "F1": self.f1,
            "F2": self.f2,
            "F3": self.f3,
            "F4": self.f4,
            "F5": self.f5,
            "F6": self.f6,
            "F7": self.f7,
            "F8": self.f8,
            "F9": self.f9,
            "F10": self.f10,
            "F11": self.f11,
            "F12": self.f12,
            "F13": self.f13,
            "F14": self.f14,
        }

    def get(self, fname):
        method = self.switch.get(fname)
        return method()

    def f1(self):
        lb = -100
        ub = 100
        dim = self.D
        fobj = self.f1_obj
        return [lb, ub, dim, fobj]

    def f2(self):
        lb = -100
        ub = 100
        dim = self.D
        fobj = self.f2_obj
        return [lb, ub, dim, fobj]

    def f3(self):
        lb = -100
        ub = 100
        dim = self.D
        fobj = self.f3_obj
        return [lb, ub, dim, fobj]

    def f4(self):
        lb = -100
        ub = 100
        dim = self.D
        fobj = self.f4_obj
        return [lb, ub, dim, fobj]

    def f5(self):
        lb = -100
        ub = 100
        dim = self.D
        fobj = self.f5_obj
        return [lb, ub, dim, fobj]

    def f6(self):
        lb = -100
        ub = 100
        dim = self.D
        fobj = self.f6_obj
        return [lb, ub, dim, fobj]

    def f7(self):
        lb = -100
        ub = 100
        dim = self.D
        fobj = self.f7_obj
        return [lb, ub, dim, fobj]

    def f8(self):
        lb = -100
        ub = 100
        dim = self.D
        fobj = self.f8_obj
        return [lb, ub, dim, fobj]

    def f9(self):
        lb = -100
        ub = 100
        dim = self.D
        fobj = self.f9_obj
        return [lb, ub, dim, fobj]

    def f10(self):
        lb = -32.768
        ub = 32.768
        dim = self.D
        fobj = self.f10_obj
        return [lb, ub, dim, fobj]

    def f11(self):
        lb = -100
        ub = 100
        dim = self.D
        fobj = self.f11_obj
        return [lb, ub, dim, fobj]

    def f12(self):
        lb = -100
        ub = 100
        dim = self.D
        fobj = self.f12_obj
        return [lb, ub, dim, fobj]

    def f13(self):
        lb = -100
        ub = 100
        dim = self.D
        fobj = self.f13_obj
        return [lb, ub, dim, fobj]

    def f14(self):
        lb = -10
        ub = 10
        dim = self.D
        fobj = self.f14_obj
        return [lb, ub, dim, fobj]

    def f1_obj(self, x):
        '''Bent Cigar (Unimodal)'''
        D = x.shape[0]
        z = np.power(x[1], 2) + pow(10, 6) * np.power(x[2:D], 2).sum()
        return z

    def f2_obj(self, x):
        '''Power (Unimodal)'''
        D = x.shape[0]
        f = np.zeros([D, 1])
        for i in range(D):
            f[i] = np.power(abs(x[i]), (i + 1))
        z = f.sum()
        return z

    def f3_obj(self, x):
        '''Zakharov (Unimodal)'''
        z = np.power(x, 2).sum() + pow((x.sum() * 0.5), 2) + pow(
            (x.sum() * 0.5), 4)
        return z

    def f4_obj(self, x):
        '''Rosenbrock (Unimodal)'''
        D = x.shape[0]
        ff = np.zeros([D - 1, 1])
        for i in range(D - 1):
            ff[i] = 100 * np.power(
                (np.power(x[i], 2) - x[i + 1]), 2) + np.power((x[i] - 1), 2)
        z = ff.sum()
        return z

    def f5_obj(self, x):
        '''Discus (Unimodal)'''
        D = x.shape[0]
        z = pow(10, 6) * np.power(x[0], 2) + np.power(x[1:D], 2).sum()
        return z

    def f6_obj(self, x):
        '''High Conditioned Elliptic Function (Unimodal)'''
        D = x.shape[0]
        f = np.zeros([D, 1])
        for i in range(D):
            f[i] = pow(pow(10, 6), (i - 1) / (D - 1)) * np.power(x[i], 2)
        z = f.sum()
        return z

    def f7_obj(self, x):
        '''Expanded Schaffer’s F6 (Multimodal)'''
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
                    0.5) / pow(1 + 0.001 *
                               (pow(x[i], 2) + pow(x[i + 1], 2)), 2)
        z = f.sum()
        return z

    def f8_obj(self, x):
        '''Levy Function (Multimodal)'''
        D = x.shape[0]
        w = np.zeros([D, 1])
        f = np.zeros([D - 1, 1])
        for i in range(D - 1):
            w[i] = 1 + (x[i] - 1) / 4
            f[i] = pow(
                (w[i] - 1), 2) * (1 + 10 * pow(np.sin(np.pi * w[i] + 1), 2))
        w[D - 1] = 1 + (x[D - 1] - 1) / 4
        z = pow(np.sin(np.pi*w[0]), 2) + f.sum() + \
            pow((w[D-1]-1), 2) * (1 + pow(np.sin(2*np.pi*w[D-1]), 2))
        return z

    def f9_obj(self, x):
        '''Modified Schwefel’s Function (Multimodal)'''
        D = x.shape[0]
        f = np.zeros([D, 1])
        for i in range(D):
            y = x[i] + 4.209687462275036e+002
            if abs(y) < 500:
                f[i] = y * np.sin(pow(abs(y), 0.5))
            elif y > 500:
                f[i] = (500 - y % 500) * np.sin(np.sqrt(
                    abs(500 - y % 500))) - pow((y - 500), 2) / (10000 * D)
            elif y < -500:
                f[i] = (abs(y) % 500 - 500) * np.sin(
                    np.sqrt(abs(abs(y) % 500 - 500))) - pow(
                        (y + 500), 2) / (10000 * D)
        z = 418.9829 * D - f.sum()
        return z

    def f10_obj(self, x):
        '''Ackley (Multimodal)'''
        D = x.shape[0]
        z = -20 * np.exp(-0.2 * pow((1/D) * np.power(x, 2).sum(), 0.5)) - \
            np.exp((1/D) * np.cos(2*np.pi*x).sum()) + 20 + np.exp(1)
        return z

    def f11_obj(self, x):
        '''weierstrass (Multimodal)'''
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

    def f12_obj(self, x):
        '''HappyCat Function (Multimodal)'''
        D = x.shape[0]
        z = pow(abs(np.power(x, 2).sum() - D), 1/4) + \
            (0.5 * np.power(x, 2).sum() + x.sum()) / D + 0.5
        return z

    def f13_obj(self, x):
        '''HGBat Function (Multimodal)'''
        D = x.shape[0]
        z = pow(abs(pow(np.power(x, 2).sum(), 2) - pow(x.sum(), 2)),
                1 / 2) + (0.5 * np.power(x, 2).sum() + x.sum()) / D + 0.5
        return z

    def f14_obj(self, x):
        '''Alpine (Multimodal)'''
        z = sum(abs(x * np.sin(x) + 0.1 * x))
        return z
