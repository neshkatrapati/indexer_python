from indexer import Indexer
import sys

source_file = sys.argv[1]
index_file = sys.argv[2]
line_number = int(sys.argv[3])

idxr = Indexer(source_file, index_file)

with idxr as i:
    print i.read(line_number)
