def get_power_cycle_help():
    msg = 'cycle command is used to power cycle a machine \n'
    msg += '\t usage: cycle [target hostname] [intermediate hostname (optional)] \n'
    msg += '\t target hostname: the hostname of the workstation you want to power cycle \n'
    msg += '\t intermediate hostname: the hostname of the workstation you want to run the ipmi client from. '
    msg += 'if not specified, a random workstation other than the one to be power cycled will be used \n'
    return msg

def generate_power_cycle_command():
    pass

def power_cycle_auto(target, jump_host):
    pass

def power_cycle_with_target(target, intermediate, jump_host):
    print('Fetching the target session from workstation ' + target + ' ...')
    target_workstation_session = jump_host.get_machine(target)['session']
    print('Fetching the intermediate session from workstation ' + intermediate + ' ...')
    intermediate_workstation_session = jump_host.get_machine(intermediate)['session']
    print('Disconnecting from the workstation ' + target + ' ...')

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