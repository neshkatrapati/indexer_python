from indexer import Indexer
import sys

source_file = sys.argv[1]
index_file = sys.argv[2]
line_number = int(sys.argv[3])

idxr = Indexer(source_file, index_file)

with idxr as i:
    for index, line in enumerate(i):
        if index < line_number:
            print index, line
        else:
            break
