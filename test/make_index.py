from indexer import Indexer
import sys

source_file = sys.argv[1]
index_file = sys.argv[2]

idxr = Indexer(source_file, index_file)
idxr.make_index()

sys.stdout.write("Done !!\n")
