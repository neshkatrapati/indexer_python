cimport indexer
cimport libc.stdio



cdef class IndexedFile(object):
    """A file which reads the source_file"""
    cdef FILE* source_file
    cdef FILE* index_file
    def __init__(self, source_file_name, index_file_name):
        self.source_file = fopen(source_file_name, "r")
        self.index_file = fopen(index_file_name, "r")

    def read(self, line_number):
        return read_from_index(self.source_file, self.index_file, line_number)

    def close(self):
        fclose(self.source_file)
        fclose(self.index_file)

class Indexer(object):
    """Loads up indexer"""
    def __init__(self, source_file_name, index_file_name):
        self.source_file_name = source_file_name
        self.index_file_name = index_file_name

    def make_index(self):
        make_index_from_file(self.source_file_name, self.index_file_name, 0)

    def __enter__(self):
        self.if_object = IndexedFile(self.source_file_name, self.index_file_name)
        return self.if_object

    def __exit__(self, type, value, traceback):
        self.if_object.close()
