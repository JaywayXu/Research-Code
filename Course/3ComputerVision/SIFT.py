from PIL import Image
from numpy import *
from pylab import *
import os


def process_image(imagename, resultname, params="--edge-thresh 10 --peak-thresh 5"):
    """ Process an image and save the results in a file. """

    if imagename[-3:] != 'pgm':
        # create a pgm file
        # .convert('L') 将RGB图像转为灰度模式，灰度值范围[0,255]
        im = Image.open(imagename).convert('L')
        im.save('tmp.pgm')  # 将灰度值图像信息保存在.pgm文件中
        imagename = 'tmp.pgm'

    cmmd = str(".\sift.exe "+imagename+" --output="+resultname +
               " "+params)
    os.system(cmmd)  # 执行sift可执行程序，生成resultname(test.sift)文件
    print('processed', imagename, 'to', resultname)


def read_features_from_file(filename):
    """ Read feature properties and return in matrix form. """

    f = loadtxt(filename)
    return f[:, :4], f[:, 4:]  # feature locations, descriptors


def plot_features(im, locs, circle=True):
    """ Show image with features. input: im (image as array), 
        locs (row, col, scale, orientation of each feature). """

    def draw_circle(c, r):
        t = arange(0, 1.01, .01)*2*pi
        x = r*cos(t) + c[0]
        y = r*sin(t) + c[1]
        plot(x, y, 'b', linewidth=2)

    imshow(im)
    if circle:
        for p in locs:
            draw_circle(p[:2], p[2])
    else:
        plot(locs[:, 0], locs[:, 1], 'ob')
    axis('off')


if __name__ == '__main__':
    imname = ('main.png')  # 待处理图像路径
    im = Image.open(imname)
    process_image(imname, 'test.sift')
    # l1为兴趣点坐标、尺度和方位角度 l2是对应描述符的128 维向
    l1, d1 = read_features_from_file('test.sift')
    figure()
    gray()
    plot_features(im, l1, circle=True)
    title('sift-features')
    show()
