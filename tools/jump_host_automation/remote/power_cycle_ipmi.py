import paramiko

def main():
    client = paramiko.SSHClient()
    client.connect('10.23.53.114', username='ADMIN', password='ADMIN')
    stdin, stdout, stderr = client.exec_command('show')
    for line in stdout:
        print('... ' + line.strip('\n'))
    client.close()

if __name__ == '__main__':
    main()