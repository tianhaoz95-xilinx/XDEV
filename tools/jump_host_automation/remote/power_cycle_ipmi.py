import paramiko

def main():
    client = paramiko.SSHClient()
    client.load_system_host_keys()
    client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    client.connect('10.23.53.114', username='ADMIN', password='ADMIN')
    stdin, stdout, stderr = client.exec_command('show')
    for line in stdout:
        print('... ' + line.strip('\n'))
    client.close()

if __name__ == '__main__':
    main()