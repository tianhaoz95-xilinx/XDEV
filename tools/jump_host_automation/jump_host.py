from jumpssh import SSHSession

class JumpHost():
    def __init__(self):
        self.machines = {}
        self.host = None
    
    def config(self, hostname, username, password):
        host_session = SSHSession(hostname, username, password=password).open()
        self.host = {
            'hostname': hostname,
            'username': username,
            'password': password,
            'session': host_session
        }

    def add(self, hostname, username, password):
        machine_session = self.host['session'].get_remote_session(hostname, username, password=password)
        self.machines[hostname] = {
            'hostname': hostname,
            'username': username,
            'password': password,
            'session': machine_session
        }

    def get_machine(self, hostname):
        if hostname not in self.machines:
            raise RuntimeError(hostname + ' not found.')
        return self.machines[hostname]

    def get_machine_hostnames(self):
        return self.machines.keys()