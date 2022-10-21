import os

import Tools

def handle_input(cmd_in:str) -> int:
    action_to_take = 1 #1 for 'continue', 0 for 'break', this continues by default.

    if cmd_in == 'q':
        action_to_take = 0
  
    elif cmd_in == 'help':
        help_file = open('.cmd_help', 'r')
        lines = help_file.readlines()     
        for line in lines:
            print(line.strip('\n'))

    elif 'gen' in cmd_in.split():
        cmd_in = cmd_in.split()
    #   try:
        Tools.generate(*cmd_in[1:])
    #   except:
    #     print('Run "help" for help')
    elif cmd_in == 'clear':
        action_to_take = 1
        os.system('clear || cls')

    else:
        print('[Error]: Non-existent instuction, run help to view available instructions')
    
    return action_to_take
    pass