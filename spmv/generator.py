import sys

import Input

def main(argc:int, argv:list) -> int:
  while True:
    cmd_in = input("cmd>> ")
    action_to_take = Input.handle_input(cmd_in)

    if action_to_take == 0:
      break
  return 0

#C/C++ entry point
print('Exit code: ', main(len(sys.argv), sys.argv))