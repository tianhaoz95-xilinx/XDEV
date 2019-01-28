def show_help():
    msg = 'show command will show the lab configurations \n'
    msg += '\t show [target] \n'
    msg += '\t target: all / host / hostname of a lab machine \n'
    return msg

def show_all(jump_host):
    print('show all')

def show(payload, jump_host):
    print('show')
    return False