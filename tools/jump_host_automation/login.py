from user_input import get_user_information

def get_login_indicator_msg():
    pass

def login_workstation(config, workstation_type, workstation_id, lab):
    workstation_title = 'unknown'
    if workstation_type == 'jump_host':
        workstation_title = 'jump host'
    if workstation_type == 'machine':
        workstation_title = 'lab machine'
    workstation_hostname = get_user_information('Enter the hostname of the ' + index + ' ' + workstation_id + ': ', config['hostname'])
    workstation_username = get_user_information('Enter the username of ' + workstation_hostname + ': ', config['username'])
    workstation_password = get_user_information('Enter the password of ' + workstation_username + '@' + workstation_hostname + ': ' , config['password'])
    if workstation_type == 'jump_host':
        lab.config(workstation_hostname, workstation_username, workstation_password)
    if workstation_type == 'machine':
        lab.add(workstation_hostname, workstation_username, workstation_password)