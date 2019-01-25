from jumpssh import SSHSession

def main():
    gateway_session = SSHSession('#', '#', password='#').open()
    remote_session = gateway_session.get_remote_session('#', '#', password='#')
    print(remote_session.get_cmd_output('ls ~/Desktop'))


if __name__ == '__main__':
    main()