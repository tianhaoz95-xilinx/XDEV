import argparse
import json
from jumpssh import SSHSession
from jump_host import JumpHost
from command import exec_dict
from parse import parse_command_input
from helper import get_help_msg
from user_input import get_user_information 
from login import login_workstation

def exec_command(jump_host):
    command_input = input('(¬_¬) ===> ')
    argument_type, argument_payload = parse_command_input(command_input)
    return exec_dict[argument_type](argument_payload, jump_host)

def main():
    parser = argparse.ArgumentParser(description='Remotely turn on/off, power cycle machines.')
    parser.add_argument('--config', help='The config file that stores the jump host group information.')

    args = parser.parse_args()
    if not args.config:
        err_msg = 'Invalid command line arguments \n' + get_help_msg()
        raise RuntimeError(err_msg)

    config = None
    with open(args.config) as config_file:
        config = json.load(config_file)

    jump_host = JumpHost()

    for lab, lab_config in config.items():
        jump_host_config = lab_config['jump_host']
        jump_host_hostname = get_user_information('Enter the hostname of the ' + lab + ' jump host: ', jump_host_config['hostname'])
        jump_host_username = get_user_information('Enter the username of ' + jump_host_hostname + ': ', jump_host_config['username'])
        jump_host_password = get_user_information('Enter the password of ' + jump_host_username + '@' + jump_host_hostname + ': ' , jump_host_config['password'])
        jump_host.config(jump_host_hostname, jump_host_username, jump_host_password)
        machines_config = lab_config['machines']
        for i, machine_config in enumerate(machines_config):
            machine_hostname = get_user_information('Enter the hostname of the ' + str(i) + ' machine: ', machine_config['hostname'])
            machine_username = get_user_information('Enter the username of ' + machine_hostname + ': ', machine_config['username'])
            machine_password = get_user_information('Enter the password of ' + machine_username + '@' + machine_hostname + ': ', machine_config['password'])
            jump_host.add(machine_hostname, machine_username, machine_password)

    while True:
        try:
            stop = exec_command(jump_host)
            if stop:
                break
        except RuntimeError as err:
            print(str(err))
        except:
            print('Unknown error')


if __name__ == '__main__':
    try:
        main()
    except RuntimeError as err:
        print(str(err))