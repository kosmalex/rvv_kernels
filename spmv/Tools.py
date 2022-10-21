from inspect import ArgInfo
from tkinter.tix import ROW, Form
from scipy.sparse import random
from scipy.sparse import csr_matrix, csc_matrix, bsr_matrix
from scipy import stats
from numpy.random import default_rng

ROWS = 0
COLS = 1
DENSITY = 2
FORMAT = 3
BLK_DIM = 4
TYPE = 5
SHUFFLE = 6

class label:
  ptr = ''
  idx = ''

__rng = default_rng()
__rvs = stats.poisson(25, loc=10).rvs
__random_mat = None
__random_vec = None

def generate(*args):
  global __rng, __rvs
  global __random_vec

  try:
    nRows = int(args[ROWS])
    nCols = int(args[COLS])
    density = float(args[DENSITY])
    blk_width = int(args[BLK_DIM])
    shuffle = bool(int(args[SHUFFLE]))
  except:
    print("[Error]: Something's wrong with the entered args")

  SpM = None
  try:
    SpM = __get_matrix_in_format(args[FORMAT], nRows, nCols, density, (blk_width, blk_width), shuffle, __rng, __rvs)
  except:
    SpM = __get_matrix_in_format(args[FORMAT], nRows, nCols, density, (2, 2), shuffle, __rng, __rvs)

  print(SpM.indices)

  #<SpMM second matrix>
  #Not yet implemented
  if shuffle or __random_vec is None:
    __random_vec = __rng.random((nCols, ))

  DenV = 200 * __random_vec + 1
  #<SpMM second matrix/>
  
  #Labels to name *_ptr and *_idx arrays for csr, csc and csb formats 
  __get_ptr_label(args[FORMAT])
    
  #<Text generation>

  head_B = ["#define B " + str(len(SpM.indptr)), "#define B_WIDTH " + str(blk_width)] if 'csb' in args[FORMAT] else ["", ""] 

  text = [
        "#define R " + str(nRows),
        "#define C " + str(nCols),
        "#define NNZ " + str(SpM.count_nonzero()) + "\n",
        head_B[0],
        head_B[1],

        "int "+label.ptr+"_ptr["+str(len(SpM.indptr))+"]={", 
  ]

  length = len(SpM.indptr)
  for i in range(length):
      if i < length - 1:
          text.append(str(SpM.indptr[i]) + ",")
      else:
          text.append(str(SpM.indptr[i]))
  
  text.extend([
    "};",
    "",
    "int "+label.idx+"_idx["+str(len(SpM.indices))+"]={",
  ])

  length = len(SpM.indices)
  for i in range(length):
      if i < length - 1:
          text.append(str(SpM.indices[i]) + ",")
      else:
          text.append(str(SpM.indices[i]))

  data_count = SpM.count_nonzero() if 'csb' not in args[FORMAT] else len(SpM.data) * blk_width**2
  text.extend([
    "};",
    "",
    "float data["+str(data_count)+"]={",
  ])

  data = __unpack_bsr_data(SpM) if 'csb' in args[FORMAT] else SpM.data
  length = len(data)
  for i in range(length):
    if i < length - 1:
        text.append(str(data[i]) + ",")
    else:
        text.append(str(data[i]))

  text.extend([
        "};\n",
        "float x["+str(nCols)+"]={",
    ])

  length = len(DenV)
  for i in range(length):
    if i < length - 1:
        text.append(str(round(DenV[i], 2)) + ",")
    else:
        text.append(str(round(DenV[i], 2)))

  text.extend([
      "};",
  ])

  if '>' in args:
    with open(args[args.index('>') + 1], 'w') as file:
      for line in text:
        file.write(line +'\n')  
  else:
    for line in text:
      print(line)
  #<Text generation/>
  pass


#private methods
def __get_matrix_in_format(format:str, nRows:int, nCols:int, density:float, blk_size:tuple[int, int], shuffle:bool, __rng, __rvs) -> csr_matrix | csc_matrix | bsr_matrix | None:
  global __random_mat

  matrix_seed = None
  
  #If user wants to 'shuffle', that is generate a new random matrix, do that and save it in __random_mat
  #in case the user wants to generate the same random matrix in another format.
  if shuffle:
    matrix_seed = random(nRows, nCols, density, random_state=__rng, data_rvs=__rvs)
    __random_mat = matrix_seed
  else:
    #If __random_mat is not yet set, set it despite user 'shuffle' input
    if __random_mat is None:
      matrix_seed = random(nRows, nCols, density, random_state=__rng, data_rvs=__rvs)
      __random_mat = matrix_seed
    else: 
      matrix_seed = __random_mat #If there is a saved random_matrix and user wants to reuse it
  
  if 'csr' in format:
    return csr_matrix(matrix_seed)
  
  elif 'csc' in format:
    return csc_matrix(matrix_seed)
  
  elif 'csb' in format:
    return bsr_matrix(matrix_seed, blocksize=blk_size)

def __get_ptr_label(format:str) -> None:
  if 'csr' in format:
    label.ptr = 'row'
    label.idx = 'col'
  
  elif 'csc' in format:
    label.ptr = 'col'
    label.idx = 'row'
  
  elif 'csb' in format:
    label.ptr = 'blk'
    label.idx = 'intra_blk'

def __unpack_bsr_data(mat:bsr_matrix) -> list:
  return [mat.data[blk][row][col] for blk in range(len(mat.data)) for row in range(len(mat.data[blk])) for col in range(len(mat.data[blk][row]))]
