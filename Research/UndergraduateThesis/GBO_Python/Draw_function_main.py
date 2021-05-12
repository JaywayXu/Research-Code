from Draw import Draw
from BenchmarkFunctions import BenchmarkFunctions

if __name__ == '__main__':
    draw = Draw()
    bmf = BenchmarkFunctions(D=2)

    for fname in range(1, bmf.size+1):
        lb, ub, nV, fobj = bmf.get(fname)
        figname = './FunctionFigure/F%d_%s' % (fname, fobj.__doc__)
        draw.drawFunction3D(lb, ub, fobj, isSave=True, figName=figname)
