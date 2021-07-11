# https://medium.com/better-programming/load-fast-load-big-with-compressed-pickles-5f311584507e
import bz2
import _pickle as cPickle


def load_compressed_pickle(path):
    data = bz2.BZ2File(path, 'rb')
    data = cPickle.load(data)
    return data
