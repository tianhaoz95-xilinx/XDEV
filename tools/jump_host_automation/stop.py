def stop_machine(hostname, jump_host):
    print('stop machine')

def stop_all(jump_host):
    print('stop all')

def stop_help():
    msg = 'stop is used to stop ssh services \n'
    msg += '\t usage: stop [target] \n'
    msg += '\t target: all / host / hostname of a lab machine \n'
    return msg

def stop(payload, jump_host):
    if len(payload) == 0:
        stop_all(jump_host)
    elif len(payload) == 1:
        if payload[0] == 'all':
            stop_all(jump_host)
        elif payload[0] == 'host':
            stop_all(jump_host)
        else:
            stop_machine(payload[0], jump_host)
    else:
        err_msg = 'Warning: Invalid stop arguments \n' + stop_help()
        raise RuntimeError(err_msg)
    return True