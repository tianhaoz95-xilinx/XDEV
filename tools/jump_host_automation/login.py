from user_input import get_user_information

def login_workstation(config, workstation_type, id, lab):
    workstation_hostname = get_user_information('Enter the hostname of the ' + index + ' jump host: ', config['hostname'])
    workstation_username = get_user_information('Enter the username of ' + workstation_hostname + ': ', config['username'])
    workstation_password = get_user_information('Enter the password of ' + workstation_username + '@' + workstation_hostname + ': ' , config['password'])
    if workstation_type == 'jump_host':
        lab.config(workstation_hostname, workstation_username, workstation_password)
    if workstation_type == 'machine':
        lab.add(workstation_hostname, workstation_username, workstation_password)