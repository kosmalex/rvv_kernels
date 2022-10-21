from scipy.sparse import random
from scipy.sparse import csr_matrix
from scipy import stats
from numpy.random import default_rng
import sys


argc = len(sys.argv)

if argc == 2:
    if(sys.argv[1] == '--help'):
        print(
            "generator.py [ROWS] [COLS] [DENSITY]\n",
            "   This script creates:\n",
            "       2 sparse matrices of random floats with a certain degree of density:\n",
            "           DENSITY = [0, 1]\n",
            "   and prints the result.\n"
        )
    else:
        print("Try --help command")
elif argc == 4:
    Rows = int(sys.argv[1])
    Cols = int(sys.argv[2])
    density = float(sys.argv[3])
    
    rng = default_rng()
    rvs = stats.poisson(25, loc=10).rvs
    
    # SpM = csr_matrix([[0, 0, 0, 0, 3, 0],
    #                   [0, 0, 9, 0, 4, 0],
    #                   [0, 8, 0, 0, 0, 7],
    #                   [2, 0, 0, 0, 0, 0],
    #                   [0, 0, 0, 0, 0, 0]])
    SpM = csr_matrix(random(Rows, Cols, density=density, random_state=rng, data_rvs=rvs))

    # SpM1 = csr_matrix([[2, 0, 0, 0, 0, 0],
    #                    [0, 0, 18, 0, 0, 0],
    #                    [0, 3, 0, 24, 0, 17],
    #                    [0, 0, 0, 0, 0, 0],
    #                    [0, 0, 0, 6, 0, 0]])
    SpM1 = csr_matrix(random(Rows, Cols, density=density, random_state=rng, data_rvs=rvs))

    text = [
        "#define R " + str(Rows),
        "#define C " + str(Cols),
        "#define NNZA " + str(SpM.count_nonzero()),
        "#define NNZB " + str(SpM1.count_nonzero()) + "\n",
        
        "int row_ptrA["+str(len(SpM.indptr))+"]={", 
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
        "int col_idxA["+str(len(SpM.indices))+"]={",
    ])

    length = len(SpM.indices)
    for i in range(length):
        if i < length - 1:
            text.append(str(SpM.indices[i]) + ",")
        else:
            text.append(str(SpM.indices[i]))

    text.extend([
        "};",
        "",
        "float dataA["+str(SpM.count_nonzero())+"]={",
    ])

    length = len(SpM.data)
    for i in range(length):
        if i < length - 1:
            text.append(str(SpM.data[i]) + ",")
        else:
            text.append(str(SpM.data[i]))
    
    text.extend([
        "};",
        "\nint row_ptrB["+str(len(SpM1.indptr))+"]={" 
    ])

    length = len(SpM1.indptr)
    for i in range(length):
        if i < length - 1:
            text.append(str(SpM1.indptr[i]) + ",")
        else:
            text.append(str(SpM1.indptr[i]))

    text.extend([
        "};",
        "",
        "int col_idxB["+str(len(SpM1.indices))+"]={",
    ])

    length = len(SpM1.indices)
    for i in range(length):
        if i < length - 1:
            text.append(str(SpM1.indices[i]) + ",")
        else:
            text.append(str(SpM1.indices[i]))

    text.extend([
        "};",
        "",
        "float dataB["+str(SpM1.count_nonzero())+"]={",
    ])

    length = len(SpM1.data)
    for i in range(length):
        if i < length - 1:
            text.append(str(SpM1.data[i]) + ",")
        else:
            text.append(str(SpM1.data[i]))
  
    text.extend([
        "};"
    ])
    
    for line in text:
        print(line)
    pass
else:
    print("ERROR, try --help command")