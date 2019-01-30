def get_power_cycle_help():
    msg = 'cycle command is used to power cycle a machine \n'
    msg += '\t usage: cycle [target hostname] [intermediate hostname (optional)] \n'
    msg += '\t target hostname: the hostname of the workstation you want to power cycle \n'
    msg += '\t intermediate hostname: the hostname of the workstation you want to run the ipmi client from. '
    msg += 'if not specified, a random workstation other than the one to be power cycled will be used \n'
    return msg

def power_cycle(payload, jump_host):
    if len(payload) == 0:
        err_msg = 'Error: too few arguments \n' + get_power_cycle_help()
        raise RuntimeError(err_msg)
    elif len(payload) > 2:
        err_msg = 'Error: too many arguments \n' + get_power_cycle_help()
        raise RuntimeError(err_msg)
    elif len(payload) == 1:
        pass
    elif len(payload) == 2:
        pass
    else:
        err_msg = 'Error: unknown error \n' + get_power_cycle_help()
        raise RuntimeError(err_msg)
    return False